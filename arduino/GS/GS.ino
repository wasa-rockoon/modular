#include <EEPROM.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
#include <WebSocketsClient.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <esp_task_wdt.h>
#include <CAN.h>
#include <TinyGPS++.h>
#include <FastCRC.h>
#include <PacketSerial.h>

#include <CANBus.hpp>
#include <Buffer.hpp>
#include <Packet.hpp>
#include "LCD.h"

#define ROCKET 0x01
#define LAUNCHER 0x02
#define GS1 0x06
#define GS2 0x05

#define UNIT GS2

#define NODE 'G'

constexpr char source[] = "GS2";
constexpr char system_id[] = "launch2023";

// constexpr bool ssl = false;
// constexpr char server[] = "Yuukis-MacBook-Pro-M2.local";
// constexpr unsigned port = 8888;
constexpr bool ssl = true;
constexpr char server[] = "telemeter.fujiy.dev";
constexpr unsigned port = 443;

// #define BUS_DEBUG_SERIAL

#define GPS_RX_PIN 5
#define GPS_TX_PIN 18
#define LED_PIN 2
#define SWITCH_PIN_1 12
#define SWITCH_PIN_2 13
#define SWITCH_PIN_3 14

#define CAN_BAUD 1000000
#define GPS_BAUD 9600

#define SEND_COMMAND_FREQ 0.2
#define SEND_LOCATION_FREQ 0.2
#define BLINK_MS 50

#define GPS_SWITCH_FREQ 0.1


#define NUM_AP 8
#define SSID_LEN 16
#define PASSWORD_LEN 16

#define BUS_BUF_SIZE 65536


TaskHandle_t thp[1];

WiFiMulti wifiMulti;
WiFiUDP udp;
NTPClient ntp(udp, "ntp.nict.jp", 0, 60000);

WebSocketsClient webSocket;

bool wifi_connected = false;

unsigned long epoch_s;
unsigned long epoch_s_start_millis = 0;

CANBus bus(NODE);

struct UploadPacket {
  uint32_t ms;
  uint8_t buf[];
};

uint8_t bus_buf[BUS_BUF_SIZE];
SectionBuf<UploadPacket> buffer(bus_buf, BUS_BUF_SIZE);


LCD lcd;
TinyGPSPlus gps;
HardwareSerial gps_serial(2);

enum class SwitchState {
  NotSelected,
  NoLaunch,
  AllowLaunch,
};

SwitchState switch_state = SwitchState::NotSelected;
unsigned long blink_ms;
unsigned long sent_command_ms;
unsigned long sent_location_ms;

int32_t gs_latitude;
int32_t gs_longitude;

Shared<int32_t> launcher_latitude;
Shared<int32_t> launcher_longitude;


void setup() {
  Serial.begin(115200);

  EEPROM.begin(2 + NUM_AP * (SSID_LEN + PASSWORD_LEN));

  readAP();
  
  bus.begin();
  bus.listenAll();
  bus.subscribe(launcher_latitude, 'r', 'A', LAUNCHER);
  bus.subscribe(launcher_longitude, 'r', 'O', LAUNCHER);

  gps_serial.begin(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
  Wire.begin(21, 22);

  // pinMode(21, INPUT_PULLUP);
  // pinMode(22, INPUT_PULLUP);

  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN_1, INPUT_PULLUP);
  pinMode(SWITCH_PIN_2, INPUT_PULLUP);
  pinMode(SWITCH_PIN_3, INPUT_PULLUP);

  digitalWrite(LED_PIN, HIGH);

  lcd.begin();

  delay(1000);

  xTaskCreatePinnedToCore(loop_task, "core0", 8192, NULL, 3, &thp[0], 0);

  // digitalWrite(LED_PIN, LOW);

  lcd.setLine1("GPS Unavailable ");
  lcd.setLine2("----------------");
  lcd.show();
}

void loop() {

  setAP();

  if (WiFi.status() == WL_CONNECTED) {
    if (!wifi_connected) {
      Serial.print("WiFi connected. SSID: ");
      Serial.print(WiFi.SSID());
      Serial.print(", IP: ");
      Serial.println(WiFi.localIP());

      ntp.begin();

      char url[64];
      sprintf(url, "/api/systems/%s/packets?source=%s", system_id, source);

      if (ssl) webSocket.beginSSL(server, port, url);
      else webSocket.begin(server, port, url);

      webSocket.onEvent(webSocketEvent);
      webSocket.setReconnectInterval(5000);

      wifi_connected = true;
    }
  }
  else {
    wifi_connected = false;
  }

  if (wifi_connected) {
    webSocket.loop();
  }

  // NTP

  if (ntp.isTimeSet()) {
    unsigned long new_epoch_s = ntp.getEpochTime();
    if (new_epoch_s != epoch_s) {
      epoch_s_start_millis = millis();
      epoch_s = new_epoch_s;
    }
  }
  uint64_t epoch_ms = (uint64_t)epoch_s * 1000 + (millis() - epoch_s_start_millis);

  // Bus

  bus.update();

  if (CAN.parsePacket() > 0 && CAN.packetExtended()) {
    int dlc = CAN.packetDlc();
    uint8_t data[9];
    for (unsigned i = 0; i < dlc; i++) data[i] = CAN.read();
    CANReceived(CAN.packetId(), data, dlc);
    // Serial.printf("%d\n", dlc);
  }

  Packet packet = bus.receive();

  if (packet.isValid()) {
    if (packet.from() == FROM_LOCAL) packet.from(UNIT);
    sendViaSerial(packet);

    pushToUploadBuffer(packet);

    packet.print();
  }


  if (wifi_connected && ntp.isTimeSet() && webSocket.isConnected() && buffer.begin() != buffer.end()) {
    UploadPacket& p = (*buffer.begin()).value();
    uint64_t packet_epoch_ms = epoch_ms + p.ms - millis();
    uint8_t buf[256];
    *reinterpret_cast<uint64_t*>(buf) = packet_epoch_ms;
    unsigned len = (*buffer.begin()).size() - sizeof(UploadPacket);
    memcpy(buf + 8, p.buf, len);

    if (webSocket.sendBIN(buf, len + 8)) {
      (*buffer.begin()).free();

      digitalWrite(LED_PIN, HIGH);
      blink_ms = millis() + 10;
    }
  }

  // GPS
  while (gps_serial.available()) {
    gps.encode(gps_serial.read());
  }
  if (gps.location.isUpdated()) {
    tm t;
    time_t tim;
    t.tm_year = gps.date.year() - 1900;
    t.tm_mon  = gps.date.month() - 1;
    t.tm_mday = gps.date.day();
    t.tm_hour = gps.time.hour();
    t.tm_min  = gps.time.minute();
    t.tm_sec  = gps.time.second() + 1;
    t.tm_isdst = -1;
    tim = mktime(&t);

    long scale=10000000UL;
    gs_latitude = gps.location.rawLat().deg * scale 
                + gps.location.rawLat().billionths / 100UL;
    if (gps.location.rawLat().negative) gs_latitude = -gs_latitude;
    gs_longitude = gps.location.rawLng().deg * scale 
                 + gps.location.rawLng().billionths / 100UL;
    if (gps.location.rawLng().negative) gs_longitude = -gs_longitude;

    if (millis() > sent_location_ms + 1000 / SEND_LOCATION_FREQ) {
      uint8_t buf[BUF_SIZE(5)];
      Packet packet(buf, sizeof(buf));
      packet.set(TELEMETRY, 'P', UNIT, BROADCAST);
      packet.begin()
        .append('A', gs_latitude)
        .append('O', gs_longitude)
        .append('H', (float)gps.altitude.meters())
        .append('T', (uint32_t)tim)
        .append('S', (uint8_t)gps.satellites.value());

      bus.send(packet);
      sendViaSerial(packet);
      pushToUploadBuffer(packet);

      sent_location_ms = millis();
    }
  }

  // LCD
  char line1[32];
  char line2[32];
  int step = int(millis() * GPS_SWITCH_FREQ) % 1000;
  if (step < 500 && step % 10 == 0) {
    strcpy(line1, "GS   ");
    if (gps.location.age() >= 1000000) {
      snprintf(line2, 7, "N/A   ");
    }
    else {
      snprintf(line2, 7, "%3ds  ", (int)(gps.location.age() / 1000) % 1000);
    }
    printDegree(line1 + 6, gs_longitude);
    printDegree(line2 + 6, gs_latitude);
    lcd.setLine1(line1);
    lcd.setLine2(line2);
    lcd.show();
  }
  else if (step >= 500 && step % 10 == 0) {
    strcpy(line1, "LC   ");
    if (launcher_latitude.age() >= 1000000) {
      snprintf(line2, 7, "N/A   ");
    }
    else {
      snprintf(line2, 7, "%3ds  ",
               (int)(launcher_latitude.age() / 1000) % 1000);
    }
    printDegree(line1 + 6, launcher_longitude.value());
    printDegree(line2 + 6, launcher_latitude.value());
    lcd.setLine1(line1);
    lcd.setLine2(line2);
    lcd.show();
  }
  lcd.update();

  SwitchState switch_state_prev = switch_state;

  // Switch
  if      (!digitalRead(SWITCH_PIN_2))
    switch_state = SwitchState::NotSelected;
  else if (!digitalRead(SWITCH_PIN_1))
    switch_state = SwitchState::NoLaunch;
  else if (!digitalRead(SWITCH_PIN_3))
    switch_state = SwitchState::AllowLaunch;
  else
    switch_state = SwitchState::NotSelected;

  if (switch_state != switch_state_prev) sent_command_ms = 0;

  // Send mode command
  if (millis() > sent_command_ms + 1000 / SEND_COMMAND_FREQ) {
    printSwitchState();

    if (switch_state != SwitchState::NotSelected) {
      uint8_t buf[BUF_SIZE(1)];
      Packet command(buf, sizeof(buf));
      command.set(COMMAND, 'M', UNIT, LAUNCHER);
      command.begin().append('L', switch_state == SwitchState::AllowLaunch ? 1 : 0);

      bus.send(command);
      pushToUploadBuffer(command);
    }
    sent_command_ms = millis();
  }

  // LED
  if (wifi_connected && blink_ms < millis()) digitalWrite(LED_PIN, LOW);

  esp_task_wdt_reset();
}

void loop1() {
  wifiMulti.run(1000);
  
  ntp.update();

  Serial.println(ntp.getFormattedTime());

  // Serial.printf("%d %d\n", bus.buf_.begin_.ptr_, bus.buf_.end_.ptr_);

  delay(1000);

  esp_task_wdt_reset();
}

void loop_task(void *args) {
  for(;;) {
    esp_task_wdt_reset();
    delay(1);
    loop1();
  }
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      Serial.printf("[WSc] Connected to url: %s\n",  payload);
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] get text: %s\n", payload);
      break;
    case WStype_BIN: {
      Serial.printf("[WSc] get binary length: %u\n", length);
      if (length < 20) break;
      // uint64_t packet_epoch_ms = *reinterpret_cast<uint64_t*>(payload);
      // uint8_t* packet_source = payload + 8;
      Packet packet(payload + 16, length - 16, length - 16);
      if (packet.kind() == COMMAND) bus.send(packet);
      break;
    }
		case WStype_ERROR:			
		case WStype_FRAGMENT_TEXT_START:
		case WStype_FRAGMENT_BIN_START:
		case WStype_FRAGMENT:
		case WStype_FRAGMENT_FIN:
			break;
    default: 
      break;
    }
}

void printDegree(char* buf, int32_t deg) {
  long scale=10000000UL;
  int d = deg / scale;
  deg -= d * scale;
  int m = deg * 60 / scale;
  deg -= m * scale;
  int s = deg * 60 / scale;
  deg -= s * scale;
  int ms = deg * 100 / scale;
  sprintf(buf, "%3d'%02d'%02d.%02d", d, m, s, ms);
}

void printSwitchState() {
  switch (switch_state) {
  case SwitchState::NotSelected:
    Serial.println("Switch: Not selected");
    break;
  case SwitchState::NoLaunch:
    Serial.println("Switch: Abort");
    break;
  case SwitchState::AllowLaunch:
    Serial.println("Switch: Launch");
    break;
    }
}

void pushToUploadBuffer(Packet& packet) {
  packet.writeCRC();
  UploadPacket& p = (*buffer.alloc(sizeof(UploadPacket) + packet.len)).value();
  p.ms = millis();
  memcpy(p.buf, packet.buf, packet.len);
}

void sendViaSerial(const Packet& packet_) {
#ifdef BUS_DEBUG_SERIAL
  uint8_t buf[BUF_SIZE(ENTRIES_MAX) + 1];
  Packet packet(buf, sizeof(buf));
  packet_.copyTo(packet);
  FastCRC8 CRC8;
  packet.buf[packet.len] = CRC8.smbus(packet.buf, packet.len);
  uint8_t encoded[BUF_SIZE(ENTRIES_MAX) + 4];
  unsigned encoded_len = COBS::encode(packet.buf, packet.len + 1, encoded);
  encoded[encoded_len] = 0;
  Serial.write(encoded, encoded_len + 1);
#endif
}

void readAP() {
  uint8_t bits = EEPROM.read(1);
  for (unsigned n = 0; n < NUM_AP; n++) {
    if (!(bits & (0b1 << n))) continue;

    char ssid[SSID_LEN];
    char password[PASSWORD_LEN];

    for (unsigned i = 0; i < SSID_LEN; i++) 
      ssid[i] = EEPROM.read(2 + n * (SSID_LEN + PASSWORD_LEN) + i);

    for (unsigned i = 0; i < PASSWORD_LEN; i++) 
      password[i] = EEPROM.read(2 + n * (SSID_LEN + PASSWORD_LEN) + SSID_LEN + i);

    wifiMulti.addAP(ssid, password);
    Serial.printf("AP #%d: %s\n", n, ssid);
  }
}

void setAP() {
  if (Serial.available() > 0) {
    Serial.setTimeout(30000);
    int n = Serial.parseInt();

    Serial.readStringUntil('\n');
    if (n < 0 || NUM_AP <= n) return;

    Serial.printf("AP #%d SSID: ", n);
    Serial.flush();
    char ssid[SSID_LEN];
    Serial.readStringUntil('\n').toCharArray(ssid, SSID_LEN);

    Serial.printf("AP #%d password: ", n);
    Serial.flush();
    char password[PASSWORD_LEN];
    Serial.readStringUntil('\n').toCharArray(password, PASSWORD_LEN);

    for (unsigned i = 0; i < SSID_LEN; i++)
      EEPROM.write(2 + n * (SSID_LEN + PASSWORD_LEN) + i, ssid[i]);

    for (unsigned i = 0; i < PASSWORD_LEN; i++)
      EEPROM.write(2 + n * (SSID_LEN + PASSWORD_LEN) + SSID_LEN + i, password[i]);

    uint8_t bits = EEPROM.read(1);
    EEPROM.write(1, bits | (0b1 << n));

    EEPROM.commit();

    Serial.printf("Set AP %s\n", ssid);

    wifiMulti.addAP(ssid, password);
  }
}

void scanWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } 
  else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
      delay(10);
    }
  }
}

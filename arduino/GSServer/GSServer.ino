#define CONFIG_ASYNC_TCP_USE_WDT 0

#include <TinyGPS++.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <SPIFFS.h>
#include <CAN.h>
#include "command.hpp"
#include "LCD.h"

#define AP_MODE

#define GPS_RX_PIN 5
#define GPS_TX_PIN 18
#define CAN_RX_PIN 32
#define CAN_TX_PIN 33
#define LED_PIN 2
#define SWITCH_PIN_1 12
#define SWITCH_PIN_2 13
#define SWITCH_PIN_3 14

#define CAN_BAUD 125000
static const uint32_t GPSBaud = 9600;

#define RETURN_COMMAND_MAX 100
#define SEND_COMMAND_FREQ 1
#define BLINK_MS 50

#define GPS_SWITCH_FREQ 0.1

const char ssid[] = "Rockoon-GS";
const char pass[] = "rockoon-gs";
const IPAddress ip(192,168,1,1);
const IPAddress subnet(255,255,255,0);
AsyncWebServer server(80);


LCD lcd;
TinyGPSPlus gps;
HardwareSerial ss(2);

CANChannel can_channel;
HexChannel hex_channel;

Command* received_remote_commands;
uint32_t received_remote_count;
uint32_t received_remote_max;

Command* received_local_commands;
uint32_t received_local_count;
uint32_t received_local_max;

enum class SwitchState {
  NotSelected,
  NoLaunch,
  AllowLaunch,
};

SwitchState switch_state = SwitchState::NotSelected;
unsigned long blink_ms;
unsigned long sent_command_ms;

float launcher_lat;
float launcher_lng;
uint32_t launcher_gps_received;


void setup() {
  Serial.begin(115200);
  ss.begin(GPSBaud, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
  Wire.begin(21, 22);

  /* pinMode(21, INPUT_PULLUP); */
  /* pinMode(22, INPUT_PULLUP); */

  pinMode(LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN_1, INPUT_PULLUP);
  pinMode(SWITCH_PIN_2, INPUT_PULLUP);
  pinMode(SWITCH_PIN_3, INPUT_PULLUP);

  digitalWrite(LED_PIN, HIGH);

  i2c_scanner();

  lcd.begin();

  init_datastore();

  delay(1000);

  init_server();

  delay(1000);

  CAN.setPins(CAN_RX_PIN, CAN_TX_PIN);
  CAN.begin(CAN_BAUD * 2);
  /* CAN.onReceive(onCANReceive); */

  digitalWrite(LED_PIN, LOW);

  char line1[] = "GPS Unavailable ";
  char line2[] = "----------------";

  strncpy(lcd.line1, line1, 16);
  strncpy(lcd.line2, line2, 16);
  lcd.show();
}

void loop() {

  int packetSize = CAN.parsePacket();
  if (packetSize > 0) onCANReceive(packetSize);

  // Read GPS
  while(ss.available()){
    char c = ss.read();
    gps.encode(c);
  }

  // Update location
  if (!gps.location.isValid()) {

  }
  else if (gps.location.isUpdated()) {
    struct tm t;
    t.tm_year  = gps.date.year() - 1900;
    t.tm_mon   = gps.date.month() - 1;
    t.tm_mday  = gps.date.day();
    t.tm_hour  = gps.time.hour();
    t.tm_min   = gps.time.minute();
    t.tm_sec   = gps.time.second();
    t.tm_isdst = -1;
    time_t epoch = mktime(&t);

    Command position('P', 0, 0, 4);
    position.entries[0].set('O', (float)gps.location.lng());
    position.entries[1].set('A', (float)gps.location.lat());
    position.entries[2].set('H', (float)gps.altitude.meters());
    position.entries[3].set('U', (uint32_t)(epoch));

    can_channel.tx.push(position);
    sendCAN();

    addReceivedCommand(position);
  }

  int step = int(millis() * GPS_SWITCH_FREQ) % 1000;
  if (step < 500 && step % 10 == 0) {
    strcpy(lcd.line1, "GS     ");
    snprintf(lcd.line2, 7, "%3.1fs ",
             min((gps.location.age() / 1000.0), 999.9));
    snprintf(lcd.line1 + 6, 11, "%3.7f", gps.location.lng());
    snprintf(lcd.line2 + 6, 10, "%3.7f", gps.location.lat());
    lcd.show();
  }
  else if (step >= 500 && step % 10 == 0) {
    strcpy(lcd.line1, "L      ");
    snprintf(lcd.line2, 7, "%3.1fs ",
             min((millis() - launcher_gps_received) / 1000.0, 999.9));
    snprintf(lcd.line1 + 6, 11, "%3.7f", launcher_lng);
    snprintf(lcd.line2 + 6, 11, "%3.7f", launcher_lat);
    lcd.show();
  }

  lcd.update();

  /* server.handleClient(); */

  /* Serial.print("data: "); */
  /* Serial.println(received_count); */

  /* delay(50); */

  /* addDummyCANData(); */

  if (millis() - blink_ms >= BLINK_MS) {
    digitalWrite(LED_PIN, LOW);
  }

  if      (!digitalRead(SWITCH_PIN_2)) switch_state = SwitchState::NotSelected;
  else if (!digitalRead(SWITCH_PIN_1)) switch_state = SwitchState::NoLaunch;
  else if (!digitalRead(SWITCH_PIN_3)) switch_state = SwitchState::AllowLaunch;
  else                                 switch_state = SwitchState::NotSelected;

  // Send mode command
  if (millis() > sent_command_ms + 1000 / SEND_COMMAND_FREQ) {
    printSwitchState();

    if (switch_state != SwitchState::NotSelected) {
      Command command('m', 'L', 0, 1);
      uint8_t type = switch_state == SwitchState::AllowLaunch ? 'A' : 'N';
      command.entries[0].set(type);

      can_channel.tx.push(command);
      sendCAN();
      addReceivedCommand(command);
    }
    sent_command_ms = millis();
  }
}


void onCANReceive(int packetSize) {
  if (CAN.packetRtr()) return;

  uint8_t id = CAN.packetId();
  uint8_t len = CAN.packetDlc();

  /* Serial.print("CAN R  "); */
  /* Serial.print(id); */
  /* Serial.print(" "); */
  /* Serial.print(len); */
  /* Serial.print(": "); */

  uint8_t data[8];

  for (int n = 0; n < len; n++) {
    data[n] = CAN.read();
    /* Serial.print(data[n], HEX); */
  }

  /* Serial.println(); */

  if (can_channel.receive(id, data, len)) {
    addReceivedCommand(can_channel.rx);

    if (can_channel.rx.id == 'n') {
      union Payload p;
      if (can_channel.rx.get('A', 0, p)) {
        launcher_lat = p.float_;
        launcher_gps_received = millis();
      }
      if (can_channel.rx.get('O', 0, p)) {
        launcher_lng = p.float_;
        launcher_gps_received = millis();
      }
    }
  }
}


void sendCAN() {
	while (true) {
		if (can_channel.isReceiving()) return;

		uint16_t std_id;
		uint8_t len;
    uint8_t data[8];

		uint8_t remains = can_channel.send(std_id, data, len);

		if (len == 0) return;

    CAN.beginPacket(std_id);
    for (int n = 0; n < len; n++) CAN.write(data[n]);
    CAN.endPacket();

		if (remains == 0) break;
	}
}

void addReceivedCommand(const Command& c) {
  Command command = c;
  command.entries[command.size].set('t', (uint32_t)(millis()));
  command.size += 1;

  if (command.from == 0) {
    received_local_commands[received_local_count % received_local_max] =
      command;
    received_local_count++;

    Serial.print("local: ");
    Serial.println(received_local_count);
  }
  else {
    received_remote_commands[received_remote_count % received_remote_max] =
      command;
    received_remote_count++;

    Serial.print("remote: ");
    Serial.println(received_remote_count);
  }

  blink();
}


void handleDataRequest(AsyncWebServerRequest *request, bool local = false) {
  uint32_t received_count =
    local ? received_local_count : received_remote_count;
  uint32_t received_max =
    local ? received_local_max : received_remote_max;

  AsyncWebParameter *p = request->getParam("index");
  int request_index;

  if (p == NULL) request_index = 0;
  else request_index = p->value().toInt();

  uint32_t index_from = request_index;
  if (request_index < 0) index_from = 0;
  else if (request_index > received_count)
    index_from = received_count;

  String response;

  int index = index_from;

  for (int n = 0; n < RETURN_COMMAND_MAX; n++) {
    if (index == received_count) break;

    hex_channel.tx.push
      ((local ? received_local_commands : received_remote_commands)
       [index % received_max]);

    uint8_t buf[14];
    uint8_t len;
    while (true) {
      int remains = hex_channel.send(buf, len);
      response += String((char*)buf);
      if (remains <= 0) break;
    }

    index++;
    if (index == received_max) index = 0;
  }

  log_d("requested %s data: %d, return %d to %d, %d chars",
        local ? "local" : "remote", request_index, index_from, index,
        response.length());

  request->send(200, "text/plain", String(index) + '\n' + response);
}



bool init_server() {
  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    return false;
  }

  WiFi.softAP(ssid, pass);
  delay(100);
  WiFi.softAPConfig(ip, ip, subnet);
  IPAddress myIP = WiFi.softAPIP();

  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.on("/remote", HTTP_GET, [](AsyncWebServerRequest *request) {
      handleDataRequest(request, false);
    });
  server.on("/local", HTTP_GET, [](AsyncWebServerRequest *request) {
      handleDataRequest(request, true);
    });
  server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
  server.onNotFound([](AsyncWebServerRequest *request) {
      request->send(404, "text/plain", "File Not Found");
    });


  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");

  /* server.enableCORS(); */

  server.begin();


  MDNS.begin("gs");
  MDNS.addService("http", "tcp", 80);

  Serial.println("Server started");

  return true;
}




bool init_datastore() {
  psramInit();
  log_d("Total heap: %d", ESP.getHeapSize());
  log_d("Free heap: %d", ESP.getFreeHeap());
  log_d("Total PSRAM: %d", ESP.getPsramSize());
  log_d("Free PSRAM: %d", ESP.getFreePsram());

  int tlm_mem_size = ESP.getFreePsram() / 3;
  int gs_mem_size = ESP.getFreePsram() / 3;

  received_remote_commands = (Command*)ps_malloc(tlm_mem_size);
  received_remote_max = tlm_mem_size / sizeof(Command);
  received_remote_count = 0;


  received_local_commands = (Command*)ps_malloc(gs_mem_size);
  received_local_max = gs_mem_size / sizeof(Command);
  received_local_count = 0;

  if (received_remote_commands == NULL || received_local_commands == NULL) {
    Serial.println("Failed to alloc memory");
    return false;
  }


  Serial.print("Allocated ");
  Serial.print(received_local_max);
  Serial.print(" + ");
  Serial.println(received_local_max);

  return true;
}



void addDummyCANData() {
  Command command('B', 0, 0, 5);
  command.entries[0].set('P', (float)(9.0 + random(-50, 50) / 100.0));
  command.entries[1].set('C', (float)(5.0 + random(-50, 50) / 100.0));
  command.entries[2].set('D', (float)(3.3 + random(-50, 50) / 100.0));
  command.entries[3].set('c', (float)(random(0, 100) / 100.0));
  command.entries[4].set('d', (float)(random(0, 100) / 100.0));

  addReceivedCommand(command);
}

void blink() {
  blink_ms = millis();
  digitalWrite(LED_PIN, HIGH);
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

void i2c_scanner() {
    byte error, address;
    int nDevices;

    Serial.println("I2C Scanner");
    Serial.println("Scanning...");

    nDevices = 0;
    for(address = 1; address < 127; address++ )
        {
            // The i2c_scanner uses the return value of
            // the Write.endTransmisstion to see if
            // a device did acknowledge to the address.
            Wire.beginTransmission(address);
            error = Wire.endTransmission();

            if (error == 0)
                {
                    Serial.print("I2C device found at address 0x");
                    if (address<16)
                        Serial.print("0");
                    Serial.print(address,HEX);
                    Serial.println("  !");

                    nDevices++;
                }
            else if (error==4)
                {
                    Serial.print("Unknown error at address 0x");
                    if (address<16)
                        Serial.print("0");
                    Serial.println(address,HEX);
                }
            else {
                //      Serial.println(error);
            }
        }
    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("done\n");
}


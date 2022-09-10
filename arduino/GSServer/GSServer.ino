#include <TinyGPS++.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WebServer.h>
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

#define CAN_BAUD 125000
static const uint32_t GPSBaud = 9600;

#define RETURN_COMMAND_MAX 1000

#define BLINK_MS 50

const char ssid[] = "Rockoon-GS";
const char pass[] = "rockoon-gs";
const IPAddress ip(192,168,1,1);
const IPAddress subnet(255,255,255,0);
WebServer server(80);

CANChannel can_channel;
HexChannel hex_channel;
StaticJsonDocument<512> json;

Command* received_tlm_commands;
uint32_t received_tlm_count;
uint32_t received_tlm_max;

Command* received_gs_commands;
uint32_t received_gs_count;
uint32_t received_gs_max;


LCD lcd;
TinyGPSPlus gps;
HardwareSerial ss(2);

unsigned long blink_ms;


void setup() {
  Serial.begin(115200);
  ss.begin(GPSBaud, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
  Wire.begin(21, 22);

  /* pinMode(21, INPUT_PULLUP); */
  /* pinMode(22, INPUT_PULLUP); */

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  i2c_scanner();

  lcd.begin();

  init_datastore();

  delay(1000);

  init_server();

  delay(1000);

  CAN.setPins(CAN_RX_PIN, CAN_TX_PIN);
  CAN.begin(CAN_BAUD * 2);
  CAN.onReceive(onCANReceive);

  digitalWrite(LED_PIN, LOW);

  char line1[] = "GPS Unavailable ";
  char line2[] = "----------------";

  strncpy(lcd.line1, line1, 16);
  strncpy(lcd.line2, line2, 16);
  lcd.show();
}

void loop() {


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

    Command position('P', 0, 0, 5);
    position.entries[0].set('O', (float)gps.location.lng());
    position.entries[1].set('A', (float)gps.location.lat());
    position.entries[2].set('H', (float)gps.altitude.meters());
    position.entries[3].set('T', (uint32_t)(epoch));
    position.entries[4].set('t', (uint32_t)(millis()));

    can_channel.tx.push(position);
    sendCAN();

    addReceivedGSCommand(position);

    strcpy(lcd.line1, "G Lng=");
    strcpy(lcd.line2, "G Lat= ");
    snprintf(lcd.line1 + 6, 11, "%3.7f", gps.location.lng());
    snprintf(lcd.line2 + 7, 10, "%2.7f", gps.location.lat());
    lcd.show();
  }

  lcd.update();

  server.handleClient();

  /* Serial.print("data: "); */
  /* Serial.println(received_count); */

  /* delay(50); */

  /* addDummyCANData(); */

  if (millis() - blink_ms >= BLINK_MS) {
    digitalWrite(LED_PIN, LOW);
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
  }

  if (can_channel.receive(id, data, len)) {
    can_channel.rx.entries[can_channel.rx.size].set('t', (uint32_t)(millis()));
    can_channel.rx.size += 1;
    addReceivedTlmCommand(can_channel.rx);
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

void addReceivedTlmCommand(Command &command) {
  Serial.print("tlm: ");
  Serial.println(received_tlm_count);
  blink();

  received_tlm_commands[received_tlm_count % received_tlm_max] = command;
  received_tlm_count++;
}
void addReceivedGSCommand(Command &command) {
  Serial.print("tlm: ");
  Serial.println(received_gs_count);
  blink();

  received_gs_commands[received_gs_count % received_gs_max] = command;
  received_gs_count++;
}

void handleDataRequest(bool gs = false) {
  int request_index = 0;

  for (int i = 0; i < server.args(); i++) {
    if (server.argName(i) == "index") {
      request_index = server.arg(i).toInt();
    }
  }

  if (request_index < 0) request_index = 0;

  int index_from = request_index % (gs ? received_gs_max : received_tlm_max);

  String response;

  int index = index_from;

  for (int n = 0; n < RETURN_COMMAND_MAX; n++) {
    if (index == (gs ? received_gs_count : received_tlm_count)) break;

    hex_channel.tx.push
      ((gs ? received_gs_commands : received_tlm_commands)[index]);

    uint8_t buf[12];
    uint8_t len;
    while (true) {
      int remains = hex_channel.send(buf, len);
      response += String((char*)buf);
      if (remains <= 0) break;
    }

    index++;
    if (index == (gs ? received_gs_max : received_tlm_max)) index = 0;
  }

  log_d("requested tlm data: %d, return %d to %d",
        request_index, index_from, index);

  server.send(200, "text/plain", response);
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

  server.on("/tlm", HTTP_GET, []() {
      handleDataRequest(false);
    });
  server.on("/gs", HTTP_GET, []() {
      handleDataRequest(true);
    });
  server.on("/", HTTP_GET, [](){
      File file = SPIFFS.open("/index.html", "r");
      if (!file || !file.available()) return false;
      server.streamFile(file, "text/html");
      file.close();
    });
  server.serveStatic("/", SPIFFS, "/");
  server.onNotFound([]() {
      log_d("404");
      server.send(404, "text/plain", "File Not Found");
    });


  /* DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*"); */
  /* DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*"); */

  server.enableCORS();

  server.begin();


  MDNS.begin("gs");
  MDNS.addService("http", "tcp", 80);

  Serial.println("Server started");

  return true;
}

bool handleFileRead(String path, String contentType) {
  log_d("read: %s",path);

  File file = SPIFFS.open(path, "r");
  log_d("opened");
  if (file.isDirectory()){
    file.close();
    log_d("Not directory: %s", path);
    return false;
  }

  server.streamFile(file, contentType);
  file.close();
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

  received_tlm_commands = (Command*)ps_malloc(tlm_mem_size);
  received_tlm_max = tlm_mem_size / sizeof(Command);
  received_tlm_count = 0;


  received_gs_commands = (Command*)ps_malloc(gs_mem_size);
  received_gs_max = gs_mem_size / sizeof(Command);
  received_gs_count = 0;

  if (received_tlm_commands == NULL || received_gs_commands == NULL) {
    Serial.println("Failed to alloc memory");
    return false;
  }


  Serial.print("Allocated ");
  Serial.print(received_gs_max);
  Serial.print(" + ");
  Serial.println(received_gs_max);

  return true;
}



void addDummyCANData() {
  Command command('B', 0, 'G', 5);
  command.entries[0].set('P', (float)(9.0 + random(-50, 50) / 100.0));
  command.entries[1].set('C', (float)(5.0 + random(-50, 50) / 100.0));
  command.entries[2].set('D', (float)(3.3 + random(-50, 50) / 100.0));
  command.entries[3].set('c', (float)(random(0, 100) / 100.0));
  command.entries[4].set('d', (float)(random(0, 100) / 100.0));

  addReceivedGSCommand(command);
}

void blink() {
  blink_ms = millis();
  digitalWrite(LED_PIN, HIGH);
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


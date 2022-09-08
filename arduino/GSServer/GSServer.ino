#include <TinyGPS++.h>
#include <Wire.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>
#include <ESPAsyncWebServer.h>
#include <AsyncJson.h>
#include <SPIFFS.h>
#include <CAN.h>
#include "command.hpp"

#define AP_MODE

#define GPS_RX_PIN 5
#define GPS_TX_PIN 18
#define CAN_RX_PIN 32
#define CAN_TX_PIN 33

#define CAN_BAUD 125000
static const uint32_t GPSBaud = 9600;

#define RETURN_COMMAND_MAX 10

const char ssid[] = "Rockoon-GS";
const char pass[] = "rockoon-gs";
const IPAddress ip(192,168,1,1);
const IPAddress subnet(255,255,255,0);
AsyncWebServer server(80);

CANChannel can_channel;
HexChannel hex_channel;
StaticJsonDocument<512> json;

Command* received_commands;
uint32_t received_count;
uint32_t received_count_max;

#define LCD_ADRS 0x3E
char bLng[] ="Lng=";
char bLat[] ="Lat= ";
char aLng[12];
char aLat[11];
TinyGPSPlus gps;
HardwareSerial ss(2);

void setup() {
  Serial.begin(115200);
  ss.begin(GPSBaud, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);

  pinMode(21, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  Wire.begin(21, 22);
  /* Wire.setClock(10000); */

  i2c_scanner();

  init_datastore();
  init_server();
  init_LCD();

  delay(1000);

  CAN.setPins(CAN_RX_PIN, CAN_TX_PIN);
  CAN.begin(CAN_BAUD * 2);
  CAN.onReceive(onCANReceive);
}

void loop() {


  // Read GPS
  while(ss.available()){
    char c = ss.read();
    gps.encode(c);
  }

  // Update location
  if (!gps.location.isValid()) {
    char msg[] = "GPS Unavailable";
    writeCommand(0x80);
    for(int i = 0; i < sizeof(msg); i++) {
      writeData(msg[i]);
    }
    delay(10);
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
    position.entries[3].set('T', (uint32_t)(epoch));

    can_channel.tx.push(position);
    sendCAN();

    addReceivedCommand(position);

    snprintf(aLng,12,"%.8f",gps.location.lng());
    snprintf(aLat,11,"%.8f",gps.location.lat());

    writeCommand(0x80);
    for(int i = 0; i < 4; i++) {
      writeData(bLng[i]);
    }
    for(int i = 0; i < 12; i++) {
      writeData(aLng[i]);
    }
    writeCommand(0x40+0x80); // 2LINE TOP
    for(int i = 0; i < 5; i++) {
      writeData(bLat[i]);
    }
    for(int i = 0; i < 11; i++) {
      writeData(aLat[i]);
    }
  }


  Serial.print("data: ");
  Serial.println(received_count);

  delay(50);

  /* addDummyCANData(); */
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
    addReceivedCommand(can_channel.rx);
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

void addReceivedCommand(Command &command) {
  /* Serial.print("data: "); */
  /* Serial.println(received_count); */

  received_commands[received_count] = command;
  received_count++;
  if (received_count >= received_count_max) {
    received_count = 0;
  }
}

void request_data(AsyncWebServerRequest *request) {
  AsyncWebParameter *p = request->getParam("index");
  int index;

  if (p == NULL) index = 0;
  else index = p->value().toInt();

  if (index < 0) index = max(0, (int)received_count - 1);
  else if (index >= received_count_max) index = 0;

  String response;

  for (int n = 0; n < RETURN_COMMAND_MAX; n++) {
    if (index == received_count_max) {
      index = 0;
      break;
    }
    if (index == received_count) break;

    hex_channel.tx.push(received_commands[index]);

    uint8_t buf[12];
    uint8_t len;
    while (true) {
      int remains = hex_channel.send(buf, len);
      response += String((char*)buf);
      if (remains <= 0) break;
    }
    index++;
  }

  request->send(200, "text/plain", response);
}

bool init_datastore() {
  psramInit();
  log_d("Total heap: %d", ESP.getHeapSize());
  log_d("Free heap: %d", ESP.getFreeHeap());
  log_d("Total PSRAM: %d", ESP.getPsramSize());
  log_d("Free PSRAM: %d", ESP.getFreePsram());

  int mem_size = ESP.getFreePsram() / 2;

  received_commands = (Command*)ps_malloc(mem_size);
  received_count_max = mem_size / sizeof(Command);
  received_count = 0;

  if (received_commands == NULL) {
    Serial.println("Failed to alloc memory");
    return false;
  }

  Serial.print("Allocated ");
  Serial.println(received_count_max);

  /* int entries_average = 8; */
  /* int entries_bytes = sizeof(Entry); */
  /* int command_bytes = entries_bytes * (entries_average + 1); */
  /* int index_item_bytes = sizeof(uint32_t); */

  /* int psram_size = ESP.getFreePsram(); */

  /* uint8_t size = psram_size / (command_bytes + index_item_bytes); */

  /* store.init((uint32_t* )ps_malloc(index_item_bytes * size), */
  /*            size, */
  /*            (Entry* )ps_malloc(command_bytes * size), */
  /*            size * entries_average); */

  return true;
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


  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/index.html");
    });
  server.on("/pure-min.css", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/pure-min.css", "text/css");
    });
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/style.css", "text/css");
    });
  server.on("/jquery.js", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/jquery.js", "text/javascript");
    });
  server.on("/main.js", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(SPIFFS, "/main.js", "text/javascript");
    });
  server.on("/data", HTTP_GET, request_data);

  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");
  server.begin();

  MDNS.begin("gs");
  MDNS.addService("http", "tcp", 80);

  Serial.println("Server started");

  return true;
}

void writeData(byte t_data) {
  Wire.beginTransmission(LCD_ADRS);
  Wire.write(0x40);//送信する１バイトのデータ
  Wire.write(t_data);//文字列の送信
  Wire.endTransmission();
  delay(1);
}

void writeCommand(byte t_command) {
  Wire.beginTransmission(LCD_ADRS);
  Wire.write(0x00);
  Wire.write(t_command);
  Wire.endTransmission();
  delay(10);
}

void init_LCD() {
  delay(20);
  writeCommand(0x38);
  delay(20);
  writeCommand(0x39);
  delay(20);
  writeCommand(0x14);
  delay(20);
  writeCommand(0x73);
  delay(20);
  writeCommand(0x56);
  delay(20);
  writeCommand(0x6C);
  delay(20);
  writeCommand(0x38);
  delay(20);
  writeCommand(0x01);
  delay(20);
  writeCommand(0x0C);
  delay(20);
}

void addDummyCANData() {
  Command command('B', 0, 'G', 5);
  command.entries[0].set('P', (float)(9.0 + random(-50, 50) / 100.0));
  command.entries[1].set('C', (float)(5.0 + random(-50, 50) / 100.0));
  command.entries[2].set('D', (float)(3.3 + random(-50, 50) / 100.0));
  command.entries[3].set('c', (float)(random(0, 100) / 100.0));
  command.entries[4].set('d', (float)(random(0, 100) / 100.0));

  received_commands[received_count] = command;
  received_count++;
  if (received_count >= received_count_max) {
    received_count = 0;
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


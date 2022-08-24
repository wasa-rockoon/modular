#include <TinyGPS++.h>
#include <Wire.h>
#define LCD_ADRS 0x3E
char bLng[] ="Lng=";
char bLat[] ="Lat= ";
char aLng[12];
char aLat[11];
static const uint32_t GPSBaud = 9600;
TinyGPSPlus gps;
HardwareSerial ss(2);
#define GPS_RX_PIN 5
#define GPS_TX_PIN 18

void setup() {
  Serial.begin(115200);
  ss.begin(GPSBaud, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
  Wire.begin();
  init_LCD();
}

void loop() {
  while(ss.available()){
    char c = ss.read();
    gps.encode(c);
    if(gps.location.isUpdated()){
      snprintf(aLng,12,"%.8f",gps.location.lng());
      snprintf(aLat,11,"%.8f",gps.location.lat());

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
  }
  delay(1000);
    init_LCD();
}

void writeData(byte t_data)
{
 Wire.beginTransmission(LCD_ADRS);
 Wire.write(0x40);//送信する１バイトのデータ
 Wire.write(t_data);//文字列の送信
 Wire.endTransmission();
delay(1);
}

void writeCommand(byte t_command)
{
 Wire.beginTransmission(LCD_ADRS);
 Wire.write(0x00);
 Wire.write(t_command);
 Wire.endTransmission();
 delay(0);
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
writeCommand(0x52);
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
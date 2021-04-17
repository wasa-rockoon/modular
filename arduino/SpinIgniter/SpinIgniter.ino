#define IGNITER 9
#define LED A5
#define SENSOR 4

int count;
int clk;

void setup() {
  // put your setup code here, to run once:
  pinMode(IGNITER, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(SENSOR, INPUT);

  digitalWrite(IGNITER, LOW);

  count = 0;
  clk = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(SENSOR) == HIGH) {
    count = 500;
  }
  else if (count > 0) {
    count--;
  }

  if (count > 0) {
    digitalWrite(IGNITER, HIGH);
  }
  else {
    digitalWrite(IGNITER, LOW);
  }

  if (clk > 0){
    clk --;
  }
  else {
    clk = 200;
    digitalWrite(LED, !digitalRead(LED));
  }
  
  delay(1);

}

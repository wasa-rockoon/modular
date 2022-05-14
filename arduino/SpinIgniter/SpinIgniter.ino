#define IGNITER 9
#define LED A5
#define SENSOR 4

#define SERIAL_SPEED  115200

#define IR_FREQ 1000
#define LOOP_PERIOD_US 20
#define ARM_DUTY 250
#define FIRE_DUTY 750
#define DUTY_EPS 50
#define SUSTAIN 500
#define RECEIVE_N 5

#define LAUNCH_COUNT 5000
#define LOOP_PERIOD 1

enum State {
  DISARM,
  ARM,
  FIRE,
};

unsigned long last_received;
State state;

int count;
int clk;

int countdown;

void setup() {
  // put your setup code here, to run once:
  pinMode(IGNITER, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(SENSOR, INPUT);

  digitalWrite(IGNITER, LOW);

  Serial.begin(SERIAL_SPEED);
  Serial.println("Start");

  state = DISARM;
  last_received = 0;

  count = 0;
  clk = 0;

  countdown = LAUNCH_COUNT;
}

State receive() {

  /* while (digitalRead(SENSOR) == HIGH) */

  while(digitalRead(SENSOR) == LOW) delayMicroseconds(LOOP_PERIOD_US);
  unsigned on_count = 0;
  while (digitalRead(SENSOR) == HIGH) {
    delayMicroseconds(LOOP_PERIOD_US);
    on_count++;
    if (on_count * LOOP_PERIOD_US > SUSTAIN) break;
  }
  unsigned off_count = 0;
  while(digitalRead(SENSOR) == LOW) {
    delayMicroseconds(LOOP_PERIOD_US);
    off_count++;
    if (off_count * LOOP_PERIOD_US > SUSTAIN) break;
  }
  if (abs(on_count * LOOP_PERIOD_US - ARM_DUTY) <= DUTY_EPS &&
      abs(off_count * LOOP_PERIOD_US - (1000 - ARM_DUTY)) <= DUTY_EPS)
    return ARM;
  if (abs(on_count * LOOP_PERIOD_US - FIRE_DUTY) <= DUTY_EPS &&
      abs(off_count * LOOP_PERIOD_US - (1000 - FIRE_DUTY)) <= DUTY_EPS)
    return FIRE;
  return DISARM;
}

State receive_N(unsigned N) {
  State s = DISARM;
  for (unsigned n = 0; n < N; n++) {
    State sn = receive();
    if (s == DISARM) s = sn;
    else if (sn == ARM) s = ARM;
    else if (s != ARM && sn == FIRE) s = FIRE;
  }
  return s;
}

void loop() {
  // put your main code here, to run repeatedly:a

  /* State sn = receive_N(RECEIVE_N); */
  /* State sn = DISARM; */

  /* if (digitalRead(SENSOR) == HIGH) digitalWrite(LED, HIGH); */
  /* else digitalWrite(LED, LOW); */

  /* if (sn != DISARM) { */
  /*   state = sn; */
  /*   last_received = millis(); */
  /* } */
  /* else if (millis() - last_received > SUSTAIN) state = DISARM; */

  /* switch (sn) { */
  /* case DISARM: */
  /*   digitalWrite(LED, HIGH); */
  /*   digitalWrite(IGNITER, LOW); */
  /*   break; */
  /* case ARM: */
  /*   digitalWrite(LED, LOW); */
  /*   digitalWrite(IGNITER, LOW); */
  /*   break; */
  /* case FIRE: */
  /*   digitalWrite(LED, LOW); */
  /*   digitalWrite(IGNITER, HIGH); */
  /*   break; */
  /* } */


  if (clk > 0){
    clk --;
  }
  else {
    clk = 200;
    digitalWrite(LED, !digitalRead(LED));
  }
 

  if (digitalRead(SENSOR) == HIGH) {
    countdown -= LOOP_PERIOD;
    count = SUSTAIN;
  }
  else if (count > 0) {
    countdown -= LOOP_PERIOD;
    count -= LOOP_PERIOD;
  }

  if (countdown < 0) {
    digitalWrite(IGNITER, HIGH);
    digitalWrite(LED, HIGH);
  }
  if (count <= 0) {
    countdown = LAUNCH_COUNT;
    digitalWrite(IGNITER, LOW);
  }

  /* if (count > 0) { */
  /*   digitalWrite(IGNITER, HIGH); */
  /* } */
  /* else { */
  /*   digitalWrite(IGNITER, LOW); */
  /* } */

 
  delay(LOOP_PERIOD);
}

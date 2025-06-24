volatile long leftCounter = 0;
volatile long rightCounter = 0;
short l = 16, r = 5;  //sm
void setup() {
  pinMode(11, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  attachInterrupt(0, left, FALLING);
  attachInterrupt(1, right, FALLING);
  pinMode(4, INPUT);
  pinMode(6, INPUT);
  Serial.begin(9600);
}
void move(int spL, int spR) {
  spR <= 0 ? digitalWrite(9, 0) : analogWrite(9, abs(spR));
  spR <= 0 ? analogWrite(10, abs(spR)) : digitalWrite(10, 0);
  spL >= 0 ? digitalWrite(11, 0) : analogWrite(11, abs(spL));
  spL >= 0 ? analogWrite(5, abs(spL)) : digitalWrite(5, 0);
}
void left() {
  if (digitalRead(4)) {
    leftCounter++;
  } else {
    leftCounter--;
  }
}
void right() {
  if (!digitalRead(6)) {
    rightCounter++;
  } else {
    rightCounter--;
  }
}
void stop() {
  long ideal = leftCounter, t = millis();
  while (millis() - t < 500) {
    long er = ideal - leftCounter;
    move(er * 100.0, er * 100.0);
  }
  move(0, 0);
}
void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    if (data == "up") {
      move(255, 255);
    } else if (data == "down") {
      move(-255, -255);
    } else if (data == "right") {
      move(200, -200);
    } else if (data == "left") {
      move(-200, 200);
    } else {
      move(0, 0);
    }
  }

  // while(1){}
}

volatile long leftCounter = 0;
volatile long rightCounter = 0;
short l = 16, r = 5;  //sm
// 600 ticks - 90 degrees => 3 degres = 20 ticks
// 660 - 31,4 => 1 - 21
void setup() {
  pinMode(11, OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  attachInterrupt(0, left, FALLING);
  attachInterrupt(1, right, FALLING);
  pinMode(4, INPUT);
  pinMode(6, INPUT);
  Serial.begin(9600);
}
int get_sign(int n) {
  return n > 0 ? 1 : -1;
}
int string_to_int(String line) {
  int size = get_size(line);
  int n = 0;
  for (auto i = 0; i < size; i++) {
    if (line[i] != '-') {
      n += (int(line[i]) - 48) * pow(10, size - i - 1);
    }
  }
  n *= line[0] == '-' ? -1 : 1;
  return n;
}
short get_size(String str) {
  short i = 0;
  for (auto k : str) {
    i++;
  }
  return i;
}
void zero() {
  rightCounter = 0;
  leftCounter = 0;
}
void turn_right_test() {
  zero();
  while ((abs(rightCounter) + abs(leftCounter)) / 2 <= 600) {
    move(255, -255);
  }
  move(0, 0);
}
void turn_right_deg(int deg) {
  zero();
  while ((abs(rightCounter) + abs(leftCounter)) / 2 <= abs(deg) / 3 * 20) {
    move(200 * get_sign(deg), -200 * get_sign(deg));
  }
  stop();
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
void move(int spL, int spR) {
  spR <= 0 ? digitalWrite(9, 0) : analogWrite(9, abs(spR));
  spR <= 0 ? analogWrite(10, abs(spR)) : digitalWrite(10, 0);
  spL >= 0 ? digitalWrite(11, 0) : analogWrite(11, abs(spL));
  spL >= 0 ? analogWrite(5, abs(spL)) : digitalWrite(5, 0);
}

void moveEnc(int sp) {
  long currLeft = leftCounter;
  long currRight = rightCounter;
  float k = 20;
  move((leftCounter - currLeft) * k + sp, sp - (leftCounter - currLeft) * k);
}
void move_sm_test() {
  zero();
  while ((abs(rightCounter) + abs(leftCounter)) / 2 <= 660) {
    move(150, 150);
  }
  stop();
}
void move_sm(int sm) {
  zero();
  while ((abs(rightCounter) + abs(leftCounter)) / 2 <= sm * 21) {
    move(255, 255);
  }
  stop();
}
void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
      
    digitalWrite(7,0);
    String movement = "", deg = "";
    bool flag = 1;
    for (auto i = 0; i < get_size(data); i++) {
      data[i] == ' ' ? flag = 0 : flag ? movement += data[i]
                                        : deg += data[i];
    }
    turn_right_deg(string_to_int(deg));
    move_sm(string_to_int(movement));
    Serial.print(string_to_int(movement));
    Serial.print(' ');
    Serial.println(string_to_int(deg));
      
    // while(1){}
  }
  else{
    
  }

    
}

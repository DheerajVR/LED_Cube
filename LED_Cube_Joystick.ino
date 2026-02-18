#include "Button.h"

int dataPin = 2;
int clockPin = 3;
int latchPin = 4;
int tPins[] = { 5, 6, 7, 8 };

int xPin = A0;
int yPin = A1;

Button Up(10);
Button Down(11);

int end[3] = { 0, 0, 0 };
int tail[3] = { 0, 0, 0 };
int body[3] = { 0, 0, 0 };
int head[3] = { 0, 0, 0 };

uint16_t cubeData[4] = { 0x0, 0x0, 0x0, 0x0 };
uint16_t cubeVal[4] = { 0x0, 0x0, 0x0, 0x0 };

void writeData(uint16_t val) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, (val & 0xFF));
  shiftOut(dataPin, clockPin, LSBFIRST, (val >> 8));
  digitalWrite(latchPin, HIGH);
}

void writeLayer(int tPin, uint16_t val) {
  writeData(val);
  digitalWrite(tPin, HIGH);
  delayMicroseconds(500);
  digitalWrite(tPin, LOW);
}

uint16_t x_y_val(int x, int y) {
  uint16_t val = 0x1;
  val = val << x;
  for (int i = 0; i < y; i++) { val = val << 4; }
  return val;
}

void cube_state(uint16_t arr[4], int point[3]) {  //uint16_t arr[4] = { 0x0, 0x0, 0x0, 0x0 };
  uint16_t val = x_y_val(point[0], point[1]);
  arr[point[2]] = val;
}

void sync4(uint16_t arr1[4], uint16_t arr2[4]) {
  for (int i = 0; i < 4; i++) {
    arr1[i] = arr1[i] | arr2[i];
  }
}

void desync4(uint16_t arr1[4], uint16_t arr2[4]) {
  for (int i = 0; i < 4; i++) {
    arr1[i] = arr1[i] & arr2[i];
  }
}

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  for (int i = 0; i < 4; i++) { pinMode(tPins[i], OUTPUT); }

  Up.begin();
  Down.begin();

  Serial.begin(9600);

  randomSeed(analogRead(A5));
}

unsigned long lastMoveTime_J = 0;
const int moveDelay_J = 100;
bool joyStick() {
  if (millis() - lastMoveTime_J < moveDelay_J) return false;

  int xIn = analogRead(xPin);
  int yIn = analogRead(yPin);
  bool moved = false;

  if (xIn < 400 && head[0] > 0) {
    head[0]--;
    moved = true;
  } else if (xIn > 600 && head[0] < 3) {
    head[0]++;
    moved = true;
  }

  if (yIn < 400 && head[1] > 0) {
    head[1]--;
    moved = true;
  } else if (yIn > 600 && head[1] < 3) {
    head[1]++;
    moved = true;
  }

  if (moved) lastMoveTime_J = millis();
  return moved;
}

bool Pushbutton() {
  bool moved = false;
  if (Up.pressed() && head[2] < 3) {
    head[2]++;
    moved = true;
  }
  if (Down.pressed() && head[2] > 0) {
    head[2]--;
    moved = true;
  }
  return moved;
}

void loop() {
  int prevHead[3] = { head[0], head[1], head[2] };
  int prevBody[3] = { body[0], body[1], body[2] };

  bool movedJ = joyStick();
  bool movedP = Pushbutton();

  if (movedJ || movedP) {
    tail[0] = prevBody[0];
    tail[1] = prevBody[1];
    tail[2] = prevBody[2];
    body[0] = prevHead[0];
    body[1] = prevHead[1];
    body[2] = prevHead[2];
  }

  for (int i = 0; i < 4; i++) {
    cubeVal[i] = 0;
  }

  int* parts[] = { head, body, tail };
  for (int s = 0; s < 3; s++) {
    for (int i = 0; i < 4; i++) cubeData[i] = 0;
    cube_state(cubeData, parts[s]);
    sync4(cubeVal, cubeData);
  }

  for (int i = 0; i < 4; i++) {
    writeLayer(tPins[i], cubeVal[i]);
  }
}
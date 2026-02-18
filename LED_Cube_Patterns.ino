#include "patterns.h"

int dataPin = 2;
int clockPin = 3;
int latchPin = 4;
int tPins[] = { 5, 6, 7, 8 };

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

template<size_t N>
void displayPattern(const uint16_t (&p)[N][5]) {
  for (int f = 0; f < N; f++) {
    unsigned long duration = pgm_read_word(&(p[f][4]));
    unsigned long startTime = millis();
    while ((millis() - startTime) < duration) {
      writeLayer(tPins[0], pgm_read_word(&(p[f][0])));
      writeLayer(tPins[1], pgm_read_word(&(p[f][1])));
      writeLayer(tPins[2], pgm_read_word(&(p[f][2])));
      writeLayer(tPins[3], pgm_read_word(&(p[f][3])));
    }
  }
}

template<size_t N>
void playPattern(const uint16_t (&p)[N][5], long time) { // time is in seconds
  time *= 1000;
  unsigned long startTime = millis();
  while ((millis() - startTime) < time) {
    displayPattern(p);
  }
}

void setup() {
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  for (int i = 0; i < 4; i++) pinMode(tPins[i], OUTPUT);
}

void loop() {
  playPattern(pattern1, 4);
  playPattern(pattern2, 4);
  playPattern(pattern3, 4);
  playPattern(pattern4, 4);
}
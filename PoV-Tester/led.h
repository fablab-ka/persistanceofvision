#ifndef LED_H
#define LED_H

#include "Arduino.h"

#define LED_DATA   D0
#define LED_CLK    D6
#define LED_ENABLE D8
#define LED_LATCH  D7

static void initLEDs() {
  pinMode(LED_DATA, OUTPUT);
  pinMode(LED_CLK, OUTPUT);
  pinMode(LED_ENABLE, OUTPUT);
  pinMode(LED_LATCH, OUTPUT);
  
  digitalWrite(LED_ENABLE, LOW);
}

static void showLEDs(uint8_t data) {
  digitalWrite(LED_CLK, LOW);
  shiftOut(LED_DATA, LED_CLK, MSBFIRST, data);
  digitalWrite(LED_LATCH, HIGH);
  digitalWrite(LED_LATCH, LOW);
}

#endif


#include "Arduino.h"
extern "C" {
#include "user_interface.h"
}
#include "motor.h"
#include "PovDisplay.h"

#define A1 D1
#define A2 D4
#define B1 D2
#define B2 D3

namespace Motor {
static const float band_width = 125.5 * 3.14;
static int steps_per_turn = 64 * 32;
static uint16_t timer_delay = 10;
static uint8_t step_state = 0;
static os_timer_t myTimer;
static uint16_t step_pos = 0;
static boolean step_ccw = true;
static boolean is_initialized = false;
  PovDisplay* disp;

static void do_step() {
  if (step_ccw) {
    step_state++;
    step_pos++;
  } else {
    step_state--;
    step_pos--;
  }
  step_state = step_state % 4;
  step_pos = step_pos % steps_per_turn;

  switch (step_state) {
    case 0:
      digitalWrite(A1, HIGH);
      digitalWrite(A2, LOW);
      digitalWrite(B1, HIGH);
      digitalWrite(B2, LOW);
      break;
    case 1:
      digitalWrite(A1, HIGH);
      digitalWrite(A2, LOW);
      digitalWrite(B1, LOW);
      digitalWrite(B2, HIGH);
      break;
    case 2:
      digitalWrite(A1, LOW);
      digitalWrite(A2, HIGH);
      digitalWrite(B1, LOW);
      digitalWrite(B2, HIGH);
      break;
    case 3:
      digitalWrite(A1, LOW);
      digitalWrite(A2, HIGH);
      digitalWrite(B1, HIGH);
      digitalWrite(B2, LOW);
      break;
  }
};

void timerCallback(void *pArg) {
  do_step();
  disp->next_step(step_pos);
};

void start_rotating() {
  os_timer_arm(&myTimer, timer_delay, true);
};

void stop_rotating() {
  os_timer_disarm(&myTimer);
};

void set_speed(float rpm) {
  stop_rotating();
  timer_delay = (steps_per_turn * 1000.0 * 60.0) / rpm;
  start_rotating();
};

void init() {
  if (!is_initialized) {
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(B1, OUTPUT);
    pinMode(B2, OUTPUT);
    os_timer_setfn(&myTimer, timerCallback, NULL);
    os_timer_arm(&myTimer, timer_delay, true);
    is_initialized = true;
  }
}

void set_display(PovDisplay &d) {
disp = &d;
}

}

#ifndef MOTOR_H
#define MOTOR_H
#include "PovDisplay.h"

namespace Motor {
  int get_steps_per_turn();
  void start_rotating();
  void stop_rotating();
  void set_speed(float rpm);
  void set_display(PovDisplay &d);
  void init();

}

#endif



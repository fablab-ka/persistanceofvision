#include "PovDisplay.h"
#include "motor.h"
#include "led.h"
#include "font.cpp"

PovDisplay::PovDisplay() {
  Motor::set_display(*this);
}


//void PovDisplay::display2(uint8_t* arr, int len) {
//  display_buffer = arr;
//  buffer_len = len;
//}

void PovDisplay::show_text(String text) {
  buffer_len = 6 * text.length();
  for(int i = 0; i < text.length(); i++) {
    for(int j = 0; j < 6; j++) {
      display_buffer[i*6 + j] = font[text.charAt(i)][j];
    }
  }
}

uint8_t PovDisplay::get_line(int posi) {
  return display_buffer[posi % buffer_len];
}


void PovDisplay::next_step(int pos) {
  int line_offset = 26;

  if (!buffer_len)
    return;
  uint8_t line = 0;
  if ((pos % 16) < 4) {              //should the forward pixels be on?
    line = get_line(pos / 16) & 0b10101010;
  }
  if (((pos - line_offset) % 16) < 4) //should the backwars pixels be on?
    line += get_line((pos - line_offset) / 16) & 0b01010101;
  showLEDs(line);
}



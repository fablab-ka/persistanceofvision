//#ifndef POVDISPLAY_H
//#define POVDISPLAY_H

#include <Arduino.h>

#pragma once

static int buffer_len;          // length of array
static uint8_t display_buffer[400]; // buffer with column-wise data to display

class PovDisplay {
  public:
    PovDisplay();  // Constructor
    void display(int arr_len, int wait_after, uint8_t *arr);  // Initialize write cycle
    void next_step(int pos);  // callback for single steps from the stepper driver
    void show_text(String text);
    void display2(uint8_t* arr, int len);
    uint8_t get_line(int posi);
};

//#endif


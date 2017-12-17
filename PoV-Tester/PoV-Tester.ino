#include "PovDisplay.h"
#include "font.h"

#define LED_DATA   D8
#define LED_CLK    D6
#define LED_ENABLE D7
#define LED_LATCH  D0

#define MOTOR_A1 D1
#define MOTOR_A2 D2
#define MOTOR_B1 D4
#define MOTOR_B2 D3

#define SPACER 1


PovDisplay myDisp(LED_DATA, LED_CLK, LED_ENABLE, LED_LATCH, 
                  MOTOR_A1, MOTOR_B1, MOTOR_A2, MOTOR_B2, 
                  26, 18, 50, 2, CW);
 
void setup() {
  Serial.begin(115200);
}

String message="PHABLABS 4.0 Fablab Karlsruhe ";

void loop() {
  for ( uint8_t i = 0; i < message.length(); i++) {
    //Serial.println(i);
    for ( uint8_t j = 0; j < FONTCOLS; j++) {
        while ( not myDisp.set_next_column( font[(uint8_t)message.charAt(i)][j])) {yield();};
    }
    for(uint8_t j = 0; j < SPACER; j++) {
      while (not myDisp.set_next_column(0)) {yield();};
    }
  }
}




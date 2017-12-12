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


PovDisplay myDisp(LED_DATA, LED_CLK, LED_ENABLE, LED_LATCH, 
                  MOTOR_A1, MOTOR_B1, MOTOR_A2, MOTOR_B2, 
                  1, 26, 26, 50, 3, CW);
 
void setup() {
  Serial.begin(115200);
}

String message="PHABLABS 4.0 Fablab Karlsruhe ";

void loop() {
  for ( int i = 0; i < message.length(); i++) {
    //Serial.println(i);
    for ( int j = 0; j < 6; j++) {
        while ( not myDisp.set_next_column(font[message.charAt(i)][j])) {yield();};
    }
    for(int j = 0; j < myDisp._spacer; j++) {
      while (not myDisp.set_next_column(0)) {yield();};
    }
  }
}




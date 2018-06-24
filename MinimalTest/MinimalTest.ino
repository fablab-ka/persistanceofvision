#include "PovDisplay.h"
#include "motor.h"
#include "led.h"
//#include <stdlib.h>
#include "font.cpp"
PovDisplay disp;

//const int arr_size = 400;
//uint8_t arr[arr_size];

void setup() {
  delay(1000);
  Motor::init();
  initLEDs();
  Serial.begin(115200);
//  for (int i = 0; i < arr_size; i++)
//    arr[i] = 1 << (i % 8);
  showLEDs(255);
  PovDisplay disp = PovDisplay();
  //disp.display2(font[35], 5);
  disp.show_text("12345");
}

int IntToBitColumn(int zahl);

void loop() {
  //  int an,aus,versatz,n;
  //
  //  for( an=1; an<42; an++) {
  //    n=IntToBitColumn(an); // n number of columns to display
  //    PovDisplay disp(3, 4, 26);  // PovDisplay::PovDisplay(int led_on, int led_off)
  //    disp.display(n, 200, array);  // PovDisplay::display(int arr_len, int wait_after, uint8_t *arr)
  //  }
}


//int IntToBitColumn(int zahl) {
//   int n;
//   const int zwischenraum=3;
//   int ziffern[5];
//   int i=0;
//   while (zahl>0) {
//     ziffern[++i]= zahl % 10;
//     zahl = zahl / 10;
//   }
//   n= (8+zwischenraum)*i;
//   int ax=0;
//   for(int z=i; z>0; z--) {
//    //Serial.print("ziffern "); Serial.print(z); Serial.print(" "); Serial.println(ziffern[z]);
//    for(int col=0; col<8; col++ ) {
//      array[ax++]= font [ziffern[z]][col];
//    }
//    //Serial.println(ax);
//    for (int col=0; col<zwischenraum; col++) {
//      array[ax++]= 0;
//    }
//   }
//
//   return(n);
//}


//



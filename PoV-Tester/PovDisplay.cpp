#include "PovDisplay.h"

PovDisplay::PovDisplay( uint8_t  LedData, uint8_t  LedClk, uint8_t  LedEna, uint8_t  LedLatch, 
            uint8_t  M_A1, uint8_t  M_A2, uint8_t  M_B1, uint8_t  M_B2, 
            uint8_t spacer,  uint8_t steps_per_pixel, uint8_t highlighted_steps, uint8_t column_offset, 
            float rpm, uint8_t m_direction) {
  _motorPins[0] = M_A1; _motorPins[1] = M_A2;
  _motorPins[2] = M_B1; _motorPins[3] = M_B2;
  _pinLedData        = LedData; 
  _pinLedClk         = LedClk;
  _pinLedEna         = LedEna;
  _pinLedLatch       = LedLatch;
  _spacer            = spacer;
  _steps_per_pixel   = steps_per_pixel;
  _highlighted_steps = highlighted_steps;
  _column_offset     = column_offset;
  _step_delay        = uint16_t() (rpm/60/STEPS_PER_ROTATION) + MILLIS_PER_STEP;
  _motor_direction   = m_direction;
  _MotorStepState    = 0;
  _currPixelStep     = 0;
  _bufsize           = sizeof(this._ringbuffer);
  pinMode(_pinLedData, OUTPUT);
  pinMode(_pinLedClk, OUTPUT);
  pinMode(_pinLedEna, OUTPUT);
  pinMode(_pinLedLatch, OUTPUT);
  digitalWrite(_pinLedEna, LOW);
  for (uint8_t i=0; i<4; i++) {
    pinMode(this._motorPins[i], OUTPUT);
  } 
  os_timer_setfn(&myTimer, this.do_next_step, NULL);
  start_rotating();
}

void PovDisplay::start_rotating(){
  os_timer_arm(&myTimer, this._step_delay, true);
}

void PovDisplay::stop_rotating(){
  os_timer_disarm(&myTimer);
}

void PovDisplay::set_rotation(uint8_t dir){
  this._motor_direction=dir;
}

void PovDisplay::set_offset(uint8_t offset){
  this._column_offset=offset;
}

void set_highlighted_steps(uint8_t stepcount){
  this._highlighted_steps = min(stepcount, this._steps_per_pixel); //make sure, that there are not more highlited pixels than steps!
}

void PovDisplay::set_speed(float rpm){
  this._step_delay        = uint16_t() (rpm/60/STEPS_PER_ROTATION) + MILLIS_PER_STEP;
}

bool PovDisplay::set_next_column (uint8_t value){
  // store another column in ringbuffer, if ringbuffer has space left
  // return true, if storing was succesful, otherwise return false
  if( (_bufend % _bufsize) != ((_bufstart+_bufsize-1) % _bufsize ) ) {
    _ringbuffer[_bufend]=value;
    _bufend=(_bufend+1) % _bufsize;
    _bufferfull=false
    return true;
  } else {
    return false;
  }
}


void PovDisplay::do_next_step() {
  uint8_t backPixelStep = (3*this._steps_per_pixel + this._currPixelStep - this._column_offset) % this._steps_per_pixel;
  uint8_t backPixelOffset = (this._column_offset+this._steps_per_pixel-this._currPixelStep) / this._steps_per_pixel;
  uint8_t output = 0b00000000;
  
  if (this._currPixelStep <= this._highlighted_steps) {
    output = (_ringbuffer[_this._bufstart] & 0b10101010)
  }
  
  if (backPixelStep <= this._highlighted_steps) {
    output = output | (_ringbuffer[_this._bufstart-backPixelOffset] & 0b01010101)
  }
  
  digitalWrite(LED_CLK, LOW);
  shiftOut(LED_DATA, LED_CLK, MSBFIRST, output);
  digitalWrite(LED_LATCH, HIGH);
  digitalWrite(LED_LATCH, LOW);
  
  this._MotorStepState=(this._MotorStepState+8+motorDirection) % 8;
  this._currPixelStep=(this._currPixelStep+1) % this._steps_per_pixel;
  if (this._currPixelStep == 0 ) {
    if(  this._bufstart !=  this._bufend ) {
      this._bufstart=(this._bufstart+1) % this._bufsize
    } else {
      this._bufferfull=true;
    }
  }
  if (! this._bufferfull ) {
    for (uint8_t i=0; i<4; i++) {
      digitalWrite(this._motorPins[i], bitRead(this._stepValues[this._currMotorStep],i));
    } 
  }  
}


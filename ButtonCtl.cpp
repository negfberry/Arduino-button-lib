#include <Arduino.h>
#include "ButtonCtl.h"


ButtonCtl::ButtonCtl(int pin) {
  _ButtonStr.bpin = pin;
  pinMode(pin, INPUT_PULLUP);
}


/*
 * 
 * Debounce button:
 *  Button number returned from function above.
 *  Return: -1 no change
 *           0 off
 *           1 on
 *           
 */
 
char ButtonCtl::read() {
   byte val;

  // Return if we haven't waited at least one millisecond
  if(_ButtonStr.btime != millis()) {
    // Read pin
    val = !digitalRead(_ButtonStr.bpin);
    // Set current millis
    _ButtonStr.btime = millis();
    // Has bounced back to where it was
    if(val == _ButtonStr.cstate && _ButtonStr.counter > 0)
      _ButtonStr.counter--;
    // In new state
    if(val != _ButtonStr.cstate)
       _ButtonStr.counter++;
    // In new state and hasn't bounced for at least DEBOUNCE milleseconds
    if(_ButtonStr.counter >= DEBOUNCE) {
      _ButtonStr.counter = 0;
      _ButtonStr.cstate = val;
      return val;
    }
  }
  return -1;
}



/*
 * 
 * Return how long a button has been pressed in deciseconds
 *  Return: >= 1 deciseconds
 *          0 not pressed.
 * 
 */
 
byte ButtonCtl::time() {
  char i;

  i = read();
  // If button state has changed
  if(i >= 0) {
    // Set recorded state to the new state
    _ButtonStr.state = i;
    // If the new state is pressed, note the deciseconds time.
    if(i) _ButtonStr.intcnt = ((millis() / 100) % 256) - 1;
  }
  // If pressed, calculate how long it has been pressed from the time now,
  // and the time it was first pressed.
  if(_ButtonStr.state) {
    _ButtonStr.decsecs = ((millis() / 100) % 256) - _ButtonStr.intcnt;
    // If that time is not 0, return that, else return 1 (to distinguish
    // it from not pressed).
    if(_ButtonStr.decsecs) return _ButtonStr.decsecs;
    else return 1;
  }
  // Or else return not pressed.
  return 0;
}


/*
 * 
 * Return how long a button has been pressed in deciseconds, 
 * after it is released.
 *  Return: >= 1 deciseconds
 *          0 not released, or not pressed yet.
 * 
 */
 
byte ButtonCtl::timeup() {
  byte i;
  
  i = time();
  if(!i && _ButtonStr.last) {
    i = _ButtonStr.last;
    _ButtonStr.last = 0;
    return i;
  }
  _ButtonStr.last = i;
  return 0;
}


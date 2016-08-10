#include <ButtonCtl.h>

// Create a Button instance on pin 2
// Note that no further setup is required.
// The library will make it an input,
// with pullup resistors activated.
ButtonCtl button(2);

void setup(){
  Serial.begin(9600);
  while(!Serial);
}

void loop() {
  int buttonS;
  
  buttonS = button.read();
  Serial.println(buttonS);
  buttonS = button.proc();
  Serial.println(buttonS);
  buttonS = button.release();
  Serial.println(buttonS);
  delay(1000);
}


#ifndef ButtonCtl_h
#define ButtonCtl_h
 
#include <Arduino.h>

#define DEBOUNCE 2

class ButtonCtl{
  public:
        ButtonCtl(int pin);
        char read();
        byte time();
        byte timeup();
  private:
        struct {
          byte bpin;
          byte cstate;
          byte counter;
          unsigned long int btime;
          byte state;
          byte intcnt;
          byte decsecs;
          byte last;
        } _ButtonStr;
};
 
#endif

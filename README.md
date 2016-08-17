# Arduino-button-lib
Arduino button debounce and control library
Provides three functions:

char ButtonCtl::read()
  Debounce button:
   Button number returned from function above.
   Return: -1 no change
            0 off
            1 on

byte ButtonCtl::time()
  Return how long a button has been pressed in deciseconds
   Return: >= 1 deciseconds
           0 not pressed.
 
byte ButtonCtl::timeup()
  Return how long a button has been pressed in deciseconds, 
  after it is released.
   Return: >= 1 deciseconds
           0 not released, or not pressed yet.
  

#include "hachibar.h"      // include HACHIBAR SDK
#include "hachibar_font.h" // include default font

Hachibar h;    // HACHIBAR SDK
int x = 4;     // initial position
int y = 8;

void setup(){
  h.init();    // initialize HACHIBAR SDK
}

void loop(){
  if(h.nextFrame()){ // keep frame rete
    h.rect(false, 0, 0, 8, 16);     // clear all
    h.pset(true, x, y);             // draw dot

    if(h.trigger[h.BTN_LEFT] >= 1){ // check left button
      if(x > 0) x --;
    }
    if(h.trigger[h.BTN_UP] >= 1){   // check up button
      if(y > 0) y --;
    }
    if(h.trigger[h.BTN_RIGHT] >= 1){ // check right button
      if(x < 7) x ++;
    }
    if(h.trigger[h.BTN_DOWN] >= 1){  // check down button
      if(y < 15) y ++;
    }
    h.updateKey();   // update keyboard input
  }
  h.updateDisplay(); // update display
}

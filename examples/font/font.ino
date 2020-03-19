#include "hachibar.h"      // include HACHIBAR SDK
#include "hachibar_font.h" // include default font
#include "hachibar_sfont.h" // include default small font

Hachibar h;    // HACHIBAR SDK
int count = 0; // scroll counter

void setup(){
  h.init();    // initialize HACHIBAR SDK
  h.setFont(&hachibar_font);  // set default font
}

void loop(){
  if(h.nextFrame()){ // keep frame rete
    h.rect(false, 0, 0, 8, 16);         // clear all
    h.drawString("Hello  ", -count, 0); // draw Hello
    h.drawString("  World", -count, 8); // draw World

    if(h.trigger[h.BTN_A] == 1){  // check A button
      h.setFont(&hachibar_font);  // set default font
    }
    if(h.trigger[h.BTN_B] == 1){  // check B button
      h.setFont(&hachibar_sfont); // set default small font
    }

    h.updateKey();   // update Keyboard input
    count ++;        // increment counter
  }
  h.updateDisplay(); // update Display
}

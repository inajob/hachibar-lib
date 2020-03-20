#include "hachibar.h"
#include "tones.h"

Hachibar h;

char data[8];
int tones[16] = {
0,
NOTE_C5,
NOTE_D5,
NOTE_E5,
NOTE_F5,
NOTE_G5,
NOTE_A5,
NOTE_B5,
NOTE_C6,
NOTE_D6,
NOTE_E6,
NOTE_F6,
NOTE_G6,
NOTE_A6,
NOTE_B6
};

int x,y;

void clear(){
  for(byte i = 0; i < 8; i ++){
    data[i] = -1;
  }
}

void setup(){
  h.init();
}
int count = 0;
int pos = 0;
int speed = 10;
void loop(){
  if(h.nextFrame()){
    h.rect(false, 0,0,8,16);
    if(count%2 == 0){
      h.rect(true, x, 15 - y, 1, 1);
    }
    h.rect(true, pos, 0, 1, 16);

    for(byte i = 0; i < 8; i ++){
      h.rect(true, i, 15 - data[i], 1, 1);
    }

    if(count%speed == 0){
      pos = (pos + 1)%8;
      tone(14, tones[data[pos]], 100);
    }

    if(h.trigger[h.BTN_B] > 3){
      if(h.trigger[h.BTN_UP] == 1 && speed > 2){
        speed --;
      }
      if(h.trigger[h.BTN_DOWN] == 1 && speed < 99){
        speed ++;
      }
    }else{
      if(h.trigger[h.BTN_UP] == 1 && y < 15){
        y ++;
      }
      if(h.trigger[h.BTN_DOWN] == 1 && y > 0){
        y --;
      }
      if(h.trigger[h.BTN_LEFT] == 1 && x > 0){
        x --;
      }
      if(h.trigger[h.BTN_RIGHT] == 1 && x < 7){
        x ++;
      }

      if(h.trigger[h.BTN_A] == 3){
        data[x] = y;
      }
    }

    h.updateKey();
    count ++;
  }
  h.updateDisplay();
}

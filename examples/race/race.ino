#include "hachibar.h"
#include "hachibar_font.h"

Hachibar h;

byte data[16];
int mx = 4;
int my = 1;
int count = 0;
int score = 0;
const byte MODE_READY = 0;
const byte MODE_GAME = 1;
const byte MODE_OVER = 2;

byte mode = 0;

byte title[16] = {
    B00011001,
    B01010110,
    B00010000,
    B00110110,
    B01010110,
    B11111111,
    B11111111,
    B11111111,

    B00011000,
    B01111011,
    B01111000,
    B01111011,
    B00011000,
    B11111111,
    B11111111,
    B11111111
};

void clearMap(){
  memset(data, 0xff, 16);
}
void stepOne(){
  for(int i = 15; i > 0; i --){
    data[i] = data[i - 1];
  }
}
bool isHit(int x, int y){
  byte row = ~data[y];
  return (row & (1 << x)) != 0;
}
byte generateLine(){
  byte r = 0B01111110;
  for(int i = 1; i < 7;i ++){
    if(random(10) > 8){
      r &= ~(1 << i);
    }
  }
  return r;
}
void draw(){
 // == stage ==
  for(int i = 0; i < 16; i ++){
    h.buf[i] = data[i];
  }

  //== self ==
  if(count%2 == 0){
    h.pset(true, mx, my);
  }
}

void reset(){
  clearMap();
  mode = MODE_READY;
  score = 0;
  mx = 4;
  my = 15;
}

void setup(){
  h.init();
  h.setFont(&hachibar_font);
  reset();
}

void gameLoop(){
  byte fast = 0;
  if(h.trigger[h.BTN_A] >= 1){
    fast = 1;
  }

  // == LOGIC ==
  if(count%(20-min(score/20, 18)) == 0 || ((fast == 1) && (count%2 == 0))){
    stepOne();
    score++;
    data[0] = generateLine();
    tone(14, 700, 50);
  }
  // == CONTROL ==
  if(h.trigger[h.BTN_RIGHT] == 1){
    mx ++;
    if(mx > 7){
      mx = 7;
    }
  }
  if(h.trigger[h.BTN_LEFT] == 1){
    mx --;
    if(mx < 0){
      mx = 0;
    }
  }
  // == HIT CHECK ==
  if(isHit(mx,my)){
    mode = MODE_OVER;
    tone(14, 200, 500);
  }
  // == DRAW ==
  h.rect(false, 0, 0, 8, 16);
  draw();
}
byte reverse(byte b){
  return 
    ((b&0B00000001) << 7) |
    ((b&0B00000010) << 5) |
    ((b&0B00000100) << 3) |
    ((b&0B00001000) << 1) |
    ((b&0B00010000) >> 1) |
    ((b&0B00100000) >> 3) |
    ((b&0B01000000) >> 5) |
    ((b&0B10000000) >> 7);
}
void readyLoop(){
  for(int i = 0; i < 16; i ++){
    h.buf[i] = reverse(title[i]);
  }
  if(h.trigger[h.BTN_B] == 1){
    mode = MODE_GAME;
  }
}
void overLoop(){
  if(h.trigger[h.BTN_B] == 1){
    reset();
  }
  h.rect(false, 0, 0, 8, 16);

  char buf[10];
  sprintf(buf, "%d", score);

  h.drawString("GAME OVER", 8-count/5, 0);
  h.drawString(buf, 8-count/5, 8);
  count ++;
}

void loop(){
  if(h.nextFrame()){
    switch(mode){
      case MODE_READY:
      readyLoop();
      break;
      case MODE_GAME:
      gameLoop();
      break;
      case MODE_OVER:
      overLoop();
      break;
    }
    count ++;
    h.updateKey();
  }
  h.updateDisplay();
}

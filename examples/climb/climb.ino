#include "hachibar.h"
#include "hachibar_font.h"

Hachibar h;
unsigned int count = 0;
unsigned int level = 0;
int score;
const int M_READY = 0;
const int M_GAME = 1;
const int M_OVER = 2;
bool stage[16][8];
int mx;
float my;
int vx;
float vy;
float ay;
int preFoot = 0;
bool jumpOk = false;

int mode;

void reset(){
  mx = 4;
  my = 1;
  vx = 0;
  vy = 0;
  ay = 0.003;
  level = 0;
  score = 0;
  for(int i = 0; i < 16; i ++){
    for(int j = 0; j < 8; j ++){
      stage[i][j] = (i == 3);
    }
  }
  stage[2][2] = true;
  stage[2][6] = true;

  mode = M_READY;
}

void downNext(){
  for(int i = 15; i >= 1; i --){
    for(int j = 0; j < 8; j ++){
      stage[i][j] = stage[i - 1][j];
    }
  }
  my ++;
  if(level%3 == 0){
    byte start = random(6);
    while(start == preFoot){
      start = random(6);
    }
    for(int i = 0; i < 8; i ++){
      stage[0][i] = (start <= i && i < start + 3);
    }
    preFoot = start;
    score ++;
  }else{
    for(int i = 0; i < 8; i ++){
      stage[0][i] = false;
    }
  }
  level ++;
  tone(14, 700, 50);
}

void draw(){
  h.rect(false, 0, 0, 8, 16);
  for(int i = 0; i < 16; i ++){
    for(int j = 0; j < 8; j ++){
      h.pset(stage[i][j], j, i);
    }
  }

  h.pset(true, mx, ceil(my));
}

void setup(){
  h.init();
  h.setFont(&hachibar_font);
  reset();
}

void gameLoop(){
  int speed = 30 - level/3;
  if(speed < 10)speed = 10;
  if(count%speed == 0){
    downNext();
  }
  bool flag = false;
  if(h.trigger[h.BTN_LEFT] == 1){
    vx += -1;
    flag = true;
  }
  if(h.trigger[h.BTN_RIGHT] == 1){
    vx += 1;
    flag = true;
  }
  if(flag == false){
    vx = 0;
    mx = floor(mx);
  }
  mx += vx;

  if(mx < 0)mx = 0;
  if(mx > 7)mx = 7;

  if(stage[(int)floor(my)][mx]|| stage[(int)ceil(my)][mx]){
    mx = mx - vx;
  }

  if(h.trigger[h.BTN_A] == 1){
    if(jumpOk){
      tone(14, 1400, 20);
      vy = -1;
      jumpOk = false;
    }
  }
  ay = 0.05;
  vy += ay;
  if(abs(vy) >= 0.4){
    my += 0.4 * vy/abs(vy);
  }else{
    my += vy;
  }
  if(my < 0){
    my = 0;
    vy = 0;
  }
  if(my > 15){
    mode = M_OVER;
    tone(14, 200, 500);
  }

  // FOOT
  if(stage[(int)ceil(my)][mx]){
    my = floor(my);
    jumpOk = true;
  }
  // HEAD
  if(stage[(int)floor(my)][mx]){
    my = ceil(my);
    vy = 0;
  }
  draw();
}

void overLoop(){
  h.rect(true, 0, 8, 8, 8);
  h.rect(false, 0, 0, 8, 8);
  char buf[10];
  sprintf(buf, "%d", score);
  h.drawString(buf, 8-count/2, 0);

  if(h.trigger[h.BTN_B] == 3){
    reset();
  }
}
void readyLoop(){
  h.rect(false, 0, 0, 8, 16);
  char* buf = "CLIMB";
  h.drawString(buf, 8-count/2, 0);

  if(h.trigger[h.BTN_B] == 3){
    mode = M_GAME;
  }
}

void loop(){
  if(h.nextFrame()){
    switch(mode){
      case M_READY:
      readyLoop();
      break;
      case M_GAME:
      gameLoop();
      break;
      case M_OVER:
      overLoop();
      break;
    }
    count ++;
    h.updateKey();
  }
  h.updateDisplay();
}

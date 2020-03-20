#include "hachibar.h"
#include "hachibar_font.h"
#include "hachibar_sfont.h"

Hachibar h;

bool stage[16][8];
bool overlay[4][4];
int score;
int freezeTimer;
int px,py;
bool shapes[5][4][4] = {
  {
  {0,0,1,0},
  {0,0,1,0},
  {0,0,1,0},
  {0,0,1,0}
  },
  {
  {0,0,1,0},
  {0,0,1,0},
  {0,1,1,0},
  {0,0,0,0}
  },
  {
  {0,0,1,0},
  {0,1,1,0},
  {0,0,1,0},
  {0,0,0,0}
  },
  {
  {0,0,0,0},
  {0,1,1,0},
  {0,1,1,0},
  {0,0,0,0}
  },
  {
  {0,1,0,0},
  {0,1,0,0},
  {0,1,1,0},
  {0,0,0,0}
  },
};

const byte M_READY = 0;
const byte M_GAME = 1;
const byte M_OVER = 2;
const byte M_SCORE = 3;

byte mode = M_GAME;
unsigned int scoreCount = 0;
unsigned int count = 0;

void clearStage(){
  for(int i = 0; i < 16; i ++){
    for(int j = 0; j < 8; j ++){
      stage[i][j] = false;
    }
  }
}
void nextBlock(){
  byte kind = random(5);
  for(int i = 0; i < 4; i ++){
    for(int j = 0; j < 4; j ++){
      overlay[i][j] = shapes[kind][i][j];
    }
  }
  py = -2;
  px = 0;
}
void reset(){
  clearStage();
  mode = M_READY;
  score = 0;
  nextBlock();
}

void rotate(){
  bool next[4][4];
  for(int i = 0; i < 4; i ++){
    for(int j = 0; j < 4; j ++){
      next[i][j] = overlay[3-j][i];
    }
  }
  for(int i = 0; i < 4; i ++){
    for(int j = 0; j < 4; j ++){
      overlay[i][j] = next[i][j];
    }
  }
}

bool check(){
  for(int i = 0; i < 4; i ++){
    for(int j = 0; j < 4; j ++){
      if(overlay[i][j]){
        if(py + i > 15){return false;}
        if(px + j < 0){return false;}
        if(px + j >= 8){return false;}
        if(0 <= py + i && py + i < 16 && 0 <= px + j && px + j < 8){
          if(stage[py + i][px + j]){
            return false;
          }
        }
      }
    }
  }
  return true;
}

bool overCheck(){
  for(int i = 0; i < 8; i ++){
    if(stage[0][i]){
      return true;
    }
  }
  return false;
}

void draw(){
  h.rect(false, 0, 0, 8, 16);
  for(int i = 0; i < 16; i ++){
    for(int j = 0; j < 8; j ++){
      if(stage[i][j]){
        h.pset(true, j, i);
      }else{
        h.pset(false, j, i);
      }
    }
  }
  for(int i = 0; i < 4; i ++){
    for(int j = 0; j < 4; j ++){
      if(overlay[j][i]){
        h.pset(true, px + i, py + j);
      }
    }
  }
}
void freeze(){
  for(int i = 0; i < 4; i ++){
    for(int j = 0; j < 4; j ++){
      if(overlay[j][i]){
        stage[py + j][px + i] = true;
      }
    }
  }
}

void scoreLoop(){
  char buf[10];
  sprintf(buf, "%d ", score);
  int len = strlen(buf);
  h.rect(false, 0, 8, 8, 8);
  h.drawString(buf, 8 - scoreCount, 8);

  scoreCount ++;
  if(scoreCount > 6*len + 8){
    mode = M_GAME;
  }
}

bool lineProc(){
  bool next = true;
  bool ret = false;
  while(next){
    next = false;
    for(int i = 0; i < 16; i ++){
      bool flag = true;
      for(int j = 0; j < 8; j ++){
        if(!stage[i][j]){
          flag = false;
          break;
        }
      }
      if(flag){
        score ++;
        ret = true;
        for(int y = i; y > 0; y --){
          for(int x = 0; x < 8; x ++){
            stage[y][x] = stage[y - 1][x];
          }
        }
        next = true;
        tone(14, 880, 100);
        break;
      }
    }
  }
  return ret;
}

void readyLoop(){
  h.rect(false, 0, 0, 8, 16);

  h.drawString("BLOCK", -count, 8);
  if(h.trigger[h.BTN_B] == 1){
    mode = M_GAME;
  }
}
void gameLoop(){
  bool fast = false;
  int speed = 30 - 30*score/50;
  if(speed < 4){
    speed = 4;
  }
  if(h.trigger[h.BTN_DOWN] > 1){
    fast = true;
  }
  if(count%speed == 0 || (fast && count%2 == 0)){
    if(fast){
      tone(14, 440, 10);
    }
    py ++;
    if(!check()){
      py --;
      if(freezeTimer == -1){
        freezeTimer = 2;
      }else{
        freezeTimer --;
      }

      if(freezeTimer == 0){
        tone(14, 220, 100);
        freeze();
        if(lineProc()){
          mode = M_SCORE;
          scoreCount = 0;
        }
        if(overCheck()){
          mode = M_OVER;
        }
        nextBlock();
      }
    }else{
      freezeTimer = -1;
    }
  }
  if(h.trigger[h.BTN_A] == 1){
    rotate();
    if(!check()){
      px ++;
      if(!check()){ // try left shift
        px --;
        px --;
        if(!check()){ //try right shift
          px ++;
          rotate();
          rotate();
          rotate();
        }
      }
    }
    tone(14, 440, 100);
  }

  if(h.trigger[h.BTN_LEFT] == 1){
    px --;
    if(!check()){
      px ++;
    }else{
      freezeTimer = -1;
      tone(14, 440, 100);
    }
  }
  if(h.trigger[h.BTN_RIGHT] == 1){
    px ++;
    if(!check()){
      px --;
    }else{
      freezeTimer = -1;
      tone(14, 440, 100);
    }
  }
  draw();
}
void overLoop(){
  h.rect(false, 0, 0, 8, 8);
  h.drawString("GAME OVER", -count, 0);
  h.rect(false, 0, 8, 8, 8);
  char buf[10];
  sprintf(buf, "%d", score);
  h.drawString(buf, -count/2, 8);

  if(h.trigger[h.BTN_B] == 1){
    reset();
  }
}

void setup(){
  h.init();
  //h.setFont(&hachibar_sfont);
  h.setFont(&hachibar_font);
  reset();
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
      case M_SCORE:
      scoreLoop();
      break;
    }
    h.updateKey();
    count ++;
  }

  h.updateDisplay();
}

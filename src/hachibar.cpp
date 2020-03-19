#include "hachibar.h"

Hachibar::Hachibar(){
}

void Hachibar::pset(bool b,int x, int y){
  if(x < 0 || x >= 8){
    return;
  }
  if(y < 0 || y >= 16){
    return;
  }
  if(!b){
    buf[y] |= (1 << x);
  }else{
    buf[y] &= ~(1 << x);
  }
#ifdef false
  if(y < 8){
    if(!b){
      buf[x+8] |= (1 << y);
    }else{
      buf[x+8] &=  ~(1 << y);
    }
  }else{
    if(!b){
      buf[x] |= (1 << (y-8));
    }else{
      buf[x] &=  ~(1 << (y-8));
    }
  }
#endif
}
void Hachibar::rect(bool b, int x, int y, byte w, byte h){
  for(int i = x; i < x + w; i ++){
    for(int j = y; j < y + h; j ++){
      pset(b, i, j);
    }
  }
}

void Hachibar::init() {

  // all blue OUTPUT LOW
  DDRD  |= B11111100;
  PORTD &= B00000011;
  DDRC |= B00110000;
  PORTC&= B11001111;

  // all orange OUTPUT LOW
  DDRB  = B11111111;
  PORTB = B00000000;

  pinMode(14, OUTPUT);

}

void Hachibar::displayOff(){
  // all blue OUTPUT LOW
  DDRD  |= B11111100;
  PORTD &= B00000011;
  DDRC |= B00110000;
  PORTC&= B11001111;

  // all orange OUTPUT LOW
  DDRB  |= B11111111;
  PORTB |= B00000000;
}
void Hachibar::displayZ(){
  // all blue INPUT Z
  DDRD  &= B00000011;
  PORTD &= B00000011;
  DDRC &= B11001111;
  PORTC&= B11001111;
  // all orange INPUT Z
  DDRB  &= B00000000; // INPUT
  PORTB &= B00000000; // Z
}

void Hachibar::orangeSelect(byte n){
  DDRB  = (1 << n); // OUTPUT
  PORTB = (1 << n); // HIGH
}
void Hachibar::orangeWrite(byte n){
  DDRB = ~n; // OUTPUT + HIGH or INPUT
  PORTB = n;
}

void Hachibar::blueSelect(byte n){
  if(n >= 2){
    DDRD  = (1 << n) | (DDRD & B00000011); // OUTPUT
    PORTD = (1 << n) | (PORTD & B00000011); // HIGH
  }else{
    DDRC = (1 << (n + 4)) | (DDRC & B11001111);
    PORTC = (1 << (n + 4)) | (PORTC & B11001111);
  }
}
void Hachibar::blueWrite(byte n){
  DDRD  = ~(n & B11111100) | (DDRD & B00000011);
  PORTD = (n & B11111100) | (PORTD & B00000011);
  DDRC  = ~((n & B00000011) << 4) | (DDRC & B11001111);
  PORTC = ((n & B00000011) << 4) | (PORTC & B11001111);
}

void Hachibar::setFont(HachibarFont* f){
  font = f->font;
  fontWidth = f->width;
}

void Hachibar::drawChar(char c, int x, int y){
  for(byte i = 0; i < fontWidth; i ++){
    byte tmp = pgm_read_byte(font+ (c - ' ')*fontWidth + i);
    for(byte j = 0; j < 8; j ++){
      if(tmp & 1){
        rect(true, x + i, y + j, 1, 1);
      }
      tmp = tmp >> 1;
    }
  }
}

void Hachibar::drawString(char *str, int x, int y){
  int len = strlen(str);
  int stringWidth = len * fontWidth;
  int pos = 0;
  while(str[pos]){
    int px = x + pos*(fontWidth+1) + stringWidth;
    if(px < 0){
      px = (8 + stringWidth) - (-px)%(8 + stringWidth);
    }else{
      px = px%(8 + stringWidth);
    }
    px -= stringWidth;
    drawChar(str[pos], px, y);
    pos++;
  }
}

void Hachibar::updateKey(){
    DDRB = 0B01000000; // PB6 is output
    PORTB = 0B10111111; // PB6 low, PB0 pull-up

    if(trigger[BTN_LEFT] < 0){trigger[BTN_LEFT] ++;}
    if(trigger[BTN_RIGHT] < 0){trigger[BTN_RIGHT] ++;}
    if(trigger[BTN_UP] < 0){trigger[BTN_UP] ++;}
    if(trigger[BTN_DOWN] < 0){trigger[BTN_DOWN] ++;}
    // above if is importat for scan timing.
    byte in = PINB;

    if((in | 0B11111110) == 0B11111110){ // PB6 is LOW
      trigger[BTN_LEFT] ++;
    }else{
      trigger[BTN_LEFT] = -1;
    }

    if((in | 0B11111101) == 0B11111101){ // PB6 is LOW
      trigger[BTN_RIGHT] ++;
    }else{
      trigger[BTN_RIGHT] = -1;
    }

    if((in | 0B11111011) == 0B11111011){ // PB6 is LOW
      trigger[BTN_UP] ++;
    }else{
      trigger[BTN_UP] = -1;
    }

    if((in | 0B11110111) == 0B11110111){ // PB6 is LOW
      trigger[BTN_DOWN] ++;
    }else{
      trigger[BTN_DOWN] = -1;
    }

    DDRB = 0B10000000; // PB7 is output
    PORTB = 0B01111111; // PB7 low, PB0 pull-up

    if(trigger[BTN_A] < 0){trigger[BTN_A] ++;}
    if(trigger[BTN_B] < 0){trigger[BTN_B] ++;}
    // above if is importat for scan timing.
    in = PINB;

    if((in | 0B11111110) == 0B11111110){
      trigger[BTN_A] ++;
    }else{
      trigger[BTN_A] = -1;
    }

    if((in | 0B11111101) == 0B11111101){
      trigger[BTN_B] ++;
    }else{
      trigger[BTN_B] = -1;
    }
}

int count8bit(byte v) {
    unsigned char count = (v & 0x55) + ((v >> 1) & 0x55);
    count = (count & 0x33) + ((count >> 2) & 0x33);
    return (count & 0x0f) + ((count >> 4) & 0x0f);
}

void Hachibar::updateDisplay(){
  int c;
  int w = 0;
  // down
  for(int i = 0; i <= 7; i ++){
    displayZ();
    delayMicroseconds(370 -w);
    blueWrite(buf[7 - i + 8]);
    orangeSelect(i);
    c = 8-count8bit(buf[7 - i + 8]);
    w = 50 + 5*c*c;
    delayMicroseconds(w); // 50 + 5*8*8 = 370
  }
  // up
  for(int i = 0; i <= 7; i ++){
    displayZ();
    delayMicroseconds(370 -w);
    orangeWrite(buf[7 - i]);
    blueSelect(i);
    c = 8-count8bit(buf[7 - i]);
    w = 50 + 5*c*c;
    delayMicroseconds(w);
  }
  displayZ();
}

bool Hachibar::nextFrame(){
  long now = millis();
  bool ret;
  if(now > nextFrameStart){
    nextFrameStart = now + 1000/30; // 30 FPS
    ret = true;
  }else{
    ret = false;
  }
  return ret;
}

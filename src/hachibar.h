#include <Arduino.h>

#ifndef __HACHIBAR__
#define __HACHIBAR__

struct HachibarFont {
  byte width;
  const unsigned char *font;
};

class Hachibar{
  public:
  int trigger[6] = {0,0,0,0,0,0};
  long nextFrameStart = 0;
  unsigned char *font;
  byte fontWidth = 4;
  byte buf[16] = {
      B00000000,
      B01111110,
      B01111110,
      B01111110,
      B01111110,
      B01111110,
      B01111110,
      B01111110,

      B01111110,
      B01111110,
      B01111110,
      B01111110,
      B01111110,
      B01111110,
      B01111110,
      B00000000
  };

  const int BTN_LEFT = 0;
  const int BTN_RIGHT = 1;
  const int BTN_UP = 2;
  const int BTN_DOWN = 3;
  const int BTN_A = 4;
  const int BTN_B = 5;

  Hachibar();

  void pset(bool b,int x, int y);
  void rect(bool b, int x, int y, byte w, byte h);
  void init();
  void setFont(HachibarFont* f);
  void drawChar(char c, int x, int y);
  void drawString(char *str, int x, int y);

  void updateKey();
  void updateDisplay();
  bool nextFrame();

  private:
  void displayOff();
  void displayZ();
  void orangeSelect(byte n);
  void orangeWrite(byte n);
  void blueSelect(byte n);
  void blueWrite(byte n);
};
#endif

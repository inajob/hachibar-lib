#include <avr/io.h>
#include <avr/pgmspace.h>
#include "hachibar.h"

const unsigned char hachibar_sfont_data[] PROGMEM = {
0x00,0x00,0x00,  // space
0x00,0x17,0x00,  // exclam
0x03,0x00,0x03,  // quotedbl
0x1f,0x0a,0x1f,  // numbersign
0x16,0x37,0x1a,  // dollar
0x09,0x04,0x12,  // percent
0x0a,0x15,0x0a,  // ampersand
0x00,0x03,0x00,  // quotesingle
0x00,0x1e,0x21,  // parenleft
0x21,0x1e,0x00,  // parenright
0x15,0x0e,0x15,  // asterisk
0x04,0x1f,0x04,  // plus
0x20,0x10,0x00,  // comma
0x04,0x04,0x04,  // hyphen
0x00,0x10,0x00,  // period
0x18,0x04,0x03,  // slash
0x0e,0x15,0x0e,  // zero
0x12,0x1f,0x10,  // one
0x12,0x19,0x16,  // two
0x11,0x15,0x0b,  // three
0x07,0x04,0x1f,  // four
0x17,0x15,0x09,  // five
0x0e,0x15,0x09,  // six
0x19,0x05,0x03,  // seven
0x1a,0x15,0x0b,  // eight
0x12,0x15,0x0e,  // nine
0x00,0x12,0x00,  // colon
0x20,0x12,0x00,  // semicolon
0x04,0x0a,0x11,  // less
0x0a,0x0a,0x0a,  // equal
0x11,0x0a,0x04,  // greater
0x01,0x15,0x02,  // question
0x0e,0x11,0x17,  // at
0x1e,0x05,0x1e,  // A
0x1f,0x15,0x0a,  // B
0x0e,0x11,0x0a,  // C
0x1f,0x11,0x0e,  // D
0x1f,0x15,0x11,  // E
0x1f,0x05,0x01,  // F
0x0e,0x11,0x1d,  // G
0x1f,0x04,0x1f,  // H
0x11,0x1f,0x11,  // I
0x08,0x10,0x0f,  // J
0x1f,0x04,0x1b,  // K
0x1f,0x10,0x10,  // L
0x1f,0x06,0x1f,  // M
0x1e,0x04,0x0f,  // N
0x0e,0x11,0x0e,  // O
0x1f,0x05,0x02,  // P
0x0e,0x11,0x2e,  // Q
0x1f,0x05,0x1a,  // R
0x12,0x15,0x09,  // S
0x01,0x1f,0x01,  // T
0x1f,0x10,0x1f,  // U
0x0f,0x18,0x0f,  // V
0x1f,0x0c,0x1f,  // W
0x1b,0x04,0x1b,  // X
0x03,0x1c,0x03,  // Y
0x19,0x15,0x13,  // Z
0x00,0x1f,0x11,  // bracketleft
0x03,0x04,0x18,  // backslash
0x11,0x1f,0x00,  // bracketright
0x02,0x01,0x02,  // asciicircum
0x20,0x20,0x20,  // underscore
0x00,0x01,0x02,  // grave
0x0c,0x12,0x1e,  // a
0x1f,0x12,0x0c,  // b
0x0c,0x12,0x12,  // c
0x0c,0x12,0x1f,  // d
0x0c,0x1a,0x14,  // e
0x04,0x1e,0x05,  // f
0x24,0x2a,0x1e,  // g
0x1f,0x02,0x1c,  // h
0x14,0x1d,0x10,  // i
0x20,0x20,0x1d,  // j
0x1f,0x04,0x1a,  // k
0x11,0x1f,0x10,  // l
0x1e,0x04,0x1e,  // m
0x1e,0x02,0x1c,  // n
0x0c,0x12,0x0c,  // o
0x3e,0x0a,0x04,  // p
0x0c,0x12,0x3e,  // q
0x1e,0x04,0x02,  // r
0x14,0x16,0x0a,  // s
0x02,0x0f,0x12,  // t
0x0e,0x10,0x1e,  // u
0x0e,0x10,0x0e,  // v
0x1e,0x08,0x1e,  // w
0x12,0x0c,0x12,  // x
0x26,0x28,0x1e,  // y
0x12,0x1a,0x16,  // z
0x04,0x1e,0x21,  // braceleft
0x00,0x1f,0x00,  // bar
0x21,0x1e,0x04,  // braceright
0x02,0x01,0x02  // asciitilde
};

struct HachibarFont hachibar_sfont = {3, hachibar_sfont_data};

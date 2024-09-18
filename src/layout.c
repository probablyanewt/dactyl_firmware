#include <keys.h>
#include <stdint.h>

#define COLUMN1 {KEY_GRAVE, KEY_TAB, KEY_ESC, KEY_LEFTSHIFT, KEY_LEFTCTRL, KEY_NONE}
#define COLUMN2 {KEY_1, KEY_Q, KEY_A, KEY_Z, KEY_LEFTALT, KEY_ENTER}
#define COLUMN3 {KEY_2, KEY_W, KEY_S, KEY_X, KEY_BACKSLASH, KEY_SPACE}
#define COLUMN4 {KEY_3, KEY_E, KEY_D, KEY_C, KEY_NONE, KEY_LEFTSHIFT}
#define COLUMN5 {KEY_4, KEY_R, KEY_F, KEY_V, KEY_NONE, KEY_LEFTCTRL}
#define COLUMN6 {KEY_5, KEY_T, KEY_G, KEY_B, KEY_LEFTALT, KEY_LEFTMETA}

#define COLUMN7 {KEY_6, KEY_Y, KEY_H, KEY_N, KEY_NONE, KEY_NONE}
#define COLUMN8 {KEY_7, KEY_U, KEY_J, KEY_M, KEY_NONE, KEY_LEFTCTRL}
#define COLUMN9 {KEY_8, KEY_I, KEY_K, KEY_COMMA, KEY_NONE, KEY_LEFTSHIFT}
#define COLUMN10 {KEY_9, KEY_O, KEY_L, KEY_DOT, KEY_NONE, KEY_SPACE}
#define COLUMN11                                                               \
  {KEY_0, KEY_P, KEY_SEMICOLON, KEY_LEFTBRACE, KEY_APOSTROPHE, KEY_BACKSPACE}
#define COLUMN12                                                               \
  {KEY_MINUS, KEY_EQUAL, KEY_SLASH, KEY_RIGHTBRACE, KEY_SLASH, KEY_NONE} 

#define BASE_LAYOUT                                                            \
  {COLUMN1, COLUMN2, COLUMN3, COLUMN4,  COLUMN5,  COLUMN6,                     \
   COLUMN7, COLUMN8, COLUMN9, COLUMN10, COLUMN11, COLUMN12}

#define COLUMN7_1 {KEY_6, KEY_Y, KEY_LEFT, KEY_N, KEY_NONE, KEY_NONE}
#define COLUMN8_1 {KEY_7, KEY_U, KEY_DOWN, KEY_M, KEY_NONE, KEY_LEFTCTRL}
#define COLUMN9_1 {KEY_8, KEY_I, KEY_UP, KEY_COMMA, KEY_NONE, KEY_LEFTSHIFT}
#define COLUMN10_1 {KEY_9, KEY_O, KEY_RIGHT, KEY_DOT, KEY_NONE, KEY_SPACE}
#define LAYOUT_1                                                               \
  {COLUMN1,   COLUMN2,   COLUMN3,   COLUMN4,    COLUMN5,  COLUMN6,             \
   COLUMN7_1, COLUMN8_1, COLUMN9_1, COLUMN10_1, COLUMN11, COLUMN12}

static const uint16_t main_layout[12][6] = BASE_LAYOUT;
static const uint16_t layout1[12][6] = LAYOUT_1;

void layout_keycodes_from_keystate(int keystate[12][6], uint8_t keycodes[6],
                                   uint8_t *modifiers) {
  const uint16_t(*layout)[12][6] = &main_layout;
  if (keystate[6][4] == 1) {
    layout = &layout1;
  }

  int column, row, keys_pressed = 0;
  for (column = 0; column < 12; column++) {
    for (row = 0; row < 6; row++) {

      if (keystate[column][row] == 0) {
        continue;
      }

      uint16_t key = (*layout)[column][row];

      if (key == KEY_NONE) {
        continue;
      }

      uint8_t base = key & 0x00FF;
      uint8_t modifier = (key >> 8) & 0x00FF;

      *modifiers = *modifiers | modifier;

      if (keys_pressed == 6) {
        continue;
      }

      keycodes[keys_pressed] = base;
      keys_pressed += 1;
    }
  }
}

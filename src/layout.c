#include <keys.h>
#include <stdint.h>

// May want to use uint16_t and use the first byte for modifiers
#define COLUMN1 {KEY_GRAVE, KEY_TAB, KEY_ESC, KEY_BACKSLASH, KEY_NONE, KEY_NONE}
#define COLUMN2 {KEY_1, KEY_Q, KEY_A, KEY_Z, KEY_NONE, KEY_BACKSPACE}
#define COLUMN3 {KEY_2, KEY_W, KEY_S, KEY_X, KEY_NONE, KEY_SPACE}
#define COLUMN4 {KEY_3, KEY_E, KEY_D, KEY_C, KEY_NONE, KEY_LEFTSHIFT}
#define COLUMN5 {KEY_4, KEY_R, KEY_F, KEY_V, KEY_NONE, KEY_LEFTCTRL}
#define COLUMN6 {KEY_5, KEY_T, KEY_G, KEY_B, KEY_LEFTALT, KEY_LEFTMETA}

#define COLUMN7 {KEY_6, KEY_Y, KEY_H, KEY_N, KEY_LEFTALT, KEY_LEFTMETA}
#define COLUMN8 {KEY_7, KEY_U, KEY_J, KEY_M, KEY_NONE, KEY_LEFTCTRL}
#define COLUMN9 {KEY_8, KEY_I, KEY_K, KEY_COMMA, KEY_NONE, KEY_LEFTSHIFT}
#define COLUMN10 {KEY_9, KEY_O, KEY_L, KEY_DOT, KEY_NONE, KEY_SPACE}
#define COLUMN11                                                               \
  {KEY_0, KEY_P, KEY_SEMICOLON, KEY_LEFTBRACE, KEY_NONE, KEY_ENTER}
#define COLUMN12                                                               \
  {KEY_MINUS, KEY_EQUAL, KEY_NONE, KEY_RIGHTBRACE, KEY_NONE, KEY_NONE}

static const uint8_t main_layout[12][6] = {
    COLUMN1, COLUMN2, COLUMN3, COLUMN4,  COLUMN5,  COLUMN6,
    COLUMN7, COLUMN8, COLUMN9, COLUMN10, COLUMN11, COLUMN12};

void set_modifier(uint8_t *modifiers, uint8_t key) {
  switch (key) {
  case KEY_LEFTCTRL:
    *modifiers = *modifiers | 1;
    break;
  case KEY_LEFTSHIFT:
    *modifiers = *modifiers | 2;
    break;
  case KEY_LEFTALT:
    *modifiers = *modifiers | 4;
    break;
  case KEY_LEFTMETA:
    *modifiers = *modifiers | 8;
    break;
  default:
    break;
  }
}

void layout_keycodes_from_keystate(int keystate[12][6], uint8_t keycodes[6],
                                   uint8_t *modifiers) {
  int column, row, keys_pressed = 0;
  for (column = 0; column < 12; column++) {
    for (row = 0; row < 6; row++) {

      int is_pressed = keystate[column][row];
      if (is_pressed == 0) {
        continue;
      }

      uint8_t key = main_layout[column][row];

      if (key == KEY_LEFTSHIFT || key == KEY_LEFTCTRL || key == KEY_LEFTALT ||
          key == KEY_LEFTMETA) {
        set_modifier(modifiers, key);
        continue;
      }

      if (keys_pressed == 6) {
        continue;
      }

      keycodes[keys_pressed] = key;
      keys_pressed += 1;
    }
  }
}

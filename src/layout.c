#include "constants.h"
#include "keymaps/keys.h"
#include "keymaps/map_1.h"
#include "keystate.h"
#include <pactf.h>
#include <stdint.h>

void keycodes_from_layer(uint8_t layer, keystate keystate,
                         uint16_t keycodes[KEYS_BUFFER_SIZE]) {
  int i;
  for (i = 0; i < keystate.len; i++) {
    uint8_t column = keystate_key_to_column(keystate.keys[i]);
    uint8_t row = keystate_key_to_row(keystate.keys[i]);
    keycodes[i] = map_1[layer][row][column];
  }
}

uint8_t calculate_layer(uint16_t keycodes[KEYS_BUFFER_SIZE]) {
  uint16_t sum = 0x0000;
  int i;
  for (i = 0; i < KEYS_BUFFER_SIZE; i++) {
    sum = sum | keycodes[i];
  }
  return (sum >> 12) & 0x000F;
}

uint8_t calculate_modifier(uint16_t keycodes[KEYS_BUFFER_SIZE]) {
  uint16_t sum = 0x0000;
  int i;
  for (i = 0; i < KEYS_BUFFER_SIZE; i++) {
    sum = sum | keycodes[i];
  }
  return (sum >> 8) & 0x000F;
}

void get_max_consecutive_keycodes(uint16_t keycodes_buf[KEYS_BUFFER_SIZE],
                                  uint8_t keycodes[MAX_CONSECUTIVE_KEYS]) {
  int i, keys_pressed = 0;
  for (i = 0; i < KEYS_BUFFER_SIZE; i++) {
    uint8_t keycode = keycodes_buf[i];

    if (keycode == K_NK) {
      continue;
    }

    if (keys_pressed == MAX_CONSECUTIVE_KEYS) {
      return;
    }

    keycodes[keys_pressed] = keycode & 0xFF;
    keys_pressed++;
  }
}

void layout_keycodes_from_keystate(uint8_t keycodes[MAX_CONSECUTIVE_KEYS],
                                   uint8_t *modifiers) {
  keystate keystate = keystate_get();
  uint16_t keycodes_buf[KEYS_BUFFER_SIZE] = {0};
  keycodes_from_layer(0, keystate, keycodes_buf);

  uint8_t layer = calculate_layer(keycodes_buf);

  if (layer > KEYMAP_LAYERS) {
    return;
  }

  if (layer != 0) {
    keycodes_from_layer(layer, keystate, keycodes_buf);
  }

  *modifiers = calculate_modifier(keycodes_buf);
  get_max_consecutive_keycodes(keycodes_buf, keycodes);
}

PACTF_SETUP(

    keystate keystate_get() { return (keystate){}; };
    uint8_t keystate_key_to_column(key key) { return 0; };
    uint8_t keystate_key_to_row(key key) { return 0; };
    uint16_t keycodes_buf[KEYS_BUFFER_SIZE] = {K_NK, K_NK, K_NK, K_NK, K_NK,
                                               K_NK, K_NK, K_NK, KB_L1, K_SHIFT,
                                               K_RBRACE, K_A};

);

PACTF_SUITE({
  P_FUNCTION("calculate_layer", {
    P_TEST(
        "it should correctly sum and return first four bits of a uint16 array",
        P_ASSERT(calculate_layer(keycodes_buf) == 0x1););
  });

  P_FUNCTION("calculate_modifier", {
    P_TEST(
        "it should correctly sum and return second four bits of a uint16 array",
        P_ASSERT(calculate_modifier(keycodes_buf) == 0x2););
  });

  P_FUNCTION("get_max_consecutive_keycodes", {
    P_TEST("it should reduce the keycodes_buf into the maximum supported "
           "number of keycodes",
           {
             uint8_t keycodes[MAX_CONSECUTIVE_KEYS] = {0};
             get_max_consecutive_keycodes(keycodes_buf, keycodes);
             P_ASSERT(keycodes[0] == 0x30);
             P_ASSERT(keycodes[1] == 0x04);
           });
  });
});

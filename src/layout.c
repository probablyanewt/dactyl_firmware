#include <constants.h>
#include <keymaps/keys.h>
#include <keymaps/map_1.h>
#include <keystate.h>
#include <stdint.h>

uint16_t keycode_from_layer(uint8_t layer, key key) {
  uint8_t column, row;
  keystate_key_to_matrix_indices(key, &column, &row);
  return map_1[layer][row][column];
}

uint8_t calculate_layer() {
  uint16_t sum = 0x0000;
  int i;
  for (i = 0; i < keystate.len; i++) {
    sum = sum | keycode_from_layer(0, keystate.keys[i]);
  }
  return (sum >> 12) & 0x000F;
}

void layout_keycodes_from_keystate(uint8_t keycodes[MAX_CONSECUTIVE_KEYS],
                                   uint8_t *modifiers) {
  uint8_t layer = calculate_layer();

  if (layer > KEYMAP_LAYERS) {
    return;
  }

  int i, keys_pressed = 0;
  for (i = 0; i < KEYS_BUFFER_SIZE; i++) {
    uint16_t keycode = keycode_from_layer(layer, keystate.keys[i]);

    if (keycode == K_NK) {
      continue;
    }

    *modifiers = *modifiers | ((keycode >> 8) & 0x000F);

    if (keys_pressed == MAX_CONSECUTIVE_KEYS) {
      continue;
    }

    keycodes[i] = keycode & 0x00FF;
    keys_pressed++;
  }
}

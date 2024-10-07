#include "keystate.h"
#include <pactf.h>
#include <stdint.h>
#include <string.h>

static keystate _keystate = {.len = 0, .keys = {}};

key matrix_indices_to_key(uint8_t column, uint8_t row) {
  return (uint8_t)(((column << 4) & 0xF0) | row);
}

void keystate_register_key(uint8_t column, uint8_t row) {
  if (_keystate.len >= KEYS_BUFFER_SIZE) {
    return;
  }
  _keystate.keys[_keystate.len] = matrix_indices_to_key(column, row);
  _keystate.len++;
}

void keystate_reset() {
  memset(_keystate.keys, 0, KEYS_BUFFER_SIZE);
  _keystate.len = 0;
}

keystate keystate_get() { return _keystate; }

uint8_t keystate_key_to_column(key key) { return (key >> 4) & 0x0F; }

uint8_t keystate_key_to_row(key key) { return key & 0x0F; }

PACTF_SETUP(

    P_BEFORE_EACH(keystate_reset(););

);

PACTF_SUITE({
  P_FUNCTION("matrix_indices_to_key", {
    P_TEST("it should combine the column and row value into a single byte",
           P_ASSERT(matrix_indices_to_key(0x04, 0x03) == 0x43));
  });

  P_FUNCTION("keystate_register_key", {
    P_TEST("it should set _keystate.keys[_keystate.len] and increment "
           "_keystate.len",
           {
             keystate_register_key(1, 1);
             P_ASSERT(_keystate.len == 1);
             P_ASSERT(_keystate.keys[0] == 0x11);
           });

    P_TEST("it should do nothing if _keystate.len == KEYS_BUFFER_SIZE", {
      int i;
      for (i = 0; i < KEYS_BUFFER_SIZE; i++) {
        keystate_register_key(i, i);
      }
      keystate_register_key(1, 1);
      P_ASSERT(_keystate.len == KEYS_BUFFER_SIZE);
      P_ASSERT(_keystate.keys[KEYS_BUFFER_SIZE - 1] != 0x11);
    });
  });

  P_FUNCTION("keystate_reset", {
    P_TEST("it should set _keystate.keys to all 0, and _keystate.len to 0", {
      _keystate.len = 3;
      _keystate.keys[0] = 0x12;
      _keystate.keys[1] = 0x23;
      keystate_reset();
      P_ASSERT(_keystate.len == 0);
      P_ASSERT(_keystate.keys[0] == 0);
      P_ASSERT(_keystate.keys[1] == 0);
    });
  });

  P_FUNCTION("keystate_key_to_column", {
    P_TEST("it should convert key byte into a column byte",
           P_ASSERT(keystate_key_to_column(0x43) == 0x04));
  });

  P_FUNCTION("keystate_key_to_row", {
    P_TEST("it should convert key byte into a row byte",
           P_ASSERT(keystate_key_to_row(0x43) == 0x03));
  });
})

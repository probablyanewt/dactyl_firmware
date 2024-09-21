#include <keystate.h>
#include <stdint.h>
#include <string.h>

key matrix_indices_to_key(uint8_t column,uint8_t row){
 return (uint8_t)(((column << 4) & 0xF0) | row);
}

void keystate_register_key(uint8_t column, uint8_t row) {
  if (keystate.len >= MAX_KEYS_BUFFER_SIZE) {
    return;
  }
  keystate.keys[keystate.len] = matrix_indices_to_key(column,row);
  keystate.len += 1;
}

void keystate_reset() {
  memset(keystate.keys, 0, MAX_KEYS_BUFFER_SIZE);
  keystate.len = 0;
}

void keystate_key_to_matrix_indices(key key, uint8_t *column, uint8_t *row){
  *column=(key>>4)&0x0F;
  *row=key&0x0F;
}

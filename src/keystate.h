#include <stdint.h>

#define KEYS_BUFFER_SIZE 12

// First four bits represent the column index, second four bits represent the row index
typedef uint8_t key;

typedef struct {
  uint8_t len;
  key keys[KEYS_BUFFER_SIZE];
} keystate;

void keystate_register_key(uint8_t column, uint8_t row);

void keystate_reset();

keystate keystate_get();

uint8_t keystate_key_to_column(key key);

uint8_t keystate_key_to_row(key key);

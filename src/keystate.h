#include <stdint.h>

#define KEYS_BUFFER_SIZE 12

// First four bits represent the column index, second four bits represent the row index
typedef uint8_t key;

struct keystate {
  uint8_t len;
  key keys[KEYS_BUFFER_SIZE];
};

static struct keystate keystate = {.len = 0, .keys = {}};

void keystate_register_key(uint8_t column, uint8_t row);

void keystate_reset();

void keystate_key_to_matrix_indices(key key, uint8_t *column, uint8_t *row);

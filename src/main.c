#include <drivers/gpio.h>
#include <keyboard.h>
#include <layout.h>
#include <matrix.h>
#include <zephyr.h>

#define MAIN_LOOP_DELAY K_USEC(500)

int main(void) {
  matrix_init();

  while (1) {
    int keystate[12][6] = {{0}};
    matrix_scan(keystate);

    uint8_t keycodes[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t modifiers = 0x00;
    layout_keycodes_from_keystate(keystate, keycodes, &modifiers);

    keyboard_send(keycodes, modifiers);

    k_sleep(MAIN_LOOP_DELAY);
  }
}

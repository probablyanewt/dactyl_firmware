#include <constants.h>
#include <drivers/gpio.h>
#include <keyboard.h>
#include <keystate.h>
#include <layout.h>
#include <matrix.h>
#include <sys/reboot.h>
#include <zephyr.h>

#define MAIN_LOOP_DELAY K_USEC(500)

int main(void) {
  matrix_init();

  while (1) {
    keystate_reset();
    matrix_scan();

    uint8_t keycodes[MAX_CONSECUTIVE_KEYS] = {0x00, 0x00, 0x00,
                                              0x00, 0x00, 0x00};
    uint8_t modifiers = 0x00;
    layout_keycodes_from_keystate(keycodes, &modifiers);

    keyboard_send(keycodes, modifiers);

    k_sleep(MAIN_LOOP_DELAY);
  }
}

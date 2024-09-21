#include <drivers/gpio.h>
#include <keyboard.h>
#include <layout.h>
#include <matrix.h>
#include <sys/reboot.h>
#include <zephyr.h>
#include <keystate.h>

#define MAIN_LOOP_DELAY K_USEC(500)
void k_sys_fatal_error_handler(unsigned int reason, const z_arch_esf_t *esf) {
  sys_reboot(SYS_REBOOT_WARM);
}
int main(void) {
  matrix_init();

  while (1) {
    keystate_reset();
    matrix_scan();

    uint8_t keycodes[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t modifiers = 0x00;
    layout_keycodes_from_keystate(keycodes, &modifiers);

    keyboard_send(keycodes, modifiers);

    k_sleep(MAIN_LOOP_DELAY);
  }
}

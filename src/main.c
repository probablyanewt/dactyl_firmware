#include <drivers/gpio.h>
#include <keyboard.h>
#include <layout.h>
#include <matrix.h>
#include <zephyr.h>

#define MAIN_LOOP_DELAY K_USEC(500)
#define LED0_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void) {
  gpio_pin_configure_dt(&led, GPIO_OUTPUT_LOW);

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

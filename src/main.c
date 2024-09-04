#include <drivers/gpio.h>
#include <dt-bindings/gpio/gpio.h>
#include <zephyr.h>

#define LED0_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void main(void) {
  gpio_pin_configure_dt(&led, GPIO_OUTPUT_HIGH);

  while (1) {
    gpio_pin_toggle_dt(&led);

    k_sleep(K_MSEC(2000));
  }
}

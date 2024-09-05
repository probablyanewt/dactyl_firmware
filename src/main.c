#include <drivers/gpio.h>
#include <drivers/uart.h>
#include <usb/usb_device.h>
#include <zephyr.h>

#define LED0_NODE DT_ALIAS(led0)
#define ZEPHYR_CONSOLE DT_CHOSEN(zephyr_console)

BUILD_ASSERT(DT_NODE_HAS_COMPAT(ZEPHYR_CONSOLE, zephyr_cdc_acm_uart),
             "Console device is not ACM CDC UART device");

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
const struct device *const uart = DEVICE_DT_GET(ZEPHYR_CONSOLE);

void print_uart(char *buf) {
  int msg_len = strlen(buf);

  for (int i = 0; i < msg_len; i++) {
    uart_poll_out(uart, buf[i]);
  }
}

void main(void) {
  gpio_pin_configure_dt(&led, GPIO_OUTPUT_HIGH);
  usb_enable(NULL);

  while (1) {
    print_uart("Hello world\n\r");
    gpio_pin_toggle_dt(&led);

    k_sleep(K_SECONDS(2));
  }
}

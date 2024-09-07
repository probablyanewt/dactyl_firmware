#include <devicetree.h>
#include <device.h>
#include <drivers/gpio.h>
#include <drivers/uart.h>
#include <stdio.h>
#include <stdlib.h>
#include <usb/usb_device.h>
#include <zephyr.h>

#define LED0_NODE DT_ALIAS(led0)
#define ZEPHYR_CONSOLE DT_CHOSEN(zephyr_console)
#define COLUMN1 DT_ALIAS(column1)
#define COLUMN2 DT_ALIAS(column2)
#define ROW1 DT_ALIAS(row1)

BUILD_ASSERT(DT_NODE_HAS_COMPAT(ZEPHYR_CONSOLE, zephyr_cdc_acm_uart),
             "Console device is not ACM CDC UART device");

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
const struct device *const uart = DEVICE_DT_GET(ZEPHYR_CONSOLE);
static const struct gpio_dt_spec column1 = GPIO_DT_SPEC_GET(COLUMN1, gpios);
static const struct gpio_dt_spec column2 = GPIO_DT_SPEC_GET(COLUMN2, gpios);
static const struct gpio_dt_spec row1 = GPIO_DT_SPEC_GET(ROW1, gpios);

void print_uart(char *buf) {
  int msg_len = strlen(buf);

  for (int i = 0; i < msg_len; i++) {
    uart_poll_out(uart, buf[i]);
  }
}

void main(void) {
  usb_enable(NULL);

  gpio_pin_configure_dt(&led, GPIO_OUTPUT_LOW);
  gpio_pin_configure_dt(&column1, GPIO_OUTPUT_LOW);
  gpio_pin_configure_dt(&column2, GPIO_OUTPUT_LOW);
  gpio_pin_configure_dt(&row1, GPIO_INPUT | GPIO_PULL_DOWN);


  gpio_pin_set_dt(&column1, 1);
  

  while (1) {
    int val = gpio_pin_get_dt(&row1);
 
    gpio_pin_set_dt(&led, val);
    k_sleep(K_MSEC(20));
  }
}

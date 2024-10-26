#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <drivers/i2c.h>
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
#define RHS DT_ALIAS(rhs)

BUILD_ASSERT(DT_NODE_HAS_COMPAT(ZEPHYR_CONSOLE, zephyr_cdc_acm_uart),
             "Console device is not ACM CDC UART device");

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
const struct device *const uart = DEVICE_DT_GET(ZEPHYR_CONSOLE);
static const struct i2c_dt_spec rhs = I2C_DT_SPEC_GET(RHS);
static const struct gpio_dt_spec column1 = GPIO_DT_SPEC_GET(COLUMN1, gpios);
static const struct gpio_dt_spec column2 = GPIO_DT_SPEC_GET(COLUMN2, gpios);
static const struct gpio_dt_spec row1 = GPIO_DT_SPEC_GET(ROW1, gpios);
static const uint8_t rhs_column_1[2] = {0xFE, 0xFF};
static const uint8_t rhs_no_column[2] = {0xFF, 0xFF};

void print_uart(char *buf) {
  int msg_len = strlen(buf);

  for (int i = 0; i < msg_len; i++) {
    uart_poll_out(uart, buf[i]);
  }
}

int main(void) {
  usb_enable(NULL);

  gpio_pin_configure_dt(&led, GPIO_OUTPUT_LOW);
  gpio_pin_configure_dt(&column1, GPIO_OUTPUT_LOW);
  gpio_pin_configure_dt(&column2, GPIO_OUTPUT_LOW);
  gpio_pin_configure_dt(&row1, GPIO_INPUT | GPIO_PULL_DOWN);

  if (!device_is_ready(rhs.bus)) {
    print_uart("Device not ready");
    return 0;
  }

  gpio_pin_set_dt(&led, 0);
  i2c_write_dt(&rhs, rhs_column_1, 2);
  k_sleep(K_MSEC(20));

  while (1) {
    uint8_t result[2] = {0xFF, 0xFF};
    i2c_read_dt(&rhs, result, 2);
    k_sleep(K_MSEC(20));

    // Get last bit to represent first row
    int val = result[1] & 1;
    gpio_pin_set_dt(&led, val == 0);

    // Debug logging to uart
    print_uart("\033[2J");
    char result_buf;
    sprintf(&result_buf, "%d", result[0]);
    print_uart(&result_buf);
    print_uart("\n");
    char result_buf2;
    uint8_t val2 = result[1];
    sprintf(&result_buf2, "%d", val2);
    print_uart(&result_buf2);
    k_sleep(K_MSEC(20));
  }
}

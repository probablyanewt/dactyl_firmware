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

#define COLUMN_DIR_REGISTER 0x00
#define COLUMN_DIR_CONFIG 0x00
#define COLUMNS_REGISTER 0x12

#define ROW_PULL_UP_REGISTER 0x0D
#define ROW_PULL_UP_CONFIG 0xFF
#define ROW_POLARITY_REGISTER 0x03
#define ROW_POLARITY_CONFIG 0xFF
#define ROWS_REGISTER 0x13
#define COLUMN_1 0xFE

BUILD_ASSERT(DT_NODE_HAS_COMPAT(ZEPHYR_CONSOLE, zephyr_cdc_acm_uart),
             "Console device is not ACM CDC UART device");

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
const struct device *const uart = DEVICE_DT_GET(ZEPHYR_CONSOLE);
static const struct i2c_dt_spec rhs = I2C_DT_SPEC_GET(RHS);
static const struct gpio_dt_spec column1 = GPIO_DT_SPEC_GET(COLUMN1, gpios);
static const struct gpio_dt_spec column2 = GPIO_DT_SPEC_GET(COLUMN2, gpios);
static const struct gpio_dt_spec row1 = GPIO_DT_SPEC_GET(ROW1, gpios);

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

  // Set columns as output and set first column high
  i2c_reg_write_byte_dt(&rhs, COLUMN_DIR_REGISTER, COLUMN_DIR_CONFIG);
  i2c_reg_write_byte_dt(&rhs, COLUMNS_REGISTER, COLUMN_1);

  // Enable row pullups and reverse polarity
  i2c_reg_write_byte_dt(&rhs, ROW_PULL_UP_REGISTER, ROW_PULL_UP_CONFIG);
  i2c_reg_write_byte_dt(&rhs, ROW_POLARITY_REGISTER, ROW_POLARITY_CONFIG);

  while (1) {
    uint8_t result;
    i2c_reg_read_byte_dt(&rhs, ROWS_REGISTER, &result);

    // Get last bit to represent first row
    int val = result & 1;
    gpio_pin_set_dt(&led, val);

    // Debug logging to uart
    print_uart("\033[2J");
    char result_buf;
    sprintf(&result_buf, "%d", result);
    print_uart(&result_buf);
    k_sleep(K_MSEC(20));
  }
}

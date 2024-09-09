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
#define RHS_COLUMNDIR DT_ALIAS(rhs_column_dir)
#define RHS_ROWS DT_ALIAS(rhs_rows)
#define RHS_COLUMNS DT_ALIAS(rhs_columns)
#define COLUMN1 DT_ALIAS(column1)
#define COLUMN2 DT_ALIAS(column2)
#define ROW1 DT_ALIAS(row1)

BUILD_ASSERT(DT_NODE_HAS_COMPAT(ZEPHYR_CONSOLE, zephyr_cdc_acm_uart),
             "Console device is not ACM CDC UART device");

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
const struct device *const uart = DEVICE_DT_GET(ZEPHYR_CONSOLE);
static const struct i2c_dt_spec rhs_columndir = I2C_DT_SPEC_GET(RHS_COLUMNDIR);
static const struct i2c_dt_spec rhs_rows = I2C_DT_SPEC_GET(RHS_ROWS);
static const struct i2c_dt_spec rhs_columns = I2C_DT_SPEC_GET(RHS_COLUMNS);
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


  
  if(!device_is_ready(rhs_columndir.bus)){
    print_uart("Device not ready");
    return 0;
  }

  gpio_pin_set_dt(&led, 1);
  // Set columns as output and set first column high
  // i2c_write_dt(&rhs_columndir, 0x0, 1);
  // i2c_write_dt(&rhs_columns, (uint8_t*)0x1, 1);
  i2c_reg_write_byte_dt(&rhs_columndir, 0x0U, 0x0U);
  i2c_reg_write_byte_dt(&rhs_columndir, 0x12U, 0x1U);

  while (1) {
    // int val = gpio_pin_get_dt(&row1);
    // uint8_t result;
    // i2c_reg_read_byte_dt(&rhs_columndir, 0x12, &result);

    // Get last bit to represent first row
    // int val = (result >> 8) & 1;

    // gpio_pin_set_dt(&led, val);
    // print_uart(&result);
    print_uart("Addr: ");
    print_uart(&rhs_columndir.addr);
    print_uart("\r\n");
    print_uart("Initialised: ");
    print_uart((char*)rhs_columndir.bus->state->initialized);
    k_sleep(K_MSEC(200));
    print_uart("\033[2J");
  }
}

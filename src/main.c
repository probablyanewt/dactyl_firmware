#include <device.h>
#include <devicetree.h>
#include <drivers/i2c.h>
#include <drivers/uart.h>
#include <lhs.h>
#include <stdio.h>
#include <stdlib.h>
#include <usb/usb_device.h>
#include <zephyr.h>

#define ZEPHYR_CONSOLE DT_CHOSEN(zephyr_console)
#define RHS DT_ALIAS(rhs)

#define COLUMN_DIR_REGISTER 0x00
#define COLUMN_DIR_CONFIG 0x00
#define COLUMNS_REGISTER 0x12

#define ROW_PULL_UP_REGISTER 0x0D
#define ROW_PULL_UP_CONFIG 0xFF
#define ROW_POLARITY_REGISTER 0x03
#define ROW_POLARITY_CONFIG 0xFF
#define ROWS_REGISTER 0x13
#define COLUMN_1 0x80

BUILD_ASSERT(DT_NODE_HAS_COMPAT(ZEPHYR_CONSOLE, zephyr_cdc_acm_uart),
             "Console device is not ACM CDC UART device");

const struct device *const uart = DEVICE_DT_GET(ZEPHYR_CONSOLE);
static const struct i2c_dt_spec rhs = I2C_DT_SPEC_GET(RHS);

void print_uart(char *buf) {
  int msg_len = strlen(buf);

  for (int i = 0; i < msg_len; i++) {
    uart_poll_out(uart, buf[i]);
  }
}

void keypress_print_uart(int keystate[6][6]) {
  int column, row;
  for (row = 0; row < 6; row++) {
    for (column = 0; column < 6; column++) {
      char tmp;
      sprintf(&tmp, "%d", keystate[column][row]);
      uart_poll_out(uart, tmp);
    }
    print_uart("\n\r");
  }
}

int main(void) {
  lhs_init();
  usb_enable(NULL);

  if (!device_is_ready(rhs.bus)) {
    print_uart("Device not ready");
    return 0;
  }

  // Set columns as output and set first column high
  i2c_reg_write_byte_dt(&rhs, COLUMN_DIR_REGISTER, COLUMN_DIR_CONFIG);
  i2c_reg_write_byte_dt(&rhs, COLUMNS_REGISTER, COLUMN_1);

  // Enable row pullups and reverse polarity
  i2c_reg_write_byte_dt(&rhs, ROW_PULL_UP_REGISTER, ROW_PULL_UP_CONFIG);
  i2c_reg_write_byte_dt(&rhs, ROW_POLARITY_REGISTER, ROW_POLARITY_CONFIG);

  while (1) {
    int keystate[6][6];
    lhs_scan(keystate);

    uint8_t result;
    i2c_reg_read_byte_dt(&rhs, ROWS_REGISTER, &result);

    // Debug logging to uart
    print_uart("\033[H");
    print_uart("\033[J");
    keypress_print_uart(keystate);
    k_sleep(K_MSEC(100));
  }
}

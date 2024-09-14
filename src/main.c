#include <device.h>
#include <devicetree.h>
#include <drivers/uart.h>
#include <matrix.h>
#include <stdio.h>
#include <usb/usb_device.h>
#include <zephyr.h>

#define ZEPHYR_CONSOLE DT_CHOSEN(zephyr_console)

BUILD_ASSERT(DT_NODE_HAS_COMPAT(ZEPHYR_CONSOLE, zephyr_cdc_acm_uart),
             "Console device is not ACM CDC UART device");

const struct device *const uart = DEVICE_DT_GET(ZEPHYR_CONSOLE);

void print_uart(char *buf) {
  int msg_len = strlen(buf);

  for (int i = 0; i < msg_len; i++) {
    uart_poll_out(uart, buf[i]);
  }
}

void keypress_print_uart(int keystate[12][6]) {
  int column, row;
  for (row = 0; row < 6; row++) {
    for (column = 0; column < 12; column++) {
      char tmp;
      sprintf(&tmp, "%d", keystate[column][row]);
      uart_poll_out(uart, tmp);
    }
    print_uart("\n\r");
  }
}

int main(void) {
  matrix_init();
  usb_enable(NULL);

  while (1) {
    int keystate[12][6];
    matrix_scan(keystate);

    // Debug logging to uart
    print_uart("\033[H");
    print_uart("\033[J");
    keypress_print_uart(keystate);
    k_sleep(K_MSEC(100));
  }
}

#include "constants.h"
#include <device.h>
#include <devicetree.h>
#include <drivers/i2c.h>
#include <keystate.h>
#include <sys/reboot.h>
#include <zephyr.h>

#define RHS DT_ALIAS(rhs)

#define COLUMN_1 {0xFE, 0xFF}
#define COLUMN_2 {0xFD, 0xFF}
#define COLUMN_3 {0xFB, 0xFF}
#define COLUMN_4 {0xF7, 0xFF}
#define COLUMN_5 {0xEF, 0xFF}
#define COLUMN_6 {0xDF, 0xFF}

#define ROW_POLARITY_REGISTER 0x03
#define ROW_POLARITY_CONFIG 0xFF
#define ROWS_REGISTER 0x13
#define ROW_1 0
#define ROW_2 1
#define ROW_3 2
#define ROW_4 3
#define ROW_5 4
#define ROW_6 5

#define RHS_SCAN_DELAY K_USEC(10)

static const struct i2c_dt_spec rhs = I2C_DT_SPEC_GET(RHS);
static const uint8_t no_columns[2] = {0xFF, 0xFF};
static const uint8_t columns[6][2] = {COLUMN_1, COLUMN_2, COLUMN_3,
                                      COLUMN_4, COLUMN_5, COLUMN_6};
static const uint8_t rows[6] = {ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6};

int rhs_init() {
  if (!device_is_ready(rhs.bus)) {
    return -1;
  }
  return 0;
}

void rhs_scan_rows(int column_index) {
  uint8_t result[2] = {0xFF, 0xFF};
  i2c_read_dt(&rhs, result, 2);

  int i;
  for (i = 0; i < 6; i++) {
    int row = (result[1] >> rows[i]) & 1;
    if (row == 0) {
      keystate_register_key(column_index + RHS_ROW_OFFSET, i);
    }
  }
}

void rhs_scan() {
  int i;
  for (i = 0; i < 6; i++) {
    i2c_write_dt(&rhs, columns[i], 2);
    k_sleep(RHS_SCAN_DELAY);
    rhs_scan_rows(i);
    k_sleep(RHS_SCAN_DELAY);
  }

  i2c_write_dt(&rhs, no_columns, 2);
  k_sleep(RHS_SCAN_DELAY);
}

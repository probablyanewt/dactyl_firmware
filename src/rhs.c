#include <device.h>
#include <devicetree.h>
#include <drivers/i2c.h>
#include <zephyr.h>

#define RHS DT_ALIAS(rhs)

#define COLUMN_DIR_REGISTER 0x00
#define COLUMN_DIR_CONFIG 0x00
#define COLUMNS_REGISTER 0x12
#define COLUMN_1 0x80
#define COLUMN_2 0x40
#define COLUMN_3 0x20
#define COLUMN_4 0x10
#define COLUMN_5 0x08
#define COLUMN_6 0x04
#define NO_COLUMN 0x00

#define ROW_PULL_UP_REGISTER 0x0D
#define ROW_PULL_UP_CONFIG 0xFF
#define ROW_POLARITY_REGISTER 0x03
#define ROW_POLARITY_CONFIG 0xFF
#define ROWS_REGISTER 0x13
#define ROW_1 1
#define ROW_2 2
#define ROW_3 4
#define ROW_4 8
#define ROW_5 16
#define ROW_6 32

#define RHS_SCAN_DELAY K_USEC(5)

static const struct i2c_dt_spec rhs = I2C_DT_SPEC_GET(RHS);
static const uint8_t columns[6] = {COLUMN_1, COLUMN_2, COLUMN_3,
                                   COLUMN_4, COLUMN_5, COLUMN_6};
static const uint8_t rows[6] = {ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6};

void rhs_init() {
  if (!device_is_ready(rhs.bus)) {
    return;
  }
  i2c_reg_write_byte_dt(&rhs, COLUMN_DIR_REGISTER, COLUMN_DIR_CONFIG);
  i2c_reg_write_byte_dt(&rhs, ROW_PULL_UP_REGISTER, ROW_PULL_UP_CONFIG);
  i2c_reg_write_byte_dt(&rhs, ROW_POLARITY_REGISTER, ROW_POLARITY_CONFIG);
}

void rhs_scan_rows(int column_buf[6]) {
  uint8_t result;
  i2c_reg_read_byte_dt(&rhs, ROWS_REGISTER, &result);
  int i;
  for (i = 0; i < 6; i++) {
    column_buf[i] = result & rows[i];
  }
}

void rhs_scan_column(uint8_t column, int column_buf[6]) {
  i2c_reg_write_byte_dt(&rhs, COLUMNS_REGISTER, column);
  k_sleep(RHS_SCAN_DELAY);
  rhs_scan_rows(column_buf);
}

void rhs_scan(int keystate[6][6]) {
  int i;
  for (i = 0; i < 6; i++) {
    rhs_scan_column(columns[i], keystate[i]);
  }
  i2c_reg_write_byte_dt(&rhs, COLUMNS_REGISTER, NO_COLUMN);
}

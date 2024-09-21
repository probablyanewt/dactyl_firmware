#include <device.h>
#include <devicetree.h>
#include <drivers/i2c.h>
#include <zephyr.h>
#include <sys/reboot.h>
#include <keystate.h>

#define RHS DT_ALIAS(rhs)

#define COLUMN_DIR_REGISTER 0x00
#define COLUMN_DIR_CONFIG 0x00
#define COLUMNS_REGISTER 0x12
#define COLUMN_1 0xFE
#define COLUMN_2 0xFD
#define COLUMN_3 0xFB
#define COLUMN_4 0xF7
#define COLUMN_5 0xEF
#define COLUMN_6 0xDF
#define NO_COLUMN 0xFF

#define ROW_POLARITY_REGISTER 0x03
#define ROW_POLARITY_CONFIG 0xFF
#define ROWS_REGISTER 0x13
#define ROW_1 0 
#define ROW_2 1
#define ROW_3 2
#define ROW_4 3
#define ROW_5 4
#define ROW_6 5

#define RHS_SCAN_DELAY K_USEC(5)

static const struct i2c_dt_spec rhs = I2C_DT_SPEC_GET(RHS);
static const uint8_t columns[6] = {COLUMN_1, COLUMN_2, COLUMN_3,
                                   COLUMN_4, COLUMN_5, COLUMN_6};
static const uint8_t rows[6] = {ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6};

static int error_count = 0;

void rhs_init() {
  if (!device_is_ready(rhs.bus)) {
    return;
  }
  i2c_reg_write_byte_dt(&rhs, COLUMN_DIR_REGISTER, COLUMN_DIR_CONFIG);
  i2c_reg_write_byte_dt(&rhs, ROW_POLARITY_REGISTER, ROW_POLARITY_CONFIG);
}

void rhs_scan_rows(int column_index) {
  uint8_t result;
  int err = i2c_reg_read_byte_dt(&rhs, ROWS_REGISTER, &result);
  if(err!=0){
    if(error_count >= 5){
      sys_reboot(SYS_REBOOT_WARM); 
    }
    error_count +=1;
  }
  error_count = 0;
  
  int i;
  for (i = 0; i < 6; i++) {
    int row = (result >> rows[i]) & 1;
    if(row==1){
      keystate_register_key(column_index,i);
    }
  }
}

void rhs_scan() {
  int i;
  for (i = 0; i < 6; i++) {
    i2c_reg_write_byte_dt(&rhs, COLUMNS_REGISTER, columns[i]);
    k_sleep(RHS_SCAN_DELAY);
    rhs_scan_rows(i);
  }
  i2c_reg_write_byte_dt(&rhs, COLUMNS_REGISTER, NO_COLUMN);
}


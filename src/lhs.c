#include <device.h>
#include <devicetree.h>
#include <drivers/gpio.h>
#include <keypress.h>
#include <zephyr.h>

#define COLUMN1 DT_ALIAS(column1)
#define COLUMN2 DT_ALIAS(column2)
#define COLUMN3 DT_ALIAS(column3)
#define COLUMN4 DT_ALIAS(column4)
#define COLUMN5 DT_ALIAS(column5)
#define COLUMN6 DT_ALIAS(column6)

#define ROW1 DT_ALIAS(row1)
#define ROW2 DT_ALIAS(row2)
#define ROW3 DT_ALIAS(row3)
#define ROW4 DT_ALIAS(row4)
#define ROW5 DT_ALIAS(row5)
#define ROW6 DT_ALIAS(row6)

#define LHS_SCAN_DELAY K_USEC(5)

static const struct gpio_dt_spec column1 = GPIO_DT_SPEC_GET(COLUMN1, gpios);
static const struct gpio_dt_spec column2 = GPIO_DT_SPEC_GET(COLUMN2, gpios);
static const struct gpio_dt_spec column3 = GPIO_DT_SPEC_GET(COLUMN3, gpios);
static const struct gpio_dt_spec column4 = GPIO_DT_SPEC_GET(COLUMN4, gpios);
static const struct gpio_dt_spec column5 = GPIO_DT_SPEC_GET(COLUMN5, gpios);
static const struct gpio_dt_spec column6 = GPIO_DT_SPEC_GET(COLUMN6, gpios);
static const struct gpio_dt_spec *columns[6] = {&column1, &column2, &column3,
                                                &column4, &column5, &column6};

static const struct gpio_dt_spec row1 = GPIO_DT_SPEC_GET(ROW1, gpios);
static const struct gpio_dt_spec row2 = GPIO_DT_SPEC_GET(ROW2, gpios);
static const struct gpio_dt_spec row3 = GPIO_DT_SPEC_GET(ROW3, gpios);
static const struct gpio_dt_spec row4 = GPIO_DT_SPEC_GET(ROW4, gpios);
static const struct gpio_dt_spec row5 = GPIO_DT_SPEC_GET(ROW5, gpios);
static const struct gpio_dt_spec row6 = GPIO_DT_SPEC_GET(ROW6, gpios);
static const struct gpio_dt_spec *rows[6] = {&row1, &row2, &row3,
                                             &row4, &row5, &row6};

void lhs_init() {
  int i;
  for (i = 0; i < 6; i++) {
    gpio_pin_configure_dt(columns[i], GPIO_OUTPUT_LOW);
    gpio_pin_configure_dt(rows[i], GPIO_INPUT);
  }
}

void scan_rows(int column_buf[6]) {
  int i;
  for (i = 0; i < 6; i++) {
    column_buf[i] = gpio_pin_get_dt(rows[i]);
  }
}

void scan_column(const struct gpio_dt_spec *column, int column_buf[6]) {
  gpio_pin_set_dt(column, 1);
  k_sleep(LHS_SCAN_DELAY);
  scan_rows(column_buf);
  gpio_pin_set_dt(column, 0);
}

void lhs_scan(int keystate[6][6]) {
  int i;
  for (i = 0; i < 6; i++) {
    scan_column(columns[i], keystate[i]);
  }
}

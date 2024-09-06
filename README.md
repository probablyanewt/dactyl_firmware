# Dactyl Firmware

This repo contains the firmware for my dactyl keyboard, written in C using the Zephyr RTOS.

## Pin configuration

### LHS
+-----+----------+
| Pin | Usage    |
+=====+==========+
|  0  | Column 1 |
+-----+----------+
|  1  | Column 2 |
+-----+----------+
|  2  | Column 3 |
+-----+----------+
|  3  | Column 4 |
+-----+----------+
|  4  | Column 5 |
+-----+----------+
|  5  | Column 6 |
+-----+----------+
|  6  | Row 1    |
+-----+----------+
|  7  | Row 2    |
+-----+----------+
|  8  | Row 3    |
+-----+----------+
|  9  | Row 4    |
+-----+----------+
| 10  | Row 5    |
+-----+----------+
| 11  | Row 6    |
+-----+----------+

+-----+----------+
| Pin | Usage    |
+=====+==========+
| 18  | I2C1_SDA | to RHS
+-----+----------+
| 19  | I2C1_SCL |
+-----+----------+

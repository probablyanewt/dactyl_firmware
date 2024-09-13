# Dactyl Firmware

This repo contains the firmware for my dactyl keyboard, written in C using the Zephyr RTOS.

## Pin configuration

### LHS
| Pin | Zephyr Port/Pin | Usage    |
|-----|-----------------|----------|
|  0  | GPIO1_3         | Column 1 |
|  1  | GPIO1_2         | Column 2 |
|  2  | GPIO4_4         | Column 3 |
|  3  | GPIO4_5         | Column 4 |
|  4  | GPIO4_6         | Column 5 |
|  5  | GPIO4_8         | Column 6 |
|  6  | GPIO2_10        | Row 1    |
|  7  | GPIO2_17        | Row 2    |
|  8  | GPIO2_16        | Row 3    |
|  9  | GPIO2_11        | Row 4    |
| 10  | GPIO2_0         | Row 5    |
| 11  | GPIO2_2         | Row 6    |

| Pin | Usage    | 
|-----|----------| 
| 18  | I2C1_SDA | to RHS
| 19  | I2C1_SCL | 

### RHS

| Pin | RegBit | Usage    |
|-----|--------|----------|
| 20  | GPA/0  | Column 1 |
| 21  | GPA/1  | Column 2 |
| 22  | GPA/2  | Column 3 |
| 23  | GPA/3  | Column 4 |
| 24  | GPA/4  | Column 5 |
| 25  | GPA/5  | Column 6 |
|  3  | GPB/0  | Row 1    |
|  4  | GPB/1  | Row 2    |
|  5  | GPB/2  | Row 3    |
|  6  | GPB/3  | Row 4    |
|  7  | GPB/4  | Row 5    |
|  8  | GPB/5  | Row 6    |

| Register | Hex Adress | Use                                   |
|----------|------------|---------------------------------------|
| IODIRA   | 0x00       | Set direction for GPIO pins on port A | 
| GPIOA    | 0x12       | Pins attached to the columns (output) |
| GPIOB    | 0x13       | Pins attached to the rows (input)     |

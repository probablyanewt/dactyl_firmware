# Dactyl Firmware

This repo contains the firmware for my dactyl keyboard, written in C using the Zephyr RTOS.   
![image of keyboard](https://github.com/probablyanewt/dactyl_firmware/blob/main/assets/keyboard.png?raw=true)

## The body

For the body I largely followed the instructions [here](https://github.com/adereth/dactyl-keyboard). 

## The journey

Mistakes were made during the build. I had to resolder the order I'd connected the columns to the pins on the MCP23018, all of the diodes on the right side, and debug a short. Other than that, the build stage was relatively painless. 

The firmware was a real learning curve. Initially I intended to use QMK, but my specific configuration was unsupported. I was faced with a decision to use a different soc, or build my firmware from scratch. So, naturally, I decided to write my own firmware. 

I came across ZMK during my research, but again, my use case wasn't that well supported, so I started looking at tools I had used before like PlatformIO and Arduino. I didn't really want to use C++, and fancied using C, and then I stumbled upon Zephyr when looking through PlatformIO.

After getting my dev environment setup, I faced a steep learning curve. I broke down the task into chunks and plowed on. I've created a branch after each of these milestones to serve as a reminder to myself in the future. 

`blinky` - something basic to compile and flash, just toggles the board led.  
`hello-world` - communicating with uart over usb.  
`boop` - make a single button work with gpio pins.  
`boop-rhs` - make a single button work on the rhs using i2c.  
`lhs` - complete scanning matrix on lhs.  
`matrix` - complete scanning of rhs.  
`main` - current version.  

If your goal is just to make a keyboard, just use QMK or ZMK. However, if you wish to learn C, or Zephyr  and really get to grips with how a keyboard works, then I can thoroughly recommend a project like this.  

## Pin configuration

### LHS
| Pin | Port/Pin | Usage    |
|-----|----------|----------|
|  0  | GPIO1_3  | Column 1 |
|  1  | GPIO1_2  | Column 2 |
|  2  | GPIO4_4  | Column 3 |
|  3  | GPIO4_5  | Column 4 |
|  4  | GPIO4_6  | Column 5 |
|  5  | GPIO4_8  | Column 6 |
|  6  | GPIO2_10 | Row 1    |
|  7  | GPIO2_17 | Row 2    |
|  8  | GPIO2_16 | Row 3    |
|  9  | GPIO2_11 | Row 4    |
| 10  | GPIO2_0  | Row 5    |
| 11  | GPIO2_2  | Row 6    |

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

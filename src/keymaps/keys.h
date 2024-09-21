#define KB_L1 0x1000
#define KB_L2 0x2000
#define KB_KM1 0x3000

#define K_NK 0x0000 // No key pressed
#define K_ERR_OVF 0x0001 //  Keyboard Error Roll Over - used for all slots if too many keys are pressed ("Phantom key")
#define K_A 0x0004 // Keyboard a and A
#define K_B 0x0005 // Keyboard b and B
#define K_C 0x0006 // Keyboard c and C
#define K_D 0x0007 // Keyboard d and D
#define K_E 0x0008 // Keyboard e and E
#define K_F 0x0009 // Keyboard f and F
#define K_G 0x000a // Keyboard g and G
#define K_H 0x000b // Keyboard h and H
#define K_I 0x000c // Keyboard i and I
#define K_J 0x000d // Keyboard j and J
#define K_K 0x000e // Keyboard k and K
#define K_L 0x000f // Keyboard l and L
#define K_M 0x0010 // Keyboard m and M
#define K_N 0x0011 // Keyboard n and N
#define K_O 0x0012 // Keyboard o and O
#define K_P 0x0013 // Keyboard p and P
#define K_Q 0x0014 // Keyboard q and Q
#define K_R 0x0015 // Keyboard r and R
#define K_S 0x0016 // Keyboard s and S
#define K_T 0x0017 // Keyboard t and T
#define K_U 0x0018 // Keyboard u and U
#define K_V 0x0019 // Keyboard v and V
#define K_W 0x001a // Keyboard w and W
#define K_X 0x001b // Keyboard x and X
#define K_Y 0x001c // Keyboard y and Y
#define K_Z 0x001d // Keyboard z and Z

#define K_1 0x001e // Keyboard 1 and !
#define K_2 0x001f // Keyboard 2 and @
#define K_3 0x0020 // Keyboard 3 and #
#define K_4 0x0021 // Keyboard 4 and $
#define K_5 0x0022 // Keyboard 5 and %
#define K_6 0x0023 // Keyboard 6 and ^
#define K_7 0x0024 // Keyboard 7 and &
#define K_8 0x0025 // Keyboard 8 and *
#define K_9 0x0026 // Keyboard 9 and (
#define K_0 0x0027 // Keyboard 0 and )

#define K_ENTER 0x0028 // Keyboard Return (ENTER)
#define K_ESC 0x0029 // Keyboard ESCAPE
#define K_BSPACE 0x002a // Keyboard DELETE (Backspace)
#define K_TAB 0x002b // Keyboard Tab
#define K_SPACE 0x002c // Keyboard Spacebar
#define K_MINUS 0x002d // Keyboard - and _
#define K_EQUAL 0x002e // Keyboard and +
#define K_LBRACE 0x002f // Keyboard [ and {
#define K_RBRACE 0x0030 // Keyboard ] and }
#define K_HASH 0x0031 // Keyboard # and ~
#define K_BSLASH 0x0064 // Keyboard unknown
#define K_SCOLON 0x0033 // Keyboard ; and :
#define K_COLON 0x0233 // Keyboard ; and :
#define K_APOST 0x0034 // Keyboard ' and "
#define K_GRAVE 0x0035 // Keyboard ` and ~
#define K_COMMA 0x0036 // Keyboard , and <
#define K_DOT 0x0037 // Keyboard . and >
#define K_SLASH 0x0038 // Keyboard / and ?
#define K_CAPSLOCK 0x0039 // Keyboard Caps Lock

#define K_F1 0x003a // Keyboard F1
#define K_F2 0x003b // Keyboard F2
#define K_F3 0x003c // Keyboard F3
#define K_F4 0x003d // Keyboard F4
#define K_F5 0x003e // Keyboard F5
#define K_F6 0x003f // Keyboard F6
#define K_F7 0x0040 // Keyboard F7
#define K_F8 0x0041 // Keyboard F8
#define K_F9 0x0042 // Keyboard F9
#define K_F10 0x0043 // Keyboard F10
#define K_F11 0x0044 // Keyboard F11
#define K_F12 0x0045 // Keyboard F12

#define K_SYSRQ 0x0046 // Keyboard Print Screen
#define K_SCROLLLOCK 0x0047 // Keyboard Scroll Lock
#define K_PAUSE 0x0048 // Keyboard Pause
#define K_INSERT 0x0049 // Keyboard Insert
#define K_HOME 0x004a // Keyboard Home
#define K_PAGEUP 0x004b // Keyboard Page Up
#define K_DELETE 0x004c // Keyboard Delete Forward
#define K_END 0x004d // Keyboard End
#define K_PAGEDOWN 0x004e // Keyboard Page Down
#define K_RIGHT 0x004f // Keyboard Right Arrow
#define K_LEFT 0x0050 // Keyboard Left Arrow
#define K_DOWN 0x0051 // Keyboard Down Arrow
#define K_UP 0x0052 // Keyboard Up Arrow

#define K_NUMLOCK 0x0053 // Keyboard Num Lock and Clear
#define K_KPSLASH 0x0054 // Keypad /
#define K_KPASTERISK 0x0055 // Keypad *
#define K_KPMINUS 0x0056 // Keypad -
#define K_KPPLUS 0x0057 // Keypad +
#define K_KPENTER 0x0058 // Keypad ENTER
#define K_KP1 0x0059 // Keypad 1 and End
#define K_KP2 0x005a // Keypad 2 and Down Arrow
#define K_KP3 0x005b // Keypad 3 and PageDn
#define K_KP4 0x005c // Keypad 4 and Left Arrow
#define K_KP5 0x005d // Keypad 5
#define K_KP6 0x005e // Keypad 6 and Right Arrow
#define K_KP7 0x005f // Keypad 7 and Home
#define K_KP8 0x0060 // Keypad 8 and Up Arrow
#define K_KP9 0x0061 // Keypad 9 and Page Up
#define K_KP0 0x0062 // Keypad 0 and Insert
#define K_KPDOT 0x0063 // Keypad . and Delete

#define K_102ND 0x0064 // Keyboard Non-US \ and |
#define K_COMPOSE 0x0065 // Keyboard Application
#define K_POWER 0x0066 // Keyboard Power
#define K_KPEQUAL 0x0067 // Keypad =

#define K_F13 0x0068 // Keyboard F13
#define K_F14 0x0069 // Keyboard F14
#define K_F15 0x006a // Keyboard F15
#define K_F16 0x006b // Keyboard F16
#define K_F17 0x006c // Keyboard F17
#define K_F18 0x006d // Keyboard F18
#define K_F19 0x006e // Keyboard F19
#define K_F20 0x006f // Keyboard F20
#define K_F21 0x0070 // Keyboard F21
#define K_F22 0x0071 // Keyboard F22
#define K_F23 0x0072 // Keyboard F23
#define K_F24 0x0073 // Keyboard F24

#define K_CTRL 0x0100 // Keyboard Left Control
#define K_SHIFT 0x0200 // Keyboard Left Shift
#define K_ALT 0x0400 // Keyboard Left Alt
#define K_META 0x0800 // Keyboard Left GUI

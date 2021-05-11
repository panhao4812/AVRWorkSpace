#ifndef USBDEVICE_H_
#define USBDEVICE_H_

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <util/delay.h>
#include <string.h>
#include <avr/iom32a.h>
#include <avr/wdt.h>
#include "usbdrv/usbdrv.h"
#include "usbdrv/usbconfig.h"

#define ENDPOINT0_SIZE		8

#define KEYBOARD_INTERFACE	0
#define KEYBOARD_ENDPOINT	1
#define KEYBOARD_SIZE		8

#define MOUSE_INTERFACE KEYBOARD_INTERFACE+1
#define MOUSE_ENDPOINT	KEYBOARD_ENDPOINT+1
#define MOUSE_SIZE		8

#define RAW_INTERFACE	 MOUSE_INTERFACE+1
#define RAW_EPSIZE  8

extern const PROGMEM uint8_t KeyboardReport[];
extern const PROGMEM uint8_t MouseReport[];
extern const PROGMEM uint8_t  RawReport[];

#define REPORT_ID_MOUSE     1
#define REPORT_ID_SYSTEM    2
#define REPORT_ID_CONSUMER  3

#define KEY_CTRL	0x01
#define KEY_SHIFT	0x02
#define KEY_ALT		0x04
#define KEY_GUI		0x08
#define KEY_LEFT_CTRL	0x01
#define KEY_LEFT_SHIFT	0x02
#define KEY_LEFT_ALT	0x04
#define KEY_LEFT_GUI	0x08
#define KEY_RIGHT_CTRL	0x10
#define KEY_RIGHT_SHIFT	0x20
#define KEY_RIGHT_ALT	0x40
#define KEY_RIGHT_GUI	0x80

#define KEY_A		4
#define KEY_B		5
#define KEY_C		6
#define KEY_D		7
#define KEY_E		8
#define KEY_F		9
#define KEY_G		10
#define KEY_H		11
#define KEY_I		12
#define KEY_J		13
#define KEY_K		14
#define KEY_L		15
#define KEY_M		16
#define KEY_N		17
#define KEY_O		18
#define KEY_P		19
#define KEY_Q		20
#define KEY_R		21
#define KEY_S		22
#define KEY_T		23
#define KEY_U		24
#define KEY_V		25
#define KEY_W		26
#define KEY_X		27
#define KEY_Y		28
#define KEY_Z		29
#define KEY_1		30
#define KEY_2		31
#define KEY_3		32
#define KEY_4		33
#define KEY_5		34
#define KEY_6		35
#define KEY_7		36
#define KEY_8		37
#define KEY_9		38
#define KEY_0		39
#define KEY_ENTER	40
#define KEY_ESC		41
#define KEY_BACKSPACE	42
#define KEY_TAB		43
#define KEY_SPACE	44
#define KEY_MINUS	45 //-_
#define KEY_EQUAL	46 //=+
#define KEY_LEFT_BRACE	47
#define KEY_RIGHT_BRACE	48
#define KEY_BACKSLASH	49
#define KEY_NUMBER	50
#define KEY_SEMICOLON	51//;
#define KEY_QUOTE	52//"
#define KEY_TILDE	53//~
#define KEY_COMMA	54//,
#define KEY_PERIOD	55//.
#define KEY_SLASH	56// /
#define KEY_CAPS_LOCK	57
#define KEY_F1		58
#define KEY_F2		59
#define KEY_F3		60
#define KEY_F4		61
#define KEY_F5		62
#define KEY_F6		63
#define KEY_F7		64
#define KEY_F8		65
#define KEY_F9		66
#define KEY_F10		67
#define KEY_F11		68
#define KEY_F12		69
#define KEY_PRINTSCREEN	70
#define KEY_SCROLL_LOCK	71
#define KEY_PAUSE	72
#define KEY_INSERT	73
#define KEY_HOME	74
#define KEY_PAGE_UP	75
#define KEY_DELETE	76
#define KEY_END		77
#define KEY_PAGE_DOWN	78
#define KEY_RIGHT	79
#define KEY_LEFT	80
#define KEY_DOWN	81
#define KEY_UP		82
#define KEY_NUM_LOCK	83
#define KEYPAD_SLASH	84
#define KEYPAD_ASTERIX	85
#define KEYPAD_MINUS	86
#define KEYPAD_PLUS	87
#define KEYPAD_ENTER	88
#define KEYPAD_1	89
#define KEYPAD_2	90
#define KEYPAD_3	91
#define KEYPAD_4	92
#define KEYPAD_5	93
#define KEYPAD_6	94
#define KEYPAD_7	95
#define KEYPAD_8	96
#define KEYPAD_9	97
#define KEYPAD_0	98
#define KEYPAD_PERIOD	99

#define MOUSE_LEFT	1<<0
#define MOUSE_RIGHT	1<<1
#define MOUSE_MID	1<<2
#define MOUSE_4	1<<3
#define MOUSE_5	1<<4

#define KEY_FN 0

#define AUDIO_MUTE              0xE2
#define AUDIO_VOL_UP            0xE9
#define AUDIO_VOL_DOWN          0xEA
#define TRANSPORT_NEXT_TRACK    0xB5
#define TRANSPORT_PREV_TRACK    0xB6
#define TRANSPORT_STOP          0xB7
#define TRANSPORT_STOP_EJECT    0xCC
#define TRANSPORT_PLAY_PAUSE    0xCD

#define KEY_NONE  0x00
#define KEY_CAPS  KEY_CAPS_LOCK
#define KEY_SCRLCK KEY_SCROLL_LOCK
#define KEY_RCTRL KEY_RIGHT_CTRL
#define KEY_LCTRL KEY_LEFT_CTRL
#define KEY_PRNSCR KEY_PRINTSCREEN
#define KEY_RALT KEY_RIGHT_ALT
#define KEY_LALT KEY_LEFT_ALT
#define KEY_RBR KEY_RIGHT_BRACE
#define KEY_LBR KEY_LEFT_BRACE
#define KEY_COLON KEY_SEMICOLON
#define KEY_DOT KEY_PERIOD
#define KEY_HASH KEY_TILDE

#define KEY_NUMLOCK KEY_NUMBER
#define KEY_LED 0x00
#define KEY_KP_1 KEYPAD_1
#define KEY_KP_2 KEYPAD_2
#define KEY_KP_3 KEYPAD_3
#define KEY_KP_4 KEYPAD_4
#define KEY_KP_5 KEYPAD_5
#define KEY_KP_6 KEYPAD_6
#define KEY_KP_7 KEYPAD_7
#define KEY_KP_8 KEYPAD_8
#define KEY_KP_9 KEYPAD_9
#define KEY_KP_0 KEYPAD_0
#define KEY_KP_AST KEYPAD_ASTERIX
#define KEY_KP_MINUS KEYPAD_MINUS
#define KEY_KP_DOT KEYPAD_PERIOD
#define KEY_KP_PLUS KEYPAD_PLUS
#define KEY_KP_SLASH KEYPAD_SLASH
/* Generic Desktop Page(0x01) - system power control */
#define SYSTEM_POWER_DOWN       0x81
#define SYSTEM_SLEEP            0x82
#define SYSTEM_WAKE_UP          0x83

uint8_t macroreport;
uint8_t macrobuffer;
static inline void ClearMacro(){macrobuffer=0;macroreport=0;}
void pressmacrokey(uint8_t key);
uint8_t usb_macro_send_required();
uint8_t usb_macro_send();
//前4个macro是被预定的，后四个自定义
#define MACRO0 0x01//full led
#define MACRO1 0x02//rgb led
#define MACRO2 0x04//esc ~
#define MACRO3 0x08//print eep
#define MACRO4 0x10
#define MACRO5 0x20
#define MACRO6 0x40
#define MACRO7 0x80

typedef struct {
    uint8_t report_id;
	uint8_t buttons;
	int8_t x;
	int8_t y;
	int8_t v;
	int8_t h;
} __attribute__ ((packed)) report_mouse0_t;
typedef struct {
	uint8_t  report_id;
	uint16_t usage;
} __attribute__ ((packed)) report_extra_t;
typedef struct {
	report_mouse0_t mouse;
	report_extra_t system_keys;
	report_extra_t consumer_keys;
} __attribute__ ((packed)) report_mouse_t;
typedef struct {
	uint8_t modifier;
	uint8_t reserved;
	uint8_t keycode[6];
}__attribute__ ((packed))  report_keyboard_t;
typedef  union  {
	uint16_t      word[RAW_EPSIZE/2];
	uint8_t       bytes[RAW_EPSIZE];
}report_raw_t;

typedef struct {
	uint8_t mouse_keys;
	int8_t x;
	int8_t y;
	int8_t v;
	int8_t h;
	uint16_t system_keys;
	uint16_t consumer_keys;
	uint8_t mouse_protocol;
	uint8_t Send_Required;
} __attribute__ ((packed)) buffer_mouse_t;
typedef struct {
	uint8_t keyboard_modifier_keys;
	uint8_t keyboard_keys[6];
	uint8_t keyboard_leds;
	uint8_t enable_pressing;
	uint8_t keyboard_idle_config;
	uint8_t keyboard_idle_count;
	uint8_t keyboard_protocol;
	uint8_t Send_Required;
}__attribute__ ((packed))  buffer_keyboard_t;
report_mouse_t print_mouse_report;
report_mouse_t mouse_report;
buffer_mouse_t mouse_buffer;
#define maxEEP (uint16_t)0x0400
report_raw_t raw_report_in;
report_raw_t raw_report_out;
report_keyboard_t print_keyboard_report;
report_keyboard_t keyboard_report;
buffer_keyboard_t keyboard_buffer;
void usb_init();
void ClearKeyboard();
void ClearMouse();
void ClearRaw();			
uint16_t suspendedTimeCount;
uint8_t suspended;
void init_SOF();
void SOF();
extern const  uint8_t  ascii_to_scan_code_table[] PROGMEM;
#endif
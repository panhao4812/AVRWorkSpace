#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include <avr/io.h>
#include "usbdevice.h"

//#define ps2avrU
//#define bface60_v2_1
#define minila

#if defined(ps2avrU)
#define ROWS  8
#define COLS  10
#define WS2812_COUNT	0
#elif defined(bface60_v2_1)
#define ROWS  5
#define COLS  15
#define WS2812_COUNT	12
#elif defined(minila)
#define ROWS  8
#define COLS  15
#define WS2812_COUNT	20
#else
#define ROWS  8
#define COLS  15
#define WS2812_COUNT	0
#endif
//ws2812
#define WS2812_PORT		PORTC
#define WS2812_DDR		DDRC
#define WS2812_MASK		(1<<1)
#define WS2812_SAVE		1
#define Maxdelay 0x1000
////////
#define LOW 0
#define HIGH 1
#define INPUT 0
#define OUTPUT 1
#define LSB(n) (n & 255)
#define MSB(n) ((n >> 8) & 255)

void pinMode(uint8_t IO,uint8_t value);
void digitalWrite(uint8_t IO,uint8_t value);
uint8_t digitalRead(uint8_t IO);
void usb_update();
uint8_t usb_keyboard_send();
uint8_t usb_keyboard_send2();
uint8_t usb_mouse_send();
uint8_t usb_keyboard_send_required();
uint8_t usb_mouse_send_required();
 void vusb_transfer_keyboard();
void pressModifierKeys(uint8_t key);
uint8_t presskey(uint8_t key);
void pressmousekey(uint8_t key);
void presssystemkey(uint8_t key);
void pressconsumerkey(uint8_t key);
void releaseAllmousekeys();
void releaseAllkeyboardkeys();
uint8_t IsBufferClear();
#define _delay_after 0x06
#define _delay_before 0x03

uint8_t keymask[ROWS][COLS];
uint8_t hexaKeys1[ROWS][COLS];
uint8_t hexaKeys0[ROWS][COLS];
uint8_t rowPins[ROWS];
uint8_t colPins[COLS];
int init_main(void);
void init_rows();
void init_cols();
void Open_LED();
void Close_LED();
void init_LED();
void Reset_LED();
void LED();

#define add1 10
#define add2 add1+ROWS //15
#define add3 add2+COLS //30
#define add4 add3+(ROWS*COLS) //30+15*5=105
#define add5 add4+(ROWS*COLS) //105+75=180
#define addRGB add5+(ROWS*COLS) //180+75=255
#define addPrint addRGB+(WS2812_COUNT*3) //255+12*3=291
uint8_t WS2812fix[(WS2812_COUNT * 3)];
uint8_t RGB_Type;// bit1-> 0 off 1 on ;bit0-> 0 fix£¬1 Rainbow
void ResetMatrix(uint8_t mask,uint16_t address);
void ResetMatrixFormEEP();
void BfaceMod();
void keyPrintWordEEP(uint16_t address_t);
#endif /* FUNCTIONS_H_ */
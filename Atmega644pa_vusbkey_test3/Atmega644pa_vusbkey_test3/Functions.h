/*
 * Functions.h
 *
 * Created: 2017/5/2 22:26:44
 *  Author: Administrator
 */ 
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "usbdevice.h"

//#define ps2avrU
//#define bface60_v2_1
#define minila

#if defined(ps2avrU)
#define ROWS  8
#define COLS  10
#elif defined(bface60_v2_1)
#define ROWS  5
#define COLS  15
#elif defined(minila)
#define ROWS  8
#define COLS  15
#else
#define ROWS  8
#define COLS  15
#endif

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
void LED();

#define add1 10
#define add2 add1+ROWS
#define add3 add2+COLS
#define add4 add3+(ROWS*COLS)
#define add5 add4+(ROWS*COLS)
void ResetMatrix(uint8_t mask,uint16_t address);
void ResetMatrixFormEEP();
void FaceUMode();
void BfaceMod();

#endif /* FUNCTIONS_H_ */
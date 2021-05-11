#include "../Functions.h"
#ifdef ps2avrU
//ledfull D4
//led D0 D4 D1
//DAT D3
//D5--稳压二极管
//col A0,A1,A2,A3,A4 A5 A6 A7 C7 C6 C5 C4 C3 C2 C1 C0 D7
//row B0 B1 B2 B3 B4 B5 B6 B7
//jump A1 B0
uint8_t i,delayval,FN;
uint8_t rowPins[ROWS]={8,9,10,11,12,13,14,15};
uint8_t colPins[COLS]={1,2,3,4,5,6,7,23,22,21};
//                     2 3 4 5 6 7 8  9  10 11
#define ledcount 3
uint8_t ledPins[ledcount]={24,25,28};
uint8_t r,c;
uint8_t delay_after=0;
uint8_t delay_before=0;

void init_cols(){
	for ( i=0; i<COLS; i++){
		pinMode(colPins[i],INPUT);
		digitalWrite(colPins[i],HIGH);
	}
}
void init_rows(){
	DDRB=0;
	PORTB=1;
}
void matrix_set_row_status(uint8_t row) {
	DDRB = (1 << row);
	PORTB = ~(1 << row);
}
uint8_t hexaKeys0[ROWS][COLS] = {
	{KEY_Q,KEY_W,KEY_E,KEY_R,KEY_U,KEY_I,KEY_O,KEY_P,KEY_CTRL,KEY_FN},//ROW0
	{KEY_TAB,KEY_CAPS,0x00,KEY_T,KEY_Y,KEY_RIGHT_BRACE,KEY_TILDE,KEY_LEFT_BRACE,KEY_SHIFT,0x00},//ROW1
	{KEY_A,KEY_S,KEY_D,KEY_F,KEY_J,KEY_K,KEY_L,KEY_SEMICOLON,KEY_RIGHT_CTRL,KEY_BACKSLASH},//ROW2
	{0x00,0x00,0x00,KEY_G,KEY_H,0x00,0x00,KEY_QUOTE,KEY_ALT,KEY_SPACE},//ROW3
	{KEY_Z,KEY_X,KEY_C,KEY_V,KEY_M,KEY_COMMA,KEY_PERIOD,0x00,KEY_RIGHT_SHIFT,KEY_ENTER},//ROW4
	{0x00,0x00,0x00,KEY_B,KEY_N,0x00,KEY_FN,KEY_SLASH,KEY_RIGHT_ALT,0x00},//ROW5
	{MACRO2,0x00,0x00,KEY_5,KEY_6,KEY_EQUAL,0x00,KEY_MINUS,KEY_FN,KEY_BACKSPACE},//ROW6
	{KEY_1,KEY_2,KEY_3,KEY_4,KEY_7,KEY_8,KEY_9,KEY_0,0x00,0x00},//ROW7
};
uint8_t hexaKeys1[ROWS][COLS] = {
	{0x00,KEY_UP,0x00,0x00,0x00,0x00,0x00,0x00,KEY_CTRL,KEY_FN},//ROW0
	{KEY_TAB,KEY_CAPS,0x00,0x00,0x00,0x00,0x00,0x00,KEY_SHIFT,0x00},//ROW1
	{KEY_LEFT,KEY_DOWN,KEY_RIGHT,0x00,0x00,0x00,0x00,0x00,KEY_RIGHT_CTRL,0x00},//ROW2
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,KEY_ALT,KEY_SPACE},//ROW3
	{KEY_NUM_LOCK,KEY_SCRLCK,KEY_INSERT,KEY_PRNSCR,0x00,AUDIO_VOL_DOWN,AUDIO_VOL_UP,0x00,KEY_RIGHT_SHIFT,KEY_ENTER},//ROW4
	{0x00,0x00,0x00,0x00,0x00,0x00,KEY_FN,0x00,KEY_RIGHT_ALT,0x00},//ROW5
	{KEY_TILDE,0x00,0x00,KEY_F5,KEY_F6,KEY_F12,0x00,KEY_F11,KEY_FN,KEY_DELETE},//ROW6
	{KEY_F1,KEY_F2,KEY_F3,KEY_F4,KEY_F7,KEY_F8,KEY_F9,KEY_F10,0x00,0x00},//ROW7
};
//keymask_bits:7-press 654-hexatype0 3-press 210-hexatype1
//type: 1-key 2-modifykey 3-mousekey 4-systemkey 5-consumerkey 6-FN 7-macro
uint8_t keymask[ROWS][COLS]={
	{0x10,0x11,0x10,0x10,0x10,0x10,0x10,0x10,0x22,0x66},//ROW0
	{0x11,0x11,0x00,0x10,0x10,0x10,0x10,0x10,0x22,0x00},//ROW1
	{0x11,0x11,0x11,0x10,0x10,0x10,0x10,0x10,0x22,0x10},//ROW2
	{0x00,0x00,0x00,0x10,0x10,0x00,0x00,0x10,0x22,0x11},//ROW3
	{0x11,0x11,0x11,0x11,0x10,0x15,0x15,0x00,0x22,0x11},//ROW4
	{0x00,0x00,0x00,0x10,0x10,0x00,0x66,0x10,0x22,0x00},//ROW5
	{0x71,0x00,0x00,0x11,0x11,0x11,0x00,0x11,0x66,0x11},//ROW6
	{0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x00,0x00},//ROW7
};
/////////////////////////////////////////////////////////////////////

void Open_LED(){
	for ( i=0; i<ledcount; i++){
		digitalWrite(ledPins[i],HIGH);
	}
}
void Close_LED(){

	for ( i=0; i<ledcount; i++){
		digitalWrite(ledPins[i],LOW);
	}
}
void init_LED(){
	for ( i=0; i<ledcount; i++){
		pinMode(ledPins[i],OUTPUT);
		digitalWrite(ledPins[i],HIGH);
	}
}
void LED(){
	for ( i=0; i<ledcount; i++){
		if((keyboard_buffer.keyboard_leds&(1<<i))==(1<<i)){ digitalWrite(ledPins[i],HIGH);}
		else{ digitalWrite(ledPins[i],LOW);}
	}
}
uint8_t usb_macro_send(){
	return 0;
}
/////////////////////////////////////////////////////////////////////

void FaceUMode(){
	FN=0xF0;
	for (r = 0; r < ROWS; r++) {
		matrix_set_row_status(r);
		//_delay_us(5);
		for (c = 0; c < COLS; c++) {
			if (digitalRead(colPins[c])) {keymask[r][c]&= ~0x88;}
			else {keymask[r][c]|= 0x88;delay_after=_delay_after;}
			if(keymask[r][c]==0xEE )FN=0x0F;
		}
		init_rows();
	}
	releaseAllkeyboardkeys();
	releaseAllmousekeys();
	macrobuffer=0;
	for (r = 0; r < ROWS; r++) {
		for (c = 0; c < COLS; c++) {
			switch(keymask[r][c]&FN){
				case 0x90:
				presskey(hexaKeys0[r][c]);
				break;
				case 0xA0:
				pressModifierKeys(hexaKeys0[r][c]);
				break;
				case 0xB0:
				pressmousekey(hexaKeys0[r][c]);
				break;
				case 0xC0:
				presssystemkey(hexaKeys0[r][c]);
				break;
				case 0xD0:
				pressconsumerkey(hexaKeys0[r][c]);
				break;
				case 0xF0:
				pressmacrokey(hexaKeys0[r][c]);
				break;
				case 0x09:
				presskey(hexaKeys1[r][c]);
				break;
				case 0x0A:
				pressModifierKeys(hexaKeys1[r][c]);
				break;
				case 0x0B:
				pressmousekey(hexaKeys1[r][c]);
				break;
				case 0x0C:
				presssystemkey(hexaKeys1[r][c]);
				break;
				case 0x0D:
				pressconsumerkey(hexaKeys1[r][c]);
				break;
				case 0x0F:
				pressmacrokey(hexaKeys1[r][c]);
				break;
			}
		}
	}
	if(usb_macro_send_required())delay_before=_delay_before;
	if(usb_keyboard_send_required())delay_before=_delay_before;
	if(usb_mouse_send_required())delay_before=_delay_before;
	if(delay_after==_delay_after && delay_before==1)
	{usb_macro_send();usb_keyboard_send2();usb_mouse_send();}
	if(delay_after==1)
	{usb_macro_send();usb_keyboard_send2();usb_mouse_send();}
	if(delay_after>0)delay_after-=1;
	if(delay_before>0)delay_before-=1;
}

int init_main(void) {
	usb_init();
	////////////////////////////////////////////////
	init_cols();
	init_rows();
	while (1) {
		init_SOF();
		init_LED();
		keyboard_buffer.enable_pressing=1;
		releaseAllkeyboardkeys();
		releaseAllmousekeys();
		ResetMatrixFormEEP();
		_delay_ms(500);
		usb_keyboard_send2();
		while (1) {
			usbPoll();
			SOF();//挂起特性
			if(keyboard_buffer.enable_pressing==2){
				break;
			}
			else if(keyboard_buffer.enable_pressing==1){
				if( suspended==0){	FaceUMode();vusb_transfer_keyboard();}
				if (usbConfiguration && usbInterruptIsReady()){
					if(delay_before==0)LED();	//LED耗时太长，所以按键的时候LED休眠
				}
			}
		}
	}
	return 0;
}
#endif
#include "../Functions.h"
#include "../ws2812.h"
#if defined ps2avrU
//ledfull D4
//led D0 D4 D1
//DAT D3
//D5--稳压二极管
//col A0,A1,A2,A3,A4 A5 A6 A7 C7 C6 C5 C4 C3 C2 C1 C0 D7
//row B0 B1 B2 B3 B4 B5 B6 B7
//jump A1 B0
#define ledcount 2
#define fullled 28
uint8_t rowPins[ROWS]={8,9,10,11,12,13,14,15};
uint8_t colPins[COLS]={1,2,3,4,5,6,7,23,22,21};
uint8_t ledPins[ledcount]={24,25};
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

///////////////////////////////////////////
#elif defined bface60_v2_1
//ps2avrGB rev_SJZZ
//col A0,A1,A2,A3,A4 A5 A6 A7 C7 C6 C5 C4 C3 C2 D7
//row B3 B4 B5 B6 B7
//usbdrv D5
//led D0 D1 D6
//fullled  D4
//RGB C1
#define ledcount 3
#define fullled 28
uint8_t rowPins[ROWS]={11,12,13,14,15};
uint8_t colPins[COLS]={0,1,2,3,4,5,6,7,23,22,21,20,19,18,31};
uint8_t ledPins[ledcount]={24,25,30};
uint16_t cindex[WS2812_COUNT]={0,34,68,102,136,170,170,136,102,68,34,0};
uint8_t hexaKeys0[ROWS][COLS] = {
	{MACRO2,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_6,KEY_7,KEY_8,KEY_9,KEY_0,KEY_MINUS,KEY_EQUAL,KEY_TILDE,KEY_BACKSPACE},
	{KEY_TAB,KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEY_Y,KEY_U,KEY_I,KEY_O,KEY_P,KEY_LEFT_BRACE,KEY_RIGHT_BRACE,KEY_BACKSLASH,0x00},
	{KEY_CAPS_LOCK,KEY_A,KEY_S,KEY_D,KEY_F,KEY_G,KEY_H,KEY_J,KEY_K,KEY_L,KEY_SEMICOLON,KEY_QUOTE,0x00,KEY_ENTER,0x00},
	{KEY_LEFT_SHIFT,0x00,KEY_Z,KEY_X,KEY_C,KEY_V,KEY_B,KEY_N,KEY_M,KEY_COMMA,KEY_PERIOD,KEY_SLASH, KEY_RIGHT_SHIFT,KEY_UP,KEY_RIGHT_CTRL},
	{KEY_LEFT_CTRL,KEY_FN,KEY_LEFT_ALT,0x00,0x00,0x00,0x00,KEY_SPACE,0x00,KEY_RIGHT_ALT,KEY_FN,KEY_LEFT,KEY_DOWN,KEY_RIGHT,0x00}
};
uint8_t hexaKeys1[ROWS][COLS] = {
	{KEY_TILDE,KEY_F1,KEY_F2,KEY_F3,KEY_F4,KEY_F5,KEY_F6,KEY_F7,KEY_F8,KEY_F9,KEY_F10,KEY_F11,KEY_F12,0x00,KEY_DELETE},
	{KEY_TAB,KEYPAD_1,KEYPAD_2,KEYPAD_3,KEYPAD_4,KEYPAD_5,KEYPAD_6,KEYPAD_7,KEYPAD_8,KEYPAD_9,KEYPAD_0,KEYPAD_MINUS,KEYPAD_PLUS,KEY_BACKSLASH,0x00},
	{KEY_CAPS_LOCK, MOUSE_LEFT,MOUSE_MID,MOUSE_RIGHT,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,KEY_ENTER,0x00},
	{KEY_LEFT_SHIFT,0x00,KEY_NUM_LOCK ,KEY_SCROLL_LOCK,KEY_INSERT,KEY_PRINTSCREEN,MACRO0,MACRO1,0x00,AUDIO_VOL_DOWN,AUDIO_VOL_UP,AUDIO_MUTE,KEY_RIGHT_SHIFT,KEY_UP,KEY_RIGHT_CTRL},
	{KEY_LEFT_CTRL,KEY_FN,KEY_LEFT_ALT,0x00,0x00,0x00,0x00,KEY_SPACE,0x00,KEY_RIGHT_ALT,KEY_FN,KEY_LEFT,KEY_DOWN,KEY_RIGHT,0x00}
};
uint8_t keymask[ROWS][COLS] = {
	{0x71,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x10,0x11},
	{0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x11,0x00},
	{0x11,0x13,0x13,0x13,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x11,0x00},
	{0x22,0x00,0x11,0x11,0x11,0x11,0x17,0x17,0x10,0x15,0x15,0x15,0x22,0x11,0x22},
	{0x22,0x66,0x22,0x00,0x00,0x00,0x00,0x11,0x00,0x22,0x66,0x11,0x11,0x11,0x00}
};
/////////////////////////////////////////////////////////////////////////////
#elif defined minila
//ps2avrGB rev_SJZZ
//col A0,A1,A2,A3,A4 A5 A6 A7 C7 C6 C5 C4 C3 C2 D7
//row B0 B1 B2 B3 B4 B5 B6 B7
//usbdrv D5
//led D0 D1 D6
//fullled  D4
//RGB C1
//hub不能识别是应为电流不足，关闭灯则可以识别。其他识别问题也可能是电流的原因。
//用avrdude来烧录。
#define ledcount 3
#define fullled 28
uint8_t rowPins[ROWS]={8,9,10,11,12,13,14,15};
uint8_t colPins[COLS]={0,1,2,3,4,5,6,7,23,22,21,20,19,18,31};
uint8_t ledPins[ledcount]={24,25,30};
uint16_t cindex[WS2812_COUNT]=
{25,50,75,100,125,150,175,200,225,250,225,200,175,150,125,100,75,50,25,0};
uint8_t hexaKeys0[ROWS][COLS] = {
	{KEY_CTRL,KEY_GUI,KEY_ALT,0x00,0x00,0x00,KEYPAD_0,0x00,KEYPAD_PERIOD,KEYPAD_ENTER,KEY_RIGHT_GUI,KEY_FN,KEY_RIGHT_CTRL,KEY_INSERT,0x00},//r1
	{KEY_SHIFT,KEY_Z,KEY_X,KEY_C,KEY_V,KEY_B,KEYPAD_1,KEYPAD_2,KEYPAD_3,0x00,KEY_SLASH,KEY_RIGHT_SHIFT,0x00,KEY_PRINTSCREEN,0x00},//r2
	{KEY_CAPS,KEY_A,KEY_S,KEY_D,KEY_F,KEY_G,KEYPAD_4,KEYPAD_5,KEYPAD_6,KEYPAD_PLUS,KEY_SEMICOLON,KEY_QUOTE,0x00,KEY_ENTER,KEY_PAUSE},//r3
	{KEY_TAB,KEY_Q,KEY_W,KEY_E,KEY_R,KEY_T,KEYPAD_7,KEYPAD_8,KEYPAD_9,0x00,KEY_P,KEY_LEFT_BRACE,KEY_RIGHT_BRACE,KEY_BACKSLASH,0x00},//r4
	{KEY_TILDE,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,KEY_NUM_LOCK,KEYPAD_SLASH,KEYPAD_ASTERIX,KEYPAD_MINUS,KEY_0,KEY_MINUS,KEY_EQUAL,KEY_TILDE,KEY_BACKSPACE},//r5
	{KEY_ESC,0x00,KEY_F1,KEY_F2,KEY_F3,KEY_F4,0x00,0x00,0x00,0x00,0x00,KEY_F9,KEY_F10,KEY_F11,KEY_F12},//r6
	{KEY_F5,KEY_6,KEY_Y,KEY_H,KEY_N,KEY_SPACE,KEY_LEFT,KEY_DOWN,KEY_UP,KEY_RIGHT,KEY_F6,KEY_7,KEY_U,KEY_J,KEY_M},//r7
	{KEY_F8,KEY_9,KEY_O,KEY_L,KEY_PERIOD,KEY_RIGHT_ALT,KEY_DELETE,0x00,KEY_PAGE_DOWN,KEY_PAGE_UP,KEY_F7,KEY_8,KEY_I,KEY_K,KEY_COMMA} //r8
};
uint8_t hexaKeys1[ROWS][COLS] = {
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//r1
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//r2
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//r3
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//r4
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//r5
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//r6
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//r7
	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00} //r8
};
uint8_t keymask[ROWS][COLS] = {
	{0x20,0x20,0x20,0x00,0x00,0x00,0x10,0x00,0x10,0x10,0x20,0x66,0x20,0x10,0x00},//r1
	{0x20,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x10,0x20,0x00,0x10,0x00},//r2
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x10,0x10},//r3
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x10,0x10,0x10,0x10,0x00},//r4
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},//r5
	{0x10,0x00,0x10,0x10,0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x10,0x10},//r6
	{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10},//r7
	{0x10,0x10,0x10,0x10,0x10,0x20,0x10,0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10} //r8
};
#endif
/////////////////////////////////////////////////////////////////////
uint8_t i,FN;
uint16_t delayval;
uint8_t ledmacro=0;//记录led状态
uint8_t r,c;
uint8_t delay_after=0;//backswing 后摇
uint8_t delay_before=0;//windup 前摇
void init_cols(){
	for ( i=0; i<COLS; i++){
		pinMode(colPins[i],INPUT);
		digitalWrite(colPins[i],HIGH);
	}
}
void init_rows(){
	for ( i=0; i<ROWS; i++){
		pinMode(rowPins[i],INPUT);
		digitalWrite(rowPins[i],HIGH);
	}
}
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
	WS2812Setup();
	WS2812Clear();
	WS2812Send2();
	for ( i=0; i<ledcount; i++){
		pinMode(ledPins[i],OUTPUT);
		digitalWrite(ledPins[i],LOW);
	}
	pinMode(fullled,OUTPUT);
	digitalWrite(fullled,LOW);
	delayval=Maxdelay;
}
void Reset_LED(){
	for ( i=0; i<ledcount; i++){
		digitalWrite(ledPins[i],LOW);
	}
	digitalWrite(fullled,LOW);
	ledmacro=0;if((RGB_Type&0xF0)==0x10)ledmacro=0x02;
	WS2812Clear();
	WS2812Send2();
}
uint8_t usb_macro_send(){
	ledmacro^=macroreport;
	if(macroreport&MACRO3){
		keyPrintWordEEP(addPrint+6);
		return 1;
	}
	return 0;
}
void LED(){
	for ( i=0; i<ledcount; i++){
		if((keyboard_buffer.keyboard_leds&(1<<i))==(1<<i)){ digitalWrite(ledPins[i],HIGH);}
		else{ digitalWrite(ledPins[i],LOW);}
	}
	if(ledmacro & (1<<0)){digitalWrite(fullled,HIGH);}
	else{digitalWrite(fullled,LOW);}
	if(delayval>=Maxdelay){
		if(ledmacro & (1<<1)){
			for(uint8_t i=0;i<WS2812_COUNT;i++){
				if((RGB_Type&0x0F)==0x01){
					if(cindex[i]>=WS2812ColorCount) cindex[i]=0;
					uint8_t r=pgm_read_byte(Rcolors+cindex[i]);
					uint8_t g=pgm_read_byte(Gcolors+cindex[i]);
					uint8_t b=pgm_read_byte(Bcolors+cindex[i]);
					WS2812SetRGB(i,r,g,b);
					cindex[i]++;
				}
				else if((RGB_Type&0x0F)==0x00){
					WS2812SetRGB(i,WS2812fix[i*3],WS2812fix[i*3+1],WS2812fix[i*3+2]);
				}
			}
			}else{WS2812Clear();}
			delayval--;
			WS2812Send2();
			}else{if(delayval){delayval--;}else {delayval=Maxdelay;}}
		}
		/////////////////////////////////////////////////////////////////////
		void BfaceMod(){
			for (r = 0; r < ROWS; r++) {
				pinMode(rowPins[r],OUTPUT);
				digitalWrite(rowPins[r],LOW);
				//串键问题，如果没有delay_us会导致col1或者col2串键，不一定每个板子都会串键，不串键可以取消掉delay_us
				//_delay_us(1);
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
			if(!IsBufferClear())FN=0xF0;//Fix FN key state error
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
			init_LED();//插电亮灯会掉电，导致hub掉电不识别。所以要提前关灯。
			_delay_ms(1000);
			//供电稳定后再识别usb，hub供电不足芯片会自动休眠。按任意按键唤醒。
			usb_init();
			////////////////////////////////////////////////
			init_cols();
			init_rows();
			while (1) {
				keyboard_buffer.enable_pressing=1;
				releaseAllkeyboardkeys();
				releaseAllmousekeys();
				ResetMatrixFormEEP();
				Reset_LED();
				FN=0xF0;
				_delay_ms(500);
				usb_keyboard_send2();
				while (1) {
					usb_update();
					if(keyboard_buffer.enable_pressing==2){
						break;
					}
					else if(keyboard_buffer.enable_pressing==1){
						BfaceMod();
						if (usbConfiguration && usbInterruptIsReady()){
							if(delay_before==0)LED();	//LED耗时太长，所以按键的时候LED休眠
						}
					}
				}
			}
			return 0;
		}
		//
		/*
		///////////////////测试SOF用/////////////////////////////
		int init_main(void) {
		usb_init();
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
		//*/

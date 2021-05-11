#include "usbdevice.h"
void clearTimers(void) {
	// timer0, timer1 reset;
	TIMSK&=~(1<<TOIE0);  // disable TCNT0 overflow
	TIMSK&=~(1<<TOIE1);  // disable TCNT1 overflow
	// timer2 reset
	TIMSK&=~(1<<TOIE2);  // disable TCNT2 overflow
}
void setUsbOn(void) {
	#ifndef DISABLED_TR_SWITCH
	DDRD &= ~(1<<5);
	PORTD |=  (1<<5);
	#endif
}
void setUsbOff(void) {
	#ifndef DISABLED_TR_SWITCH
	DDRD  |= (1 << 5);
	PORTD &= ~(1 << 5);
	#endif
}
uint8_t vusb_idle_rate = 0;
void usb_init(){
clearTimers();
setUsbOn();
uint8_t i = 0;
	usbInit();
	usbDeviceDisconnect();  
	  while(--i){      
		  wdt_reset();
		  _delay_ms(1);
	  }
	usbDeviceConnect();
	sei();
	ClearKeyboard();
	ClearMouse();
	ClearRaw();
	ClearMacro();
	#ifdef CLKPR
	CLKPR = 0x80, CLKPR = 0;
	#endif
}
void ClearMouse(){
	memset(&print_mouse_report, 0, sizeof(mouse_report));
	memset(&mouse_report, 0, sizeof(mouse_report));
	memset(&mouse_buffer,0,sizeof(mouse_buffer));
	mouse_report.mouse.report_id= REPORT_ID_MOUSE;
	mouse_report.system_keys.report_id= REPORT_ID_SYSTEM;
	mouse_report.consumer_keys.report_id= REPORT_ID_CONSUMER;
}
void ClearKeyboard(){
	memset( &print_keyboard_report, 0,sizeof(keyboard_report));
	memset( &keyboard_report, 0,sizeof(keyboard_report));
	memset( &keyboard_buffer, 0,sizeof(keyboard_buffer));
	keyboard_buffer.enable_pressing=1;
}
void ClearRaw(){
	memset( &raw_report_in, 0,sizeof(raw_report_in));
	memset(&raw_report_out, 0,sizeof(raw_report_out));
}
usbRequest_t* rq ;
usbMsgLen_t usbFunctionSetup(uchar data[8])
{
	rq = (usbRequest_t *)((void *)data);
	if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS){
		if(rq->bRequest == USBRQ_HID_GET_REPORT){
			usbMsgPtr = (void *)&keyboard_report;
			return sizeof(keyboard_report);
		}
		else if(rq->bRequest == USBRQ_HID_GET_IDLE){
			usbMsgPtr = &vusb_idle_rate;
			return 1;
		}
		else if(rq->bRequest == USBRQ_HID_SET_IDLE){
			vusb_idle_rate = rq->wValue.bytes[1];
		}
		else if(rq->bRequest == USBRQ_HID_SET_REPORT){
			if (rq->wValue.word == 0x0200 && rq->wIndex.word == 0) {
				//rq->wLength.word==0x0001
				keyboard_buffer.keyboard_leds|=(1<<7);//用最高位标注状态灯，赋值后自动还原0
			}
			return USB_NO_MSG;
		}
	}
	return 0;
}
uchar usbFunctionWrite(uchar *data, uchar len)
{
	if ((keyboard_buffer.keyboard_leds&(1<<7))==(1<<7)) {
		keyboard_buffer.keyboard_leds = data[0];
		return 1;
	}
	return -1;
}
void init_SOF(){
 suspendedTimeCount=0;
 suspended=0;
}
void SOF(){
#if USB_COUNT_SOF
if (usbSofCount != 0) {
	suspended = 0;usbSofCount = 0;suspendedTimeCount=0;
}
else{
	if (suspendedTimeCount>1000) {suspended = 1;}else{suspendedTimeCount++;}
}
#endif
}
////////////////////////////////////////////////////////////////////////////////
const uint8_t ascii_to_scan_code_table[] PROGMEM = {
	0,0,0,0,0,0,0,0,
	/* ASCII:   8 */ 42,
	/* ASCII:   9 */ 43,
	/* ASCII:  10 */ 40,
	/* ASCII:  11 */ 0,
	/* ASCII:  12 */ 0,
	/* ASCII:  13 */ 0,
	/* ASCII:  14 */ 0,
	/* ASCII:  15 */ 0,
	/* ASCII:  16 */ 0,
	/* ASCII:  17 */ 0,
	/* ASCII:  18 */ 0,
	/* ASCII:  19 */ 0,
	/* ASCII:  20 */ 0,
	/* ASCII:  21 */ 0,
	/* ASCII:  22 */ 0,
	/* ASCII:  23 */ 0,
	/* ASCII:  24 */ 0,
	/* ASCII:  25 */ 0,
	/* ASCII:  26 */ 0,
	/* ASCII:  27 */ 41,
	/* ASCII:  28 */ 0,
	/* ASCII:  29 */ 0,
	/* ASCII:  30 */ 0,
	/* ASCII:  31 */ 0,
	/* ASCII:  32 */ 44,
	/* ASCII:  33 */ 158,
	/* ASCII:  34 */ 180,
	/* ASCII:  35 */ 160,
	/* ASCII:  36 */ 161,
	/* ASCII:  37 */ 162,
	/* ASCII:  38 */ 164,
	/* ASCII:  39 */ 52,
	/* ASCII:  40 */ 166,
	/* ASCII:  41 */ 167,
	/* ASCII:  42 */ 165,
	/* ASCII:  43 */ 174,
	/* ASCII:  44 */ 54,
	/* ASCII:  45 */ 45,
	/* ASCII:  46 */ 55,
	/* ASCII:  47 */ 56,
	/* ASCII:  48 */ 39,
	/* ASCII:  49 */ 30,
	/* ASCII:  50 */ 31,
	/* ASCII:  51 */ 32,
	/* ASCII:  52 */ 33,
	/* ASCII:  53 */ 34,
	/* ASCII:  54 */ 35,
	/* ASCII:  55 */ 36,
	/* ASCII:  56 */ 37,
	/* ASCII:  57 */ 38,
	/* ASCII:  58 */ 179,
	/* ASCII:  59 */ 51,
	/* ASCII:  60 */ 182,
	/* ASCII:  61 */ 46,
	/* ASCII:  62 */ 183,
	/* ASCII:  63 */ 184,
	/* ASCII:  64 */ 159,
	/* ASCII: A 65 */ 132,
	/* ASCII:  66 */ 133,
	/* ASCII:  67 */ 134,
	/* ASCII:  68 */ 135,
	/* ASCII:  69 */ 136,
	/* ASCII:  70 */ 137,
	/* ASCII:  71 */ 138,
	/* ASCII:  72 */ 139,
	/* ASCII:  73 */ 140,
	/* ASCII:  74 */ 141,
	/* ASCII:  75 */ 142,
	/* ASCII:  76 */ 143,
	/* ASCII:  77 */ 144,
	/* ASCII:  78 */ 145,
	/* ASCII:  79 */ 146,
	/* ASCII:  80 */ 147,
	/* ASCII:  81 */ 148,
	/* ASCII:  82 */ 149,
	/* ASCII:  83 */ 150,
	/* ASCII:  84 */ 151,
	/* ASCII:  85 */ 152,
	/* ASCII:  86 */ 153,
	/* ASCII:  87 */ 154,
	/* ASCII:  88 */ 155,
	/* ASCII:  89 */ 156,
	/* ASCII: Z 90 */ 157,
	/* ASCII:  91 */ 47,
	/* ASCII:  92 */ 49,
	/* ASCII:  93 */ 48,
	/* ASCII:  94 */ 163,
	/* ASCII:  95 */ 173,
	/* ASCII:  96 */ 53,
	/* ASCII: a 97 */ 4,
	/* ASCII:  98 */ 5,
	/* ASCII:  99 */ 6,
	/* ASCII: 100 */ 7,
	/* ASCII: 101 */ 8,
	/* ASCII: 102 */ 9,
	/* ASCII: 103 */ 10,
	/* ASCII: 104 */ 11,
	/* ASCII: 105 */ 12,
	/* ASCII: 106 */ 13,
	/* ASCII: 107 */ 14,
	/* ASCII: 108 */ 15,
	/* ASCII: 109 */ 16,
	/* ASCII: 110 */ 17,
	/* ASCII: 111 */ 18,
	/* ASCII: 112 */ 19,
	/* ASCII: 113 */ 20,
	/* ASCII: 114 */ 21,
	/* ASCII: 115 */ 22,
	/* ASCII: 116 */ 23,
	/* ASCII: 117 */ 24,
	/* ASCII: 118 */ 25,
	/* ASCII: 119 */ 26,
	/* ASCII: 120 */ 27,
	/* ASCII: 121 */ 28,
	/* ASCII: 122 */ 29,
	/* ASCII: 123 */ 175,
	/* ASCII: 124 */ 177,
	/* ASCII: 125 */ 176,
	/* ASCII: 126 */ 181
};

#include "Functions.h"

#define KBUF_SIZE 32
static report_keyboard_t kbuf[KBUF_SIZE];
static uint8_t kbuf_head = 0;
static uint8_t kbuf_tail = 0;
uint8_t i1=0;
uint8_t i2=0;
 void vusb_transfer_keyboard()
{
	if (usbConfiguration && usbInterruptIsReady()) {
		if (kbuf_head != kbuf_tail) {
			usbSetInterrupt((void *)&kbuf[kbuf_tail], sizeof(report_keyboard_t));
			kbuf_tail = (kbuf_tail + 1) % KBUF_SIZE;
		}
	}
}
static void send_keyboard(report_keyboard_t *report){
	uint8_t next = (kbuf_head + 1) % KBUF_SIZE;
	if (next != kbuf_tail) {
		kbuf[kbuf_head] = *report;
		kbuf_head = next;
	}
	usbPoll();
	vusb_transfer_keyboard();
}
uint8_t usb_keyboard_send2(){
	//usbPoll();
	uint8_t send_required_t=0;
		if(keyboard_buffer.Send_Required) {
			keyboard_buffer.Send_Required=0;
			send_keyboard(&keyboard_report);
			send_required_t=1;	
		}
	return send_required_t;
}
uint8_t usb_mouse_send_required(){
	uint8_t send_required_t=0;
	if(mouse_report.mouse.buttons!=mouse_buffer.mouse_keys)
	{
		mouse_report.mouse.buttons=mouse_buffer.mouse_keys;
		send_required_t=REPORT_ID_MOUSE;
	}
	if(mouse_report.system_keys.usage!=mouse_buffer.system_keys)
	{
		mouse_report.system_keys.usage=mouse_buffer.system_keys;
		send_required_t=REPORT_ID_SYSTEM;
	}
	if(mouse_report.consumer_keys.usage!=mouse_buffer.consumer_keys)
	{
		mouse_report.consumer_keys.usage=mouse_buffer.consumer_keys;
		send_required_t=REPORT_ID_CONSUMER;
	}
	if(send_required_t){
		mouse_buffer.Send_Required=send_required_t;
	}
	return send_required_t;
}
uint8_t usb_keyboard_send_required(){
	uint8_t send_required_t=0;
	if(keyboard_report.modifier!=keyboard_buffer.keyboard_modifier_keys)
	{keyboard_report.modifier = keyboard_buffer.keyboard_modifier_keys;send_required_t=1;}
	if(keyboard_report.keycode[0]!=keyboard_buffer.keyboard_keys[0])
	{keyboard_report.keycode[0]=keyboard_buffer.keyboard_keys[0];send_required_t=1;}
	if(keyboard_report.keycode[1]!=keyboard_buffer.keyboard_keys[1])
	{keyboard_report.keycode[1]=keyboard_buffer.keyboard_keys[1];send_required_t=1;}
	if(keyboard_report.keycode[2]!=keyboard_buffer.keyboard_keys[2])
	{keyboard_report.keycode[2]=keyboard_buffer.keyboard_keys[2];send_required_t=1;}
	if(keyboard_report.keycode[3]!=keyboard_buffer.keyboard_keys[3])
	{keyboard_report.keycode[3]=keyboard_buffer.keyboard_keys[3];send_required_t=1;}
	if(keyboard_report.keycode[4]!=keyboard_buffer.keyboard_keys[4])
	{keyboard_report.keycode[4]=keyboard_buffer.keyboard_keys[4];send_required_t=1;}
	if(keyboard_report.keycode[5]!=keyboard_buffer.keyboard_keys[5])
	{keyboard_report.keycode[5]=keyboard_buffer.keyboard_keys[5];send_required_t=1;}
	if(send_required_t)keyboard_buffer.Send_Required=send_required_t;
	return send_required_t;
}
uint8_t usb_mouse_send(){
	if(mouse_buffer.Send_Required==0)return 0;
	i1=0;
	while(++i1<50){
		usbPoll();
		if (usbInterruptIsReady3()){
			if(mouse_buffer.Send_Required==REPORT_ID_MOUSE){
				usbSetInterrupt3((void *)&mouse_report.mouse, sizeof(report_mouse0_t));
				mouse_buffer.Send_Required=0;
			}
			else if(mouse_buffer.Send_Required==REPORT_ID_SYSTEM){
				usbSetInterrupt3((void *)&mouse_report.system_keys, sizeof(report_extra_t));
				mouse_buffer.Send_Required=0;
			}
			else if(mouse_buffer.Send_Required==REPORT_ID_CONSUMER){
				usbSetInterrupt3((void *)&mouse_report.consumer_keys, sizeof(report_extra_t));
				mouse_buffer.Send_Required=0;
			}
			return 1;
		}
	}
	return 0;
}
uint8_t usb_keyboard_send(){
	if(keyboard_buffer.Send_Required==0)return 0;
	i2=0;
	while(++i2<50){
		usbPoll();
		if (usbInterruptIsReady()){
			if(keyboard_buffer.Send_Required){
				usbSetInterrupt((void *)&keyboard_report, sizeof(report_keyboard_t));
				keyboard_buffer.Send_Required=0;
			}
			return 1;
		}
	}
	return 0;
}
void usb_update(){
usbPoll();
#ifdef KBUF_SIZE
vusb_transfer_keyboard();
#endif
}
///////////////////////////////////////////////////////////////////////
uint8_t presskey(uint8_t key){
	uint8_t i;
	for ( i=0; i < 6; i++) {
		if (keyboard_buffer.keyboard_keys[i] == key) {
			return 1;
		}
	}
	for ( i=0; i < 6; i++) {
		if (keyboard_buffer.keyboard_keys[i] == 0) {
			keyboard_buffer.keyboard_keys[i] = key;
			return 1;
		}
	}
	return 0;
}
void pressModifierKeys(uint8_t key){
	keyboard_buffer.keyboard_modifier_keys|=key;
}
void pressmousekey(uint8_t key){
	mouse_buffer.mouse_keys|=key;
}
void presssystemkey(uint8_t key){
	mouse_buffer.system_keys=(uint16_t)key;
}
void pressconsumerkey(uint8_t key){
	uint8_t mask_t=key&0xF0;
	switch(mask_t){
		case 0xB0:
		mouse_buffer.consumer_keys=0x0000|key;
		break;
		case 0xC0:
		mouse_buffer.consumer_keys=0x0000|key;
		break;
		case 0xE0:
		mouse_buffer.consumer_keys=0x0000|key;
		break;
		case 0x80:
		mouse_buffer.consumer_keys=0x0100|key;
		break;
		case 0x90:
		mouse_buffer.consumer_keys=0x0100|key;
		break;
		case 0x20:
		mouse_buffer.consumer_keys=0x0200|key;
		break;
		case 0x00:
		mouse_buffer.consumer_keys=0x0200|key;
		break;
	}
}
void releaseAllmousekeys(){
	mouse_buffer.mouse_keys=0;
	mouse_buffer.system_keys=0;
	mouse_buffer.consumer_keys=0;
}
void releaseAllkeyboardkeys(){
	uint8_t i;
	for ( i=0; i < 6; i++) {
		keyboard_buffer.keyboard_keys[i] = 0;
	}
	keyboard_buffer.keyboard_modifier_keys=0;
}
uint8_t IsBufferClear(){
uint8_t i;
	if(mouse_buffer.mouse_keys!=0)return 1;
	if(mouse_buffer.system_keys!=0)return 1;
	if(mouse_buffer.consumer_keys!=0)return 1;
	for ( i=0; i < 6; i++) {
		if(keyboard_buffer.keyboard_keys[i] != 0)return 1;
	}
	if(keyboard_buffer.keyboard_modifier_keys!=0)return 1;
	if(macrobuffer!=0)return 1;
	return 0;
}
void ResetMatrix(uint8_t mask,uint16_t address){
	uint8_t j=0;
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			switch (mask){
				case 0:
				hexaKeys0[r][c]=eeprom_read_byte((uint8_t *)((uint16_t)j+address));
				break;
				case 1:
				hexaKeys1[r][c]=eeprom_read_byte((uint8_t *)((uint16_t)j+address));
				break;
				case 2:
				keymask[r][c]=eeprom_read_byte((uint8_t *)((uint16_t)j+address));
				break;
			}
			j++;
		}
	}
}
void ResetMatrixFormEEP(){
	//////////////////////////////////menu///////////////////////
	//(u8)address_hexakeys0,(u8)address_hexakeys0,(u16)address_hexakeys0,(u16)address_hexaKeys1,(u16)address_keymask
	//   10            10+5=15               10+5+14=29               10+5+14+70=99       10+5+14+140=169
	uint16_t address_row=eeprom_read_word((uint16_t *)0);
	uint16_t address_col=eeprom_read_word((uint16_t *)2);
	uint16_t address_hexakeys0=eeprom_read_word((uint16_t *)4);
	uint16_t address_hexaKeys1=eeprom_read_word((uint16_t *)6);
	uint16_t address_keymask=eeprom_read_word((uint16_t *)8);
	uint16_t j;
	///////////////////////////////////
	if(address_row!=add1){return;}
	if(address_col!=add2){return;}
	if(address_hexakeys0!=add3){return;}
	if(address_hexaKeys1!=add4){return;}
	if(address_keymask!=add5){return;}
	for( j=0;j<ROWS;j++){rowPins[j]=eeprom_read_byte((uint8_t *)(j+address_row));}
	for( j=0;j<COLS;j++){colPins[j]=eeprom_read_byte((uint8_t *)(j+address_col));}
	ResetMatrix(0,address_hexakeys0);
	ResetMatrix(1,address_hexaKeys1);
	ResetMatrix(2,address_keymask);
	for( j=0;j<(WS2812_COUNT * 3);j++){WS2812fix[j]=eeprom_read_byte((uint8_t *)(j+addRGB));}
	RGB_Type=eeprom_read_byte((uint8_t *)addPrint);
}
void usbFunctionWriteOut(uchar *data, uchar len){
	if(len==8){
		if(data[0]==0xFF && data[1]==0xF1 ){
			if( keyboard_buffer.enable_pressing==1 )keyboard_buffer.enable_pressing=0;
			return;
		}
		else if(data[0]==0xFF && data[1]==0xF2 ){
			if( keyboard_buffer.enable_pressing==0 ){
				keyboard_buffer.enable_pressing=2;
				Close_LED();
			}
			return;
		}
		else if(keyboard_buffer.enable_pressing==0){
			uint8_t i=0;
			memset(&raw_report_out, 0,sizeof(raw_report_out));
			for(i=0;i<8;i++)raw_report_out.bytes[i]=data[i];
			uint16_t address=raw_report_out.word[0];
			Open_LED();
			if(address<(maxEEP-1)){
				eeprom_busy_wait();
				eeprom_write_word ((uint16_t *)address,raw_report_out.word[1]);
			}
			if((address+2)<(maxEEP-1)){
				eeprom_busy_wait();
				eeprom_write_word ((uint16_t *)(address+2),raw_report_out.word[2]);
			}
			if((address+4)<(maxEEP-1)){
				eeprom_busy_wait();
				eeprom_write_word ((uint16_t *)(address+4),raw_report_out.word[3]);
			}
			Close_LED();
		}
	}
}
#ifdef _AVR_ATMEGA32A_H_INCLUDED
void pinMode(uint8_t IO,uint8_t value){
	switch(IO){
		case 0: if(value){DDRA|= (1<<0);}else{DDRA &= ~(1<<0);}break;
		case 1: if(value){DDRA|= (1<<1);}else{DDRA &= ~(1<<1);}break;
		case 2: if(value){DDRA|= (1<<2);}else{DDRA &= ~(1<<2);}break;
		case 3: if(value){DDRA|= (1<<3);}else{DDRA &= ~(1<<3);}break;
		case 4: if(value){DDRA|= (1<<4);}else{DDRA &= ~(1<<4);}break;
		case 5: if(value){DDRA|= (1<<5);}else{DDRA &= ~(1<<5);}break;
		case 6: if(value){DDRA|= (1<<6);}else{DDRA &= ~(1<<6);}break;
		case 7: if(value){DDRA|= (1<<7);}else{DDRA &= ~(1<<7);}break;

		case 8:  if(value){DDRB|= (1<<0);}else{DDRB &= ~(1<<0);}break;
		case 9:  if(value){DDRB|= (1<<1);}else{DDRB &= ~(1<<1);}break;
		case 10: if(value){DDRB|= (1<<2);}else{DDRB &= ~(1<<2);}break;
		case 11: if(value){DDRB|= (1<<3);}else{DDRB &= ~(1<<3);}break;
		case 12: if(value){DDRB|= (1<<4);}else{DDRB &= ~(1<<4);}break;
		case 13: if(value){DDRB|= (1<<5);}else{DDRB &= ~(1<<5);}break;
		case 14: if(value){DDRB|= (1<<6);}else{DDRB &= ~(1<<6);}break;
		case 15: if(value){DDRB|= (1<<7);}else{DDRB &= ~(1<<7);}break;

		case 16: if(value){DDRC|= (1<<0);}else{DDRC &= ~(1<<0);}break;
		case 17: if(value){DDRC|= (1<<1);}else{DDRC &= ~(1<<1);}break;
		case 18: if(value){DDRC|= (1<<2);}else{DDRC &= ~(1<<2);}break;
		case 19: if(value){DDRC|= (1<<3);}else{DDRC &= ~(1<<3);}break;
		case 20: if(value){DDRC|= (1<<4);}else{DDRC &= ~(1<<4);}break;
		case 21: if(value){DDRC|= (1<<5);}else{DDRC &= ~(1<<5);}break;
		case 22: if(value){DDRC|= (1<<6);}else{DDRC &= ~(1<<6);}break;
		case 23: if(value){DDRC|= (1<<7);}else{DDRC &= ~(1<<7);}break;

		case 24: if(value){DDRD|= (1<<0);}else{DDRD &= ~(1<<0);}break;
		case 25: if(value){DDRD|= (1<<1);}else{DDRD &= ~(1<<1);}break;
		case 26: if(value){DDRD|= (1<<2);}else{DDRD &= ~(1<<2);}break;
		case 27: if(value){DDRD|= (1<<3);}else{DDRD &= ~(1<<3);}break;
		case 28: if(value){DDRD|= (1<<4);}else{DDRD &= ~(1<<4);}break;
		case 29: if(value){DDRD|= (1<<5);}else{DDRD &= ~(1<<5);}break;
		case 30: if(value){DDRD|= (1<<6);}else{DDRD &= ~(1<<6);}break;
		case 31: if(value){DDRD|= (1<<7);}else{DDRD &= ~(1<<7);}break;
	}
}
void digitalWrite(uint8_t IO,uint8_t value){
	switch(IO){
		case 0: if(value){PORTA|= (1<<0);}else{PORTA &= ~(1<<0);}break;
		case 1: if(value){PORTA|= (1<<1);}else{PORTA &= ~(1<<1);}break;
		case 2: if(value){PORTA|= (1<<2);}else{PORTA &= ~(1<<2);}break;
		case 3: if(value){PORTA|= (1<<3);}else{PORTA &= ~(1<<3);}break;
		case 4: if(value){PORTA|= (1<<4);}else{PORTA &= ~(1<<4);}break;
		case 5: if(value){PORTA|= (1<<5);}else{PORTA &= ~(1<<5);}break;
		case 6: if(value){PORTA|= (1<<6);}else{PORTA &= ~(1<<6);}break;
		case 7: if(value){PORTA|= (1<<7);}else{PORTA &= ~(1<<7);}break;

		case 8: if(value){PORTB|= (1<<0);}else{PORTB &= ~(1<<0);}break;
		case 9: if(value){PORTB|= (1<<1);}else{PORTB &= ~(1<<1);}break;
		case 10: if(value){PORTB|= (1<<2);}else{PORTB &= ~(1<<2);}break;
		case 11: if(value){PORTB|= (1<<3);}else{PORTB &= ~(1<<3);}break;
		case 12: if(value){PORTB|= (1<<4);}else{PORTB &= ~(1<<4);}break;
		case 13: if(value){PORTB|= (1<<5);}else{PORTB &= ~(1<<5);}break;
		case 14: if(value){PORTB|= (1<<6);}else{PORTB &= ~(1<<6);}break;
		case 15: if(value){PORTB|= (1<<7);}else{PORTB &= ~(1<<7);}break;

		case 16: if(value){PORTC|= (1<<0);}else{PORTC &= ~(1<<0);}break;
		case 17: if(value){PORTC|= (1<<1);}else{PORTC &= ~(1<<1);}break;
		case 18: if(value){PORTC|= (1<<2);}else{PORTC &= ~(1<<2);}break;
		case 19: if(value){PORTC|= (1<<3);}else{PORTC &= ~(1<<3);}break;
		case 20: if(value){PORTC|= (1<<4);}else{PORTC &= ~(1<<4);}break;
		case 21: if(value){PORTC|= (1<<5);}else{PORTC &= ~(1<<5);}break;
		case 22: if(value){PORTC|= (1<<6);}else{PORTC &= ~(1<<6);}break;
		case 23: if(value){PORTC|= (1<<7);}else{PORTC &= ~(1<<7);}break;

		case 24: if(value){PORTD|= (1<<0);}else{PORTD &= ~(1<<0);}break;
		case 25: if(value){PORTD|= (1<<1);}else{PORTD &= ~(1<<1);}break;
		case 26: if(value){PORTD|= (1<<2);}else{PORTD &= ~(1<<2);}break;
		case 27: if(value){PORTD|= (1<<3);}else{PORTD &= ~(1<<3);}break;
		case 28: if(value){PORTD|= (1<<4);}else{PORTD &= ~(1<<4);}break;
		case 29: if(value){PORTD|= (1<<5);}else{PORTD &= ~(1<<5);}break;
		case 30: if(value){PORTD|= (1<<6);}else{PORTD &= ~(1<<6);}break;
		case 31: if(value){PORTD|= (1<<7);}else{PORTD &= ~(1<<7);}break;

	}
}
uint8_t digitalRead(uint8_t IO){
	uint8_t value=0;
	switch(IO){
		case 0:  value= PINA& (1<<0) ;break;
		case 1:  value= PINA& (1<<1) ;break;
		case 2:  value= PINA& (1<<2) ;break;
		case 3:  value= PINA& (1<<3) ;break;
		case 4:  value= PINA& (1<<4) ;break;
		case 5:  value= PINA& (1<<5) ;break;
		case 6:  value= PINA& (1<<6) ;break;
		case 7:  value= PINA& (1<<7) ;break;

		case 8:  value= PINB& (1<<0) ;break;
		case 9:  value= PINB& (1<<1) ;break;
		case 10:  value= PINB& (1<<2) ;break;
		case 11:  value= PINB& (1<<3) ;break;
		case 12:  value= PINB& (1<<4) ;break;
		case 13:  value= PINB& (1<<5) ;break;
		case 14:  value= PINB& (1<<6) ;break;
		case 15:  value= PINB& (1<<7) ;break;

		case 16:  value= PINC& (1<<0) ;break;
		case 17:  value= PINC& (1<<1) ;break;
		case 18:  value= PINC& (1<<2) ;break;
		case 19:  value= PINC& (1<<3) ;break;
		case 20:  value= PINC& (1<<4) ;break;
		case 21:  value= PINC& (1<<5) ;break;
		case 22:  value= PINC& (1<<6) ;break;
		case 23:  value= PINC& (1<<7) ;break;

		case 24:  value= PIND& (1<<0) ;break;
		case 25:  value= PIND& (1<<1) ;break;
		case 26:  value= PIND& (1<<2) ;break;
		case 27:  value= PIND& (1<<3) ;break;
		case 28:  value= PIND& (1<<4) ;break;
		case 29:  value= PIND& (1<<5) ;break;
		case 30:  value= PIND& (1<<6) ;break;
		case 31:  value= PIND& (1<<7) ;break;
	}
	return value;
}
#endif
////////////////////////print//////////////////////
void pressmacrokey(uint8_t key){
	if(key==MACRO2){
		if(keyboard_report.modifier){
			//不能用keyboard buffer 因为buffer是记录不稳定状态
			//report 则记录稳定状态
			presskey(KEY_TILDE);
		}
		else{
			presskey(KEY_ESC);
		}
	}
	macrobuffer|=key;
}
uint8_t usb_macro_send_required(){
	if (macroreport!=macrobuffer){
		macroreport=macrobuffer;
	return 1;}
	return 0;
}
void keyPrintChinese(uint8_t data[5]){
memset( &print_keyboard_report, 0,sizeof(keyboard_report));
	while(1){usbPoll();
		if(usbConfiguration && usbInterruptIsReady()){
			print_keyboard_report.modifier = 0x40;
			print_keyboard_report.keycode[0] =0;
			usbSetInterrupt((void *)&print_keyboard_report, sizeof(report_keyboard_t));
			break;
		}
	}usbPoll();
	uint8_t i=0;
	for( i=0;i<5;i++){
		while(1){usbPoll();
			if(usbConfiguration && usbInterruptIsReady()){
				print_keyboard_report.keycode[0]=98;
				if(data[i]>0){print_keyboard_report.keycode[0]=data[i]+88;}
				usbSetInterrupt((void *)&print_keyboard_report, sizeof(report_keyboard_t));
				break;
			}
		}usbPoll();
		while(1){usbPoll();
			if(usbConfiguration && usbInterruptIsReady()){
				print_keyboard_report.keycode[0] =0;
				usbSetInterrupt((void *)&print_keyboard_report, sizeof(report_keyboard_t));
				break;
			}
		}usbPoll();
	}
	while(1){usbPoll();
		if(usbConfiguration && usbInterruptIsReady()){
			print_keyboard_report.modifier = 0;
			print_keyboard_report.keycode[0] =0;
			usbSetInterrupt((void *)&print_keyboard_report, sizeof(report_keyboard_t));
			break;
		}
	}usbPoll();
}
void keyPrintEnglish(uint8_t data)
{
	if(data==0)return;
	memset( &print_keyboard_report, 0,sizeof(keyboard_report));
	while(1){usbPoll();
		if(usbConfiguration && usbInterruptIsReady()){
			print_keyboard_report.modifier = (data >> 7) ? 0x20 : 0x00;//shift加了128
			print_keyboard_report.keycode[0] =data & 0b01111111;//abs删除正负号
			usbSetInterrupt((void *)&print_keyboard_report, sizeof(report_keyboard_t));
			break;
		}
	}usbPoll();
	while(1){usbPoll();
		if(usbConfiguration && usbInterruptIsReady()){
			print_keyboard_report.modifier = 0;
			print_keyboard_report.keycode[0] =0;
			usbSetInterrupt((void *)&print_keyboard_report, sizeof(report_keyboard_t));
			break;
		}
	}usbPoll();
}
void keyPrintChar(uint16_t data_t){
usbWord_t data=(usbWord_t)data_t;
	if(data.bytes[1]==0x00){
		keyPrintEnglish(data.bytes[0]);
		}else{
		uint16_t out=(uint16_t)data.word;
		//out|=0x8080;//汉字内码每个byte最高位为1
		uint8_t datachinese[5];
		datachinese[4]=out%10;out=out/10;
		datachinese[3]=out%10;out=out/10;
		datachinese[2]=out%10;out=out/10;
		datachinese[1]=out%10;out=out/10;
		datachinese[0]=out;
		keyPrintChinese(datachinese);
	}
}
void keyPrintWord(char * word){
	uint8_t i=0;
	uint8_t len=strlen(word);
	for(i=0;i<len;i++){
		while(1){
			if(usbConfiguration && usbInterruptIsReady()){
				uint8_t data = pgm_read_byte_near(ascii_to_scan_code_table + word[i]);
				keyPrintEnglish(data);
				break;
			}usbPoll();
		}
	}
}
void keyPrintWordEEP(uint16_t address_t){
	uint16_t len=eeprom_read_word((uint16_t *)address_t);
	for(uint16_t i=0;i<len;i++){
		uint16_t address=address_t+i*2+2;
		if(address>maxEEP)break;
		uint16_t data = eeprom_read_word((uint16_t *)address);
		keyPrintChar(data);
	}
}

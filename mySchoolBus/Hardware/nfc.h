#ifndef __NFC_H
#define __NFC_H

#include "stm32f4xx.h"

extern uint8_t nfcdata;
extern const uint8_t nfc_ack[];
extern uint8_t nfc_frame[50];
extern uint8_t nfcRecv[50];

extern const uint8_t nfc_start[24];
extern const uint8_t nfc_find[11];
extern const uint8_t nfc_read[];
extern const uint8_t nfc_reply[];
enum nfc_order{
	ack,
	find,
	read
};

struct nfc_data{
	uint32_t frame;
	uint8_t check;
	uint64_t dataH;
	uint32_t dataL;
	uint16_t end;
};	

extern enum nfc_order nfc;

void nfc_WakeUp(void);
void nfc_findCard(void);
#endif

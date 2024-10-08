#ifndef __NFC_H
#define __NFC_H

#include "stm32f4xx.h"

extern uint8_t nfcdata;
extern const uint8_t nfc_readack[];
extern uint8_t nfc_frame[50];
extern uint8_t nfcRecv[50];
extern const uint8_t nfc_reply[];
extern struct nfc_data mynfc;


enum nfc_order{
	loss,
	find,
	read
};

enum nfc_checkflag{
		uncheck,
		checked
};

struct nfc_data{
	uint32_t Card_ID;
	int16_t sumCard;
	uint32_t lastCardID;
};



extern enum nfc_order nfc;

void nfc_WakeUp(void);
void nfc_findCard(void);
#endif

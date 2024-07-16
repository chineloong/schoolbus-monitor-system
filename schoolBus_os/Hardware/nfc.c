#include "nfc.h"
#include "string.h"
extern UART_HandleTypeDef huart2;

const uint8_t nfc_readack[]={00, 00 ,0xFF ,0x0C ,0xF4};

uint8_t nfcdata;
uint8_t nfc_frame[50]={0};
uint8_t nfcRecv[50]={0};

//发送命令
const uint8_t nfc_start[24]={0x55,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x03,0xFD,0xD4,0x14,0x01,0x17,0x00,};
const uint8_t nfc_find[11]={00 ,0x00 ,0xFF ,0x04 ,0xFC,0xD4 ,0x4A ,0x02 ,00 ,0xE0 ,00};
//const uint8_t nfc_read[]={0x00, 0x00, 0xFF, 0x08 ,0xf8 ,0xd4 ,0x40 ,0x01 ,0xc0 ,0xf1 ,00 ,0x01 ,0x08 ,0x31 ,00};
const uint8_t nfc_reply[]={00,00 ,0xFF ,00 ,0xFF ,00};


struct nfc_data mynfc;
enum nfc_order nfc;

//外部变量
//上车是否刷卡
enum nfc_checkflag nfcflag;

//解决大小端的问题
uint32_t swap_endian_32(uint32_t val) {  
    return ((val & 0x000000FF) << 24) |  
           ((val & 0x0000FF00) << 8)  |  
           ((val & 0x00FF0000) >> 8)  |  
           ((val & 0xFF000000) >> 24);  
}  

//激活nfc模块
void nfc_WakeUp(void)
{
	mynfc.Card_ID = 0;
	mynfc.lastCardID = 0;
	mynfc.sumCard = 0;
	HAL_UART_Transmit(&huart2,&nfc_start[0],24,100);

}


//读取卡号
void nfc_findCard(void)
{
	uint32_t ID;
	HAL_UART_Transmit(&huart2,&nfc_find[0],11,100);
	nfc = find;
	HAL_UART_Receive_IT(&huart2,&nfc_frame[0],25);
	mynfc.lastCardID = mynfc.Card_ID;
	memcpy(&ID,&nfcRecv[13],4);
	ID = swap_endian_32(ID);
	
	if(ID!=mynfc.lastCardID)
	{
			mynfc.Card_ID = ID;
			mynfc.sumCard++;
			nfcflag = checked;
	}
	

}

//void nfc_readCard(void)
//{
//		//发送读卡指令
//		HAL_UART_Transmit(&huart2,&nfc_read[0],15,100);
//		HAL_UART_Receive_IT(&huart2,&nfc_frame[0],25);
//		//nfc = find;

//}

//void nfc_process(void)
//{		
//		if(nfc == find)
//				nfc_findCard();
//		if(nfc == read)
//				nfc_readCard();

//}

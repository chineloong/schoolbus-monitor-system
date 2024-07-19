/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @brief           : 
  * @author          : 
  ******************************************************************************
  * @attention			 ：无
  *
  ******************************************************************************
  */
/* USER CODE END Header */
#include "main.h"
#ifndef __VOICE_MIDDLEWARE_H
#define __VOICE_MIDDLEWARE_H


#define	_FRAME_HEADER			0xFD
#define _FRAME_LENGTH			1u
#define _DATA_LENGTH			2u
#define _CMD_LENGTH				1u
#define _ENCODE_LENGTH		1u
#define _TEXT_MAX_LENGTH	(4*1024u)
#define _FRAME_MAX_LENGTH	(_TEXT_MAX_LENGTH+_CMD_LENGTH+_ENCODE_LENGTH)

/* 发送指令 */
typedef enum{
	VOICE_GEN = 0x01,
	MOD_CHECK = 0x21,
	GEN_PULSE = 0x03,
	GEN_CONTINUE = 0x04,
	GEN_STOP = 0x02,
	
}	Module_Sendcommand;
/* 发送后返回指令 */
typedef enum{
	COMMAND_CORRRECT = 0x41,
}	Module_Recvcommand;
/* 内部预存库 */
typedef struct{
	uint8_t *init;
	uint8_t *children_leavebus;
	uint8_t *robomaster;
}GB2312_sentenseLIB;
/* 上位机字符接收器 */
typedef struct{
	UART_HandleTypeDef *pHUSARTx;
	DMA_HandleTypeDef *pHDMArx;
	uint8_t recvbuf[_TEXT_MAX_LENGTH];
	uint8_t gb_sentense[_TEXT_MAX_LENGTH];
	uint32_t sentense_length;
	uint8_t recvd;
}GBPack_Receiver;
/* 字符串拼接存储区 */
typedef struct{
	uint8_t text_buffer[_TEXT_MAX_LENGTH];
	
	uint32_t buffer_size;
	uint32_t sentense_length;
	
	
	uint8_t is_text_buffer_right;
	
}Txt_recv;



typedef struct{
	UART_HandleTypeDef *pHUSARTx;
	/* 内置语音模块库 */
	GB2312_sentenseLIB sentenselib;
	/* 接收上位机 */
	GBPack_Receiver pack_recver;
	/* 接收语音模块 */
	uint8_t Recv_command;
	/* 开始发送 */
	uint32_t sendmsg_start;
	
	
	unsigned short text_length;
	unsigned char frame_buf[_FRAME_MAX_LENGTH];
	unsigned short data_length;	
	
	uint8_t voice_cmd_complete;
	
	uint8_t voicepack_init_done;
	
	//函数
	void(*clr_voicemodule_recvflag_)(void);
	void(*restart_idle_packrecv_)(void);
	void(*voicepack_send_)(void);
	void(*start_transmit)(void);
	void(*clearvoice)(void);
	
}Voice_packer;

/* 内部函数禁止调用 */
void Voice_completeflagClear(void);

void Init_voicemodule(void);

void Restart_dmaIDLErecv(void);

void voicepacker_send(void);

void VoiceMsg_start(void);

void VoiceMsg_clear(void);
/* -----------------*/

/* extern param&function */
//疲劳驾驶通知
char sleepydriving[]={0xC4,0xFA,0xD2,0xD1,0xC6,0xA3,0xC0,0xCD,0xBC,0xDD,0xCA,0xBB,0xA3,0xAC,0xC7,0xEB,0xD7,0xA2,0xD2,0xE2,0xD0,0xDD,0xCF,0xA2,0x00};
//开车打电话通知
char overSpeedWarning[]={0xC7,0xEB,0xCE,0xF0,0xBF,0xAA,0xB3,0xB5,0xB4,0xF2,0xB5,0xE7,0xBB,0xB0,0xA3,0xAC,0xD7,0xA2,0xD2,0xE2,0xBD,0xBB,0xCD,0xA8,0xB0,0xB2,0xC8,0xAB,0x00};
//刷卡通知
char checkcard[]={0xC9,0xCF,0xB3,0xB5,0xC7,0xEB,0xCB,0xA2,0xBF,0xA8,0x00};

void Voice_Sendmsg(uint8_t *text_buffer,uint32_t sentense_length);
void Broadcast(char * msg,uint8_t sendType);


extern Voice_packer voice_packer;

extern Txt_recv text_recv;
extern uint8_t word_seq;

#endif

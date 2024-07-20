/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @brief           : 
  * @author          : 
  ******************************************************************************
  * @attention			 ����
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

/* ����ָ�� */
typedef enum{
	VOICE_GEN = 0x01,
	MOD_CHECK = 0x21,
	GEN_PULSE = 0x03,
	GEN_CONTINUE = 0x04,
	GEN_STOP = 0x02,
	
}	Module_Sendcommand;
/* ���ͺ󷵻�ָ�� */
typedef enum{
	COMMAND_CORRRECT = 0x41,
}	Module_Recvcommand;
/* �ڲ�Ԥ��� */
typedef struct{
	uint8_t *init;
	uint8_t *children_leavebus;
	uint8_t *robomaster;
}GB2312_sentenseLIB;
/* ��λ���ַ������� */
typedef struct{
	UART_HandleTypeDef *pHUSARTx;
	DMA_HandleTypeDef *pHDMArx;
	uint8_t recvbuf[_TEXT_MAX_LENGTH];
	uint8_t gb_sentense[_TEXT_MAX_LENGTH];
	uint32_t sentense_length;
	uint8_t recvd;
}GBPack_Receiver;
/* �ַ���ƴ�Ӵ洢�� */
typedef struct{
	uint8_t text_buffer[_TEXT_MAX_LENGTH];
	
	uint32_t buffer_size;
	uint32_t sentense_length;
	
	
	uint8_t is_text_buffer_right;
	
}Txt_recv;



typedef struct{
	UART_HandleTypeDef *pHUSARTx;
	/* ��������ģ��� */
	GB2312_sentenseLIB sentenselib;
	/* ������λ�� */
	GBPack_Receiver pack_recver;
	/* ��������ģ�� */
	uint8_t Recv_command;
	/* ��ʼ���� */
	uint32_t sendmsg_start;
	
	
	unsigned short text_length;
	unsigned char frame_buf[_FRAME_MAX_LENGTH];
	unsigned short data_length;	
	
	uint8_t voice_cmd_complete;
	
	uint8_t voicepack_init_done;
	
	//����
	void(*clr_voicemodule_recvflag_)(void);
	void(*restart_idle_packrecv_)(void);
	void(*voicepack_send_)(void);
	void(*start_transmit)(void);
	void(*clearvoice)(void);
	
}Voice_packer;

/* �ڲ�������ֹ���� */
void Voice_completeflagClear(void);

void Init_voicemodule(void);

void Restart_dmaIDLErecv(void);

void voicepacker_send(void);

void VoiceMsg_start(void);

void VoiceMsg_clear(void);
/* -----------------*/

/* extern param&function */


void Voice_Sendmsg(uint8_t *text_buffer,uint32_t sentense_length);



extern Voice_packer voice_packer;

extern Txt_recv text_recv;
extern uint8_t word_seq;

#endif

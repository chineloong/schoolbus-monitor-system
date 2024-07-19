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
#include "voiceMiddleware.h"
#include <string.h>
#include <stdio.h>

extern UART_HandleTypeDef huart5;

/* 不用管 */
	
Voice_packer voice_packer;

Txt_recv text_recv = {0};

/* 预包含的话 */
#define init_length 								14			//设备初始化完成
#define children_leavebus_length		12			//小朋友请下车
#define robomaster_length						24			//机甲大师启动
uint8_t GB_deviceok[14] = {0xC9, 0xE8, 0xB1, 0xB8, 0xB3, 0xF5, 0xCA, 0xBC,0xBB, 0xAF, 0xCD, 0xEA, 0xB3, 0xC9};
uint8_t GB_ChildrenPleaseLeaveBus[12] = {0xD0,0xA1,0xC5,0xF3,0xD3,0xD1,0xC7,0xEB,0xCF,0xC2,0xB3,0xB5};
uint8_t GB_Robomaster_Start[24] = {0xBB,0xB6,0xD3,0xAD,0xCA,0xB9,0xD3,0xC3,0xD0,0xA3,0xB3,0xB5,0xD6,0xC7,0xC4,0xDC,0xB0,0xB2,0xC8,0xAB,0xCF,0xB5,0xCD,0xB3};

/**
	* @brief          初始化语言库
  * @param[in]      none
  * @retval         none
  */
void Init_sentenselib(void)
{
	voice_packer.sentenselib.init = GB_deviceok;
	voice_packer.sentenselib.children_leavebus = GB_ChildrenPleaseLeaveBus;
	voice_packer.sentenselib.robomaster = GB_Robomaster_Start;
}

/**
	* @brief          发送指定话语
  * @param[in]      none
  * @retval         none
  */
void voicepacker_send(void)
{
	switch(voice_packer.voicepack_init_done){
		case 0:	
			//得到文本长度
			voice_packer.text_length = robomaster_length;	
			//拷贝文本
			voice_packer.data_length = _CMD_LENGTH + _ENCODE_LENGTH + voice_packer.text_length;
			voice_packer.frame_buf[0] = _FRAME_HEADER;
			voice_packer.frame_buf[1] = (uint8_t)(voice_packer.data_length>>8)&0x00FF;
			voice_packer.frame_buf[2] = (uint8_t)(voice_packer.data_length)&0x00FF;
			voice_packer.frame_buf[3] = 0x01;
			voice_packer.frame_buf[4] = 0x01;		
			//拷贝文本
			memcpy(&(voice_packer.frame_buf[5]),voice_packer.sentenselib.robomaster,voice_packer.text_length );
			/* 标准操作不用改 */
			HAL_UART_Receive_IT(voice_packer.pHUSARTx, &voice_packer.Recv_command , 1);
			HAL_UART_Transmit_DMA(voice_packer.pHUSARTx,voice_packer.frame_buf,(voice_packer.data_length +_FRAME_LENGTH+_DATA_LENGTH));		
			HAL_Delay(10);
			if( (voice_packer.voice_cmd_complete) == 1 )
				voice_packer.voicepack_init_done = 1;
					
		break;
		case 1:
			voice_packer.voice_cmd_complete = (voice_packer.voice_cmd_complete==1)?0:voice_packer.voice_cmd_complete;
			/* 标准操作不用改 */
			voice_packer.text_length = voice_packer.pack_recver.sentense_length;	
			//得到文本长度
			voice_packer.data_length = _CMD_LENGTH + _ENCODE_LENGTH + voice_packer.text_length;
			voice_packer.frame_buf[0] = _FRAME_HEADER;
			voice_packer.frame_buf[1] = (uint8_t)(voice_packer.data_length>>8)&0x00FF;
			voice_packer.frame_buf[2] = (uint8_t)(voice_packer.data_length)&0x00FF;
			voice_packer.frame_buf[3] = 0x01;
			voice_packer.frame_buf[4] = 0x01;		
			//得到文本真实数据
			memcpy(&(voice_packer.frame_buf[5]),voice_packer.pack_recver.gb_sentense,voice_packer.text_length );
			/* 标准操作不用改 */
			HAL_UART_Receive_IT(voice_packer.pHUSARTx, &voice_packer.Recv_command , 1);
			HAL_UART_Transmit_DMA(voice_packer.pHUSARTx,voice_packer.frame_buf,(voice_packer.data_length +_FRAME_LENGTH+_DATA_LENGTH));				
			HAL_Delay(10);
			if( (voice_packer.voice_cmd_complete) == 1 )
				return;
			
		break;
		default:
		break;
	}
}


/**
* @brief          ���Ͷ�Ӧ�ַ���
  * @param[in]      none
  * @retval         none
  */
void Voice_Sendmsg(uint8_t *text_buffer,uint32_t sentense_length)
{
	voice_packer.start_transmit();
	if( voice_packer.sendmsg_start == 1 ){
		
		voice_packer.pack_recver.sentense_length = sentense_length;
		memset(voice_packer.pack_recver.gb_sentense,0,_TEXT_MAX_LENGTH);
		memcpy(	voice_packer.pack_recver.gb_sentense,\
						text_buffer,\
						voice_packer.pack_recver.sentense_length);
		voice_packer.voicepack_send_();		
	}	
}


/**
	* @brief          ��ʼ������ģ��Ӳ������ⷢ���Ƿ�ɹ�
  * @param[in]      none
  * @retval         none
  */
void Init_voicemodule(void)
{
	Init_sentenselib();
	
	voice_packer.pHUSARTx = &huart5;
	
	voice_packer.clr_voicemodule_recvflag_ = Voice_completeflagClear;
	voice_packer.restart_idle_packrecv_ = Restart_dmaIDLErecv;
	voice_packer.voicepack_send_ = voicepacker_send; 
	voice_packer.start_transmit = VoiceMsg_start;
	voice_packer.clearvoice = VoiceMsg_clear;
	
	voicepacker_send();//����ͨ�ż��(��һ�η��ͻ���)
	
	//HAL_UARTEx_ReceiveToIdle_DMA(voice_packer.pack_recver.pHUSARTx,voice_packer.pack_recver.recvbuf,_TEXT_MAX_LENGTH);//IDLE����
	
	HAL_Delay(10);
}





void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
    }
}

/**
	* @brief          �Զ�����������flag
  * @param[in]      none
  * @retval         none
  */
void Voice_completeflagClear(void)
{
	voice_packer.Recv_command = 0;
	voice_packer.voice_cmd_complete = 0;
}


/**
	* @brief          ��������dma����
  * @param[in]      none
  * @retval         none
  */
void Restart_dmaIDLErecv(void)
{
	HAL_UARTEx_ReceiveToIdle_DMA(voice_packer.pack_recver.pHUSARTx,voice_packer.pack_recver.recvbuf,_TEXT_MAX_LENGTH);//IDLE����	
}

/**
	* @brief          ��������ģ�鷢��
  * @param[in]      none
  * @retval         none
  */
void VoiceMsg_start(void)
{
	voice_packer.sendmsg_start ++;
	
}

/**
* @brief          �������ģ�鷢��
  * @param[in]      none
  * @retval         none
  */
void VoiceMsg_clear(void)
{
	voice_packer.sendmsg_start = 0;
	memset(text_recv.text_buffer,0x00,_TEXT_MAX_LENGTH);
	memset(voice_packer.pack_recver.gb_sentense,0x00,voice_packer.pack_recver.sentense_length);
	memset(voice_packer.frame_buf,0x00,_TEXT_MAX_LENGTH);
}

/**
* @brief         自定义发送语音
* @param[in]      none
* @retval         none
*/
uint8_t word_seq;
void Broadcast(char * msg,uint8_t sendType)
{
		switch(sendType)
		{
			case 1:
				
				sprintf((char *)text_recv.text_buffer,"%s",msg);
				
				/* 必须紧跟sprintf(复制粘贴即可) */
				//求sentence length
				// text_recv.buffer_size = sizeof(text_recv.text_buffer)/sizeof(text_recv.text_buffer[0])-1;
				text_recv.buffer_size = strlen(msg);
				
				if( text_recv.text_buffer[text_recv.buffer_size-1] == 0 ){
					text_recv.sentense_length = strlen((const char *)text_recv.text_buffer);
				}
				else
					text_recv.sentense_length = text_recv.buffer_size;	
				//执行单次发送
				Voice_Sendmsg(text_recv.text_buffer,text_recv.sentense_length);	
				/* ---------复制粘贴结束---------*/
				
				break;
			case 2:
				/* 必须和sprintf 不同时执行*/
				voice_packer.clearvoice();
				break;
			

			default:
				break;
			
		}
}

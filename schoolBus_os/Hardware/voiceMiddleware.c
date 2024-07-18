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

extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_rx;
	
Voice_packer voice_packer;

/* Ԥ�����Ļ� */
#define init_length 								14				//�豸��ʼ�����
#define children_leavebus_length		12				//С�������³�
#define robomaster_length						20				//���״�ʦ����
uint8_t GB_deviceok[14] = {0xC9, 0xE8, 0xB1, 0xB8, 0xB3, 0xF5, 0xCA, 0xBC,0xBB, 0xAF, 0xCD, 0xEA, 0xB3, 0xC9};
uint8_t GB_ChildrenPleaseLeaveBus[12] = {0xD0,0xA1,0xC5,0xF3,0xD3,0xD1,0xC7,0xEB,0xCF,0xC2,0xB3,0xB5};
uint8_t GB_Robomaster_Start[20] = {0xBB,0xFA,0xBC,0xD7,0xB4,0xF3,0xCA,0xA6,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0xC6,0xF4,0xB6,0xAF};

/**
	* @brief          ��ʼ�����Կ�
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
	* @brief          ����ָ������
  * @param[in]      none
  * @retval         none
  */
void voicepacker_send(void)
{
	switch(voice_packer.voicepack_init_done){
		case 0:	
			//�õ��ı�����
			voice_packer.text_length = robomaster_length;	
			/* ��׼�������ø� */
			voice_packer.data_length = _CMD_LENGTH + _ENCODE_LENGTH + voice_packer.text_length;
			voice_packer.frame_buf[0] = _FRAME_HEADER;
			voice_packer.frame_buf[1] = (uint8_t)(voice_packer.data_length>>8)&0x00FF;
			voice_packer.frame_buf[2] = (uint8_t)(voice_packer.data_length)&0x00FF;
			voice_packer.frame_buf[3] = 0x01;
			voice_packer.frame_buf[4] = 0x01;		
			//�����ı�
			memcpy(&(voice_packer.frame_buf[5]),voice_packer.sentenselib.robomaster,voice_packer.text_length );
			/* ��׼�������ø� */
			HAL_UART_Receive_IT(voice_packer.pHUSARTx, &voice_packer.Recv_command , 1);
			HAL_UART_Transmit_DMA(voice_packer.pHUSARTx,voice_packer.frame_buf,(voice_packer.data_length +_FRAME_LENGTH+_DATA_LENGTH));		

				
			
		break;
		case 1:
			voice_packer.voice_cmd_complete = (voice_packer.voice_cmd_complete==1)?0:voice_packer.voice_cmd_complete;
			//�õ��ı�����
			voice_packer.text_length = voice_packer.pack_recver.sentense_length;	
			/* ��׼�������ø� */
			voice_packer.data_length = _CMD_LENGTH + _ENCODE_LENGTH + voice_packer.text_length;
			voice_packer.frame_buf[0] = _FRAME_HEADER;
			voice_packer.frame_buf[1] = (uint8_t)(voice_packer.data_length>>8)&0x00FF;
			voice_packer.frame_buf[2] = (uint8_t)(voice_packer.data_length)&0x00FF;
			voice_packer.frame_buf[3] = 0x01;
			voice_packer.frame_buf[4] = 0x01;		
			//�����ı�
			memcpy(&(voice_packer.frame_buf[5]),voice_packer.pack_recver.gb_sentense,voice_packer.text_length );
			/* ��׼�������ø� */
			HAL_UART_Receive_IT(voice_packer.pHUSARTx, &voice_packer.Recv_command , 1);
			HAL_UART_Transmit_DMA(voice_packer.pHUSARTx,voice_packer.frame_buf,(voice_packer.data_length +_FRAME_LENGTH+_DATA_LENGTH));				
			

		break;
		default:
		break;
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
	
	voice_packer.pack_recver.pHUSARTx = &huart2;
	voice_packer.pack_recver.pHDMArx = &hdma_usart2_rx;
	voice_packer.pHUSARTx = &huart5;
	voice_packer.clr_voicemodule_recvflag_ = Voice_completeflagClear;
	voice_packer.restart_idle_packrecv_ = Restart_dmaIDLErecv;
	voice_packer.voicepack_send_ = voicepacker_send; 
	
	voicepacker_send();//����ͨ�ż��(��һ�η��ͻ���)
	
	HAL_Delay(10);
	if( (voice_packer.voice_cmd_complete) == 1 )
		voice_packer.voicepack_init_done = 1;

	HAL_UARTEx_ReceiveToIdle_DMA(voice_packer.pack_recver.pHUSARTx,voice_packer.pack_recver.recvbuf,_TEXT_MAX_LENGTH);//IDLE����
	
	HAL_Delay(10);
}


/**
	* @brief          call-back
  * @param[in]      none
  * @retval         none
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
				
//			if( voice_packer.Recv_command == (uint8_t)COMMAND_CORRRECT )
					voice_packer.voice_cmd_complete = 1;
				HAL_UART_Receive_IT(voice_packer.	pHUSARTx, &voice_packer.Recv_command , 1 );
    }

}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart->Instance == USART2) {
		
				/* ��ȡ���� */
				HAL_UART_DMAStop(huart);
				voice_packer.pack_recver.sentense_length =  _TEXT_MAX_LENGTH -  __HAL_DMA_GET_COUNTER(voice_packer.pack_recver.pHDMArx);
				voice_packer.pack_recver.recvd = 1;
				/* ����dmaд��IRQ�� */
			//����dma IDLE
    }		
	
	
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




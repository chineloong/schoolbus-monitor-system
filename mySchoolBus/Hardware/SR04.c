#include "SR04.h"
#include "stm32f4xx.h"
#include "nfc.h"

struct SR04 SR04;

extern TIM_HandleTypeDef htim1;
extern enum nfc_checkflag nfcflag;

void SR04_Init(void)
{
		SR04.distance1 = 0;
		SR04.distance2 = 0;
		SR04.measure_state1 = 0;
		SR04.measure_state2 = 0;
}

//��ȡ����
void SR04_GetData(void)
{	
	if(SR04.measure_state1 == 0)
	{
			TRIG_H;
			for(int i=0;i<720;i++)
				__NOP();
			TRIG_L;

			__HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
			HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);	//�������벶�� 
			SR04.measure_state1 = 1;
	}
	if(SR04.measure_state2 == 0)
	{
			TRIG2_H;
			for(int i=0;i<720;i++)
				__NOP();
			TRIG2_L;

			__HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);
			HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);	//�������벶��   
			SR04.measure_state2 = 1;
	}

}


//�жϻص�����
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//
{
	
	if(htim == &htim1)// �жϴ������жϵĶ�ʱ��ΪTIM1
	{
			if(htim->Channel ==	HAL_TIM_ACTIVE_CHANNEL_1)
			{
					switch(SR04.measure_state1)
					{
						case 1:
							htim1.Instance->CNT = 0;
							__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);  //����Ϊ�½��ز���
							SR04.measure_state1 = 2;
							HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_1);                                    
							break;              
						case 2:
							SR04.distance1 = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_1)/1000000.0f*340.0f/2.0f;//��ȡ��ǰ�Ĳ���ֵ.
							HAL_TIM_IC_Stop_IT(&htim1,TIM_CHANNEL_1); //ֹͣ����   ����: __HAL_TIM_DISABLE(&htim5);
							SR04.measure_state1 = 0;  
															 
					}
			}
			if(htim->Channel ==	HAL_TIM_ACTIVE_CHANNEL_2)
			{
					switch(SR04.measure_state2)
					{
						case 1:
							htim1.Instance->CNT = 0;
							__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);  //����Ϊ�½��ز���
							SR04.measure_state2 = 2;
							HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_2);                                    
							break;              
						case 2:
							SR04.distance2 = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_2)/1000000.0f*340.0f/2.0f;//��ȡ��ǰ�Ĳ���ֵ.
							HAL_TIM_IC_Stop_IT(&htim1,TIM_CHANNEL_2); //ֹͣ����   ����: __HAL_TIM_DISABLE(&htim5);
							SR04.measure_state2 = 0;  
															 
					}
			}
			
	
	}
	
}
 
int BusFlag = 0;
//����ϳ�
int intoBus(void)
{
		static int8_t refreshflag1 = 0;
		static int8_t refreshflag2 = 0;
		if(SR04.distance1 <= 1.0 && SR04.distance1 >= 0.2)
		{
				SR04.time1 = HAL_GetTick();
				refreshflag1 = 1;
		}
		if(SR04.distance2 <= 1.0 && SR04.distance2 >= 0.2)
		{
				SR04.time2 = HAL_GetTick();
				refreshflag2 = 1;
		}
		
		if(refreshflag1 && refreshflag2)
		{
				if(SR04.time2 > SR04.time1)
						BusFlag = 1;
				else 
						BusFlag = 0;
				
				refreshflag1 = refreshflag2 = 0;
		}
		
}


int flag = 0;
void cardWarning(void)
{
		static int8_t lastSum = 0;
		
		//�ϳ���ˢ��
		if(flag == 0 && lastSum < mynfc.sumCard)
		{
				flag = 1;
				lastSum = mynfc.sumCard;
		
		}
		//ˢ����ͨ��
		if(flag == 1 && BusFlag)
				flag = 2;
		//��λ
		else if(flag == 2)
		{
				flag = 0;
				BusFlag = 0;
				SR04.time1 = SR04.time2 = 0;
		}
			
		//�ϳ�����û��ˢ��
		if(flag == 0 && BusFlag)
				flag = 3;
		
		//û��ˢ����������
		if(flag == 3)
		{
				WarningStart;
				flag = 4;
		}
		//ˢ����رվ���
		else if(flag == 4 && lastSum < mynfc.sumCard)
		{
				lastSum = mynfc.sumCard;
				WarningStop;
				flag = 0;
				BusFlag = 0;
			
				SR04.time1 = SR04.time2 = 0;
		}

}

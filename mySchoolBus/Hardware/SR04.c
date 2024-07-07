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

//读取距离
void SR04_GetData(void)
{	
	if(SR04.measure_state1 == 0)
	{
			TRIG_H;
			for(int i=0;i<720;i++)
				__NOP();
			TRIG_L;

			__HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
			HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);	//启动输入捕获 
			SR04.measure_state1 = 1;
	}
	if(SR04.measure_state2 == 0)
	{
			TRIG2_H;
			for(int i=0;i<720;i++)
				__NOP();
			TRIG2_L;

			__HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);
			HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);	//启动输入捕获   
			SR04.measure_state2 = 1;
	}

}


//中断回调函数
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)//
{
	
	if(htim == &htim1)// 判断触发的中断的定时器为TIM1
	{
			if(htim->Channel ==	HAL_TIM_ACTIVE_CHANNEL_1)
			{
					switch(SR04.measure_state1)
					{
						case 1:
							htim1.Instance->CNT = 0;
							__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_1,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
							SR04.measure_state1 = 2;
							HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_1);                                    
							break;              
						case 2:
							SR04.distance1 = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_1)/1000000.0f*340.0f/2.0f;//获取当前的捕获值.
							HAL_TIM_IC_Stop_IT(&htim1,TIM_CHANNEL_1); //停止捕获   或者: __HAL_TIM_DISABLE(&htim5);
							SR04.measure_state1 = 0;  
															 
					}
			}
			if(htim->Channel ==	HAL_TIM_ACTIVE_CHANNEL_2)
			{
					switch(SR04.measure_state2)
					{
						case 1:
							htim1.Instance->CNT = 0;
							__HAL_TIM_SET_CAPTUREPOLARITY(&htim1,TIM_CHANNEL_2,TIM_ICPOLARITY_FALLING);  //设置为下降沿捕获
							SR04.measure_state2 = 2;
							HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_2);                                    
							break;              
						case 2:
							SR04.distance2 = HAL_TIM_ReadCapturedValue(&htim1,TIM_CHANNEL_2)/1000000.0f*340.0f/2.0f;//获取当前的捕获值.
							HAL_TIM_IC_Stop_IT(&htim1,TIM_CHANNEL_2); //停止捕获   或者: __HAL_TIM_DISABLE(&htim5);
							SR04.measure_state2 = 0;  
															 
					}
			}
			
	
	}
	
}
 
int BusFlag = 0;
//检测上车
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
		
		//上车并刷卡
		if(flag == 0 && lastSum < mynfc.sumCard)
		{
				flag = 1;
				lastSum = mynfc.sumCard;
		
		}
		//刷卡后通过
		if(flag == 1 && BusFlag)
				flag = 2;
		//复位
		else if(flag == 2)
		{
				flag = 0;
				BusFlag = 0;
				SR04.time1 = SR04.time2 = 0;
		}
			
		//上车但是没有刷卡
		if(flag == 0 && BusFlag)
				flag = 3;
		
		//没有刷卡开启警报
		if(flag == 3)
		{
				WarningStart;
				flag = 4;
		}
		//刷卡后关闭警报
		else if(flag == 4 && lastSum < mynfc.sumCard)
		{
				lastSum = mynfc.sumCard;
				WarningStop;
				flag = 0;
				BusFlag = 0;
			
				SR04.time1 = SR04.time2 = 0;
		}

}

#include "stm32f4xx.h"
#include "CheckCard.h"
#include "SR04.h"

extern struct SR04 SR04;

enum BusState intoBusFlag,outofBusFlag;

//����ϳ�
void intoBus(void)
{
		static int8_t refreshflag1 = 0;
		static int8_t refreshflag2 = 0;
		if(SR04.distance1 <= 1.0f && SR04.distance1 >= 0.2f)
		{
				SR04.time1 = HAL_GetTick();
				refreshflag1 = 1;
		}
		if(SR04.distance2 <= 1.0f && SR04.distance2 >= 0.2f)
		{
				SR04.time2 = HAL_GetTick();
				refreshflag2 = 1;
		}
		
		if(refreshflag1 && refreshflag2)
		{
				if(SR04.time2 > SR04.time1)
						intoBusFlag = intoBus_1;
				else 
						intoBusFlag = intoBus_0;
				
				refreshflag1 = refreshflag2 = 0;
		}
		
}
//����³�
void outofBus(void)
{
		static int8_t refreshflag1 = 0;
		static int8_t refreshflag2 = 0;
		if(SR04.distance1 <= 1.0f && SR04.distance1 >= 0.2f)
		{
				SR04.time1 = HAL_GetTick();
				refreshflag1 = 1;
		}
		if(SR04.distance2 <= 1.0f && SR04.distance2 >= 0.2f)
		{
				SR04.time2 = HAL_GetTick();
				refreshflag2 = 1;
		}
		
		if(refreshflag1 && refreshflag2)
		{
				if(SR04.time2 < SR04.time1)
						outofBusFlag = outofBus_1;
				else 
						outofBusFlag = outofBus_0;
				
				refreshflag1 = refreshflag2 = 0;
		}

}	

//�ϳ�ˢ������
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
		if(flag == 1 && intoBusFlag == intoBus_1)
				flag = 2;
		//��λ
		else if(flag == 2)
		{
				flag = 0;
				intoBusFlag = intoBus_0;
				SR04.time1 = SR04.time2 = 0;
		}
			
		//�ϳ�����û��ˢ��
		if(flag == 0 && intoBusFlag == intoBus_1)
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
				intoBusFlag = intoBus_0;
			
				SR04.time1 = SR04.time2 = 0;
		}

}


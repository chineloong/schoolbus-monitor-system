#include "LCD_Task.h"
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "qdtft_demo.h"
#include "picture.h"


static void GUI_Reset(void);
static void GUI_Checked(void);

const char LOGO[] = "�����󳵳�";
const char systemName[] = "У�����ܰ�ȫϵͳ";
const char CheckSuccess[] = "ˢ���ɹ�";
enum GUI_State GUI_Flag;

void LCD_Task(void)
{
    Lcd_Init();
		LCD_LED_SET;//ͨ��IO���Ʊ�����		
		GUI_Reset();
    while(1)
    {	
				if(GUI_Flag)
				{
						GUI_Checked();
						vTaskDelay(1000);
						GUI_Reset();
						GUI_Flag = GUIwaiting;
				}
				vTaskDelay(300);
    }
}

static void GUI_Reset(void)
{
		
	
	showimage(gImage_schoolBus,0,25,160,76);//ͼƬ��ʾʾ��
	Gui_DrawFont_GBK16(30,0,GREEN,GRAY0,(uint8_t *)LOGO);
	Gui_DrawFont_GBK16(20,100,RED,GRAY0,(uint8_t *)systemName);

}

static void GUI_Checked(void)
{
		showimage(gImage_success,30,40,80,25);//ͼƬ��ʾʾ��

}

static void GUI_Failure(void)
{
		showimage(gImage_failure,50,20,80,31);//ͼƬ��ʾʾ��

}
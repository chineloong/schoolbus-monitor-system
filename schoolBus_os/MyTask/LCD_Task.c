#include "LCD_Task.h"
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "qdtft_demo.h"
#include "picture.h"


static void GUI_Reset(void);
static void GUI_Checked(void);

const char LOGO[] = "天竺鼠车车";
const char systemName[] = "校车智能安全系统";
const char CheckSuccess[] = "刷卡成功";
enum GUI_State GUI_Flag;

void LCD_Task(void)
{
    Lcd_Init();
		LCD_LED_SET;//通过IO控制背光亮		
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
		
	
	showimage(gImage_schoolBus,0,25,160,76);//图片显示示例
	Gui_DrawFont_GBK16(30,0,GREEN,GRAY0,(uint8_t *)LOGO);
	Gui_DrawFont_GBK16(20,100,RED,GRAY0,(uint8_t *)systemName);

}

static void GUI_Checked(void)
{
		showimage(gImage_success,30,40,80,25);//图片显示示例

}

static void GUI_Failure(void)
{
		showimage(gImage_failure,50,20,80,31);//图片显示示例

}
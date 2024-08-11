/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "Lcd_Driver.h"
#include "GUI.h"
#include "QDTFT_demo.h"
extern SPI_HandleTypeDef hspi1;
unsigned char Num[10]={0,1,2,3,4,5,6,7,8,9};
void Redraw_Mainmenu(void)
{

	Lcd_Clear(GRAY0);
	
	Gui_DrawFont_GBK16(16,0,BLUE,GRAY0,"全动电子技术");
	Gui_DrawFont_GBK16(16,20,RED,GRAY0,"液晶测试程序");

	DisplayButtonUp(15,38,113,58); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(16,40,YELLOW,GRAY0,"颜色填充测试");

	DisplayButtonUp(15,68,113,88); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(16,70,BLUE,GRAY0,"文字显示测试");

	DisplayButtonUp(15,98,113,118); //x1,y1,x2,y2
	Gui_DrawFont_GBK16(16,100,RED,GRAY0,"图片显示测试");
	HAL_Delay(1500);
}

void Num_Test(void)
{
	uint8_t i=0;
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(16,20,RED,GRAY0,"Num Test");
	HAL_Delay(1000);
	Lcd_Clear(GRAY0);

	for(i=0;i<10;i++)
	{
	Gui_DrawFont_Num32((i%3)*40,32*(i/3)+5,RED,GRAY0,Num[i+1]);
	HAL_Delay(100);
	}
	
}

void Font_Test(void)
{
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(16,10,BLUE,GRAY0,"沐泽");

	HAL_Delay(1000);
	Lcd_Clear(GRAY0);
	Gui_DrawFont_GBK16(16,30,GREEN,GRAY0,"天竺鼠车车");
	HAL_Delay(1000);
//	Gui_DrawFont_GBK16(16,50,BLUE,GRAY0,"专注液晶批发");
//	Gui_DrawFont_GBK16(16,70,RED,GRAY0, "全程技术支持");
//	Gui_DrawFont_GBK16(0,100,BLUE,GRAY0,"Tel:11111111111");
//	Gui_DrawFont_GBK16(0,130,RED,GRAY0, "QQ:11111111");	
//	HAL_Delay(1800);	
}

void Color_Test(void)
{
	uint8_t i=1;
	Lcd_Clear(GRAY0);
	
	Gui_DrawFont_GBK16(20,10,BLUE,GRAY0,"Color Test");
	HAL_Delay(200);

	while(i--)
	{
		Lcd_Clear(WHITE);
		Lcd_Clear(BLACK);
		Lcd_Clear(RED);
		Lcd_Clear(GREEN);
		Lcd_Clear(BLUE);
	}		
}

//取模方式 水平扫描 从左到右 低位在前
void showimage(const unsigned char * p,int startx,int starty,int sizex,int sizey)
{
  int i; 
	Lcd_Clear(WHITE); //清屏  
	
	Lcd_SetRegion(startx,starty,startx+sizex-1,starty+sizey-1);		//坐标设置
 LCD_CS_CLR;
 LCD_RS_SET;
 for(i=0;i<sizex*sizey*2;i+=2)
 {				
	HAL_SPI_Transmit_DMA(&hspi1,(uint8_t *)&p[i],2); 						
 }
	
 LCD_CS_SET; 
		

}


void QDTFT_Test_Demo(void)
{
	Lcd_Init();
	LCD_LED_SET;//通过IO控制背光亮				
//	Redraw_Mainmenu();//绘制主菜单(部分内容由于分辨率超出物理值可能无法显示)
//	Color_Test();//简单纯色填充测试
//	Num_Test();//数码管字体测试
		//Font_Test();//中英文显示测试
	
	//showimage(gImage_schoolBus,0,25,160,76);//图片显示示例
	Gui_DrawFont_GBK16(30,0,GREEN,GRAY0,"天竺鼠车车");
	Gui_DrawFont_GBK16(20,100,RED,GRAY0,"校车智能安全系统");
	//Redraw_Mainmenu();
	HAL_Delay(1200);
	LCD_LED_CLR;//IO控制背光灭	
	
}

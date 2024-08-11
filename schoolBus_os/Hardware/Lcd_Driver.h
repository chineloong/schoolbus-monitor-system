//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//  ��������   : 1.8��LCD 4�ӿ���ʾ����(STM32ϵ��)
/******************************************************************************
//������������STM32F103C8
//              GND   ��Դ��
//              VCC   ��5V��3.3v��Դ
//              SCL   ��PA5��SCL��
//              SDA   ��PA7��SDA��
//              RES   ��PB0
//              DC    ��PB1
//              CS    ��PA4 
//							BL		��PB10
*******************************************************************************/
#ifndef __LCD_DRIVER_H
#define __LCD_DRIVER_H

#include "stm32f4xx.h"


#define RED  	0xf800
#define GREEN	0x07e0
#define BLUE 	0x001f
#define WHITE	0xffff
#define BLACK	0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//��ɫ0 3165 00110 001011 00101
#define GRAY1   0x8410      	//��ɫ1      00000 000000 00000
#define GRAY2   0x4208      	//��ɫ2  1111111111011111




#define LCD_CTRLA   	  	GPIOA		//����TFT���ݶ˿�
#define LCD_CTRLB   	  	GPIOB		//����TFT���ݶ˿�

//ʱ��
#define LCD_SCL        	GPIO_PIN_5	//PA5--->>TFT --SCL/SCK
//����
#define LCD_SDA        	GPIO_PIN_7	//PA7 MOSI--->>TFT --SDA/DIN
//Ƭѡ
#define LCD_CS        	GPIO_PIN_4  //MCU_PA4--->>TFT --CS/CE
//�������
#define LCD_LED        	GPIO_PIN_4  //MCU_PC4--->>TFT --BL
//����\����ѡ��
#define LCD_RS         	GPIO_PIN_5	//PC5--->>TFT --RS/DC
//��λ
#define LCD_RST     	  GPIO_PIN_0	//PB0--->>TFT --RST

//#define LCD_CS_SET(x) LCD_CTRL->ODR=(LCD_CTRL->ODR&~LCD_CS)|(x ? LCD_CS:0)


//#define	LCD_SCL_SET  	HAL_GPIO_WritePin(GPIOA,LCD_SCL,GPIO_PIN_SET) 
//#define	LCD_SCL_CLR  	HAL_GPIO_WritePin(GPIOA,LCD_SCL,GPIO_PIN_RESET) 

//#define	LCD_SDA_SET  	HAL_GPIO_WritePin(GPIOA,LCD_SDA,GPIO_PIN_SET)   
//#define	LCD_SDA_CLR  	HAL_GPIO_WritePin(GPIOA,LCD_SDA,GPIO_PIN_RESET) 

//#define	LCD_CS_SET  	HAL_GPIO_WritePin(GPIOA,LCD_CS,GPIO_PIN_SET) 
//#define	LCD_CS_CLR  	HAL_GPIO_WritePin(GPIOA,LCD_CS,GPIO_PIN_RESET) 
//											
//#define	LCD_LED_SET  	HAL_GPIO_WritePin(GPIOC,LCD_LED,GPIO_PIN_SET) 
//#define	LCD_LED_CLR  	HAL_GPIO_WritePin(GPIOC,LCD_LED,GPIO_PIN_RESET) 

//#define	LCD_RS_SET  	HAL_GPIO_WritePin(GPIOC,LCD_RS,GPIO_PIN_SET) 
//#define	LCD_RS_CLR  	HAL_GPIO_WritePin(GPIOC,LCD_RS,GPIO_PIN_RESET) 
//											
//#define	LCD_RST_SET  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_SET) 
//#define	LCD_RST_CLR  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET) 

#define	LCD_SCL_SET  	GPIOA->BSRR=LCD_SCL    
#define	LCD_SDA_SET  	GPIOA->BSRR=LCD_SDA   
#define	LCD_CS_SET  	GPIOA->BSRR=LCD_CS  

    
#define	LCD_LED_SET  	GPIOC->BSRR=LCD_LED   
#define	LCD_RS_SET  	GPIOC->BSRR=LCD_RS 
#define	LCD_RST_SET  	GPIOB->BSRR=LCD_RST 
//Һ�����ƿ���0�������궨��
//�˿�λ����Ĵ��������õ�ƽΪ0
#define	LCD_SCL_CLR  	GPIOA->BSRR=LCD_SCL<< 16U  
#define	LCD_SDA_CLR  	GPIOA->BSRR=LCD_SDA<< 16U
#define	LCD_CS_CLR  	GPIOA->BSRR=LCD_CS<< 16U
    
#define	LCD_LED_CLR  GPIOC->BSRR=LCD_LED<< 16U 
#define	LCD_RS_CLR   GPIOC->BSRR=LCD_RS<< 16U
#define	LCD_RST_CLR  GPIOB->BSRR=LCD_RST<< 16U
// 
//�������õ�ǰ�˿ڵĵ�ƽ״̬����16λ(0~15)ÿһλ��Ӧÿһ���˿�
#define LCD_DATAOUT(x) LCD_DATA->ODR=x; //�������
//����Ĵ�����������ȡ��ǰ�˿ڵĵ�ƽ״̬����16λ(0~15)ÿһλ��Ӧÿһ���˿�
#define LCD_DATAIN     LCD_DATA->IDR;   //��������

#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
LCD_DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
} 



void Lcd_WriteIndex(uint8_t Index);
void Lcd_WriteData(uint8_t Data);
void Lcd_WriteReg(uint8_t Index,uint8_t Data);
uint16_t Lcd_ReadReg(uint8_t LCD_Reg);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(uint16_t Color);
void Lcd_SetXY(uint16_t x,uint16_t y);
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data);
unsigned int Lcd_ReadPoint(uint16_t x,uint16_t y);
void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end);
void LCD_WriteData_16Bit(uint16_t Data);

#endif

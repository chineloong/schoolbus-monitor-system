
#ifndef __LCD_TASK_H
#define __LCD_TASK_H

#include "Lcd_Driver.h"
#include "GUI.h"
#include "QDTFT_demo.h"
#include "stm32f4xx.h"

enum GUI_State{
		GUIwaiting,
		success,
		failure
};


extern enum GUI_State GUI_Flag;
void LCD_Task(void);


#endif

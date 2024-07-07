#ifndef __CHECK_CARD_H
#define __CHECK_CARD_H


#define WarningStart HAL_GPIO_WritePin(warning_GPIO_Port,warning_Pin,GPIO_PIN_SET);
#define WarningStop HAL_GPIO_WritePin(warning_GPIO_Port,warning_Pin,GPIO_PIN_RESET);


enum BusState{
		intoBus_0,
		intoBus_1,
		outofBus_0,
		outofBus_1
};

extern int flag;
void cardWarning(void);
#endif

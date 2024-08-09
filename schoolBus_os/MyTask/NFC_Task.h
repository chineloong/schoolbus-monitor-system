#ifndef __NFC_TASK_H
#define __NFC_TASK_H


enum BusState{
		intoBus_0,
		intoBus_1,
		outofBus_0,
		outofBus_1,
		state_change,
		midstate
};

enum StudentState{
		waiting,
		onBus,
		outofBus,
		onBus_checked,
		onBus_unchecked,
		outofBus_checked,
		outofBus_unchecked

};
void NFC_Task(void* pvParameters);

extern float check1_time;
extern float check2_time;

#endif

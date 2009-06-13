#ifndef INPUT_H_
#define INPUT_H_
#include "Globals.h"

#define INPUT_CONTROLLER_UNDEFINED -1
#define INPUT_BUTTON_UNDEFINED -1
#define INPUT_VALUE_UNDEFINED -1.0f
#define INPUT_VALUE_RELEASED 0.0f
#define INPUT_VALUE_PRESSED 1.0f
#define INPUT_STATE_UNDEFINED -1
#define INPUT_STATE_NONE 0
#define INPUT_STATE_TRIGGERED 1
#define INPUT_STATE_RELEASED 2


typedef struct InputData
{
	int controller;
	int button;
	float value;
	int state;
} InputData;

InputData* InputData_new(int controller, int button, float value, int state);



typedef struct InputCallback
{
	void (*func)(void* data, InputData* input);
	void* data;
} InputCallback;


InputCallback* InputCallBack_new(void (*func)(void* data, InputData* input), void* data);



int Input_init();
void Input_destroy();
void Input_handleInput(Time t);
void Input_addInputCallback(InputCallback* callback, InputData filter);




#endif



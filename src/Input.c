#include "Input.h"
#include "GL/glfw.h"

#include "Engine.h"
#include "LinkedList.h"


static LinkedList* input_callbackList;

InputData* InputData_new(int controller, int button, float value, int state)
{
	InputData* self = (InputData*)malloc(sizeof(InputData));
	
	self->controller = controller;
	self->button = button;
	self->value = value;
	self->state = state;
	
	return self;
}


InputCallback* InputCallBack_new(void (*func)(void* data, InputData* input), void* data)
{
	InputCallback* self = (InputCallback*)malloc(sizeof(InputCallback));
	
	assert(func);
	self->func = func;
	self->data = data;	
	return self;
}

int Input_init()
{
	input_callbackList = LinkedList_new();
		
	return 0;
}
void Input_destroy()
{
	LinkedList_destroy(input_callbackList);
}


void Input_addInputCallback(InputCallback* callback, InputData filter)
{
	LinkedList_addLast(input_callbackList, callback);
}



static void sendInput(InputData* data)
{	
	InputCallback* callback;
	Node* p; 
	for (p = input_callbackList->first; p != NULL; p = p->next)
	{
		callback = (InputCallback*)p->item;
		callback->func(callback->data, data);
	}	
}

void Input_handleInput(Time t)
{	
	if ((int)glfwGetKey(GLFW_KEY_ESC))
	{
		Engine_stop();
	}
	
	if (glfwGetMouseButton(0))
	{
		InputData* data = InputData_new(0,0,INPUT_VALUE_PRESSED, INPUT_STATE_TRIGGERED);
		sendInput(data);	
	}
}

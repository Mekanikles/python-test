#include "Input.h"
#include "GL/glfw.h"

#include "Engine.h"
#include "LinkedList.h"


typedef struct _InputCallback
{
	void (*func)(void* data, InputData input);
	void* data;
} _InputCallback;


static LinkedList* input_callbackList;


int Input_init()
{
	input_callbackList = LinkedList_new();
		
	return 0;
}
void Input_destroy()
{
	LinkedList_destroy(input_callbackList);
}


void Input_addInputCallback(void (*func)(void* data, InputData input), void* data, InputData filter)
{
	_InputCallback* callback = (_InputCallback*)malloc(sizeof(_InputCallback));
	
	assert(func);
	callback->func = func;
	callback->data = data;

	LinkedList_addLast(input_callbackList, callback);
}



static void sendInput(InputData data)
{	
	_InputCallback* callback;
	Node* p = input_callbackList->first; 
	for (;p != NULL; p = p->next)
	{
		callback = (_InputCallback*)p->item;
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
		fprintf(stderr, " ^.^ "); 
		InputData data;
		data.controller = 0;
		data.button = 0;
		data.value = INPUT_VALUE_PRESSED;
		data.state = INPUT_STATE_TRIGGERED;	
		sendInput(data);	
	}
}

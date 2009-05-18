#include "Timer.h"

#include "LinkedList.h"

typedef struct _TimerCallback
{
	void (*func)(void* data, Time t);
	void* data;
	Time lastcall;
	Time interval;
} _TimerCallback;

static LinkedList* callbackList;


int Timer_init()
{
	callbackList = LinkedList_new();
	
	return 0;
}
void Timer_destroy()
{
	LinkedList_destroy(callbackList);
}


void Timer_addCallback(void (*func)(void* data, Time t), void* data, Time interval)
{
	_TimerCallback* callback = (_TimerCallback*)malloc(sizeof(_TimerCallback));
	
	assert(func);
	callback->func = func;
	callback->data = data;
	callback->interval = interval;
	callback->lastcall = 0;

	LinkedList_addLast(callbackList, callback);
}

void Timer_callFunctions(Time currentTime)
{
	_TimerCallback* callback;
	Node* p = callbackList->first; 
	for (;p != NULL; p = p->next)
	{
		callback = (_TimerCallback*)p->item;
		assert(callback->func);
		if (callback->lastcall == 0)
		{
			callback->func(callback->data, currentTime);
			callback->lastcall = currentTime;	
			continue;
		}
		while (currentTime - callback->lastcall > callback->interval)
		{
			//fprintf(stderr, "value: %f, interval: %f\n", callback->lastcall, callback->interval);
			
			callback->func(callback->data, currentTime);
			callback->lastcall += callback->interval;
		}		
	}
}

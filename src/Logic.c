#include "Logic.h"

#include "Physics.h"
#include "Script.h"
#include "LinkedList.h"

typedef struct _UpdateCallback
{
	void (*func)(void* data, Time t);
	void* data;
} _UpdateCallback;


static LinkedList* update_callbackList;

int Logic_init()
{
	update_callbackList = LinkedList_new();
		
	return 0;
}
void Logic_destroy()
{
	LinkedList_destroy(update_callbackList);
}

void Logic_handleCollisions(struct CollisionList* collisions)
{
	struct Collision* p = NULL;
	for (p = collisions->first; p != NULL; p = p->next)
	{
		//fprintf(stderr, "collide\n");
		//Script_callFunction(p->obj1);	
	}
}

void Logic_addUpdateCallback(void (*func)(void* data, Time t), void* data)
{
	_UpdateCallback* callback = (_UpdateCallback*)malloc(sizeof(_UpdateCallback));
	
	assert(func);
	callback->func = func;
	callback->data = data;

	LinkedList_addLast(update_callbackList, callback);
}

void Logic_update(Time t)
{	
	_UpdateCallback* callback;
	Node* p = update_callbackList->first; 
	for (;p != NULL; p = p->next)
	{
		callback = (_UpdateCallback*)p->item;
		callback->func(callback->data, t);
	}	
}

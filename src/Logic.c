#include "Logic.h"

#include "Physics.h"
#include "Script.h"
#include "LinkedList.h"
#include "ObjectType.h"
#include "World.h"

UpdateCallback* UpdateCallback_new(void (*func)(void* data, Time t), void* data)
{
	UpdateCallback* self = (UpdateCallback*)malloc(sizeof(UpdateCallback));
	
	assert(func);
	self->func = func;
	self->data = data;	
	return self;
}

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

void Logic_handleCollisions(struct WorldObject* world)
{
	struct CollisionData* p = NULL;
	for (p = world->collisionlist->first; p != NULL; p = p->next)
	{
		Node* n;
		CollisionCallback* cb;
		ObjectType* ot;
		
		// Call all listeners for the objects type
		ot = World_getObjectType(p->obj1->type);
		if (ot->collisionListeners)
		{
			for (n = ot->collisionListeners->first; n != NULL; n = n->next)
			{
				cb = (CollisionCallback*)n->item;
				cb->func(cb->data, p);
			}	
		}
		
		// Call all listeners for the specific object
		if (p->obj1->collisionListeners)
		{
			for (n = p->obj1->collisionListeners->first; n != NULL; n = n->next)
			{
				cb = (CollisionCallback*)n->item;
				cb->func(cb->data, p);
			}	
		}

	}
}

void Logic_addUpdateCallback(UpdateCallback* callback)
{
	LinkedList_addLast(update_callbackList, callback);
}

void Logic_update(Time t)
{	
	UpdateCallback* callback;
	Node* p = update_callbackList->first; 
	for (;p != NULL; p = p->next)
	{
		callback = (UpdateCallback*)p->item;
		callback->func(callback->data, t);
	}	
}

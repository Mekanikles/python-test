#include "ObjectType.h"

#include "GameObject.h"
#include "Physics.h"
#include "LinkedList.h"

ObjectType* ObjectType_new()
{
	struct ObjectType* obj = (struct ObjectType*)malloc(sizeof(struct ObjectType));
	obj->collisionListeners = NULL;
	obj->objectlist = GameObjectList_new(); 
	obj->id = OBJECTTYPE_UNDEFINED;
	
	return obj;
}


void ObjectType_destroy(void* obj)
{
	ObjectType* self = (ObjectType*)obj;
	GameObjectList_destroy(self->objectlist);
	if (self->collisionListeners != NULL)
	{
		LinkedList_destroy(self->collisionListeners);
	}
	self->id = OBJECTTYPE_UNDEFINED;
	free(self);
}

#ifndef OBJECTTYPE_H_
#define OBJECTTYPE_H_

#include "Globals.h"

#define OBJECTTYPE_UNDEFINED -1


struct LinkedList;
struct GameObjectList;

typedef struct ObjectType
{
	struct LinkedList* collisionListeners;
	struct GameObjectList* objectlist;
	
	unsigned int id;
} ObjectType;

ObjectType* ObjectType_new();
void ObjectType_destroy(void* obj);

#endif

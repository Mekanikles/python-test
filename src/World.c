#include "World.h"

#include "GameObject.h"
#include "ObjectType.h"
#include "Physics.h"

#include "ArrayList.h"

static WorldObject* currentWorld = NULL;
static unsigned int objectCount = 0;
static unsigned int typeCount = 0;

WorldObject* WorldObject_new()
{
	WorldObject* obj = (WorldObject*)malloc(sizeof(WorldObject));

	obj->objectTypeArray = ArrayList_new(16);

	obj->collisionlist = CollisionDataList_new();
	return obj;
}

void WorldObject_destroy(void* obj)
{
	WorldObject* self = (WorldObject*)obj;
	ArrayList_destroy(self->objectTypeArray, &ObjectType_destroy);
	CollisionDataList_destroy(self->collisionlist);
	free(self);
}	

void World_setWorldObject(WorldObject* world)
{
	currentWorld = world;
}
void World_refresh()
{
	CollisionDataList_clear(currentWorld->collisionlist);
}

void World_addGameObject(struct GameObject* object, unsigned int type)
{
	if (object->type != OBJECTTYPE_UNDEFINED)
	{
		fprintf(stderr, "Warning: don't try to add an object more than once, remove it first.\n");
		return;
	}
	ObjectType* ot = World_getObjectType(type);
	if (ot == NULL)
	{
		ot = ObjectType_new();
		ot->id = type;
		ArrayList_set(currentWorld->objectTypeArray, type, ot);
		if (type >= typeCount)
			typeCount = type + 1;
	}
	object->type = type;
	GameObjectList_addLast(ot->objectlist, object);
	objectCount++;	
}

void World_removeGameObject(GameObject* object)
{
	if (object->type == OBJECTTYPE_UNDEFINED)
	{
		fprintf(stderr, "Warning: you're trying to remove an object not in world, stop that.\n");
		return;
	}
	ObjectType* type = World_getObjectType(object->type);
	if (GameObjectList_remove(type->objectlist, object))
	{
		objectCount--;		
		object->type = OBJECTTYPE_UNDEFINED;
	}
}

unsigned int World_getObjectCount()
{
	return objectCount;
}
unsigned int World_getTypeCount()
{
	return typeCount;
}

ObjectType* World_getObjectType(int type)
{
	return ArrayList_get(currentWorld->objectTypeArray, type);
}


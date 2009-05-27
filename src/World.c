#include "World.h"

#include "GameObject.h"
#include "Physics.h"

static WorldObject* currentworld = NULL;
static unsigned int objectCount = 0;

WorldObject* WorldObject_new()
{
	WorldObject* obj = (WorldObject*)malloc(sizeof(WorldObject));

	obj->objectlist = GameObjectList_new();
	obj->collisionlist = CollisionList_new();
	return obj;
}

void WorldObject_destroy(WorldObject* obj)
{
	GameObjectList_destroy(obj->objectlist);
	CollisionList_destroy(obj->collisionlist);
	free(obj);
}	

void World_setWorldObject(WorldObject* world)
{
	currentworld = world;
}
void World_refresh()
{
	assert(currentworld);
	CollisionList_clear(currentworld->collisionlist);
}

void World_addGameObject(GameObject* object)
{
	assert(object);
	assert(currentworld);
	GameObjectList_addLast(currentworld->objectlist, object);
	objectCount++;	
	
	fprintf(stderr, "Added %u to List: ", object->id);
	GameObject* p;
	for (p = currentworld->objectlist->first; p != NULL; p=p->next)
	{
		fprintf(stderr, "%u ", p->id);
	}
	fprintf(stderr, "\n");
}

void World_removeGameObject(GameObject* object)
{
	assert(object);
	assert(currentworld);

	if (GameObjectList_remove(currentworld->objectlist, object))
	{
		objectCount--;
	
		fprintf(stderr, "Removed %u from List: ", object->id);
		GameObject* p;
		for (p = currentworld->objectlist->first; p != NULL; p=p->next)
		{
			fprintf(stderr, "%u ", p->id);
		}
		fprintf(stderr, "\n");
	}
}

unsigned int World_getObjectCount()
{
	return objectCount;
}

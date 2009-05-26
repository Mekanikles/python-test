#include "World.h"

#include "GameObject.h"
#include "Physics.h"

static WorldObject* currentworld = NULL;

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
	GameObjectList_remove(currentworld->objectlist, object);
}

void World_removeGameObject(GameObject* object)
{
	assert(object);
}

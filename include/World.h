#ifndef WORLD_H_
#define WORLD_H_

#include "Globals.h"

struct GameObjectList;
struct CollisionList;
struct GameObject;

typedef struct WorldObject
{
	struct GameObjectList* objectlist;
	struct CollisionList* collisionlist;		
} WorldObject;


WorldObject* WorldObject_new();
void WorldObject_destroy(WorldObject* obj);

void World_setWorldObject(WorldObject* world);
void World_flush();

void World_addGameObject(struct GameObject* object);




#endif


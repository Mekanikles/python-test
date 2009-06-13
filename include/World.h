#ifndef WORLD_H_
#define WORLD_H_

#include "Globals.h"

struct GameObjectList;
struct CollisionDataList;
struct GameObject;
struct ObjectType;
struct ArrayList;

typedef struct WorldObject
{
	struct ArrayList* objectTypeArray;
	struct CollisionDataList* collisionlist;	
} WorldObject;


WorldObject* WorldObject_new();
void WorldObject_destroy(void* obj);

void World_setWorldObject(WorldObject* world);
void World_refresh();

void World_addGameObject(struct GameObject* object, unsigned int type);
void World_removeGameObject(struct GameObject* object);
unsigned int World_getObjectCount();
unsigned int World_getTypeCount();
struct ObjectType* World_getObjectType(int type);

void World_registerNewObjectType(struct ObjectType* type);

#endif


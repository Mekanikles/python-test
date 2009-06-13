#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "Globals.h" 
struct GameObject;
struct ObjectType;
struct GameObjectList;
struct WorldObject;

typedef struct CollisionData
{
	struct CollisionData* next;
	struct CollisionData* prev;

	struct GameObject* obj1;
	struct GameObject* obj2;
	
} CollisionData;

CollisionData* CollisionData_new();


typedef struct CollisionCallback
{
	void (*func)(void* data, CollisionData* coll);
	void* data;
} CollisionCallback;


CollisionCallback* CollisionCallback_new(void (*func)(void* data, CollisionData* coll), void* data);


typedef struct CollisionDataList
{
	CollisionData* first;
	CollisionData* last;
} CollisionDataList;

CollisionDataList* CollisionDataList_new();
void CollisionDataList_destroy(CollisionDataList* list);
void CollisionDataList_clear(CollisionDataList* list);
void CollisionDataList_addLast(CollisionDataList* list, CollisionData* obj);


int Physics_init();
void Physics_destroy();

void Physics_update(struct WorldObject* world);
void Physics_detectCollisions(struct WorldObject* world);
int gameObjectsColliding(struct GameObject* self, struct GameObject* obj);

void Physics_addCollisionCallbackOnGameObject(struct CollisionCallback* callback, struct GameObject* object);
void Physics_addCollisionCallbackOnObjectType(struct CollisionCallback* callback, struct ObjectType* type);
void Physics_addCollisionCheck(int type1, int type2);

int Physics_getCheckCounter();
void Physics_resetCheckCounter();



#endif

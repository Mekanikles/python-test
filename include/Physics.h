#ifndef PHYSICS_H_
#define PHYSICS_H_

#include "Globals.h" 
#include "GameObject.h"

typedef struct Collision
{
	struct Collision* next;
	struct Collision* prev;

	struct GameObject* obj1;
	struct GameObject* obj2;
} Collision;

struct Collision* Collision_new();


typedef struct CollisionList
{
	struct Collision* first;
	struct Collision* last;
} CollisionList;

struct CollisionList* CollisionList_new();
void CollisionList_destroy(struct CollisionList* list);
void CollisionList_clear(struct CollisionList* list);
void CollisionList_addLast(struct CollisionList* list, struct Collision* obj);



void Physics_update(struct GameObjectList* list);
void Physics_detectCollisions(struct GameObjectList* list, struct CollisionList* collisions);
int gameObjectsColliding(struct GameObject* self, struct GameObject* obj);

#endif

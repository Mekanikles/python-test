#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Globals.h"

struct CollisionCallback;
struct GameObjectList;
struct ObjectType;
struct LinkedList;

typedef struct GameObject
{
	struct GameObject* next;
	struct GameObject* prev;
	struct GameObjectList* list;
	
	void* scriptobject;
	struct LinkedList* collisionListeners;
	
	float x,y;
	float w,h;
	float vx, vy;
	unsigned int id;
	int type;

} GameObject;

struct GameObject* GameObject_new();
void GameObject_destroy(void* obj);

typedef struct GameObjectList
{
	struct GameObject* first;
	struct GameObject* last;
} GameObjectList;

struct GameObjectList* GameObjectList_new();
void GameObjectList_destroy(struct GameObjectList* list);
void GameObjectList_addLast(struct GameObjectList* list, struct GameObject* obj);
int GameObjectList_remove(struct GameObjectList* list, struct GameObject* obj);


#endif

#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Globals.h"

struct GameObjectList;

typedef struct GameObject
{
	struct GameObject* next;
	struct GameObject* prev;
	struct GameObjectList* list;

	float x,y;
	float w,h;
	float vx, vy;
	unsigned int id;

} GameObject;

struct GameObject* GameObject_new();


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

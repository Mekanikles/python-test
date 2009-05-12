#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

struct GameObject
{
	struct GameObject* next;
	struct GameObject* prev;

	float x,y;
	float w,h;
	float vx, vy;
};

struct GameObject* GameObject_new();


struct GameObjectList
{
	struct GameObject* first;
	struct GameObject* last;
};

struct GameObjectList* GameObjectList_new();
void GameObjectList_delete(struct GameObjectList* list);
void GameObjectList_addLast(struct GameObjectList* list, struct GameObject* obj);


#endif

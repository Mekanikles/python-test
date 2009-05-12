#include "GameObject.h"
#include "stdlib.h"


struct GameObject* GameObject_new()
{
	struct GameObject* obj = (struct GameObject*)malloc(sizeof(struct GameObject));

	obj->x=0;
	obj->y=0;
	obj->vx=0;
	obj->vy=0;
	obj->w=32;
	obj->h=16;
	return obj;
}


struct GameObjectList* GameObjectList_new()
{
	struct GameObjectList* list = (struct GameObjectList*)malloc(sizeof(struct GameObjectList));
	list->first = NULL;
	list->last = NULL;
	return list;
}

void GameObjectList_delete(struct GameObjectList* list)
{	
	struct GameObject* p = list->first;
	struct GameObject* t = NULL;

	if (list == NULL)
		return;
			
	while(p != NULL)
	{	
		t=p->next;
		free(p);
		p = t;
	}

	free(list);
		
	list = NULL;
}

void GameObjectList_addLast(struct GameObjectList* list, struct GameObject* obj)
{
	if (list->first == NULL)
	{	
		list->first = obj;
		list->last = obj;
		obj->next = NULL;
		obj->prev = NULL;
	}
	else
	{
		list->last->next = obj;
		obj->prev = list->last;
		obj->next = NULL;
		list->last = obj;	
	}
}



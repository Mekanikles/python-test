#include "GameObject.h"

#include "LinkedList.h"
#include "ObjectType.h"

static unsigned int objects = 0;

struct GameObject* GameObject_new()
{
	struct GameObject* obj = (struct GameObject*)malloc(sizeof(struct GameObject));
	obj->next = NULL;
	obj->prev = NULL;
	obj->list = NULL;
	obj->scriptobject = NULL;
	obj->collisionListeners = NULL;
	
	obj->x=0;
	obj->y=0;
	obj->vx=0;
	obj->vy=0;
	obj->w=32;
	obj->h=16;
	
	obj->id = objects++;
	obj->type = OBJECTTYPE_UNDEFINED;	
		
	return obj;
}

void GameObject_destroy(void* obj)
{
	GameObject* self = (GameObject*)obj;
	if (self->collisionListeners != NULL)
	{
		LinkedList_destroy(self->collisionListeners);
	}
	free(self);
}


struct GameObjectList* GameObjectList_new()
{
	struct GameObjectList* list = (struct GameObjectList*)malloc(sizeof(struct GameObjectList));
	list->first = NULL;
	list->last = NULL;
	return list;
}

void GameObjectList_destroy(struct GameObjectList* list)
{	
	struct GameObject* p = list->first;
	struct GameObject* t = NULL;

	if (list == NULL)
		return;
			
	while(p != NULL)
	{	
		t=p->next;
		GameObject_destroy(p);
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
	obj->list = list;
}

int GameObjectList_remove(struct GameObjectList* list, struct GameObject* obj)
{
	assert(list->first);
	assert(obj);
	if (obj->list != list)
	{
		fprintf(stderr, "Cannot remove object %u, object not in list.\n", obj->id);
		return 0;
	}
	
	if (obj->next != NULL)
	{	
		obj->next->prev = obj->prev;
	}
	if (obj->prev != NULL)
	{	
		obj->prev->next = obj->next;
	}
	if (list->first == obj)
	{
		list->first = obj->next;
	}
	if (list->last == obj)
	{
		list->last = obj->prev;
	}
	obj->list = NULL;
	
	return 1;
}




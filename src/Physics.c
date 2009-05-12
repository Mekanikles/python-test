#include "Physics.h"
#include "stdlib.h"

struct Collision* Collision_new(struct GameObject* obj1, struct GameObject* obj2)
{
	struct Collision* col = (struct Collision*)malloc(sizeof(struct Collision));
	col->next = NULL;
	col->prev = NULL;
	
	col->obj1 = obj1;
	col->obj2 = obj2;
	return col;
}


struct CollisionList* CollisionList_new()
{
	struct CollisionList* list = (struct CollisionList*)malloc(sizeof(struct CollisionList));
	list->first = NULL;
	list->last = NULL;
	return list;
}

void CollisionList_delete(struct CollisionList* list)
{	
	struct Collision* p = list->first;
	struct Collision* t = NULL;

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

void CollisionList_addLast(struct CollisionList* list, struct Collision* obj)
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



void Physics_update(struct GameObjectList* list)
{
	struct GameObject* p1 = NULL;
	for (p1 = list->first; p1 != NULL; p1 = p1->next)
	{
		p1->vy += 0.98f;
		p1->x += p1->vx;
		p1->y += p1->vy;
	}
}


void Physics_detectCollisions(struct GameObjectList* list, struct CollisionList* collisions)
{
	struct GameObject* p1 = NULL;
	struct GameObject* p2 = NULL;
	for (p1 = list->first; p1 != NULL; p1 = p1->next)
	{
		for (p2 = list->first; p2 != NULL; p2 = p2->next)
		{
			if (p1 != p2)
			{	
				if (gameObjectsColliding(p1, p2))
				{
					CollisionList_addLast(collisions, Collision_new(p1, p2));
				}			
			}
		}	
	}
}

int gameObjectsColliding(struct GameObject* self, struct GameObject* obj)
{
	return !(self->x + self->w < obj->x ||
		self->x > obj->x + obj->w ||
		self->y + self->h < obj->y ||
		self->y > obj->y + obj->h);
}




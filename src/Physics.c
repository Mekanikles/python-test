#include "Physics.h"
#include "stdlib.h"
#include "LinkedList.h"

#include "ObjectType.h"
#include "GameObject.h"
#include "World.h"

LinkedList* activeCollisionChecks;

static int numOfChecks = 0;

typedef struct TypePair
{
	int type1;
	int type2;
} TypePair;

TypePair* TypePair_new(int type1, int type2)
{
	TypePair* self = (TypePair*)malloc(sizeof(TypePair));
	self->type1 = type1;
	self->type2 = type2;
	return self;
}

CollisionCallback* CollisionCallback_new(void (*func)(void* data, CollisionData* coll), void* data)
{
	CollisionCallback* self = (CollisionCallback*)malloc(sizeof(CollisionCallback));
	
	assert(func);
	self->func = func;
	self->data = data;	
	return self;
}


CollisionData* CollisionData_new(struct GameObject* obj1, struct GameObject* obj2)
{
	CollisionData* col = (CollisionData*)malloc(sizeof(CollisionData));
	col->next = NULL;
	col->prev = NULL;
	
	col->obj1 = obj1;
	col->obj2 = obj2;
	return col;
}


CollisionDataList* CollisionDataList_new()
{
	CollisionDataList* list = (CollisionDataList*)malloc(sizeof(CollisionDataList));
	list->first = NULL;
	list->last = NULL;
	return list;
}

void CollisionDataList_destroy(CollisionDataList* list)
{	
	assert(list);

	CollisionDataList_clear(list);
	free(list);
		
	list = NULL;
}


void CollisionDataList_clear(CollisionDataList* list)
{
	CollisionData* p = list->first;
	CollisionData* t = NULL;
				
	assert(list);

	while(p != NULL)
	{	
		t=p->next;
		free(p);
		p = t;
	}
	
	list->first = NULL;
	list->last = NULL;
}


void CollisionDataList_addLast(CollisionDataList* list, CollisionData* obj)
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


int Physics_init()
{
	activeCollisionChecks = LinkedList_new();

	return 0;
}

void Physics_destroy()
{
	LinkedList_destroy(activeCollisionChecks);
}


void Physics_update(struct WorldObject* world)
{
	int i;
	int cap = World_getTypeCount();
	ObjectType* ot;
	for (i = 0; i < cap; i++)
	{
		ot = World_getObjectType(i);
		if (ot == NULL)
			continue;
			
		GameObject* p1 = NULL;
		for (p1 = ot->objectlist->first; p1 != NULL; p1 = p1->next)
		{
			//p1->vy += 0.98f;
			p1->x += p1->vx;
			p1->y += p1->vy;
		}
	}
}


void Physics_detectCollisions(struct WorldObject* world)
{
	Node* n;
	TypePair* t;
	ObjectType* ot1;
	ObjectType* ot2;
	GameObject* p1;
	GameObject* p2;
	for (n = activeCollisionChecks->first; n != NULL; n = n->next)
	{
		t = (TypePair*)n->item;
		ot1 = World_getObjectType(t->type1);
		ot2 = World_getObjectType(t->type2);
		
		if (ot1 == NULL || ot2 == NULL)
			continue;
		
		for (p1 = ot1->objectlist->first; p1 != NULL; p1 = p1->next)
		{
			for (p2 = ot2->objectlist->first; p2 != NULL; p2 = p2->next)
			{
				if (p1 != p2)
				{	
					numOfChecks++;
					if (gameObjectsColliding(p1, p2))
					{
						CollisionDataList_addLast(world->collisionlist, CollisionData_new(p1, p2));
					}			
				}
			}	
		}
	}
}

int gameObjectsColliding(struct GameObject* self, struct GameObject* obj)
{
	return !(self->x + self->w <= obj->x ||
		self->x >= obj->x + obj->w ||
		self->y + self->h <= obj->y ||
		self->y >= obj->y + obj->h);
}

void Physics_addCollisionCallbackOnGameObject(CollisionCallback* callback, GameObject* object)
{
	if (object->collisionListeners == NULL)
	{
		object->collisionListeners = LinkedList_new();
	}
	
	LinkedList_addLast(object->collisionListeners, callback);
}
 
void Physics_addCollisionCallbackOnObjectType(CollisionCallback* callback, ObjectType* type)
{
	if (type->collisionListeners == NULL)
	{
		type->collisionListeners = LinkedList_new();
	}
	
	LinkedList_addLast(type->collisionListeners, callback);
}

void Physics_addCollisionCheck(int type1, int type2)
{
	TypePair* pair = TypePair_new(type1, type2);
	
	LinkedList_addLast(activeCollisionChecks, pair);
}

int Physics_getCheckCounter()
{
	return numOfChecks;
}
void Physics_resetCheckCounter()
{
	numOfChecks = 0;
}




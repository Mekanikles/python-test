#include "ArrayList.h"



ArrayList* ArrayList_new(unsigned int capacity)
{
	ArrayList* self = (ArrayList*)malloc(sizeof(ArrayList));
	
	self->capacity = capacity;
	self->array = (void**)malloc(capacity * sizeof(void*));
	int i;
	for (i = 0; i < capacity; i++)
		self->array[i] = NULL;
	
	return self;
}

void ArrayList_destroy(struct ArrayList* list, void (*destructor)(void* item))
{
	int i;
	if (destructor)
	{
		for (i = 0; i < list->capacity; i++)
		{
			if (list->array[i] != NULL)
				destructor(list->array[i]);
		}
	}
	else
	{
		for (i = 0; i < list->capacity; i++)
		{
			if (list->array[i] != NULL)
				free(list->array[i]);
		}
	}

	free(list);	
}

void ArrayList_clear(struct ArrayList* list)
{
	int i;
	for (i = 0; i < list->capacity; i++)
		list->array[i] = NULL;
}

void ArrayList_set(struct ArrayList* list, unsigned int pos, void* item)
{
	if (pos >= list->capacity)
	{
		unsigned int newcap = list->capacity; 
		while (newcap <= pos)
		{
			newcap = newcap << 1;
		}
		void** newarray = (void**)malloc(newcap * sizeof(void*));
		int i;
		for (i = 0; i < list->capacity; i++)
			newarray[i] = list->array[i];

		for (i = list->capacity; i < newcap; i++)
			newarray[i] = NULL;
			
		free(list->array);
		list->array = newarray;
	}
	
	list->array[pos] = item;
}

void* ArrayList_get(struct ArrayList* list, unsigned int pos)
{
	if (pos < list->capacity)
		return  list->array[pos];
	else
		return NULL;
}

unsigned int ArrayList_getCapacity(struct ArrayList* list)
{
	return list->capacity;
}




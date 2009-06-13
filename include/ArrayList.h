#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

#include "Globals.h"

typedef struct ArrayList
{
	void** array;
	unsigned int capacity;
} ArrayList;


ArrayList* ArrayList_new(unsigned int capacity);
void ArrayList_destroy(struct ArrayList* list, void (*destructor)(void* item));
void ArrayList_clear(struct ArrayList* list);
void ArrayList_set(struct ArrayList* list, unsigned int pos, void* item);
void* ArrayList_get(struct ArrayList* list, unsigned int pos);
unsigned int ArrayList_getCapacity(struct ArrayList* list);














#endif

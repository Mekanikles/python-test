#ifndef LOGIC_H_
#define LOGIC_H_

#include "Globals.h" 
#include "GameObject.h"

struct CollisionList;

int Logic_init();
void Logic_destroy();

void Logic_handleCollisions(struct CollisionList* collisions);

void Logic_addUpdateCallback(void (*func)(void* data, Time t), void* data);
void Logic_update(Time t);
void Logic_setupGame();

#endif

#ifndef LOGIC_H_
#define LOGIC_H_

#include "Globals.h" 
#include "GameObject.h"

struct CollisionList;

int Logic_init();
void Logic_destroy();

void Logic_handleCollisions(struct CollisionList* collisions);




#endif

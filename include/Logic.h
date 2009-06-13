#ifndef LOGIC_H_
#define LOGIC_H_

#include "Globals.h" 
#include "GameObject.h"

struct CollisionList;
struct CollisionDataList;
struct WorldObject;

typedef struct UpdateCallback
{
	void (*func)(void* data, Time t);
	void* data;
} UpdateCallback;

UpdateCallback* UpdateCallback_new(void (*func)(void* data, Time t), void* data);


int Logic_init();
void Logic_destroy();

void Logic_handleCollisions(struct WorldObject* world);

void Logic_addUpdateCallback(UpdateCallback* callback);
void Logic_update(Time t);
void Logic_setupGame();

#endif

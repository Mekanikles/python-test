#include "Logic.h"

#include "Physics.h"
#include "Script.h"

int Logic_init()
{
	if (Script_init() != 0)
		BREAK_ERROR;

	return 0;
}
void Logic_destroy()
{
	Script_destroy();
}

void Logic_handleCollisions(struct CollisionList* collisions)
{
	struct Collision* p = NULL;
	for (p = collisions->first; p != NULL; p = p->next)
	{
		//fprintf(stderr, "collide\n");
		Script_callFunction(p->obj1);	
	}
}

#include "Engine.h"

#include "GameObject.h"
#include "Physics.h"
#include "Graphics.h"
#include "Logic.h"
#include "World.h"
#include "Timer.h"

#include "GL/glfw.h"

static int done = 1;

WorldObject* theworld = NULL;
Time time = 0;	


int Engine_init()
{
	if (Graphics_init() != 0)
		BREAK_ERROR;

	if (Timer_init() != 0)
		BREAK_ERROR;

	if (Logic_init() != 0)
		BREAK_ERROR;
	
	theworld = WorldObject_new();
	World_setWorldObject(theworld);	
		
	done = 0;
	
	return 0;
}

void Engine_destroy()
{
	Logic_destroy();
	
	Timer_destroy();
	
	Graphics_destroy();
}

void Engine_stop()
{
	done = 1;
}

int Engine_isRunning()
{
	return !done;
}

void Engine_run()
{
	double timestart = glfwGetTime();	
	int fps = 0;	
	int objcount = 0;	
		
	time = Timer_getTime();		
	
	while(!done)
	{
		Timer_update();
		time = Timer_getTime();	
		done = done | (int)glfwGetKey(GLFW_KEY_ESC);
		
		if (glfwGetMouseButton(0))
		{
			struct GameObject* obj = GameObject_new();
			obj->x = 50; obj->y = 50; obj->vx = 7; obj->vy=-5;
			World_addGameObject(obj);
			objcount++;
		}
			
		World_refresh();
		
		Logic_update(time);	
			
		Physics_update(theworld->objectlist);
		
		Physics_detectCollisions(theworld->objectlist, theworld->collisionlist);
			
		Logic_handleCollisions(theworld->collisionlist);	
		
		Graphics_renderScene(theworld->objectlist);
		
		Graphics_refresh();
		
		fps++;
		if (glfwGetTime() - timestart >= 1.0)
		{
			fprintf(stderr, "Fps: %i, Objects: %i\n", fps, objcount);
			
			fps = 0;
			timestart = glfwGetTime();
		}
	}
	
	WorldObject_destroy(theworld);
}

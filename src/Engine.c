#include "Engine.h"

#include "GameObject.h"
#include "Physics.h"
#include "Graphics.h"
#include "Logic.h"
#include "World.h"
#include "Timer.h"
#include "Input.h"
#include "Script.h"

#include "GL/glfw.h"

static int done = 1;
static int initialize = 0;

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
		
	if (Physics_init() != 0)
		BREAK_ERROR;
		
	if (Input_init() != 0)
		BREAK_ERROR;
		
	theworld = WorldObject_new();
	World_setWorldObject(theworld);	
		
	done = 0;

	initialize = 1;
	return 0;
}

void Engine_destroy()
{
	Input_destroy();
	
	Logic_destroy();
	
	Physics_destroy();
	
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

	time = Timer_getTime();		
	
	while(!done)
	{
		Timer_update();
		time = Timer_getTime();	
	
		Input_handleInput(time);					
			
		World_refresh();
			
		Logic_update(time);	
			
		Physics_update(theworld);
		
		Physics_detectCollisions(theworld);
			
		Logic_handleCollisions(theworld);	
		
		Graphics_renderScene(theworld);
		
		Graphics_refresh();
		
		fps++;
		if (glfwGetTime() - timestart >= 1.0)
		{
			fprintf(stderr, "Fps: %i, Objects: %u, Collision checks: %i, Script calls: %i\n", fps, World_getObjectCount(), Physics_getCheckCounter(), Script_getCallCounter());
			
			Physics_resetCheckCounter();
			Script_resetCallCounter();
			fps = 0;
			timestart = glfwGetTime();
		}
		
		glfwSleep(0.033);
	}
	
	WorldObject_destroy(theworld);
}

#include "stdio.h"
#include "string.h"


#include "Globals.h"
#include "GameObject.h"
#include "Physics.h"
#include "Graphics.h"
#include "Logic.h"

#include "GL/glfw.h"

int destroy()
{
	Graphics_destroy();
	
	Logic_destroy();
	
	return 0;
}

int init()
{
	if (Logic_init() != 0)
		BREAK_ERROR;
		
	if (Graphics_init() != 0)
		BREAK_ERROR;

	g_done = 0;
	
	return 1;
}

int mainLoop()
{	
	double timestart = glfwGetTime();	
	int fps = 0;	
	int objcount = 0;	
		
	struct GameObjectList* objectlist = GameObjectList_new();
	struct CollisionList* collisionlist;		
		
	while(!g_done)
	{
		glfwPollEvents();
		g_done = g_done | (int)glfwGetKey(GLFW_KEY_ESC);
		
		if (glfwGetMouseButton(0))
		{
			struct GameObject* obj = GameObject_new();
			obj->x = 50; obj->y = 50; obj->vx = 7; obj->vy=-5;
			GameObjectList_addLast(objectlist, obj);
			objcount++;
		}
			
		Physics_update(objectlist);
		
		collisionlist = CollisionList_new();
		Physics_detectCollisions(objectlist, collisionlist);
			
		Logic_handleCollisions(collisionlist);	
		CollisionList_delete(collisionlist);
		
		Graphics_renderScene(objectlist);
		
		glfwSwapBuffers();
	
		fps++;
		if (glfwGetTime() - timestart >= 1.0)
		{
			fprintf(stderr, "Fps: %i, Objects: %i\n", fps, objcount);
			
			fps = 0;
			timestart = glfwGetTime();
		}
	}
	
	GameObjectList_delete(objectlist);

	return 0;
}


int main(int argc, char *argv[])
{
	fprintf(stderr, "Physics/python test\n");

	if (init() != 0)
		mainLoop();
		
	destroy();
	
	return 0;
}

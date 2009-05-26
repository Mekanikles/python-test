#include "Timer.h"

#include "GL/glfw.h"

static Time currentTime = 0;
static double startTime = 0;

int Timer_init()
{
	startTime = glfwGetTime();
	return 0;
}

void Timer_destroy()
{

}

void Timer_update()
{
	glfwPollEvents();
	currentTime = (float)(glfwGetTime() - startTime);
}

Time Timer_getTime()
{
	return currentTime;
}

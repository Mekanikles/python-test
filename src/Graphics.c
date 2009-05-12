#include "Graphics.h"

#include "GL/glfw.h"

#include "stdio.h"

static int GLFWCALL closeWindowCallBack(void* data)
{
	g_done = 1;
	return GL_TRUE;
} 

int Graphics_init()
{
	if (glfwInit() != GL_TRUE)
		BREAK_ERROR;
	
	if (glfwOpenWindow(640, 480, 0, 0, 0, 0, 0, 0, GLFW_WINDOW) != GL_TRUE)
		BREAK_ERROR;

	glfwSetWindowCloseCallback(&closeWindowCallBack, NULL);

	glMatrixMode(GL_PROJECTION_MATRIX);
	glLoadIdentity();
	glOrtho(0,640,480,0,-1, 1);
	glMatrixMode(GL_MODELVIEW_MATRIX);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	return 0;
}

void Graphics_destroy()
{
	glfwTerminate();
}

void Graphics_renderScene(struct GameObjectList* list)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	{
		struct GameObject* p1 = NULL;
		for (p1 = list->first; p1 != NULL; p1 = p1->next)
		{
			glVertex2f(p1->x, p1->y);
			glVertex2f(p1->x, p1->y + p1->h);
			glVertex2f(p1->x + p1->w, p1->y + p1->h);
			glVertex2f(p1->x + p1->w, p1->y);
		}
	}
	glEnd();
}


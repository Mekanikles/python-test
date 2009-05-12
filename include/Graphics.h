#ifndef GRAHPICS_H_
#define GRAPHICS_H_

#include "Globals.h"
#include "GameObject.h"

int Graphics_init();
void Graphics_destroy();

void Graphics_renderScene(struct GameObjectList* objectlist);

#endif


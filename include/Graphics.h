#ifndef GRAHPICS_H_
#define GRAPHICS_H_

#include "Globals.h"

struct WorldObject;

int Graphics_init();
void Graphics_destroy();

void Graphics_renderScene(struct WorldObject* world);
void Graphics_refresh();

#endif


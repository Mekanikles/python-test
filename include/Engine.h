#ifndef ENGINE_H_
#define ENGINE_H_

#include "Globals.h"

int Engine_init();
void Engine_destroy();
void Engine_run();

void Engine_stop();
int Engine_isRunning();

#endif

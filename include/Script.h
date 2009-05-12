#ifndef SCRIPT_H_
#define SCRIPT_H_

#include "Globals.h"

struct GameObject;

int Script_init();
void Script_destroy();

void Script_callFunction(struct GameObject* obj);


#endif

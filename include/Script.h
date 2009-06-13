#ifndef SCRIPT_H_
#define SCRIPT_H_

#include "Globals.h"

#include "Events.h"
#include "Input.h"
#include "Physics.h"

struct GameObject;

int Script_init(const char* script);
void Script_destroy();

void Script_callTimedFunction(void* functionObject, Time t);
void Script_callInputFunction(void* functionObject, InputData* input);
void Script_callCollisionFunction(void* functionObject, CollisionData* coll);

void Script_callListeners();
void Script_callMain();
void Script_handleEvent(enum EventType e);

void Script_addListener(void* listener);

int Script_getCallCounter();
void Script_resetCallCounter();

#endif

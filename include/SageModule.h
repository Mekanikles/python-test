#ifndef SAGEINTERFACE_H_
#define SAGEINTERFACE_H_

#include "Python.h"

struct GameObject;

typedef struct Sage_GameObject
{
    PyObject_HEAD
    struct GameObject* gameobject;
} Sage_GameObject;


struct Sage_GameObject* Sage_GameObject_new(struct GameObject* gameobj);



int initModule();

#endif

#ifndef SAGEMODULE_GAMEOBJECT_H_
#define SAGEMODULE_GAMEOBJECT_H_

#include "Python.h"

struct GameObject;
typedef struct Sage_GameObject
{
    PyObject_HEAD
    struct GameObject* gameobject;
} Sage_GameObject;

extern PyTypeObject Sage_GameObject_type;


#endif

#include "SageModule.h"
#include "Globals.h"

#include "GameObject.h"
#include "World.h"
#include "Script.h"
#include "Timer.h"
#include "Physics.h"
#include "Logic.h"
#include "Input.h"


/**** Exported Datatypes ****/
#include "SageModule_GameObject.h"
#include "SageModule_Input.h"

/**** Exported Function Declarations ****/

static PyObject* Sage_addObject(PyObject*, PyObject*);
static PyObject* Sage_removeObject(PyObject*, PyObject*);
static PyObject* Sage_registerUpdateFunction(PyObject*, PyObject*);
static PyObject* Sage_objectsColliding(PyObject*, PyObject*);

static PyObject* Sage_registerInputListener(PyObject*, PyObject*);

static PyObject* Sage_setObjectPosX(PyObject*, PyObject*);
static PyObject* Sage_setObjectPosY(PyObject*, PyObject*);
static PyObject* Sage_getObjectPosX(PyObject*, PyObject*);
static PyObject* Sage_getObjectPosY(PyObject*, PyObject*);
static PyObject* Sage_setObjectVelX(PyObject*, PyObject*);
static PyObject* Sage_setObjectVelY(PyObject*, PyObject*);
static PyObject* Sage_getObjectVelX(PyObject*, PyObject*);
static PyObject* Sage_getObjectVelY(PyObject*, PyObject*);


static PyMethodDef exportSageMethods[] = 
{
	{"registerUpdateFunction",  Sage_registerUpdateFunction, METH_VARARGS, "Register a function that runs once every frame"},
	{"registerInputListener", Sage_registerInputListener, METH_VARARGS, "Register an input listener function"},
	
	{"addObject",  Sage_addObject, METH_VARARGS, "Add a game object to the world."},
	{"removeObject",  Sage_removeObject, METH_VARARGS, "Remove a game object from the world."},
	{"objectsColliding",  Sage_objectsColliding, METH_VARARGS, "Detects whether two objects collides or not."},
	{"setObjectPosX",  Sage_setObjectPosX, METH_VARARGS, "Set the x position of a Game Object."},
	{"setObjectPosY",  Sage_setObjectPosY, METH_VARARGS, "Set the y position of a Game Object."},
	{"getObjectPosX",  Sage_getObjectPosX, METH_VARARGS, "get the x position of a Game Object."},
	{"getObjectPosY",  Sage_getObjectPosY, METH_VARARGS, "get the y position of a Game Object."},
	{"setObjectVelX",  Sage_setObjectVelX, METH_VARARGS, "Set the x velocity of a Game Object."},
	{"setObjectVelY",  Sage_setObjectVelY, METH_VARARGS, "Set the y velocity of a Game Object."},
	{"getObjectVelX",  Sage_getObjectVelX, METH_VARARGS, "get the x velocity of a Game Object."},
	{"getObjectVelY",  Sage_getObjectVelY, METH_VARARGS, "get the y velocity of a Game Object."},
	{NULL, NULL, 0, NULL}
};

int initModule()
{
    PyObject* m;

    if (PyType_Ready(&Sage_GameObject_type) < 0)
        BREAK_ERROR;
    if (PyType_Ready(&Sage_InputData_type) < 0)
        BREAK_ERROR;
		
    m = Py_InitModule("sage", exportSageMethods);

    Py_INCREF(&Sage_GameObject_type);
    PyModule_AddObject(m, "GameObject", (PyObject*)&Sage_GameObject_type);
    Py_INCREF(&Sage_InputData_type);
    PyModule_AddObject(m, "InputData", (PyObject*)&Sage_InputData_type);
	
	return 0;
}


/**** Exported Function Bodies ****/

static PyObject* Sage_registerUpdateFunction(PyObject* self, PyObject* args)
{
    PyObject *result = NULL;
    PyObject *func;

    if (PyArg_ParseTuple(args, "O", &func)) 
	{
        if (!PyCallable_Check(func)) 
		{
            PyErr_SetString(PyExc_TypeError, "parameter must be callable");
            return NULL;
        }
        Py_XINCREF(func);

		Logic_addUpdateCallback(&Script_callTimedFunction, func);
		
        result = Py_BuildValue("");
    }
	
    return result;
}

static PyObject* Sage_registerInputListener(PyObject* self, PyObject* args)
{
    PyObject* result = NULL;
    PyObject* func;
	InputData* inputdata; 

    if (PyArg_ParseTuple(args, "OO", &func, &inputdata)) 
	{
        if (!PyCallable_Check(func)) 
		{
            PyErr_SetString(PyExc_TypeError, "parameter 1 must be callable");
            return NULL;
        }
        Py_XINCREF(func);

		InputData data;
		data.controller = inputdata->controller;
		data.button = inputdata->button;		
		data.state = inputdata->state;
		data.value = inputdata->value;
			
		Input_addInputCallback(&Script_callInputFunction, func, data);
		
        result = Py_BuildValue("");
    }
	
    return result;
}

static PyObject* Sage_addObject(PyObject *self, PyObject *args)
{	
	Sage_GameObject* obj;
	PyArg_ParseTuple(args, "O", &obj);
	
	World_addGameObject(obj->gameobject);
	Py_INCREF(obj);
	
    return Py_BuildValue("");
}

static PyObject* Sage_removeObject(PyObject *self, PyObject *args)
{	
	Sage_GameObject* obj;
	PyArg_ParseTuple(args, "O", &obj);
	
	World_removeGameObject(obj->gameobject);
	Py_DECREF(obj);
	
    return Py_BuildValue("");
}

static PyObject* Sage_objectsColliding(PyObject *self, PyObject *args)
{	
	Sage_GameObject* obj1;
	Sage_GameObject* obj2;
	PyArg_ParseTuple(args, "OO", &obj1, &obj2);
	
	if (gameObjectsColliding(obj1->gameobject, obj2->gameobject))
	{
		return Py_BuildValue("i", 1);
	}
	
    return Py_BuildValue("i", 0);
}

static PyObject* Sage_setObjectPosX(PyObject* self, PyObject* args)
{
	Sage_GameObject* obj;
	float pos;
	PyArg_ParseTuple(args, "Of", &obj, &pos);
	obj->gameobject->x = pos;

    return Py_BuildValue("");
}
static PyObject* Sage_setObjectPosY(PyObject* self, PyObject* args)
{
	Sage_GameObject* obj;
	float pos;
	PyArg_ParseTuple(args, "Of", &obj, &pos);
	obj->gameobject->y = pos;

    return Py_BuildValue("");
}

static PyObject* Sage_getObjectPosX(PyObject* self, PyObject* args)
{
	Sage_GameObject* obj;
	PyArg_ParseTuple(args, "O", &obj);
	
    return Py_BuildValue("f", obj->gameobject->x);
}
static PyObject* Sage_getObjectPosY(PyObject* self, PyObject* args)
{
	Sage_GameObject* obj;
	PyArg_ParseTuple(args, "O", &obj);
	
    return Py_BuildValue("f", obj->gameobject->y);
}

static PyObject* Sage_setObjectVelX(PyObject* self, PyObject* args)
{
	Sage_GameObject* obj;
	float pos;
	PyArg_ParseTuple(args, "Of", &obj, &pos);
	obj->gameobject->vx = pos;

    return Py_BuildValue("");
}
static PyObject* Sage_setObjectVelY(PyObject* self, PyObject* args)
{
	Sage_GameObject* obj;
	float pos;
	PyArg_ParseTuple(args, "Of", &obj, &pos);
	obj->gameobject->vy = pos;

    return Py_BuildValue("");
}

static PyObject* Sage_getObjectVelX(PyObject* self, PyObject* args)
{
	Sage_GameObject* obj;
	PyArg_ParseTuple(args, "O", &obj);
	
    return Py_BuildValue("f", obj->gameobject->vx);
}
static PyObject* Sage_getObjectVelY(PyObject* self, PyObject* args)
{
	Sage_GameObject* obj;
	PyArg_ParseTuple(args, "O", &obj);
	
    return Py_BuildValue("f", obj->gameobject->vy);
}





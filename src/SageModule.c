#include "SageModule.h"
#include "Globals.h"

#include "Engine.h"
#include "GameObject.h"
#include "ObjectType.h"
#include "World.h"
#include "Script.h"
#include "Timer.h"
#include "Physics.h"
#include "Logic.h"
#include "Input.h"


/**** Exported Datatypes ****/
#include "SageModule_GameObject.h"
#include "SageModule_Input.h"
#include "SageModule_Collision.h"

/**** Exported Function Declarations ****/

static PyObject* Sage_initialize(PyObject* self, PyObject* args)
{
	if (Engine_init() != 0)
	{
		fprintf(stderr, "Could not initialize engine, exiting...\n");
		return NULL;
	}
    return Py_BuildValue("");
}


static PyObject* Sage_run(PyObject* self, PyObject* args)
{
	Engine_run();

    return Py_BuildValue("");
}


static PyObject* Sage_terminate(PyObject* self, PyObject* args)
{
	Engine_destroy();
		
    return Py_BuildValue("");
}


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

		Logic_addUpdateCallback(UpdateCallback_new(&Script_callTimedFunction, func));
		
        result = Py_BuildValue("");
    }
	
    return result;
}

static PyObject* Sage_registerInputListener(PyObject* self, PyObject* args)
{
    PyObject* result = NULL;
    PyObject* func;
	Sage_InputData* inputdata; 

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
			
		Input_addInputCallback(InputCallBack_new(&Script_callInputFunction, func), data);
		
        result = Py_BuildValue("");
    }
	
    return result;
}

static PyObject* Sage_registerCollisionListener(PyObject* self, PyObject* args)
{
    PyObject* result = NULL;
    PyObject* func;
	Sage_CollisionData* colldata; 

    if (PyArg_ParseTuple(args, "OO", &func, &colldata)) 
	{
        if (!PyCallable_Check(func)) 
		{
            PyErr_SetString(PyExc_TypeError, "parameter 1 must be callable");
            return NULL;
        }
        Py_XINCREF(func);
		
		if (colldata->obj1 != NULL)
		{
			Physics_addCollisionCallbackOnGameObject(CollisionCallback_new(&Script_callCollisionFunction, func), colldata->obj1->gameobject);
		}
		else if (colldata->type1 != OBJECTTYPE_UNDEFINED && colldata->type2 == OBJECTTYPE_UNDEFINED)
		{
			ObjectType* objtype = World_getObjectType(colldata->type1);
			if (objtype != NULL)
				Physics_addCollisionCallbackOnObjectType(CollisionCallback_new(&Script_callCollisionFunction, func), World_getObjectType(colldata->type1));
		}
			
        result = Py_BuildValue("");
    }
	
    return result;
}


static PyObject* Sage_addCollisionCheck(PyObject *self, PyObject *args)
{	
	int t1, t2;
	if (!PyArg_ParseTuple(args, "ii", &t1,&t2))
		return NULL;
		
	Physics_addCollisionCheck(t1, t2);
	
    return Py_BuildValue("");
}



static PyObject* Sage_addObject(PyObject *self, PyObject *args)
{	
	Sage_GameObject* obj;
	int type;
	
	PyArg_ParseTuple(args, "Oi", &obj, &type);
	
	World_addGameObject(obj->gameobject, type);
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


/**** Interface declaration ****/

static PyMethodDef exportSageMethods[] = 
{
	{"initialize",  Sage_initialize, METH_VARARGS, "Initialize the engine."},
	{"run",  Sage_run, METH_VARARGS, "Run the engine, will return when engine is killed."},
	{"terminate",  Sage_terminate, METH_VARARGS, "Cleans up resources."},

	{"registerUpdateListener",  Sage_registerUpdateFunction, METH_VARARGS, "Register a function that runs once every frame"},
	{"registerInputListener", Sage_registerInputListener, METH_VARARGS, "Register an input listener"},	
	{"registerCollisionListener", Sage_registerCollisionListener, METH_VARARGS, "Register an collision listener"},
	{"enableCollisionCheck", Sage_addCollisionCheck, METH_VARARGS, "Enables collision checking between given object types"},
	
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

PyMODINIT_FUNC initsage()
{
    PyObject* m;

	// Do not fucking forget these, Python won't motherfucking tell you what is wrong if you do.
    if (PyType_Ready(&Sage_GameObject_type) < 0)
        return;
    if (PyType_Ready(&Sage_InputData_type) < 0)
        return;
    if (PyType_Ready(&Sage_CollisionData_type) < 0)
        return;

    m = Py_InitModule("sage", exportSageMethods);

    Py_INCREF(&Sage_GameObject_type);
    PyModule_AddObject(m, "GameObject", (PyObject*)&Sage_GameObject_type);
    Py_INCREF(&Sage_InputData_type);
    PyModule_AddObject(m, "InputData", (PyObject*)&Sage_InputData_type);
    Py_INCREF(&Sage_CollisionData_type);
    PyModule_AddObject(m, "CollisionData", (PyObject*)&Sage_CollisionData_type);

}

int initModule()
{
	initsage();
	return 0;
}





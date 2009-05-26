#include "SageModule.h"
#include "Globals.h"

#include "GameObject.h"
#include "World.h"
#include "Script.h"
#include "Timer.h"
#include "Physics.h"
#include "Logic.h"

/**** Exported Datatypes ****/


static void Sage_GameObject_tp_dealloc(Sage_GameObject* self)
{
	if (self->gameobject != NULL)
	{
		free(self->gameobject);
	}

    self->ob_type->tp_free((PyObject*)self);
}


static PyObject* Sage_GameObject_tp_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	Sage_GameObject* self = (Sage_GameObject*)type->tp_alloc(type, 0);
	assert(self);
	
	self->gameobject = NULL;

	return (PyObject*)self;	
}

static int Sage_GameObject_tp_init(Sage_GameObject* self, PyObject* args, PyObject* kwds)
{
	float xpos, ypos, width, height;

	static char* kwlist[] = {"xpos", "ypos", "width", "height", NULL};

    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|ffff", kwlist, 
                                      &xpos, &ypos, 
                                      &width, &height))
        return -1; 


	self->gameobject = GameObject_new();
	self->gameobject->x = xpos;
	self->gameobject->y = ypos;
	self->gameobject->w = width;
	self->gameobject->h = height;
	
	return 0;
}


static PyTypeObject Sage_GameObject_type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "sage.GameObject",         /*tp_name*/
    sizeof(Sage_GameObject),   /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)Sage_GameObject_tp_dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "GameObject objects",      /*tp_doc*/
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    0,             /* tp_methods */
    0,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)Sage_GameObject_tp_init,      /* tp_init */
    0,                         /* tp_alloc */
    Sage_GameObject_tp_new,                 /* tp_new */

};


Sage_GameObject* Sage_GameObject_new(struct GameObject* gameobj)
{
	Sage_GameObject* obj = (Sage_GameObject*)Sage_GameObject_tp_new(&Sage_GameObject_type, NULL, NULL);
	obj->gameobject = gameobj;
	
	return obj;
}


/**** Exported Function Declarations ****/

static PyObject* Sage_addObject(PyObject*, PyObject*);
static PyObject* Sage_removeObject(PyObject*, PyObject*);
static PyObject* Sage_registerUpdate(PyObject*, PyObject*);
static PyObject* Sage_objectsColliding(PyObject*, PyObject*);

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
	{"registerUpdate",  Sage_registerUpdate, METH_VARARGS, "Print some stuff."},
	{"addObject",  Sage_addObject, METH_VARARGS, "Print some stuff."},
	{"removeObject",  Sage_removeObject, METH_VARARGS, "Print some stuff."},
	{"objectsColliding",  Sage_objectsColliding, METH_VARARGS, "Print some stuff."},
	{"setObjectPosX",  Sage_setObjectPosX, METH_VARARGS, "Set the x position of a Game Object."},
	{"setObjectPosY",  Sage_setObjectPosY, METH_VARARGS, "Set the y position of a Game Object."},
	{"getObjectPosX",  Sage_getObjectPosX, METH_VARARGS, "get the x position of a Game Object."},
	{"getObjectPosY",  Sage_getObjectPosY, METH_VARARGS, "get the y position of a Game Object."},
	{"setObjectVelX",  Sage_setObjectVelX, METH_VARARGS, "Set the x position of a Game Object."},
	{"setObjectVelY",  Sage_setObjectVelY, METH_VARARGS, "Set the y position of a Game Object."},
	{"getObjectVelX",  Sage_getObjectVelX, METH_VARARGS, "get the x position of a Game Object."},
	{"getObjectVelY",  Sage_getObjectVelY, METH_VARARGS, "get the y position of a Game Object."},
	{NULL, NULL, 0, NULL}
};

int initModule()
{
    PyObject* m;

    Sage_GameObject_type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&Sage_GameObject_type) < 0)
        BREAK_ERROR;
		
    m = Py_InitModule("sage", exportSageMethods);

    Py_INCREF(&Sage_GameObject_type);
    PyModule_AddObject(m, "GameObject", (PyObject*)&Sage_GameObject_type);
	
	return 0;
}


/**** Exported Function Bodies ****/

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



static PyObject* Sage_registerUpdate(PyObject* self, PyObject* args)
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





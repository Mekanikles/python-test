#include "Python.h"
#include "SageModule.h"
#include "Globals.h"

#include "GameObject.h"


/**** Exported Datatypes ****/

static PyTypeObject Sage_GameObject_type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "sage.GameObject",         /*tp_name*/
    sizeof(struct Sage_GameObject),   /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    0,                         /*tp_dealloc*/
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
    Py_TPFLAGS_DEFAULT,        /*tp_flags*/
    "GameObject objects",      /*tp_doc*/
};


struct Sage_GameObject* Sage_GameObject_new(struct GameObject* gameobj)
{
	//struct Sage_GameObject* obj = (struct Sage_GameObject*)malloc(sizeof(struct Sage_GameObject));
	Sage_GameObject* obj = PyObject_New(Sage_GameObject, &Sage_GameObject_type);

	obj->gameobject = gameobj;
	//Py_INCREF(obj);
	return obj;	
}


/**** Exported Function Declarations ****/

static PyObject* Sage_test(PyObject*, PyObject*);

static PyObject* Sage_setObjectPos(PyObject*, PyObject*);

static PyMethodDef exportSageMethods[] = 
{
	{"test",  Sage_test, METH_VARARGS, "Print some stuff."},
	{"setObjectPos",  Sage_setObjectPos, METH_VARARGS, "Set the position of a Game Object."},
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

static PyObject* Sage_test(PyObject *self, PyObject *args)
{	
	fprintf(stderr, ".");
    return Py_BuildValue("i", 5);
}


static PyObject* Sage_setObjectPos(PyObject* self, PyObject* args)
{
	Sage_GameObject* obj;
	int pos;
	PyArg_ParseTuple(args, "Oi", &obj, &pos);
	obj->gameobject->y = pos;
    return Py_None;
}



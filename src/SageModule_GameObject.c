#include "SageModule_GameObject.h"
#include "GameObject.h"

#include "World.h"
#include "ObjectType.h"

void Sage_GameObject_tp_dealloc(Sage_GameObject* self)
{
	if (self->gameobject != NULL)
	{
		GameObject_destroy(self->gameobject);
	}

    self->ob_type->tp_free((PyObject*)self);
}


PyObject* Sage_GameObject_tp_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	Sage_GameObject* self = (Sage_GameObject*)type->tp_alloc(type, 0);
	assert(self);
	
	self->gameobject = NULL;

	return (PyObject*)self;	
}

int Sage_GameObject_tp_init(Sage_GameObject* self, PyObject* args, PyObject* kwds)
{
	float xpos, ypos, width, height;

	static char* kwlist[] = {"xpos", "ypos", "width", "height", NULL};

    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|ffff", kwlist, 
                                      &xpos, &ypos, 
                                      &width, &height))
        return -1; 

	
	self->gameobject = GameObject_new();
	self->gameobject->type = OBJECTTYPE_UNDEFINED;
	self->gameobject->x = xpos;
	self->gameobject->y = ypos;
	self->gameobject->w = width;
	self->gameobject->h = height;
	
	return 0;
}

PyTypeObject Sage_GameObject_type = {
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



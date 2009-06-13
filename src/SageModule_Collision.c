#include "SageModule_Collision.h"

#include "GameObject.h"
#include "Physics.h"

// Seriously, why isn't this already included in python.h?
#include "structmember.h"
#include "ObjectType.h"

#include "SageModule_GameObject.h"


void Sage_CollisionData_tp_dealloc(Sage_CollisionData* self)
{
    self->ob_type->tp_free((PyObject*)self);
}

PyObject* Sage_CollisionData_tp_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	Sage_CollisionData* self = (Sage_CollisionData*)type->tp_alloc(type, 0);
	assert(self);
	
	self->type1 = OBJECTTYPE_UNDEFINED;
	self->type2 = OBJECTTYPE_UNDEFINED;
	self->obj1 = NULL;
	self->obj2 = NULL;

	return (PyObject*)self;	
}

int Sage_CollisionData_tp_init(Sage_CollisionData* self, PyObject* args, PyObject* kwds)
{
	int type1, type2;
	Sage_GameObject* obj1;
	Sage_GameObject* obj2;

	static char* kwlist[] = {"type1", "type2", "object1", "object2", NULL};

    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|iiOO", kwlist, 
                                      &type1, &type2,
									  &obj1, &obj2))
        return -1; 

	self->type1 = type1;
	self->type2 = type2;
	self->obj1 = obj1;
	self->obj2 = obj2;
		
	return 0;
}

PyMemberDef Sage_CollisionData_tp_members[] = {
	{"controller", T_INT, offsetof(Sage_CollisionData, type1), 0,
     "controller id"},
    {"button", T_INT, offsetof(Sage_CollisionData, type2), 0,
     "button id"},
    {"value", T_OBJECT, offsetof(Sage_CollisionData, obj1), 0,
     "button value [0.0 - 1.0]"},
    {"state", T_OBJECT, offsetof(Sage_CollisionData,  obj2), 0,
     "recent state change"},
    {NULL}
};

PyTypeObject Sage_CollisionData_type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "sage.CollisionData",         /*tp_name*/
    sizeof(Sage_CollisionData),   /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)Sage_CollisionData_tp_dealloc, /*tp_dealloc*/
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
    Py_TPFLAGS_DEFAULT, /*tp_flags*/
    "Collision data/filter",      /*tp_doc*/
    0,		               	/* tp_traverse */
    0,		               	/* tp_clear */
    0,		               	/* tp_richcompare */
    0,		               	/* tp_weaklistoffset */
    0,		               	/* tp_iter */
    0,		               	/* tp_iternext */
    0,             			/* tp_methods */
	Sage_CollisionData_tp_members, /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)Sage_CollisionData_tp_init,      /* tp_init */
    0,                         /* tp_alloc */
    Sage_CollisionData_tp_new,                 /* tp_new */
};

Sage_CollisionData* Sage_CollisionData_new(int type1, 
											int type2, 
											struct Sage_GameObject* obj1, 
											struct Sage_GameObject* obj2)
{
	Sage_CollisionData* self = (Sage_CollisionData*)Sage_CollisionData_type.tp_alloc(&Sage_CollisionData_type, 0);
	assert(self);
	
	self->type1 = type1;
	self->type2 = type2;
	self->obj1 = obj1;
	self->obj2 = obj2;

	return self;	
}



#include "SageModule_Input.h"
#include "GameObject.h"
#include "Input.h"

// WTF, stackless is this yooooou!?
#include "structmember.h"


void Sage_InputData_tp_dealloc(Sage_InputData* self)
{
    self->ob_type->tp_free((PyObject*)self);
}

PyObject* Sage_InputData_tp_new(PyTypeObject* type, PyObject* args, PyObject* kwds)
{
	Sage_InputData* self = (Sage_InputData*)type->tp_alloc(type, 0);
	assert(self);
	
	self->controller = INPUT_CONTROLLER_UNDEFINED;
	self->button = INPUT_BUTTON_UNDEFINED;
	self->value = INPUT_VALUE_UNDEFINED;
	self->state = INPUT_STATE_UNDEFINED;

	return (PyObject*)self;	
}

int Sage_InputData_tp_init(Sage_InputData* self, PyObject* args, PyObject* kwds)
{
	int controller, button, state;

	static char* kwlist[] = {"controller", "button", "state", NULL};

    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|iii", kwlist, 
                                      &controller, &button, 
                                      &state))
        return -1; 


	self->controller = controller;
	self->button = button;
	self->state = state;
	
	return 0;
}

PyMemberDef Sage_InputData_tp_members[] = {
	{"controller", T_INT, offsetof(Sage_InputData, controller), 0,
     "controller id"},
    {"button", T_INT, offsetof(Sage_InputData, button), 0,
     "button id"},
    {"value", T_FLOAT, offsetof(Sage_InputData, value), 0,
     "button value [0.0 - 1.0]"},
    {"state", T_INT, offsetof(Sage_InputData, state), 0,
     "recent state change"},
    {NULL}
};

PyTypeObject Sage_InputData_type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "sage.GameObject",         /*tp_name*/
    sizeof(Sage_InputData),   /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)Sage_InputData_tp_dealloc, /*tp_dealloc*/
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
    "Input data",      /*tp_doc*/
    0,		               	/* tp_traverse */
    0,		               	/* tp_clear */
    0,		               	/* tp_richcompare */
    0,		               	/* tp_weaklistoffset */
    0,		               	/* tp_iter */
    0,		               	/* tp_iternext */
    0,             			/* tp_methods */
	Sage_InputData_tp_members, /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)Sage_InputData_tp_init,      /* tp_init */
    0,                         /* tp_alloc */
    Sage_InputData_tp_new,                 /* tp_new */
};

Sage_InputData* Sage_InputData_new(int controller, int button, float value, int state)
{
	Sage_InputData* self = (Sage_InputData*)Sage_InputData_type.tp_alloc(&Sage_InputData_type, 0);
	assert(self);
	
	self->controller = controller;
	self->button = button;
	self->value = value;
	self->state =  state;

	return self;	
}



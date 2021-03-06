#include "Script.h"
#include "Python.h"

#include "SageModule.h"
#include "LinkedList.h"
#include "Timer.h"
#include "Input.h"
#include "Physics.h"
#include "GameObject.h"
#include "ObjectType.h"

#include "SageModule_Input.h"
#include "SageModule_Collision.h"

PyObject *pName;
PyObject *pModule;
PyObject *pDict;
PyObject *pValue;

PyObject *pMain;

static int callCount = 0;


int Script_init(const char* script)
{
	Py_Initialize();
	
	initModule();
  
    pName = PyString_FromString(script);
	
    if (!(pModule = PyImport_Import(pName)))
	{
        PyErr_Print();
		BREAK_ERROR;
	}
    pDict = PyModule_GetDict(pModule);

    pMain = PyDict_GetItemString(pDict, "main");
	
    if (!PyCallable_Check(pMain)) 
	{
        PyErr_Print();
		fprintf(stderr, "Could not find 'main' python function.\n");
		BREAK_ERROR;
    }
	
	return 0;
}

void Script_destroy()
{
	if (pModule) 
	{
		Py_DECREF(pModule);
	}
    if (pName)
	{
		Py_DECREF(pName);
	}
	
    Py_Finalize();
}

void Script_callTimedFunction(void* functionObject, Time t)
{
	assert(functionObject);
	PyObject *arg;
	arg = Py_BuildValue("(f)", t);
	PyObject_CallObject((PyObject*)functionObject, arg);
	PyErr_Print();
	callCount++;
}

void Script_callInputFunction(void* functionObject, InputData* input)
{
	assert(functionObject);
	Sage_InputData* inputdata = Sage_InputData_new(input->controller, 
										input->button, 
										input->value,
										input->state);
	PyObject* arg;
	arg = Py_BuildValue("(O)", inputdata);
	PyObject_CallObject((PyObject*)functionObject, arg);
	PyErr_Print();
	callCount++;
}

void Script_callCollisionFunction(void* functionObject, CollisionData* coll)
{
	assert(functionObject);
	Sage_CollisionData* colldata = Sage_CollisionData_new(coll->obj1->type, 
										coll->obj2->type, 
										coll->obj1->scriptobject,
										coll->obj2->scriptobject);
	PyObject* arg;
	arg = Py_BuildValue("(O)", colldata);
	PyObject_CallObject((PyObject*)functionObject, arg);
	PyErr_Print();
	callCount++;
}

void Script_callMain()
{
	PyObject_CallObject(pMain, NULL);
	callCount++;
}

int Script_getCallCounter()
{
	return callCount;
}
void Script_resetCallCounter()
{
	callCount = 0;
}


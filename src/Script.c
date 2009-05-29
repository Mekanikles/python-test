#include "Script.h"
#include "Python.h"

#include "SageModule.h"
#include "LinkedList.h"
#include "Timer.h"
#include "Input.h"

#include "SageModule_Input.h"


PyObject *pName;
PyObject *pModule;
PyObject *pDict;
PyObject *pValue;

PyObject *pSetup;
PyObject *pClean;

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

    pSetup = PyDict_GetItemString(pDict, "setup");
	
    if (!PyCallable_Check(pSetup)) 
	{
        PyErr_Print();
		BREAK_ERROR;
    }
	
	return 0;
}

void Script_destroy()
{
    if (PyCallable_Check(pClean)) 
	{
		PyObject_CallObject(pClean, NULL);
    }

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
}

void Script_callInputFunction(void* functionObject, InputData input)
{
	assert(functionObject);
	Sage_InputData* inputdata = Sage_InputData_new(input.controller, 
										input.button, 
										input.value,
										input.state);
	PyObject* arg;
	arg = Py_BuildValue("(O)", inputdata);
	PyObject_CallObject((PyObject*)functionObject, arg);
}


void Script_callSetup()
{
	PyObject_CallObject(pSetup, NULL);
}

#include "Script.h"
#include "Python.h"

#include "SageModule.h"

PyObject *pName;
PyObject *pModule;
PyObject *pDict;
PyObject *pFunc;
PyObject *pValue;

int Script_init()
{
	Py_Initialize();
	
	initModule();
  
    pName = PyString_FromString("test");
	
    if (!(pModule = PyImport_Import(pName)))
		BREAK_ERROR;

    pDict = PyModule_GetDict(pModule);

    pFunc = PyDict_GetItemString(pDict, "test");

    if (!PyCallable_Check(pFunc)) 
	{
        PyErr_Print();
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

void Script_callFunction(struct GameObject* obj)
{

	PyObject *arg, *args;
	
	struct Sage_GameObject* theobj = Sage_GameObject_new(obj);
	
	arg = Py_BuildValue("(O)", theobj);
	PyObject_CallObject(pFunc, arg);
}

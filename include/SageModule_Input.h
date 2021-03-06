#ifndef SAGEMODULE_INPUT_H_
#define SAGEMODULE_INPUT_H_


#include "Python.h"

#include "Input.h"

typedef struct Sage_InputData
{
    PyObject_HEAD
	int controller;
	int button;
	float value;
	int state;
} Sage_InputData;

extern PyTypeObject Sage_InputData_type;
Sage_InputData* Sage_InputData_new(int controller, int button, float value, int state);


#endif

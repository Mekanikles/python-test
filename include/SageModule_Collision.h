#ifndef SAGEMODULE_COLLISION_H_
#define SAGEMODULE_COLLISION_H_


#include "Python.h"

#include "Input.h"

struct Sage_GameObject;

typedef struct Sage_CollisionData
{
    PyObject_HEAD
	int type1;
	int type2;
	
	struct Sage_GameObject* obj1;
	struct Sage_GameObject* obj2;
} Sage_CollisionData;

extern PyTypeObject Sage_CollisionData_type;
Sage_CollisionData* Sage_CollisionData_new(int type1, 
											int type2, 
											struct Sage_GameObject* obj1, 
											struct Sage_GameObject* obj2);



#endif

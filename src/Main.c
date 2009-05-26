#include "stdio.h"

#include "Engine.h"
#include "Script.h"

int main(int argc, char *argv[])
{
	if (argc != 1)
	{
		fprintf(stderr, "Please provide script file\n");
		return 0;	
	}

	if (Engine_init() != 0)
	{
		fprintf(stderr, "Could not initialize engine, exiting...\n");
		return 0;
	}
		
	if (Script_init(argv[0]) != 0)
	{
		fprintf(stderr, "Could not initialize script, exiting...\n");
	}
	else
	{
		Script_callSetup();
		Engine_run();
	}
	
	Script_destroy();
	Engine_destroy();
	
	return 0;
}

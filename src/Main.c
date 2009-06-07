#include "stdio.h"

#include "Engine.h"
#include "Script.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Please provide script file\n");
		return 0;	
	}
		
	if (Script_init(argv[1]) != 0)
	{
		fprintf(stderr, "Could not initialize script, exiting...\n");
		Script_destroy();
		return 0;
	}

	Script_callMain();
	Script_destroy();
	
	return 0;
}

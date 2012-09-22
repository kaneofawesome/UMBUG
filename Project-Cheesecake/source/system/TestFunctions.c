#include "Task.h"
#include "TestFunctions.h"
/*
 * tasks and taskIndex are defned in Task.c
 */
 
 
extern GroundCommandTask tasks[];
extern int taskIndex;
int testFunction1(){

	printf("Test function 1\n");
	return 1;
}

int testFunction2(){
	
	printf("Test function 2\n");
	return 2;
}

int testFunction3(){

	printf("Test function 3\n");
	return 3;
}

void initTestTasks(){
		
		initGroundCommandTask(&(tasks[0]),&testFunction1);
		initGroundCommandTask(&(tasks[1]),&testFunction2);
		initGroundCommandTask(&(tasks[2]),&testFunction3);
	
}


#include "Task.h"
#include "TimeCounter.h"
#include "TestFunctions.h"

/*Array of tasks... this is jsut for test purposes as of now.  Might use a linked list structure for easier processing later on
 */
GroundCommandTask tasks[3];
int taskIndex = 0;

void initGroundCommandTask(GroundCommandTask *t, int (*pt2Func)()/*, TimeCounter *schedTime, TimeCounter *duration*/)
{
	
	t->func = pt2Func;
	/*t->scheduledTime = *schedTime;
	t->duration = *duration;
	*/
}
void destroyGroundCommandTask(GroundCommandTask *t)
{
	
//	free(t);
	
}
int performGroundCommandTask(GroundCommandTask *t){
	
	return t->func();
	
}

void performCurrentTask()
{
	
	int result = performGroundCommandTask(&(tasks[taskIndex]));
	taskIndex = (taskIndex + 1)%3;//this is just test for now.  prob not gonna use an array to store these....
	printf("Result: %d\n",result);
		
}

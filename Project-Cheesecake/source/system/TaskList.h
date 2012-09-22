/*
 * TaskList - a circular buffer of task structures.
 * 
 * Ground commands get their own task list, as do routine operations.
 * 
 * 
 * 
 * */


#ifndef TASKLIST_H_
#define TASKLIST_H_




#define TASKLIST_MAX_NUM_TASKS 128 //this is just a guess right now.

/*
typedef struct 
{
	RoutineTask tasks[TASKLIST_MAX_NUM_TASKS];	//the circular buffer
	int insert;							//the insert position
	int current;						//the current task position
	int num;							//the number of tasks in the system.
		
} RoutineTaskList;

typedef struct 
{
	GroundCommandTask tasks[TASKLIST_MAX_NUM_TASKS];	//the circular buffer
	int insert;							//the insert position
	int current;						//the current task position
	int num;							//the number of tasks in the system.
		
} GroundCommandTaskList;
*/
typedef struct
{
	GroundCommandTask	gct;
	BasicTaskNode* next;
	
}	BasicTaskNode;

typedef struct	//may not need this
{
	int size;
	BasicTaskNode* head;	//the first node
}	BasicTaskList;

/*
typedef struct
{
	
	RoutineTaskNode *next;	
	RoutineTask task;
	
}	RoutineTaskNode;

typedef struct
{
	
	GroundCommandTaskNode *next;	
	GroundCommandTask task;
	
}	GroundCommandTaskNode;
*/

/*
 * initialize a taskList structure.
 */
 /*
void initGroundCommandTaskList(GroundCommandTaskList *tl);
void initRoutineTaskList(RoutineTaskList *tl);
*/

/*
 *	add a task to the list.  Tasks are removed upon completion. 
 */
/*
int addRoutineTask(RoutineTaskList *tl, RoutineTask *t); 
int addGroundCommandTask(GroundCommandTaskList *tl, GroundCommandTask *t);
*/
#endif /*TASKLIST_H_*/

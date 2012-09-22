/*void insertTask(BasicTaskList *btl,GroundCommandTask *gct)
{
	BasicTaskNode *newTask;
	newTask = (BasicTaskNode*)malloc(sizeof(BasicTaskNode));
	newTask->gct = gct;
	if (*btl->size == 0)
	{
		*btl->head = newTask;
		*btl->head->next = NULL;
		
	} else 
	{
		BasicTaskNode *prev;
		
		BasicTaskNode *btn = btl->head;
		int i;
		while(btn->next != NULL && compareTimeCount(gct->scheduledTime, btn->next->gct->scheduledTime) >= 0)
		{
			prev = btn;
			btn = btn->next;
		}
		if (btn->next == NULL)
		{
			btn->next = (BasicTaskNode*)malloc(sizeof(BasicTaskNode));
			btn->next->gct = gct;
			btn->next->next = NULL;	
		} else
		{
			newTask->next = btn->next;
			prev->next = newTask;
		}
		
	}
}
void initBasicTaskList(BasicTaskList *btl)
{
	*btl->size = 0;
	*btl->head = NULL;	
}




void initGroundCommandTaskList(GroundCommandTaskList *tl){
	tl->insert = 0;
	tl->current = 0;
	tl->num = 0;
	int i;
	for(i = 0; i < TASKLIST_MAX_NUM_TASKS)
	{
		
	}
}
void initRoutineTaskList(RoutineTaskList *tl){
	tl->insert = 0;
	tl->current = 0;
	tl->num = 0;
	int i;
	RoutineTask dummy;
	dummy.completed = TASK_COMPLETE;
	for(i = 0; i < TASKLIST_MAX_NUM_TASKS)
	{
		tl->tasks[i] = dummy;
	}
}



int addRoutineTask(RoutineTaskList *tl, RoutineTask *t)
{

	if(tl->tasks[tl->insert].completed == TASK_COMPLETED)
	{
		tl->tasks[tl->insert] = *t;
		tl->insert = (tl->insert + 1)%TASKLIST_MAX_NUM_TASKS;
		return 1;	//success
	} else {
		return 0;
	}
}
int addGroundCommandTask(GroundCommandTaskList *tl, GroundCommandTask *t)
{
	if(tl->tasks[tl->insert].completed == TASK_COMPLETED)
	{
		tl->tasks[tl->insert] = *t;
		tl->insert = (tl->insert + 1)%TASKLIST_MAX_NUM_TASKS;
		return 1;	//success
	} else {
		return 0;
	}
	
}
*/

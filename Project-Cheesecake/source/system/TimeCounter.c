#include "TimeCounter.h"



int compareTimeCount(TimeCount *a, TimeCount *b)
{
	//a is greater than b, return 1
	
	if ((a->MSW > b->MSW) || (a->MSW == b->MSW && (a->LSW > b->LSW)))
		return 1;
	//a is equal to be, return 0
	if (a->MSW == b->MSW && a->LSW == b->LSW)
		return 0;
	
	//a is less than b, return -1
	else	
		return -1;
}
void initTimeCount(TimeCounter *a) //MODIFIED SO THAT CODE WOULD COMPILE. TODO: change it to what is actually desirable.
{
	a->LSW = 0;
	a->MSW = 0;
	
}
void incrementTimeCount(TimeCount *a){
	
	a->LSW++;
	if (a->LSW == 0)	//a rollover has occured.
	{
		a->MSW++;		//so increment most significant word
		if (a->MSW == END_OF_LIFE_MSW && a->LSW == END_OF_LIFE_LSW)
			{
						//SATELLITE IS NOT SUPPOSED TO LIVE THIS LONG!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
						//send a final beacon 
			}
	}
	
	
}
void addToTimeCounter(TimeCounter *orig, TimeCounter *more)
{
	UL32 oldLSW= orig->LSW;
	
	orig->MSW += more->MSW;
	orig->LSW += more->LSW;
	
	if (orig->LSW < oldLSW)//rollover occured, add one to MSW
	{
		orig->MSW += 1;
	}	
	
}

//use initDuration to create a duration. dont use this function.
//if i ever catch you using this function i will break your kneecapS, note the emphasis on plural -Troy

void __UL32_to_TimeCounter_LSW__(TimeCounter *t, UL32 l)
{
	initTimeCounter(t);
	t->LSW = l;
	
}

void initDuration(TimeCounter *t, int days, int hours, int minutes, int seconds, int milliseconds)
{
	initTimeCounter(t);
	TimeCounter *w = (TimeCounter*)malloc(1*sizeof(TimeCounter));
	
	__UL32_to_TimeCounter_LSW__(w,(UL32)days*(UL32)TIMECOUNTER_DAY);
	addToTimeCounter(t,w);
	
	__UL32_to_TimeCounter_LSW__(w,(UL32)hours*(UL32)TIMECOUNTER_HOUR);
	addToTimeCounter(t,w);
	
	__UL32_to_TimeCounter_LSW__(w,(UL32)minutes*(UL32)TIMECOUNTER_MINUTE);
	addToTimeCounter(t,w);
	
	__UL32_to_TimeCounter_LSW__(w,(UL32)seconds*(UL32)TIMECOUNTER_SECOND);
	addToTimeCounter(t,w);
	
	__UL32_to_TimeCounter_LSW__(w,(UL32)milliseconds*(UL32)TIMECOUNTER_MILLISECOND);
	addToTimeCounter(t,w);
	
	
}



void destroyTimeCounter(TimeCounter *a)
{
	free(a);	//no dynamic structures (pointers) inside timecounter struct.	
}

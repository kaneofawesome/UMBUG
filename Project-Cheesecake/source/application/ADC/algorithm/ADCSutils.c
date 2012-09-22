/**
* ADCSutils.c
*
* Contains utility functions needed in ADCS code
*
* Last updated: 2012-09-11
*/

// TODO: Check data types

#include "./ADCSutils.h"

void editHistory(SI16 var, SI16 *history, UI16 histSize)
{
	/**
	* PURPOSE:	Updates variable history with current value
	* 
	* INPUT: 	double var - variable to update
	* 			double *history - pointer to array of previous values of var
	*			int histSize - size of history array			
	*
	* OUTPUT: 	updates first element of history with var and shifts the
	* 			rest of the array one space towards the end
	*/

	UI16 i;
	
	// Shift everything over one spot to make room
	// Note: this automatically pushes the oldest element out of the arrray
	for(i = 0; i < histSize - 1; i++)
		history[i+1] = history[i];
	
	history[0] = var;
}

/************************************************************************/

SI16 deriv(SI16 *array, UI16 size, UI16 timeSinceEpoch)
{
	/**
	* PURPOSE:	Performs finite backwards differencing for 1st derivative
	* 			with 5 elements
	* 
	* INPUT: 	double *array - data to differentiate
	* 			int size - size of array
	* 			int timeSinceEpoch - number of seconds elapsed since separation
	*
	* OUTPUT: 	double deriv - 1st derivative of array at the current time step
	*/
	
	UI16 minTimeSinceEpoch = 5;  	// seconds
	// UI16 step = 1; 				// seconds (uncomment if step != 1)
	SI16 deriv = 0; 				// 1000 * [array] / second
	UI16 threshold = 1;
	
	if(timeSinceEpoch >= minTimeSinceEpoch)
	{
		// Finite backwards differencing for 1st derivative with 5 elements
		// Note that earlier times are at higher indices in the array
		
		// Decimal approximations of fractional coefficients:
		// 25/12 ~= 2.083
		// 4/3 ~= 1.333
		// 1/4 = 0.25
		
		deriv = 2083*array[0] - 4000*array[1] + 3000*array[2] - 1333*array[3] + 250*array[4];
		
		// IMPORTANT: Uncomment this line if step != 1
		// deriv /= step; 
	}
	
	// Funky conditions to avoid using abs function
	if((deriv < 0 && deriv > -threshold) || (deriv > 0 && deriv < threshold))
	{
		deriv = 0;
	}
	
	return deriv;
}

/************************************************************************/

SI16 integrate(SI16 *array, UI16 size, UI16 timeSinceEpoch)
{
	/**
	* PURPOSE:	Integrates numerical data using trapezoid rule for evenly spaced data 			
	* 
	* INPUT: 	double *array - data to integrate
	* 			int size - size of array
	* 			int timeSinceEpoch - seconds elapsed since separation
	*
	* OUTPUT: 	double integral - trapezoid integral of array
	*/
	
	UI16 i;
	// UI16 step = 10;		// seconds (uncomment if step != 1)
	SI16 integral = 0;		// 1000*[array]*seconds
	
	if(timeSinceEpoch >= size) // i.e. make sure the array is full so we don't integrate junk data
	{		
		// POSSIBLE OPTIMIZATION: if we decide on a fixed history size, we can just 
		// roll out the loop instead accomodataing arbitrary history size with iteration
		integral += 500*(array[0] + array[size-1]);
		
		for (i = 1; i < size-1; i++)
			integral += 1000*array[i];
			
		// IMPORTANT: Uncomment this line if step != 1
		// integral *= step;
	}
	
	return integral;
}

#include "TimerA.h"
#include "../../../system/Task.h"
#include <stdio.h>
/*
 * Refer to this outside of the file with the extern keyword!!
 */
void (*timerAInt_taccr1)(void);
void dumbFunc(void){
	printf("Test\n");	
}

void initTimerA(){
	#if COM_PROCESSOR_COMPILE
		/*Timer A control register.
		 * TASSEL_2 = use SMCLK for clock source
		 * TAIE = timer a interrupt enable
		 * MC_1 is count-up mode
		 * ID_0 = divide frequency by 1 (2^0)
		 * 
		 */
		TACTL = TASSEL_2 | TAIE | MC_1 | ID_0;
		
		/*Timer A Capture/Compare Control 0
		 * CM_0 = capture mode 0 (disabled, we want compare mode).
		 * CCIS_0 = capture compare input (gnd, we not using an input signal.  Clock yes, input no.)
		 * CCIE = capture compare input enable
		 */
		TACCTL0 = CM_0 | CCIS_0 | CCIE;
		
		/*Timer A Capture/Compare 0
		 * period of count - counts up from 0 to TACCR0 and then registers an interrupt.
		 */
		TACCR0 = 0x8F;
		//TACCR0 = 65535;
		
		//interrupt 2 for the listening
		TACCTL1 = CM_0 | CCIS_3 | CCIE;
		TACCR1 = 0x45;//TODO 
		
		/*
		 * interrupt call for basic task switching.
		 */
		//timerAInt_taccr1 = &performCurrentTask;
		
	#elif CDH_PROCESSOR_COMPILE
		/*Timer A control register.
		 * TASSEL_2 = use SMCLK for clock source
		 * TAIE = timer a interrupt enable
		 * MC_1 is count-up mode
		 * ID_0 = divide frequency by 1 (2^0)
		 * 
		 */
		TACTL = TASSEL_2 | TAIE | MC_1 | ID_0;
		
		/*Timer A Capture/Compare Control 0
		 * CM_0 = capture mode 0 (disabled, we want compare mode).
		 * CCIS_0 = capture compare input (gnd, we not using an input signal.  Clock yes, input no.)
		 * CCIE = capture compare input enable
		 */
		TACCTL0 = CM_0 | CCIS_0 | CCIE;
		
		/*Timer A Capture/Compare 0
		 * period of count - counts up from 0 to TACCR0 and then registers an interrupt.
		 */
		TACCR0 = 0xFF;
		//TACCR0 = 65535;
	
		/*
		 * interrupt call for basic task switching.
		 */
		//timerAInt_taccr1 = &performCurrentTask;
		
	#endif
	
}


/*
 * get this working at some point, maybe it already does?
void changeTimerAInterrupt((*pt2func)(void)){
	timerAInt_taccr1 = pt2func;	
}
*/

#pragma vector=TIMERA0_VECTOR
__interrupt void timerA0int()
{
	if(TAIV && TAIV_TACCR1)	//if capture compare reg 1 interrupt
	{
		#if CDH_PROCESSOR_COMPILE
			CDH_timerA_ISR();
		#endif
		
		#if COM_PROCESSOR_COMPILE
			COM_timerA_ISR();
		#endif
		
	}
	
	
	else if (TAIV && TAIV_TACCR2) //if capture compare reg 2 interrupt
	{
		#if COM_PROCESSOR_COMPILE
			COM_timerA2_ISR();
			//printf("timerA interrupt 2");
		#endif		
	}
	
	
	else
	{
		
	}
	
	return;
	
}


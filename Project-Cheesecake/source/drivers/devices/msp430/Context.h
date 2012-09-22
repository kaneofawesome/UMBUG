#include "../SimpleDefinitions.h"
#ifndef CONTEXT_H_
#define CONTEXT_H_



typedef struct
{
	/*	Program Counter
	 */
	UI16 PC;
	/*	Stack Pointer
	 */
	UI16 SP;
	/*	Do we need to hold the entire STATUS register? might just need N,C,Z bits.
	 */
	UI16 STATUS;
	/*	R0 through R3 are constant generators (dont need to keep track of them)
	 */
	UI16 R4;  //R4 to R15
	UI16 R5;
	UI16 R6;
	UI16 R7;
	UI16 R8;
	UI16 R9;
	UI16 R10;
	UI16 R11;
	UI16 R12;
	UI16 R13;
	UI16 R14;
	UI16 R15;
	
	
} Context;

/*	storeContext-  take a Context struct and fill it with the current operating context of the processor.
 * 
 */
void storeContext(Context *c);

/*	loadContext- take a Context struct and load it in as the processor's working state.
 * 
 */
void loadContext(Context *c);


#endif /*CONTEXT_H_*/
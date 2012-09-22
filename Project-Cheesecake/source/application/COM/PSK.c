//////////////////////////////////////////////////////////////////
//                                                              //
//    PSK source                                                //
//    last edited by: Tong Duan                                 //
//    date: July 30, 2012                                       //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "String.h"
#include "PSK.h"
#include "Math.h"

///////////////////////////////////////////////////////////////////

UI8 currentPhaseShiftIndex;
UI8 phaseShifts[PhaseShiftHistoryLength];
//	  0.00	 11.25	 22.50	 34.75	 45.00	 56.25	 67.50	 78.75
//	 90.00	101.25	112.50	123.75	135.00	146.25	157.50	168.75
//	180.00	191.23	202.50	213.75	225.00	236.25	247.50	258.75
//	270.00	281.25	292.50	303.75	315.00	326.23	337.50	348.75
const Word phaseAngles[M_PSK] =
	{	  0,	 11,	 22,	 35,	 45,	 56,	 68,	 79,
	 	 90,	101,	112,	124,	135,	146,	158,	169,
	 	180,	191,	202,	214,	225,	236,	248,	259,
	 	270,	281,	292,	304,	315,	326,	338,	349};

///////////////////////////////////////////////////////////////////

#if DebugMode
	#include <stdio.h>
	#define PRINT_PSK_TRACE 0
#else
	#define PRINT_PSK_TRACE 0
#endif

void initializePSKBuffer()
{
	for (currentPhaseShiftIndex = 0; currentPhaseShiftIndex < PhaseShiftHistoryLength; currentPhaseShiftIndex++)
	{
		phaseShifts[currentPhaseShiftIndex] = 0;
	}
	currentPhaseShiftIndex = 0;	
}

UI8 phaseChange(int digital[])
{
	UI8 i;
	UI16 final = 0;
	
	#if PRINT_PSK_TRACE
		printf(" Word phaseChange(int digital[]) ...\n");
		printf(" digital = ");
		for (i = 0; i < 5; i++) // why 5? -DS
		{
			printf("%d ", digital[i]);
		}
		printf("\n");
	#endif
	
    for(i = 0; i < 5; i++) 
    {
        final += (digital[i] * pow(10,4-i));
        
        #if PRINT_PSK_TRACE
        	printf(" tallying up 'final': %d\n", final);
        #endif
    }
    
    #if PRINT_PSK_TRACE
		printf(" searching switch statement...\n");
	#endif
	
	UI8 temp_dChange = 0.0;
	
	switch(final)
	{
														// DEGREES
		case     0: temp_dChange = 0;		break;		// 0.0
		case     1: temp_dChange = 1;		break;		// 11.25
		case    10: temp_dChange = 3;		break;		// 33.75
		case    11: temp_dChange = 2;		break;		// 22.5
		case   100: temp_dChange = 7;		break;		// 78.75
		case   101: temp_dChange = 6;		break;		// 67.5
		case   110: temp_dChange = 4;		break;		// 45
		case   111: temp_dChange = 5;		break;		// 56.25
		case  1000: temp_dChange = 15;		break;		// 168.75
		case  1001: temp_dChange = 14;		break;		// 157.5
		case  1010: temp_dChange = 12;		break;		// 135
		case  1011: temp_dChange = 13;		break;		// 146.25
		case  1100: temp_dChange = 8;		break;		// 90
		case  1101: temp_dChange = 9;		break;		// 101.25
		case  1110: temp_dChange = 11;		break;		// 123.75
		case  1111: temp_dChange = 10;		break;		// 112.5
		case 10000: temp_dChange = 31;		break;		// 348.75
		case 10001: temp_dChange = 30;		break;		// 337.5
		case 10010: temp_dChange = 28;		break;		// 315
		case 10011: temp_dChange = 29;		break;		// 326.25
		case 10100: temp_dChange = 24;		break;		// 270
		case 10101: temp_dChange = 25;		break;		// 281.25
		case 10110: temp_dChange = 27;		break;		// 303.75
		case 10111: temp_dChange = 26;		break;		// 292.5
		case 11000: temp_dChange = 16;		break;		// 180
		case 11001: temp_dChange = 17;		break;		// 191.25
		case 11010: temp_dChange = 19;		break;		// 213.75
		case 11011: temp_dChange = 18;		break;		// 202.5
		case 11100: temp_dChange = 23;		break;		// 258.75
		case 11101: temp_dChange = 22;		break;		// 247.5
		case 11110: temp_dChange = 20;		break;		// 225
		case 11111: temp_dChange = 21;		break;		// 236.25
		default:	
					#if PRINT_PSK_TRACE
						printf("\n\n\nfailure in PSK.c: Word phaseChange(int digital[])\n    variable final: %d\n", final);
						fflush(stdout);
					#endif
					
					system_abort();
	}

    #if PRINT_PSK_TRACE || 1
    	printf("     degreeChange: %d\n",temp_dChange);
    #endif
	return temp_dChange;
}

void convertBinaryToPSK(Byte data[], int size)
{
	// initializers ///////////////////////////////////////////
	
	int tempB[8], binary[14], phase[5] = {0, 0, 0, 0, 0}, tpBinary[14];
	int front = 0, rear = 0, i, j, k, outNo = 0, occupyNo = 0;
	
	for(i = 0; i < 14; i++)
	{
		binary[i] = 0;
		tpBinary[i] = 3;
	}
	
	// cycle through incoming bytes ///////////////////////////
	
	for(i = 0; i < size; i++)
	{
		UI8 fiveCount = 0, former = 0, latter = 0;
		Byte current = data[i];
		
		#if PRINT_PSK_TRACE
			printf("\n TEST ROUND %d\n ------------\r\n",i);
			printf(" current: %x\n",current);
        	printf(" tempB: ");
    	#endif
    	
        for(j = 0; j < 8; j++) 
        {
        	//convert hex into 8 binary char
    	    char temp = (char)(((current >> (7-j)) & 1) + '0');
            Byte intemp = atoi(&temp);
            tempB[j] = intemp;
            
            #if PRINT_PSK_TRACE
            	printf("%c",temp);
            	if (j == 7) { printf("\n"); }
            #endif
        }
        
        for(j = 0; j < 8; j++)    //load next byte into the binary array
        {
        	if((rear + j) < 14)
        	{
        	    binary[rear+j] = tempB[j];
        	}
        	else
        	{
        		binary[(rear+j)%14] = tempB[j];
        	}
        	occupyNo++;
        }
        rear = (rear + 8) % 14;
        
        #if PRINT_PSK_TRACE
        	printf("\n");
        	printf(" After load...\n");
        	printf("          array: ");
        	for(j = 0; j < 14; j++)
        	{
       		 	printf("%d", binary[j]);
       		}
        	printf("\n");
        #endif
        
        for(j = 0; j < 14; j++)
        {
		    tpBinary[j] = 3;		// reset
	    }
        for(j = 0; j < occupyNo; j++)
        {
        	if((front + j) < 14)
        	{
        		tpBinary[j] = binary[front+j];
        	}
        	else
        	{
        		tpBinary[j] = binary[(front+j)%14];
        	}
        }
        
        #if PRINT_PSK_TRACE
        	printf("          front: %d\n", front);
        	printf("           rear: %d\n", rear);
        #endif
        
        
        // bit-stuffing ///////////////////////////////////////
        
        for(j = 0; j < 13; j++)
        {
        	if(tpBinary[j] == 1)
        	{
        		// check if we've got 5 consecutive 1s yet
        		fiveCount++;
        		if(fiveCount == 5)
        		{
        			// insert a 0
        			for(k = 0; k < 13 - j; k++)
        			{
        			    latter = tpBinary[j+k+1];
        			    tpBinary[j+k+1] = former;
        			    former = latter;
        			}
        			latter = 0, former = 0, fiveCount = 0;	// reset
        			occupyNo++;
        			rear = (rear + 1) % 14;
        		}
        	}
        	else
        	{
        		fiveCount = 0;
        	}
        }
        
        for(j = 0; j < occupyNo; j++){
        	if((front + j) < 14)
        	{
        		binary[front+j] = tpBinary[j];
        	}
        	else
        	{
        		binary[(front+j)%14] = tpBinary[j];
        	}
        }
        
        #if PRINT_PSK_TRACE
        	printf("\n");
        	printf(" After bit-stuffing...\n");
        	printf("          array: ");
        	for(j = 0; j < 14; j++){
        		printf("%d",binary[j]);
        	}
        	printf("\n");
        	printf("          front: %d\n", front);
        	printf("           rear: %d\n", rear);
        #endif
        
        // done bit-stuffing //////////////////////////////////////
        
        
        //calculate how many times extraction after this round of loading
        int tMod = (int) (occupyNo / 5);      
        
        for(j = 0; j < tMod; j++)
        {
        	#if PRINT_PSK_TRACE
        		printf("\n Inter TEST %d:\n", j);
        		assert(front < 14);
        	#endif
        	
        	for(k = 0; k < 5; k++)
        	{
				//extract uniform 5 bits into a phase from the binary array
        		if((front + k) < 14)
        		{
        			phase[k] = binary[front+k];
        			binary[front+k] = 2;
        		}
        		else
        		{
        			phase[k] = binary[(front+k)%14];
        			binary[(front+k)%14] = 2;
        		}
        		occupyNo--;
        	}
            front = (front + 5) % 14;
            
            // find the phase change!
        	phaseShifts[currentPhaseShiftIndex++] += phaseChange(phase);
        	printf(" currentPhaseShiftIndex=%d phaseChange(phase)=%d\n", currentPhaseShiftIndex, phaseChange(phase));
        	if (currentPhaseShiftIndex >= PhaseShiftHistoryLength)
        	{
        		currentPhaseShiftIndex = 0;
        	}
		    
		    #if PRINT_PSK_TRACE
		    	printf("\n");
            	printf(" After extraction...\n");
            	printf("          front: %d\n", front);
            	printf("           rear: %d\n", rear);
            	printf("       outputNo: %d\n", outNo);
		    #endif
		    		   
		    outNo = outNo + 1;
        }
        if(i == size-1 && (occupyNo%5) != 0) //Check if facing the end of incoming data, if so, do clearance.
        { 
        	#if PRINT_PSK_TRACE
        		printf("\n Clear TEST:\n");
        		printf(" The rest binary is: ");
        		for(k=0;k<12;k++){
        			printf("%d",binary[k]);
        		}
        		printf("\n");
        	#endif
        	
        	int reminder = 0,rest = 0;
        	reminder = occupyNo%5;
        	for(k = 5-reminder; k < 5; k++)
        	{
				//extract the reminder bits into the last phase from the binary array
        		if((front + rest) < 14)
        		{
        			phase[k] = binary[front+rest];
        			binary[front+rest] = 2;
        		}
        		else
        		{
        			phase[k] = binary[(front+rest)%14];
        			binary[(front+rest)%14] = 2;
        		}
        		rest = rest + 1;
        		occupyNo = occupyNo - 1;
        	}
            
            for(k = 0; k < 5-reminder; k++)
            {
            	phase[k] = 0;
            }

        	// find the phase change!
        	phaseShifts[currentPhaseShiftIndex++] += phaseChange(phase);
        	printf(" currentPhaseShiftIndex=%d phaseChange(phase)=%d\n", currentPhaseShiftIndex, phaseChange(phase));
        	if (currentPhaseShiftIndex >= PhaseShiftHistoryLength)
        	{
        		currentPhaseShiftIndex = 0;
        	}
        	
		    #if PRINT_PSK_TRACE
            	printf(" Number of Occupy: %d\n", occupyNo);
		    	printf(" outputNo: %d\n", outNo);
		    #endif
		    
		    outNo = outNo + 1;
		    
        }
        
	}
	
	//for(i = 0; i < 8; i++)
	//{
	//	phaseShifts[i] = i;
	//}
	//printf("FIXED VALUES\n");
	//phaseShifts[0] = 0;
	//phaseShifts[1] = 1;
	//phaseShifts[2] = 2;
	//phaseShifts[3] = 3;
	//phaseShifts[4] = 4;
	//phaseShifts[5] = 5;
	//phaseShifts[6] = 6;
	//phaseShifts[7] = 7;
}

///////////////////////////////////////////////////////////////////





/*//
//  torqure.c
//  
//
//  Created by Joshua Hernandez on 12-05-05.
//  Copyright (c) 2012.
//



#include <stdio.h>


#define VECTOR_LENGTH 3


typedef enum{
	
    FALSE,
    TRUE
	
}boolean;


int* calcMoment(int* tau,int* BField){
	
	
	 
	 tau = 3d torque requiered
	 BField = 3d magnetic field of current position
	 moment = 3d magnetic moment needed
	 
	 unit-A == unit vector in the direction of A	 

	 | Vector | == magnitude of vector
	 
	 -------------------------------------
	 
	 tau = moment X BField
	 
	 unit-tau = unit-moment X unit-BField
	 
	 enforce that unit-moment is pertendicular to both
	 tau and BField. Thus creating a right-handed set of vectorts
	 So we have the following:
	 
	 unit-moment = unit-BField X unit-tau
	 
	 So we can conclude that:
	 
	 moment = ( BField X tau ) / | BField |^2
	 
	 
	
	
	
	int* moment;
	int BFieldMagSq=0;
	int i=0;
	
	
	moment = malloc( sizeof(int)*VECTOR_LENGTH );

	for(i=0 ; i<VECTOR_LENGTH ; i++){

		BFieldMagSq += BField[i]*BField[i];
	}
	
	moment[1-1]=BField[2-1]*tau[3-1] - BField[3-1]*tau[2-1] ;
	moment[2-1]=BField[3-1]*tau[1-1] - BField[1-1]*tau[3-1] ;
	moment[3-1]=BField[1-1]*tau[2-1] - BField[2-1]*tau[1-1] ;
	
	for(i=0 ; i<VECTOR_LENGTH ; i++){
		
		moment[i]=moment[i]/BFieldMagSq;
	}
	
	return moment;
}

boolean testCross(int* A,int* B,int* C){
	
	boolean returnBool=TRUE;
	
	// tests A = B X C
	
	// where A,B,C are all vectors
	
	if( a[1-1] != b[2-1]*c[3-1] - b[3-1]*c[2-1] ) {
		returnBool=FALSE;
	}
	if( a[2-1] != b[3-1]*c[1-1] - b[1-1]*c[3-1]  ){
		returnBool=FALSE;
	}
	if( a[3-1] != b[1-1]*c[2-1] - b[2-1]*c[1-1] ){
		returnBool=FALSE;
	}
	
	return returnBool;
}
*/

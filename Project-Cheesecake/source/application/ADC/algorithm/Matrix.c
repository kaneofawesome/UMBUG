//////////////////////////////////////////////////////////////////
//                                                              //
//    Matrix source                                             //
//    last edited by:  Chen Liu                                 //
//    date: July 2, 2012                                        //
//                                                              //
//////////////////////////////////////////////////////////////////



#include<stdio.h>
#include"matrix.h"
#include"../../../SimpleDefinitions.h"

/* matric add operation for two 3 by 3 matrix */
/* the result matrix is stored in result matrix */
/* optimization for the msp430 processor will be done in the future */

extern void matrix_add(UI16 m1[3][3], UI16 m2[3][3],UI16 result[3][3])
{
	UI16 r,c;
	zeroMatrix(result);
	for(r=0;r<3;r++)
		for(c=0;c<3;c++)
			result[r][c]=m1[r][c]+m2[r][c];
    
}
extern void matrix_multiply(UI16 m1[3][3],UI16 m2[3][3], UI16 result[3][3])
{
	UI16 row,col,i;
	zeroMatrix(result);
	for(row=0;row<3;row++)
	{
		for(col=0;col<3;col++)
		{
			for(i=0;i<3;i++)
			{
				result[row][col] += m1[row][i]*m2[i][col]; 
			}
		}
	}
    
    
}
//TODO:remove
extern void printMatrix(UI16 m[3][3])
{
	UI16 i,j;
    
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			printf("%d ",m[i][j]);
		}
		printf("\n");
	}
    
	printf("matrix print end\n");
    
}

/****************************/
/*	Static Functions    */
/****************************/


static void zeroMatrix(UI16 m[3][3])
{
	UI16 i,j;
    
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			m[i][j]=0;
		}
	}
}

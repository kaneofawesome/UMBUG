//////////////////////////////////////////////////////////////////
//                                                              //
//    Matrix header                                             //
//    last edited by:  Chen Liu                                 //
//    date: July 2, 2012                                        //
//                                                              //
//////////////////////////////////////////////////////////////////

#ifndef MATRIX_H
#define MATRIX_H

#include"../../../SimpleDefinitions.h"
/*********************/
extern void matrix_add(UI16 m1[3][3],UI16 m2[3][3],UI16 result[3][3]);
extern void matrix_multiply(UI16 m1[3][3],UI16 m2[3][3],UI16 result[3][3]);

//TODO:remove 
extern void printMatrix(UI16 m[3][3]);

/*********************/
static void zeroMatrix(UI16 m[3][3]);

#endif

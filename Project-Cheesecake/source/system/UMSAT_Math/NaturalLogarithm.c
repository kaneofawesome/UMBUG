//////////////////////////////////////////////////////////////////
//                                                              //
//    Natural log source                                       	//
//    last edited by: Kane Anderson                             //
//    date: 08/13/2012		                                    //
//                                                              //
//////////////////////////////////////////////////////////////////

#include "NaturalLogarithm.h"

// definition /////////////////////////////////

float const pl[4] = {-1.080310025160955, 1.999999947089217};
float const ql[4] = {0.091284365719509, -0.873491916557671};
#define MAXFLOAT ((float)3.40282346638528860e+38)

// functions //////////////////////////////////

// returns the the natural log of x
float naturalLog(float x)
{
   float y, res, r, y2;

   UI8  data1,data2;

   signed char n;

   y = x;
   if (y == 0)
   	return -MAXFLOAT;
   if (y != 1.0)
   {

   data2 = *(((UI8*)(&y))+3);
   *(((UI8*)(&y))+3) = 0x3F;
   data1 = *(((UI8*)(&y))+2);
   data1 &= 0x7F;
   *(((UI8*)(&y))+2) = data1;
   if(data2 & 0x80)
     *(((UI8*)(&y))+3) |= 0x80;


      y = (y - 1.0)/(y + 1.0);

      y2=y*y;

      res = pl[0]*y2 + pl[1];

      r = ql[0]*y2 + ql[1];
      r = r*y2 + 1.0;

      res = y*res/r;


    data1 = *(((UI8*)(&x)+3));
    UI8 k;
    k=data1;
    if(k&0x80){
    	k<<=1;
    	k|=0x01;
    }
    else
    	k<<=1;
    data1=k;
    data2 = *(((UI8*)(&x)+2));
    if(data2 & 0x80)
      data1 |= 0x01;
    n = data1 - 0x7E;


      if (n<0) 
         r = -(float)-n;
      else
         r = (float)n;

      res += r*LN2;
   }

   else
      res = 0.0;

   return(res);
}








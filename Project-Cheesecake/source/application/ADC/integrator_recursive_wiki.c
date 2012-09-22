#include <math.h>  // include file for fabs and sin
#include <stdio.h> // include file for printf
/* 
//
// Recursive auxiliary function for adaptiveSimpsons() function below
//                                                                                                 
double adaptiveSimpsonsAux(double (*f)(double), double a, double b, double epsilon,                 
                         double S, double fa, double fb, double fc, int bottom) {                 
  double c = (a + b)/2, h = b - a;                                                                  
  double d = (a + c)/2, e = (c + b)/2;                                                              
  double fd = f(d), fe = f(e);                                                                      
  double Sleft = (h/12)*(fa + 4*fd + fc);                                                           
  double Sright = (h/12)*(fc + 4*fe + fb);                                                          
  double S2 = Sleft + Sright;                                                                       
  if (bottom <= 0 || fabs(S2 - S) <= 15*epsilon)                                                    
    return S2 + (S2 - S)/15;                                                                        
  return adaptiveSimpsonsAux(f, a, c, epsilon/2, Sleft,  fa, fc, fd, bottom-1) +                    
         adaptiveSimpsonsAux(f, c, b, epsilon/2, Sright, fc, fb, fe, bottom-1);                     
}         
 
//
// Adaptive Simpson's Rule
//
double adaptiveSimpsons(double (*f)(double),   // ptr to function
                           double a, double b,  // interval [a,b]
                           double epsilon,  // error tolerance
                           int maxRecursionDepth) {   // recursion cap        
  double c = (a + b)/2, h = b - a;                                                                  
  double fa = f(a), fb = f(b), fc = f(c);                                                           
  double S = (h/6)*(fa + 4*fc + fb);                                                                
  return adaptiveSimpsonsAux(f, a, b, epsilon, S, fa, fb, fc, maxRecursionDepth);                   
}                                                                                                   
 
 
int main(){
 double I = adaptiveSimpsons(sin, 0, 1, 0.000000001, 10); // compute integral of sin(x)
                                                          // from 0 to 1 and store it in 
                                                          // the new variable I
 printf("I = %lf\n",I); // print the result
 return 0;
}*/

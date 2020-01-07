
//**********************************************************
// Pseudo random number generator:
//     double drandom
//     void range (lower_limit, higher_limit)
//     void seed ()
//**********************************************************
//
// A simple linear congruential random number generator
// (Numerical Recipies chapter 7, 1st ed.) with parameters
// from the table on page 198j.
//
//  Uses a linear congruential generator to return a value between
//  0 and 1, then scales and shifts it to fill the desired range.  This
//  range is set when the random number generator range is called.
// 
// USAGE:
//
//      pseudo random sequence uniformally distributed in a range
//
//            void range (lower_limit, higher_limit)
//   
//      A basic seed is set inside range() which gives a deterministic 
//      pseudo random sequence.  For a higher quality seed call the 
//      function:
//
//            void seed()
//
//      AFTER the range is set.
//
//      In either case, once a range (and an optional seed) are called
//      you can generate a sequence of pseudo random numbers wiht repeated
//      calls to the function:
//
//            double drandom()
//
// History: 
//      Written by Tim Mattson, 9/2007.
//      changed to drandom() to avoid collision with standard libraries, 11/2011
//      updated seed with call to timeofday added

#include <sys/time.h>
#include <stdio.h>

static long MULTIPLIER  = 1366;
static long ADDEND      = 150889;
static long PMOD        = 714025;
long random_last = 0;
double random_low, random_hi;

double drandom()
{
    long random_next;
    double ret_val;

// 
// compute an integer random number from zero to PMOD
//
    random_next = (MULTIPLIER  * random_last + ADDEND)% PMOD;
    random_last = random_next;

//
// shift into preset range
//
    ret_val = ((double)random_next/(double)PMOD)*(random_hi-random_low)+random_low;
    return ret_val;
}
//
// set the range and a simple (but fixed) seed
//
void range(double low_in, double hi_in)
{
   if(low_in < hi_in)
   { 
      random_low = low_in;
      random_hi  = hi_in;
   }
   else
   {
      random_low = hi_in;
      random_hi  = low_in;
   }
   random_last = PMOD/ADDEND;  // just pick something

}
//
// set the seed using timeofday() to get a different value
// from one run to the next
//
void seed()
{
   struct timeval tim;
   union {
    double d;
    long   l;
   } double_cast;

   gettimeofday(&tim, NULL);
   double_cast.d = tim.tv_sec*100000+tim.tv_usec;
   random_last = (double_cast.l)%PMOD;
}
//**********************************************************
// end of pseudo random generator code.
//**********************************************************



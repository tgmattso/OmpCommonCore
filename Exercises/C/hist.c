/*

NAME:
   hist:  histogram

Purpose:
   This program will fill an array with pseudo random values, build
   a histogram of that array, and then compute statistics. This 
   can be used as a simple test of the quality of a random number
   generator 

Usage:
   To keep the program as simple as possible, you must edit the file
   and change basic parameters.  Then compile and run the program.

Algorithm:
   As a point of nomenclature, I like to think of a histogram as a sequence
   of buckets.  I take each item from an array, figure out which bucket it
   belongs to, then increment the appropriate bucket counter.
     
History: 
   Written by Tim Mattson, 7/2017.

*/
#include <stdio.h>
#include <omp.h>
#include <math.h>
#include "random.h"

// uncomment this #define if you want tons of diagnostic output
//#define     DEBUG         0

#define     num_trials    1000000 // number of x values
#define     num_buckets   50         // number of buckets in hitogram
static long xlow        = 0.0;      // low end of x range
static long xhi         = 100.0;    // High end of x range

int main ()
{

   double x[num_trials];     // array used to assign counters in the historgram 
   long   hist[num_buckets]; // the histogram
   double bucket_width;      // the width of each bucket in the histogram
   double time;


   seed(xlow, xhi);  // seed the random number generator over range of x
   bucket_width = (xhi-xlow)/(double)num_buckets;

   // fill the array
   for(int i=0;i<num_trials;i++)
     x[i] = drandom();

  // initialize the histogram
   for(int i=0;i<num_buckets;i++)
     hist[i] = 0;

  // Assign x values to the right historgram bucket
   time = omp_get_wtime();
   for(int i=0;i<num_trials;i++){
     
      long ival = (long) (x[i] - xlow)/bucket_width;

      hist[ival]++;  

      #ifdef DEBUG
      printf("i = %d,  xi = %f, ival = %d\n",i,(float)x[i], ival);
      #endif

   }

  time = omp_get_wtime() - time;

  double sumh=0.0, sumhsq=0.0, ave, std_dev;
  // compute statistics ... ave, std-dev for whole histogram and quartiles
   for(int i=0;i<num_buckets;i++){
     sumh   += (double) hist[i];
     sumhsq += (double) hist[i]*hist[i];
   }

   ave     = sumh/num_buckets;
   std_dev = sqrt(sumhsq - sumh*sumh/(double)num_buckets); 


   printf(" histogram for %d buckets of %d values\n",num_buckets, num_trials);
   printf(" ave = %f, std_dev = %f\n",(float)ave, (float)std_dev);
   printf(" in %f seconds\n",(float)time);

   return 0;
}
	  

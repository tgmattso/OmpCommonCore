// sample compile command: "gcc -fopenmp -c Fig_11.6_hist.c" to generate *.o object file

#include <omp.h>
#include <math.h>
//#include "random.h"  //seed() and drandom()                     

extern double drandom();
extern void seed(double low_in, double hi_in);

#define num_trials 1000000	 // number of x values
#define num_bins   100		   // number of bins in histogram
static long xlow = 0.0;		   // low end of x range
static long xhi = 100.0;	   // High end of x range

int main ()
{
   double x;                 
   long hist[num_bins];  // the histogram
   double bin_width;     // the width of each bin in the histogram
   omp_lock_t hist_lcks[num_bins]; // array of locks, one per bucket
   seed(xlow, xhi);  // seed random generator over range of x
   bin_width = (xhi - xlow) / (double)num_bins;

   // initialize the histogram and the array of locks
   #pragma omp parallel for schedule(static) 
   for (int i = 0; i < num_bins; i++) {
      hist[i] = 0;
      omp_init_lock(&hist_lcks[i]);
   }
   // test uniform pseudorandom sequence by assigning values 
   // to the right histogram bin
   #pragma omp parallel for schedule(static) private(x)
      for(int i = 0; i < num_trials; i++) {
     
      x = drandom();
      long ival = (long) (x - xlow)/bin_width;

      // protect histogram bins. Low overhead due to uncontended locks
      omp_set_lock(&hist_lcks[ival]);      
         hist[ival]++;                               
      omp_unset_lock(&hist_lcks[ival]);  
   }
   double sumh = 0.0, sumhsq = 0.0, ave, std_dev;
   // compute statistics (ave, std_dev) and destroy locks
   #pragma omp parallel for schedule(static) reduction(+:sumh,sumhsq)
      for (int i = 0; i < num_bins; i++) {
         sumh   += (double) hist[i];
         sumhsq += (double) hist[i] * hist[i];
         omp_destroy_lock(&hist_lcks[i]); 
      }
   ave = sumh / num_bins;
   std_dev = sqrt(sumhsq / ((double)num_bins) - ave * ave); 
   return 0;
}  

//---------------------------------------------------------------------------
//  Name:     pi_vec 
//
//  Purpose:  This function will numerically compute the integral of
//
//                  4/(1+x*x) 
//
//            from 0 to 1.  The value of this integral is pi.
//
//            In this version of the program, we unroll the loop by four
//            and use SSE 128 bit instructions on values of type packed 
//            float (ps).  We access SSE using the interface defined in 
//            xmmintrin.h and with g++.
//
// Results:   On a Mac OS X MacBook Pro with OS X 10.6.4 and an an Intel 
//            Core 2 Duo CPU at 2.4 GHz with 2 GB 667 MHz DDRw SDRAM 
//            with only a single thread for all CPU results (g++  -m64 -O3)
//
//               pi_reg    4000000   3.141593       0.080886 secs
//               pi_unroll 4000000   3.141593       0.033658 secs
//               pi_sse    4000000   3.141349       0.008818 secs
//
//             But the pi_reg and pi_unroll used double internally.  
//             Switching to float:
//
//               pi_reg    4000000   3.125990       0.042709 secs
//               pi_unroll 4000000   3.141348       0.051934 secs
//               pi_sse    4000000   3.141349       0.008776 secs
//
//            That the answers are so unstable for float is not surprising
//            given that an unordered sum is suseptible to round-off errors.
//            This effect is worse as the number of steps increases, so I 
//            tested just a couple data points for fewer steps:
//
//               pi_reg      1000000   3.1413       0.0111   secs
//               pi_sse      1000000   3.1415       0.0023   secs
//
//            To compare to the OCL vector results (pi_vocl), we checked
//            the results with NSTEPS = 512*512*16 (and for vocl, ITERS
//            equal to NSTEPS/(512*4) so we have 4 work groups of 512
//            work items
//
//               pi_vocl   4194304   3.141592       0.010563 secs   GPU
//               pi_reg    4194304   3.125117       0.044999 secs
//               pi_unroll 4194304   3.140426       0.054423 secs
//               pi_sse    4194304   3.140426       0.009209 secs
//
// NOTES:     We assue that the number of steps are a multiple of 4.
//
// HISTORY:   Written by Tim Mattson, July 2010
//---------------------------------------------------------------------------
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <immintrin.h>

#define NSTEPS (512*512*32)

#define NTRIALS     50
#define MAX_THREADS 4
#define DONE        1
#define BIG         10000000.0
#define SMALL       0.00000001
//---------------------------------------------------------------------------
// timer function 
//---------------------------------------------------------------------------
#define wtime omp_get_wtime

//---------------------------------------------------------------------------
// The various pi programs
//---------------------------------------------------------------------------
float pi_reg_default(int  num_steps)  // literals take default type .. double
{
   int i, j;
   float  step, x, pi, sum = 0.0;
   double start_time, run_time;
   double min, max, ave;
   min = BIG;  max = SMALL; ave = 0.0;

   step = 1.0/((float) num_steps);
   for (j=0;j<NTRIALS;j++){
   start_time = wtime();
   sum = 0.0;

   for (i=1;i<= num_steps; i++){
      x = (i-0.5)*step;
      sum = sum + 4.0/(1.0+x*x);
   }

   pi = step * sum;
   run_time = wtime() - start_time;

   ave+=run_time; if(run_time<min)min=run_time; if(run_time>max)max=run_time;
   }  //end of loop over trials
   printf("\n Base default  %d steps %f: ave=%f min=%f max=%f secs ",
                           num_steps,pi,(ave/(double)NTRIALS),min,max);

   return pi;
}	  

float pi_reg_float(int  num_steps) // literals explicity made float
{
   int i, j;
//   double step, x, pi, sum = 0.0;
   float  step, x, pi, sum = 0.0;
   double start_time, run_time;
   double min, max, ave;
   min = BIG;  max = SMALL; ave = 0.0;

   step = 1.0f/((float) num_steps);
   for (j=0;j<NTRIALS;j++){
   start_time = wtime();
   sum = 0.0f;

   for (i=1;i<= num_steps; i++){
      x = (i-0.5f)*step;
      sum = sum + 4.0f/(1.0f+x*x);
   }

   pi = step * sum;
   run_time = wtime() - start_time;

   ave+=run_time; if(run_time<min)min=run_time; if(run_time>max)max=run_time;
   }  //end of loop over trials
   printf("\n Base float    %d steps %f: ave=%f min=%f max=%f secs ",
                    num_steps,pi,(ave/(double)NTRIALS),min,max);

   return pi;
}	  

// unroll loop four times
float pi_unroll(int  num_steps)
{
   int i,j;
   float step, x0, x1, x2, x3, pi, sum = 0.0;
   double start_time, run_time;
   double min, max, ave;
   min = BIG;  max = SMALL; ave = 0.0;

   step = 1.0/(float) num_steps;

   for(j=0;j<NTRIALS;j++){
      start_time = wtime();
      sum=0.0;

      for (i=1;i<= num_steps; i=i+4){
         x0 = (i-0.5f)*step;
         x1 = (i+0.5f)*step;
         x2 = (i+1.5f)*step;
         x3 = (i+2.5f)*step;
         sum = sum + 4.0f*(1.0f/(1.0f+x0*x0) + 1.0f/(1.0f+x1*x1)  + 
                       1.0f/(1.0f+x2*x2)  + 1.0f/(1.0f+x3*x3));
      }

      pi = step * sum;
      run_time = wtime() - start_time;

      ave+=run_time; if(run_time<min)min=run_time; if(run_time>max)max=run_time;

   }  //end of loop over trials
   printf("\n Unroll 4      %d steps %f: ave=%f min=%f max=%f secs ",
                                          num_steps,pi,ave/NTRIALS,min,max);
   return pi;
}	  

// unroll loop, use SSE for loop body
float pi_sse(int  num_steps)   
{
   int i,j;
   float step, pi;
   double start_time, run_time;
   float scalar_one   = 1.0, scalar_zero = 0.0;
   float ival, scalar_four  = 4.0;
   float vsum[4];
   double min, max, ave;
   min = BIG;  max = SMALL; ave = 0.0;
   step = 1.0/(float) num_steps;

   for (j=0;j<NTRIALS;j++){
   start_time = wtime();
   __m128 ramp   = _mm_setr_ps(0.5, 1.5, 2.5, 3.5);
   __m128 one    = _mm_load1_ps(&scalar_one);
   __m128 four   = _mm_load1_ps(&scalar_four);
   __m128 vstep  = _mm_load1_ps(&step);
   __m128 sum    = _mm_load1_ps(&scalar_zero);
   __m128 xvec; 
   __m128 denom; 
   __m128 eye; 

   // unroll loop 4 times ... assume num_steps%4 = 0
   for (i=0;i< num_steps; i=i+4){
      ival  = (float)i;
      eye   = _mm_load1_ps(&ival);
      xvec  = _mm_mul_ps(_mm_add_ps(eye,ramp),vstep);
      denom = _mm_add_ps(_mm_mul_ps(xvec,xvec),one);
      sum   = _mm_add_ps(_mm_div_ps(four,denom),sum);
   }
   _mm_store_ps(&vsum[0],sum);

   pi = step * (vsum[0]+vsum[1]+vsum[2]+vsum[3]);
   run_time = wtime() - start_time;
   ave+=run_time; if(run_time<min)min=run_time; if(run_time>max)max=run_time;

   }
   printf("\n SSE           %d steps %f: ave=%f min=%f max=%f secs ",
                                          num_steps,pi,ave/NTRIALS,min,max);
   return pi;
}	  

// unroll loop, use SSE for loop body and parallel omp
float pi_sse_par(int  num_steps)
{
   int k,j;
   float step, local_sum[MAX_THREADS],pi;
   double start_time, run_time;
   double min, max, ave;
   min = BIG;  max = SMALL; ave = 0.0;
   step = 1.0/(float) num_steps;

   for (j=0;j<NTRIALS;j++){

      start_time = wtime();
      pi = 0.0f;
      for (k=0; k<MAX_THREADS; k++) local_sum[k] = 0.0;
      #pragma omp parallel 
      {
        int i,ID=omp_get_thread_num();
        float scalar_one   = 1.0, scalar_zero = 0.0;
        float ival, scalar_four  = 4.0;
        float vsum[4];
        __m128 ramp   = _mm_setr_ps(0.5, 1.5, 2.5, 3.5);
        __m128 one    = _mm_load1_ps(&scalar_one);
        __m128 four   = _mm_load1_ps(&scalar_four);
        __m128 vstep  = _mm_load1_ps(&step);
        __m128 sum    = _mm_load1_ps(&scalar_zero);
        __m128 xvec; 
        __m128 denom; 
        __m128 eye; 

        // unroll loop 4 times ... assume num_steps%4 = 0
        #pragma omp for
        for (i=0;i< num_steps; i=i+4){
           ival  = (float)i;
           eye   = _mm_load1_ps(&ival);
           xvec  = _mm_mul_ps(_mm_add_ps(eye,ramp),vstep);
           denom = _mm_add_ps(_mm_mul_ps(xvec,xvec),one);
           sum   = _mm_add_ps(_mm_div_ps(four,denom),sum);
        }
        _mm_store_ps(&vsum[0],sum);
   
        local_sum[ID] = step * (vsum[0]+vsum[1]+vsum[2]+vsum[3]);
      }

      for(k=0;k<MAX_THREADS;k++) pi += local_sum[k];
      run_time = wtime() - start_time;
      ave+=run_time; if(run_time<min)min=run_time; if(run_time>max)max=run_time;

   }
   printf("\n SSE + OMP par %d steps %f: ave=%f min=%f max=%f secs ",
                                          num_steps,pi,ave/NTRIALS,min,max);
   return pi;
}	  

float pi_omp_simd (int  num_steps)
{
   int i, j;
//   double step, x, pi, sum = 0.0;
   float  step, x, x0, pi, sum = 0.0;
   double start_time, run_time;
   double min, max, ave;
   min = BIG;  max = SMALL; ave = 0.0;

   step = 1.0/((float) num_steps);
   for (j=0;j<NTRIALS;j++){
   start_time = wtime();
   sum = 0.0f;

   x0 = -0.5*step;
   #pragma omp simd private(x) reduction(+:sum) 
   for (i=1;i<= num_steps; i++){
      x = x0 + (float)(i)*step;
      sum = sum + 4.0f/(1.0f+x*x);
   }

   pi = step * sum;
   run_time = wtime() - start_time;

   ave+=run_time; if(run_time<min)min=run_time; if(run_time>max)max=run_time;
   }  //end of loop over trials
   printf("\n OMP SIMD      %d steps %f: ave=%f min=%f max=%f secs ",
                   num_steps,pi,(ave/(double)NTRIALS),min,max);

   return pi;
}	  

float pi_omp_par_simd (int  num_steps)
{
   int i, j;
//   double step, x, pi, sum = 0.0;
   float  step, x, x0, pi, sum = 0.0;
   double start_time, run_time;
   double min, max, ave;
   min = BIG;  max = SMALL; ave = 0.0;

   step = 1.0/((float) num_steps);
   for (j=0;j<NTRIALS;j++){
   start_time = wtime();
   sum = 0.0f;

   x0 = -0.5f*step;
   #pragma omp parallel for simd private(x) reduction(+:sum)
   for (i=1;i<= num_steps; i++){
      x = x0 + (float)(i)*step;
      sum = sum + 4.0f/(1.0f+x*x);
   }

   pi = step * sum;
   run_time = wtime() - start_time;

   ave+=run_time; if(run_time<min)min=run_time; if(run_time>max)max=run_time;
   }  //end of loop over trials
   printf("\n OMP par SIMD  %d steps %f: ave=%f min=%f max=%f secs ",
                 num_steps,pi,(ave/(double)NTRIALS),min,max);

   return pi;
}	  

// unroll loop, use AVX for loop body and parallel omp
/*   <<<< skip this function.  Not all compilers support AVX >>>
float pi_avx(int  num_steps)
{
   int k,j;
   float step, local_sum[MAX_THREADS],pi;
   double start_time, run_time;
   double min, max, ave;
   min = BIG;  max = SMALL; ave = 0.0;
   step = 1.0/(float) num_steps;

   for (j=0;j<NTRIALS;j++){

      start_time = wtime();
      pi = 0.0f;
      for (k=0; k<MAX_THREADS; k++) local_sum[k] = 0.0;
      #pragma omp parallel 
      {
        int i,ID=omp_get_thread_num();
        float scalar_one   = 1.0, scalar_zero = 0.0;
        float ival, scalar_four  = 4.0;
//        float vsum[8];
          void *vsum_space;
          float *vsum;
          int r = posix_memalign(&vsum_space, 32, 8*sizeof(float));
          vsum = (float *)vsum_space;
//          float vsum[8] __attribute__((aligned(32)));
printf("\n%d vsum address %08x %ld\n",j,(unsigned)&vsum[0],((long)&vsum[0]%32));
       
        __m256 ramp   = _mm256_setr_ps(0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5);
        __m256 one    = _mm256_load_ps(&scalar_one);
        __m256 four   = _mm256_load_ps(&scalar_four);
        __m256 vstep  = _mm256_load_ps(&step);
        __m256 sum    = _mm256_load_ps(&scalar_zero);
        __m256 xvec; 
        __m256 denom; 
        __m256 eye; 

        // unroll loop 8 times ... assume num_steps%8 = 0
        #pragma omp for
        for (i=0;i< num_steps; i=i+8){
           ival  = (float)i;
           eye   = _mm256_load_ps(&ival);
           xvec  = _mm256_mul_ps(_mm256_add_ps(eye,ramp),vstep);
           denom = _mm256_add_ps(_mm256_mul_ps(xvec,xvec),one);
           sum   = _mm256_add_ps(_mm256_div_ps(four,denom),sum);
        }
//
//  This causes a segmentation fault
//
        _mm256_store_ps(&vsum[0],sum);
   
        local_sum[ID] = step * (vsum[0]+vsum[1]+vsum[2]+vsum[3]+
                                vsum[4]+vsum[5]+vsum[6]+vsum[7]);
      }

      for(k=0;k<MAX_THREADS;k++) pi += local_sum[k];
      run_time = wtime() - start_time;
      ave+=run_time; if(run_time<min)min=run_time; if(run_time>max)max=run_time;

   }
   printf("\n AVX + OMP par %d steps %f: ave=%f min=%f max=%f secs ",
                                          num_steps,pi,ave/NTRIALS,min,max);
   return pi;
}	  
<<<< skip pi AVX function >>>>>>>   */

int main()
{
  int num_steps=NSTEPS;

  // turn off dynamic mode ... so the same number of threads
  // are used for each parallel region
    omp_set_dynamic(0);
  
  float pi_val1    = pi_reg_default (num_steps);
  float pi_val2    = pi_reg_float   (num_steps);
  float pi_val3    = pi_unroll      (num_steps);
  float pi_val4    = pi_sse         (num_steps);
  float pi_val7    = pi_sse_par     (num_steps);
  float pi_val5    = pi_omp_simd    (num_steps);
  float pi_val6    = pi_omp_par_simd(num_steps);
//  float pi_val8    = pi_avx         (num_steps);
  printf("\n");
    #pragma omp parallel
    {
       #pragma omp master
         printf(" %d threads used when parallel.\n",omp_get_num_threads());
    }

}

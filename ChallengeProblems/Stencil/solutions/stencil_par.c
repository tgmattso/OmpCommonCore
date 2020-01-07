/*******************************************************************

NAME:    Stencil

PURPOSE: This program tests the efficiency with which a space-invariant,
         linear, symmetric filter (stencil) can be applied to a square
         grid or image.
  
USAGE:   The program takes as input the linear
         dimension of the grid, and the number of iterations on the grid

               <progname> <iterations> <grid size> 
  
         The output consists of diagnostics to make sure the 
         algorithm worked, and of timing statistics.

HISTORY: This program is based on the stencil program from the Parallel
         Reserach kernels.  To learn more, go to

             https://github.com/ParRes/Kernels
  
**********************************************************************************/

#include <stdio.h>
#ifdef APPLE
#include <stdlib.h>
#endif
#include <sys/time.h>
#include <omp.h>
#define  USEC_TO_SEC  1.0e-6    /* to convert microsecs to secs */

#define DEF_SIZE      2000
#define RADIUS        8
//#define RESTRICT    restrict
#define RESTRICT
#define EPSILON       1.0e-8
#define COEFX         1.0
#define COEFY         1.0
#define EXIT_FAIL     66
#define EXIT_SUCCESS  0  

/* define shorthand for indexing a multi-dimensional array                       */
#define IN(i,j)       in[i+(j)*(n)]
#define OUT(i,j)      out[i+(j)*(n)]
#define WEIGHT(ii,jj) weight[ii+RADIUS][jj+RADIUS]
#define ABS(x)        ((x)>0 ? (x) : (-(x)))

double wtime() {
  double time_seconds;
  struct timeval  time_data; /* seconds since 0 GMT */
   
  gettimeofday(&time_data,NULL);
  time_seconds  = (double) time_data.tv_sec;
  time_seconds += (double) time_data.tv_usec * USEC_TO_SEC;

  return time_seconds;
}

int main(int argc, char ** argv) {

  long   n;                 /* linear grid dimension                               */
  int    i, j, ii, jj, iter;/* dummies                                             */
  double norm = 0.0,        /* L1 norm of solution                                 */
         reference_norm;
  double f_active_points; /* interior of grid with respect to stencil            */
  double flops;           /* floating point ops per iteration                    */
  int    iterations=25;   /* number of times to run the algorithm                */
  double stencil_time,    /* timing parameters                                   */
         avgtime;
  int    stencil_size;    /* number of points in stencil                         */
  double  * RESTRICT in;  /* input grid values                                   */
  double  * RESTRICT out; /* output grid values                                  */
  long   total_length;    /* total required length to store grid values          */
  double weight[2*RADIUS+1][2*RADIUS+1]; /* weights of points in the stencil     */

   if(argc ==2){
      n = atoi(argv[1]);
   }
   else{
      n = DEF_SIZE;
   }

  if (2*RADIUS +1 > n) {
    printf("ERROR: Stencil radius %d exceeds grid size %d\n", RADIUS, n);
    exit(EXIT_FAIL);
  }

  /*  allocate the required space                                               */
  total_length = n*n*sizeof(double);
  in  = (double *) malloc(total_length);
  out = (double *) malloc(total_length);
  if (!in || !out) {
    printf("ERROR: could not allocate space for input or output array\n");
    exit(EXIT_FAIL);
  }

  /* fill the stencil weights to reflect a discrete divergence operator         */
  stencil_size = (2*RADIUS+1)*(2*RADIUS+1);
  for (jj=-RADIUS; jj<= RADIUS; jj++) for (ii=-RADIUS; ii<= RADIUS; ii++)
    WEIGHT(ii,jj)=0.0;
  for (jj=1; jj<=RADIUS; jj++) {
    for (ii=-jj+1; ii<jj; ii++) {
      WEIGHT(ii,jj)  =  (double) (1.0/(4.0*jj*(2.0*jj-1)*RADIUS));
      WEIGHT(ii,-jj) = -(double) (1.0/(4.0*jj*(2.0*jj-1)*RADIUS));
      WEIGHT(jj,ii)  =  (double) (1.0/(4.0*jj*(2.0*jj-1)*RADIUS));
      WEIGHT(-jj,ii) = -(double) (1.0/(4.0*jj*(2.0*jj-1)*RADIUS));      
    }
    WEIGHT(jj,jj)    =  (double) (1.0/(4.0*jj*RADIUS));
    WEIGHT(-jj,-jj)  = -(double) (1.0/(4.0*jj*RADIUS));
  }

  f_active_points = (double) (n-2*RADIUS)*(double) (n-2*RADIUS);

  printf("Serial stencil execution on 2D grid\n");
  printf("Grid size            = %d\n", n);
  printf("Radius of stencil    = %d\n", RADIUS);
  printf("Type of stencil      = compact\n");
  printf("Number of iterations = %d\n", iterations);

  /* intialize the input and output arrays                                     */
  #pragma omp parallel for collapse(2) private(i,j)
  for (j=0; j<n; j++) for (i=0; i<n; i++) 
    IN(i,j) = COEFX*i+COEFY*j;
  #pragma omp parallel for collapse(2) private(i,j)
  for (j=RADIUS; j<n-RADIUS; j++) for (i=RADIUS; i<n-RADIUS; i++) 
    OUT(i,j) = 0.0;

  for (iter = 0; iter<=iterations; iter++){

    /* start timer after a warmup iteration */
    if (iter == 1)  stencil_time = wtime();

    /* Apply the stencil operator                                               */
    #pragma omp parallel for collapse(2) private(ii,jj,i,j)
    for (j=RADIUS; j<n-RADIUS; j++) {
      for (i=RADIUS; i<n-RADIUS; i++) {
        /* would like to be able to unroll this loop, but compiler will ignore  */
        for (jj=-RADIUS; jj<=RADIUS; jj++) 
        for (ii=-RADIUS; ii<=RADIUS; ii++)  OUT(i,j) += WEIGHT(ii,jj)*IN(i+ii,j+jj);
      }
    }

    /* add constant to solution to force refresh of input data                  */
    #pragma omp parallel for collapse(2) private(i,j)
    for (j=0; j<n; j++) for (i=0; i<n; i++) IN(i,j)+= 1.0;

  } /* end of iterations                                                        */

  stencil_time = wtime() - stencil_time;

  /* compute L1 norm                                                            */
  for (j=RADIUS; j<n-RADIUS; j++) for (i=RADIUS; i<n-RADIUS; i++) {
    norm += (double)ABS(OUT(i,j));
  }

  norm /= f_active_points;

  /******************************************************************************
  ** Analyze and output results.
  *******************************************************************************/

/* verify correctness                                                           */
  reference_norm = (double) (iterations+1) * (COEFX + COEFY);
  if (ABS(norm-reference_norm) > EPSILON) {
    printf("ERROR: L1 norm = %lf, Reference L1 norm = %lf\n",
           norm, reference_norm);
    exit(EXIT_FAIL);
  }
  else {
    printf("Solution validates\n");
  }

  flops = (double) (2*stencil_size+1) * f_active_points;
  avgtime = stencil_time/iterations;
  printf("Parallel Rate (MFlops/s): %lf  Avg time (s): %lf\n",
         1.0E-06 * flops/avgtime, avgtime);

  exit(EXIT_SUCCESS);
}

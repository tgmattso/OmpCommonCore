// sample compile command: "gcc -fopenmp -c Fig_10.3_runtimeEx.c" to generate *.o object file

#include <omp.h>
#include <stdio.h>

#define DEBUG 1

// map schedule kind enum values to strings for printing
static char* schdKind[] = { "ERR","static","dynamic","guided","auto"};

// external function for potential energy term
extern double pot(double dist);

void forces(int npart,double x[],double f[],double side,double rcoff)
{
   #pragma omp parallel for schedule(runtime) 
      for (int i = 0; i < npart*3; i += 3) {

      // zero force components on particle i 
      double fxi = 0.0; double fyi = 0.0; double fzi = 0.0;

      // loop over all particles with index > i 
         for (int j = i + 3; j < npart * 3; j += 3) {

	    // compute distance between i and j with wraparound 
            double xx = x[i] - x[j];    
            double yy = x[i+1] - x[j+1];    
            double zz = x[i+2] - x[j+2];

            if(xx<(-0.5*side)) xx+=side; if(xx>(0.5*side)) xx-=side;
            if(yy<(-0.5*side)) yy+=side; if(yy>(0.5*side)) yy-=side;
            if(zz<(-0.5*side)) zz+=side; if(zz>(0.5*side)) zz-=side;
            double rd = xx * xx + yy * yy + zz * zz;

	    // if distance is inside cutoff radius, compute forces
            if (rd <= rcoff*rcoff) {
            double fcomp = pot(rd);
            fxi += xx*fcomp;   fyi += yy*fcomp;    fzi += zz*fcomp;
            f[j] -= xx*fcomp;  f[j+1] -= yy*fcomp; f[j+2] -= zz*fcomp;
            }
         } 
      // update forces on particle i 
	    f[i] += fxi;   f[i+1] += fyi;   f[i+2] += fzi;
      } 
   #ifdef DEBUG
      omp_sched_t kind;        
      int chunk_size;
      omp_get_schedule(&kind, &chunk_size);
      printf("schedule(%s,%d)\n",schdKind[kind],chunk_size);
   #endif 
}

/*
**  function: Matrix Multiplication ... three loop, basic 
**            algorithm with prior transpose of B for large 
**            matrices. 
**
**  HISTORY: Written by Tim Mattson, July 2012. 
*/
#include "mm_utils.h"
//#define LocalDEBUG 1
#define SMALLMAT 100


// 
// declare internal support functions
//
int matmul_trans(int Ndim, int Mdim, int Pdim, TYPE *A, TYPE *B, TYPE *C);

int matmul(int Ndim, int Mdim, int Pdim, TYPE *A, TYPE *B, TYPE *C);

//*******************************************************************
// Multiply two matrices (note this is not the official  dgemm def).
//  
//    C = A*B   (C is NxM, A is NxP and B is PxM)
//
void mm_trans(int N, int M, int P, TYPE *A, TYPE *B, TYPE *C)
{
   int ierr;
   if ((N + M + P)<(3*SMALLMAT)){
#ifdef LocalDEBUG
      printf("small mat mul %d, %d, %d\n",N,M,P);
#endif
      ierr = matmul(N, M, P, A, B, C);
   }
   else{
#ifdef LocalDEBUG
      printf("large (trans) mat mul %d, %d, %d\n",N,M,P);
#endif
      ierr = matmul_trans(N, M, P, A, B, C);
   }
}

/****************************************************************/
/*
** Compute C(Ndim, Mdim) = A(Ndim, Pdim) * B(Pdim,Mdim)
*/
int matmul(int Ndim, int Mdim, int Pdim, 
                 TYPE *A, TYPE *B, TYPE *C) 
{
   int i,j,k;
      
   for (i=0; i<Ndim; i++){
          for(k=0;k<Pdim;k++){
       for (j=0; j<Mdim; j++){
               /* C(i,j) = sum(over k) A(i,k) * B(k,j) */
               *(C+(i*Mdim+j)) += *(A+(i*Pdim+k)) *  *(B+(k*Mdim+j));
          }
       }
   }
   return 1;
}
/****************************************************************/
//
// transpose B before the multiplication
//
int matmul_trans(int Ndim, int Mdim, int Pdim, TYPE *A, TYPE *B, TYPE *C)
{
   TYPE *Bwrk;
   int i,j,k;

   Bwrk = (TYPE *) malloc(Pdim*Mdim*sizeof(double));

 // copy the transposed B matrix into Bwrk
   for (i=0; i<Pdim; i++){
       for (j=0; j<Mdim; j++){
         *(Bwrk+(j*Pdim+i)) =  *(B+(i*Mdim+j));
       }
   }

#ifdef LocalDEBUG
for (i=0; i<Pdim*Mdim; i++)
    printf(" B %d is %f\n",i,*(B+i));

for (i=0; i<Pdim*Mdim; i++)
    printf(" Btrans %d is %f\n",i,*(Bwrk+i));
#endif
      
//  do the multiplication but now assume B transposed for more
//  efficient memory access pattern
   for (i=0; i<Ndim; i++){
       for (j=0; j<Mdim; j++){
          for(k=0;k<Pdim;k++){
               /* C(i,j) = sum(over k) A(i,k) * B(k,j) */
               *(C+(i*Mdim+j)) += *(A+(i*Pdim+k)) *  *(Bwrk+(j*Pdim+k));
          }
       }
   }
   return 1;
}


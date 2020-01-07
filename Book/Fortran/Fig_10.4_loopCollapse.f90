! sample compile command to generate *.o object file:
!      gfortran -fopenmp -c Fig_10.4_loopCollapse.f90

   subroutine Apply(N, M, A, MFUNC)
      use omp_lib
      implicit none

      integer :: N, M
      real :: A(N,M), res
      integer :: i, j

      interface 
         function MFUNC (i,j,x) result (res)
            integer, intent(in) :: i, j
            real :: x, res 
         end function MFUNC
      end interface

      ! apply a function MFUNC to each element of an N by M array

      !$omp parallel do num_threads(4) collapse(2) if(N*M>100)
          do i = 1, N
             do j = 1, M
                res = MFUNC(i, j, A(i,j))
             enddo
          enddo
       !$omp end parallel do
   end subroutine 

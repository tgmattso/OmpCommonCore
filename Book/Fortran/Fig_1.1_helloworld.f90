program helloworld
use omp_lib
!$omp parallel
   write(*, '(a)', advance='no')'Hello '
   write(*, '(a)') 'World '
!$omp end parallel
end program helloworld

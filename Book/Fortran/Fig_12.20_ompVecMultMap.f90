program main
   use omp_lib

   integer, parameter :: N = 1024
   real*8, allocatable, dimension (:) :: a, b, c
   integer :: i

   allocate (a(N))
   allocate (b(N))
   allocate (c(N))

! initialize a, b, and c (code not shown)

!$omp target map(to:a(1:N),b(1:N)) map(tofrom:c(1:N))
!$omp teams distribute parallel do simd
   do i = 1, N
      c(i) = c(i) + a(i) * b(i)
   enddo
!$omp end teams distribute parallel do simd
!$omp end target

end program main

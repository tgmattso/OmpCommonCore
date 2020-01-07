! sample compile command to generate *.o object file:
!      gfortran -fopenmp -c Fig_10.3_runtimeEx.f90

subroutine forces(npart, x, f, side, rcoff)
   use omp_lib
   implicit none

   interface
      ! external function for potential energy term
      function pot (dist) result(res)
         real*8 :: dist
         real*8 :: res
      end function pot
   end interface

   integer(kind=omp_sched_kind) :: kind
   integer :: chunk_size
   logical :: DEBUG

   integer :: npart, i, j
   real*8 :: x(0:npart*3+2), f(0:npart*3+2)
   real*8 :: side, rcoff
   real*8 :: fxi, fyi, fzi
   real*8 :: xx, yy, zz, rd, fcomp

   character (len=:), allocatable :: schdKind(:)
   allocate (character(8) :: schdKind(0:4))
   ! map schedule kind enum values to strings for printing

   schdKind(0) = "ERR"
   schdKind(1) = "static"
   schdKind(2) = "dynamic"
   schdKind(3) = "guided"
   schdKind(4) = "auto"

   DEBUG = .true. 

   !$omp parallel do schedule(runtime) private(fxi,fyi,fzi,j,xx,yy,zz,rd,fcomp) 

      do i = 0, npart*3-1, 3
      ! zero force components on particle i 
       fxi = 0.0
       fyi = 0.0
       fzi = 0.0

      ! loop over all particles with index > i 
         do j = i+3, npart*3-1, 3

	    ! compute distance between i and j with wraparound 
            xx = x(i) - x(j)    
            yy = x(i+1) - x(j+1)    
            zz = x(i+2) - x(j+2)

            if (xx < (-0.5*side)) xx = xx + side
            if (xx > (0.5*side)) xx = xx - side
            if (yy < (-0.5*side)) yy = yy + side
            if (yy > (0.5*side)) yy = yy - side
            if (zz < (-0.5*side)) zz = zz + side
            if (zz > (0.5*side)) zz = zz - side
            rd = xx * xx + yy * yy + zz * zz

	    ! if distance is inside cutoff radius, compute forces
            if (rd <= rcoff*rcoff) then
               fcomp = pot(rd)
               fxi = fxi + xx*fcomp 
               fyi = fyi + yy*fcomp
               fzi = fzi + zz*fcomp
               f(j) = f(j) - xx*fcomp
               f(j+1) = f(j+1) - yy*fcomp
               f(j+2) = f(j+2) - zz*fcomp
            endif 
         enddo
         ! update forces on particle i 
         f(i) = f(i) + fxi 
         f(i+1) = f(i+1) + fyi 
         f(i+2) = f(i+2) + fzi
      enddo
   !$omp end parallel do

   if (DEBUG) then 
      call omp_get_schedule(kind, chunk_size)
      print *, "schedule ",schdKind(kind),"chunk_size=",chunk_size
   endif 
end subroutine forces

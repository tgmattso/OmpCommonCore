
/*
 *  Compute forces and accumulate the virial and the potential
 */
  extern double epot, vir;

  void
  forces(int npart, double x[], double f[], double side, double rcoff){

    int   i;
    vir    = 0.0;
    epot   = 0.0;

#pragma omp parallel for default(none) shared(f,x,npart,side,rcoff) reduction(+:epot,vir) schedule(static,32) 
    for (i=0; i<npart*3; i+=3) {


      // zero force components on particle i 

      double fxi = 0.0;
      double fyi = 0.0;
      double fzi = 0.0;
      int j;

      // loop over all particles with index > i 
 
      for (j=i+3; j<npart*3; j+=3) {

	// compute distance between particles i and j allowing for wraparound 

        double xx = x[i]-x[j];
        double yy = x[i+1]-x[j+1];
        double zz = x[i+2]-x[j+2];

        if (xx< (-0.5*side) ) xx += side;
        if (xx> (0.5*side) )  xx -= side;
        if (yy< (-0.5*side) ) yy += side;
        if (yy> (0.5*side) )  yy -= side;
        if (zz< (-0.5*side) ) zz += side;
        if (zz> (0.5*side) )  zz -= side;

        double rd = xx*xx+yy*yy+zz*zz;

	// if distance is inside cutoff radius compute forces
	// and contributions to pot. energy and virial 

        if (rd<=rcoff*rcoff) {

          double rrd      = 1.0/rd;
          double rrd3     = rrd*rrd*rrd;
          double rrd4     = rrd3*rrd;
          double r148     = rrd4*(rrd3 - 0.5);


          epot    += rrd3*(rrd3-1.0); 
          vir     -= rd*r148;

          fxi     += xx*r148;
          fyi     += yy*r148;
          fzi     += zz*r148;

#pragma omp atomic
	    f[j]    -= xx*r148;
#pragma omp atomic
	    f[j+1]  -= yy*r148;
#pragma omp atomic
	    f[j+2]  -= zz*r148;

        }

      }

      // update forces on particle i 
#pragma omp atomic
	f[i]     += fxi;
#pragma omp atomic
	f[i+1]   += fyi;
#pragma omp atomic
	f[i+2]   += fzi;
    }
  }

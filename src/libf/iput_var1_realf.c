/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*  
 *  (C) 2003 by Argonne National Laboratory and Northwestern University.
 *      See COPYRIGHT in top-level directory.
 *
 * This file is automatically generated by ./buildiface -infile=../lib/pnetcdf.h -deffile=defs
 * DO NOT EDIT
 */
#include "mpinetcdf_impl.h"


#ifdef F77_NAME_UPPER
#define nfmpi_iput_var1_real_ NFMPI_IPUT_VAR1_REAL
#elif defined(F77_NAME_LOWER_2USCORE)
#define nfmpi_iput_var1_real_ nfmpi_iput_var1_real__
#elif !defined(F77_NAME_LOWER_USCORE)
#define nfmpi_iput_var1_real_ nfmpi_iput_var1_real
/* Else leave name alone */
#endif


/* Prototypes for the Fortran interfaces */
#include "mpifnetcdf.h"
FORTRAN_API int FORT_CALL nfmpi_iput_var1_real_ ( int *v1, int *v2, MPI_Offset v3[], float *v4, MPI_Fint *v5 ){
    int ierr;
    int l2 = *v2 - 1;
    MPI_Offset *l3 = 0;

    { int ln = ncmpixVardim(*v1,*v2-1);
    if (ln > 0) {
        int li;
        l3 = (MPI_Offset *)malloc( ln * sizeof(MPI_Offset) );
        for (li=0; li<ln; li++) 
            l3[li] = v3[ln-1-li] - 1;
    }
    else if (ln < 0) {
        /* Error return */
        ierr = ln; 
	return ierr;
    }
    }
    ierr = ncmpi_iput_var1_float( *v1, l2, l3, v4, v5 );

    if (l3) { free(l3); }
    return ierr;
}

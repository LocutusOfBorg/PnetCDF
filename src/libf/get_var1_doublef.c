/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*  
 *  (C) 2001 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 *
 * This file is automatically generated by buildiface -infile=../lib/pnetcdf.h -deffile=defs
 * DO NOT EDIT
 */
#include "mpinetcdf_impl.h"


#ifdef F77_NAME_UPPER
#define nfmpi_get_var1_double_ NFMPI_GET_VAR1_DOUBLE
#elif defined(F77_NAME_LOWER_2USCORE)
#define nfmpi_get_var1_double_ nfmpi_get_var1_double__
#elif !defined(F77_NAME_LOWER_USCORE)
#define nfmpi_get_var1_double_ nfmpi_get_var1_double
/* Else leave name alone */
#endif


/* Prototypes for the Fortran interfaces */
#include "mpifnetcdf.h"
FORTRAN_API void FORT_CALL nfmpi_get_var1_double_ ( int *v1, int *v2, int v3[], double*v4, MPI_Fint *ierr ){
    *ierr = ncmpi_get_var1_double( *v1, *v2, (const size_t *)(v3), v4 );
}

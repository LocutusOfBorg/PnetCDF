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
#define nfmpi_inq_dim_ NFMPI_INQ_DIM
#elif defined(F77_NAME_LOWER_2USCORE)
#define nfmpi_inq_dim_ nfmpi_inq_dim__
#elif !defined(F77_NAME_LOWER_USCORE)
#define nfmpi_inq_dim_ nfmpi_inq_dim
/* Else leave name alone */
#endif


/* Prototypes for the Fortran interfaces */
#include "mpifnetcdf.h"
FORTRAN_API void FORT_CALL nfmpi_inq_dim_ ( int *v1, int *v2, char *v3 FORT_MIXED_LEN(d3), int *v4, MPI_Fint *ierr FORT_END_LEN(d3) ){
    *ierr = ncmpi_inq_dim( *v1, *v2, v3, v4 );
}

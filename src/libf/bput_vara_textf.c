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
#define nfmpi_bput_vara_text_ NFMPI_BPUT_VARA_TEXT
#elif defined(F77_NAME_LOWER_2USCORE)
#define nfmpi_bput_vara_text_ nfmpi_bput_vara_text__
#elif !defined(F77_NAME_LOWER_USCORE)
#define nfmpi_bput_vara_text_ nfmpi_bput_vara_text
/* Else leave name alone */
#endif


/* Prototypes for the Fortran interfaces */
#include "mpifnetcdf.h"
FORTRAN_API int FORT_CALL nfmpi_bput_vara_text_ ( int *v1, int *v2, MPI_Offset v3[], MPI_Offset v4[], char *v5 FORT_MIXED_LEN(d5), MPI_Fint *v6 FORT_END_LEN(d5) ){
    int ierr;
    int l2 = *v2 - 1;
    MPI_Offset *l3 = 0;
    MPI_Offset *l4 = 0;

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

    { int ln = ncmpixVardim(*v1,*v2-1);
    if (ln > 0) {
        int li;
        l4 = (MPI_Offset *)malloc( ln * sizeof(MPI_Offset) );
        for (li=0; li<ln; li++) 
            l4[li] = v4[ln-1-li];
    }
    else if (ln < 0) {
        /* Error return */
        ierr = ln; 
	return ierr;
    }
    }
    ierr = ncmpi_bput_vara_text( *v1, l2, l3, l4, v5, v6 );

    if (l3) { free(l3); }

    if (l4) { free(l4); }
    return ierr;
}

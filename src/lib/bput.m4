dnl Process this m4 file to produce 'C' language file.
dnl
dnl If you see this line, you can ignore the next one.
/* Do not edit this file. It is produced from the corresponding .m4 source */
dnl
/*
 *  Copyright (C) 2003, Northwestern University and Argonne National Laboratory
 *  See COPYRIGHT notice in top-level directory.
 */
/* $Id$ */

#if HAVE_CONFIG_H
# include <ncconfig.h>
#endif

#include <stdio.h>
#include <unistd.h>
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#include <assert.h>

#include <mpi.h>

#include "nc.h"
#include "ncx.h"
#include "ncmpidtype.h"
#include "macro.h"

/*----< ncmpi_buffer_attach() >-----------------------------------------------*/
int
ncmpi_buffer_attach(int        ncid,
                    MPI_Offset bufsize)
{
    int status;
    NC *ncp;

    if (bufsize <= 0) DEBUG_RETURN_ERROR(NC_ENULLBUF)

    status = ncmpii_NC_check_id(ncid, &ncp);
    if (status != NC_NOERR) return status;

    /* check if the buffer has been previously attached
     * note that in nc.c, the NC object is allocated with calloc, so
     * abuf should be initialized to NULL then
     */
    if (ncp->abuf != NULL) DEBUG_RETURN_ERROR(NC_EPREVATTACHBUF)

    ncp->abuf = (NC_buf*) NCI_Malloc(sizeof(NC_buf));

    ncp->abuf->size_allocated = bufsize;
    ncp->abuf->size_used = 0;
    ncp->abuf->table_size = NC_ABUF_DEFAULT_TABLE_SIZE;
    ncp->abuf->occupy_table = (NC_buf_status*)
               NCI_Calloc(NC_ABUF_DEFAULT_TABLE_SIZE, sizeof(NC_buf_status));
    ncp->abuf->tail = 0;
    ncp->abuf->buf = NCI_Malloc((size_t)bufsize);
    return NC_NOERR;
}

/*----< ncmpi_buffer_detach() >-----------------------------------------------*/
int
ncmpi_buffer_detach(int ncid)
{
    int  i, status;
    NC  *ncp;

    status = ncmpii_NC_check_id(ncid, &ncp);
    if (status != NC_NOERR) return status;

    /* check if the buffer has been previously attached */
    if (ncp->abuf == NULL) DEBUG_RETURN_ERROR(NC_ENULLABUF)

    /* this API assumes users are responsible for no pending bput */
    for (i=0; i<ncp->numPutReqs; i++) {
        if (ncp->put_list[i].abuf_index >= 0) /* check for a pending bput */
            DEBUG_RETURN_ERROR(NC_EPENDINGBPUT)
            /* return now, so users can call wait and try detach again */
    }

    NCI_Free(ncp->abuf->buf);
    NCI_Free(ncp->abuf->occupy_table);
    NCI_Free(ncp->abuf);
    ncp->abuf = NULL;

    return NC_NOERR;
}

#ifdef THIS_SEEMS_OVER_DONE_IT
/*----< ncmpi_buffer_detach() >-----------------------------------------------*/
/* mimic MPI_Buffer_detach()
 * Note from MPI: Even though the 'bufferptr' argument is declared as
 * 'void *', it is really the address of a void pointer.
 */
int
ncmpi_buffer_detach(int         ncid,
                    void       *bufptr,
                    MPI_Offset *bufsize)
{
    int  i, status;
    NC  *ncp;

    status = ncmpii_NC_check_id(ncid, &ncp);
    if (status != NC_NOERR) return status;

    /* check if the buffer has been previously attached */
    if (ncp->abuf == NULL) DEBUG_RETURN_ERROR(NC_ENULLABUF)

    /* check MPICH2 src/mpi/pt2pt/bsendutil.c for why the bufptr is void* */
    *(void **)bufptr = ncp->abuf->buf;
    *bufsize         = ncp->abuf->size_allocated;

    /* this API assumes users are responsible for no pending bput when called */
    for (i=0; i<ncp->numPutReqs; i++) {
        if (ncp->put_list[i].abuf_index >= 0) /* check for a pending bput */
            DEBUG_RETURN_ERROR(NC_EPENDINGBPUT)
            /* return now, so users can call wait and try detach again */
    }

    NCI_Free(ncp->abuf->occupy_table);
    NCI_Free(ncp->abuf);
    ncp->abuf = NULL;

    return NC_NOERR;
}
#endif


/*----< ncmpi_inq_buffer_usage() >--------------------------------------------*/
int
ncmpi_inq_buffer_usage(int         ncid,
                       MPI_Offset *usage) /* OUT: in bytes */
{
    int  status;
    NC  *ncp;

    status = ncmpii_NC_check_id(ncid, &ncp);
    if (status != NC_NOERR) return status;

    /* check if the buffer has been previously attached */
    if (ncp->abuf == NULL) DEBUG_RETURN_ERROR(NC_ENULLABUF)

    /* return the current usage in bytes */
    *usage = ncp->abuf->size_used;

    return NC_NOERR;
}

/*----< ncmpi_inq_buffer_size() >---------------------------------------------*/
int
ncmpi_inq_buffer_size(int         ncid,
                      MPI_Offset *buf_size) /* OUT: in bytes */
{
    int  status;
    NC  *ncp;

    status = ncmpii_NC_check_id(ncid, &ncp);
    if (status != NC_NOERR) return status;

    /* check if the buffer has been previously attached */
    if (ncp->abuf == NULL) DEBUG_RETURN_ERROR(NC_ENULLABUF)

    /* return the current usage in bytes */
    *buf_size = ncp->abuf->size_allocated;

    return NC_NOERR;
}

include(`foreach.m4')dnl
include(`utils.m4')dnl
dnl
define(`APINAME',`ifelse(`$2',`',`ncmpi_bput_var$1',`ncmpi_bput_var$1_$2')')dnl
dnl
dnl BPUT_API(kind, itype)
dnl
define(`BPUT_API',dnl
`dnl
/*----< APINAME($1,$2)() >------------------------------------------------*/
int
APINAME($1,$2)(int ncid, int varid, ArgKind($1) BufArgs(`put',$2), int *reqid)
{
    int         status;
    NC         *ncp;
    NC_var     *varp=NULL;
    ifelse(`$1', `',  `MPI_Offset *start, *count;',
           `$1', `1', `MPI_Offset *count;')

    if (reqid != NULL) *reqid = NC_REQ_NULL;
    status = ncmpii_sanity_check(ncid, varid, ArgStartCountStride($1),
                                 ifelse(`$2', `', `bufcount', `0'),
                                 ifelse(`$2', `', `buftype',  `ITYPE2MPI($2)'),
                                 API_KIND($1), ifelse(`$2', `', `1', `0'),
                                 0, WRITE_REQ,
                                 NONBLOCKING_IO, &ncp, &varp);
    if (status != NC_NOERR) return status;

    if (ncp->abuf == NULL) DEBUG_RETURN_ERROR(NC_ENULLABUF)

    ifelse(`$1', `',  `GET_FULL_DIMENSIONS(start, count)',
           `$1', `1', `GET_ONE_COUNT(count)')

    /* APINAME($1,$2) is a special case of APINAME(m,$2) */
    status = ncmpii_igetput_varm(ncp, varp, start, count, ArgStrideMap($1),
                                 (void*)buf,
                                 ifelse(`$2', `', `bufcount, buftype',
                                                  `-1, ITYPE2MPI($2)'),
                                 reqid, WRITE_REQ, 1, 0);
    ifelse(`$1', `', `NCI_Free(start);', `$1', `1', `NCI_Free(count);')
    return status;
}
')dnl
dnl
/*---- PnetCDF flexible APIs ------------------------------------------------*/
foreach(`kind', (, 1, a, s, m),`BPUT_API(kind,)
')

/*---- PnetCDF high-level APIs ----------------------------------------------*/
foreach(`kind', (, 1, a, s, m),
        `foreach(`itype', (ITYPE_LIST),
                 `BPUT_API(kind,itype)'
)')

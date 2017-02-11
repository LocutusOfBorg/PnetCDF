/*
 *  Copyright (C) 2017, Northwestern University and Argonne National Laboratory
 *  See COPYRIGHT notice in top-level directory.
 */
/* $Id$ */

#if HAVE_CONFIG_H
# include <ncconfig.h>
#endif

#include <dispatch.h>
#include <ncmpi_dispatch.h>
#include <nc.h>

static PNC_Dispatch ncmpi_dispatcher = {
    ncmpii_create,
    ncmpii_open,
    ncmpii_close,
    ncmpii_enddef,
    ncmpii__enddef,
    ncmpii_redef,
    ncmpii_sync,
    ncmpii_abort,
    ncmpii_set_fill,
    ncmpii_inq,
    ncmpii_inq_striping,
    ncmpii_inq_num_rec_vars,
    ncmpii_inq_num_fix_vars,
    ncmpii_inq_recsize,
    ncmpii_inq_put_size,
    ncmpii_inq_get_size,
    ncmpii_inq_header_size,
    ncmpii_inq_header_extent,
    ncmpii_inq_file_info,
    ncmpii_sync_numrecs,
    ncmpii_begin_indep_data,
    ncmpii_end_indep_data,

    ncmpii_def_dim,
    ncmpii_inq_dimid,
    ncmpii_inq_dim,
    ncmpii_rename_dim,

    ncmpii_inq_att,
    ncmpii_inq_attid,
    ncmpii_inq_attname,
    ncmpii_copy_att,
    ncmpii_rename_att,
    ncmpii_del_att,

    ncmpii_def_var,
    ncmpii_inq_var,
    ncmpii_inq_varid,
    ncmpii_rename_var
};

PNC_Dispatch* ncmpii_inq_dispatcher(void) {
    return &ncmpi_dispatcher;
}


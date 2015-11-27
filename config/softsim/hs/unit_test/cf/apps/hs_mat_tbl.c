/************************************************************************
** File:
**   $Id: hs_mat_tbl.c 1.2 2015/03/03 12:16:05EST sstrege Exp  $
**
**   Copyright © 2007-2014 United States Government as represented by the 
**   Administrator of the National Aeronautics and Space Administration. 
**   All Other Rights Reserved.  
**
**   This software was created at NASA's Goddard Space Flight Center.
**   This software is governed by the NASA Open Source Agreement and may be 
**   used, distributed and modified only pursuant to the terms of that 
**   agreement.
**
** Purpose:
**  The CFS Health and Safety (HS) Message Actions Table Definition
**
** Notes:
**
** $Log: hs_mat_tbl.c  $
** Revision 1.2 2015/03/03 12:16:05EST sstrege 
** Added copyright information
** Revision 1.1 2010/11/17 17:01:47EST aschoeni 
** Initial revision
** Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/hs/fsw/unit_test/cf/apps/project.pj
** Revision 1.1 2009/05/22 17:54:15EDT aschoeni 
** Initial revision
** Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/hs/fsw/unit_test/cf/project.pj
** Revision 1.1 2009/05/04 11:50:10EDT aschoeni 
** Initial revision
** Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/hs/fsw/project.pj
**
*************************************************************************/


/************************************************************************
** Includes
*************************************************************************/
#include "cfe.h"
#include "hs_tbl.h"
#include "hs_tbldefs.h"
#include "cfe_tbl_filedef.h"


static CFE_TBL_FileDef_t CFE_TBL_FileDef =
{
    "HS_Default_MsgActs_Tbl", "HS_APP.MsgActs_Tbl", "HS MsgActs Table",
    "hs_mat.tbl", (sizeof(HS_MATEntry_t) * HS_MAX_MSG_ACT_TYPES)
};



HS_MATEntry_t      HS_Default_MsgActs_Tbl[HS_MAX_MSG_ACT_TYPES] =
{
/*          EnableState               Cooldown       Message */

/*   0 */ { HS_MAT_STATE_ENABLED,      2,            {0x94, 0x19, 0x01, 0xC0, 0x09, 0x00, 0x37, 0x13, 
                                                      0x0d, 0xd0, 0x75, 0x34, 0x4D, 0xD3, 0xEF, 0xFE} },
/*   1 */ { HS_MAT_STATE_NOEVENT,      0,            {0x95, 0x19, 0x02, 0xC0, 0x07, 0x00, 0x37, 0x13, 
                                                      0xd0, 0x0d, 0x00, 0x15, 0xD3, 0x4D, 0x00, 0x00} },
/*   2 */ { HS_MAT_STATE_DISABLED,    10,            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} },
/*   3 */ { HS_MAT_STATE_DISABLED,    10,            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} },
/*   4 */ { HS_MAT_STATE_DISABLED,    10,            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} },
/*   5 */ { HS_MAT_STATE_DISABLED,    10,            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} },
/*   6 */ { HS_MAT_STATE_DISABLED,    10,            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} },
/*   7 */ { HS_MAT_STATE_DISABLED,    10,            {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
                                                      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} },

};

/************************/
/*  End of File Comment */
/************************/

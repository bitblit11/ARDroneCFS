/************************************************************************
** File:
**   $Id: hs_amt_bad.c 1.2 2015/03/03 12:16:22EST sstrege Exp  $
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
**  The CFS Health and Safety (HS) Applications Monitor Table Definition
**
** Notes:
**
** $Log: hs_amt_bad.c  $
** Revision 1.2 2015/03/03 12:16:22EST sstrege 
** Added copyright information
** Revision 1.1 2010/11/17 17:01:30EST aschoeni 
** Initial revision
** Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/hs/fsw/unit_test/cf/apps/project.pj
** Revision 1.1 2009/05/22 17:54:10EDT aschoeni 
** Initial revision
** Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/hs/fsw/unit_test/cf/project.pj
** Revision 1.1 2009/05/04 11:50:07EDT aschoeni 
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
    "HS_Default_AppMon_Tbl", "HS_APP.AppMon_Tbl", "HS AppMon Table",
    "hs_amt_bad.tbl", (sizeof(HS_AMTEntry_t) * HS_MAX_CRITICAL_APPS)
};



HS_AMTEntry_t      HS_Default_AppMon_Tbl[HS_MAX_CRITICAL_APPS] =
{
/*          AppName                    NullTerm CycleCount     ActionType */
                                                
/*   0 */ { "CFE_ES",                  1,       10,            HS_AMT_ACT_EVENT },
/*   1 */ { "CFE_EVS",                 0,       10,            47 },
/*   2 */ { "CFE_TIME",                0,       10,            HS_AMT_ACT_PROC_RESET },
/*   3 */ { "CFE_TBL",                 0,       10,            HS_AMT_ACT_MSG(0) },
/*   4 */ { "CFE_SB",                  0,       10,            HS_AMT_ACT_NOACT },
/*   5 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*   6 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*   7 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*   8 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*   9 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  10 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  11 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  12 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  13 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  14 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  15 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  16 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  17 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  18 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  19 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  20 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  21 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  22 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  23 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  24 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  25 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  26 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  27 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  28 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  29 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  30 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },
/*  31 */ { "",                        0,       10,            HS_AMT_ACT_NOACT },

};

/************************/
/*  End of File Comment */
/************************/

/************************************************************************
** File:
**   $Id: hs_emt_bad.c 1.2 2015/03/03 12:16:01EST sstrege Exp  $
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
**  The CFS Health and Safety (HS) Event Monitor Table Definition
**
** Notes:
**
** $Log: hs_emt_bad.c  $
** Revision 1.2 2015/03/03 12:16:01EST sstrege 
** Added copyright information
** Revision 1.1 2010/11/17 17:01:34EST aschoeni 
** Initial revision
** Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/hs/fsw/unit_test/cf/apps/project.pj
** Revision 1.1 2009/05/22 17:54:12EDT aschoeni 
** Initial revision
** Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/hs/fsw/unit_test/cf/project.pj
** Revision 1.1 2009/05/04 11:50:09EDT aschoeni 
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
    "HS_Default_EventMon_Tbl", "HS_APP.EventMon_Tbl", "HS EventMon Table",
    "hs_emt_bad.tbl", (sizeof(HS_EMTEntry_t) * HS_MAX_CRITICAL_EVENTS)
};



HS_EMTEntry_t      HS_Default_EventMon_Tbl[HS_MAX_CRITICAL_EVENTS] =
{
/*          AppName                    NullTerm EventID        ActionType */
                                                
/*   0 */ { "TASK_1",                  1,       2,             HS_EMT_ACT_MSG(0) },
/*   1 */ { "TASK_2",                  0,       5,             47 },
/*   2 */ { "TASK_3",                  0,       10,            HS_EMT_ACT_PROC_RESET },
/*   3 */ { "TASK_4",                  0,       10,            HS_EMT_ACT_APP_DELETE },
/*   4 */ { "TASK_1",                  0,       20,            HS_EMT_ACT_MSG(1) },
/*   5 */ { "",                        0,       10,            HS_EMT_ACT_NOACT },
/*   6 */ { "",                        0,       10,            HS_EMT_ACT_NOACT },
/*   7 */ { "",                        0,       10,            HS_EMT_ACT_NOACT },
/*   8 */ { "",                        0,       10,            HS_EMT_ACT_NOACT },
/*   9 */ { "",                        0,       10,            HS_EMT_ACT_NOACT },
/*  10 */ { "",                        0,       10,            HS_EMT_ACT_NOACT },
/*  11 */ { "",                        0,       10,            HS_EMT_ACT_NOACT },
/*  12 */ { "",                        0,       10,            HS_EMT_ACT_NOACT },
/*  13 */ { "",                        0,       10,            HS_EMT_ACT_NOACT },
/*  14 */ { "",                        0,       10,            HS_EMT_ACT_NOACT },
/*  15 */ { "",                        0,       10,            HS_EMT_ACT_NOACT },
                                 
};                               
                                 
/************************/       
/*  End of File Comment */       
/************************/       

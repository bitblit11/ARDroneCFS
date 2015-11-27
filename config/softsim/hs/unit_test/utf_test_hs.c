/************************************************************************
** File:
**   $Id: utf_test_hs.c 1.5 2015/03/03 12:16:31EST sstrege Exp  $
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
**   CFS Health and Safety (HS) unit test
**
**   $Log: utf_test_hs.c  $
**   Revision 1.5 2015/03/03 12:16:31EST sstrege 
**   Added copyright information
**   Revision 1.4 2011/10/17 16:43:57EDT aschoeni 
**   Updated Unit Tests
**   Revision 1.3 2010/11/17 17:08:46EST aschoeni 
**   updated to support cpu utilization monitoring
**   Revision 1.2 2010/05/25 18:55:18EDT aschoeni 
**   Updated to increase message limit from event msgid on event pipe
**   Revision 1.1 2009/05/22 17:56:19EDT aschoeni 
**   Initial revision
**   Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/hs/fsw/unit_test/project.pj
**
*************************************************************************/

/************************************************************************
** Includes
*************************************************************************/

#include "cfe.h"
#include "hs_app.h"
#include "hs_monitors.h"
#include "hs_cmds.h"
#include "hs_custom.h"
#include "hs_platform_cfg.h"
#include "utf_custom.h"
#include "utf_types.h"
#include "utf_cfe_sb.h"
#include "utf_cfe_time.h"
#include "utf_osapi.h"
#include "utf_cfe.h"
#include "utf_cfe_psp.h"
#include "cfe_es_cds.h"

/************************************************************************
** HS global data
*************************************************************************/
extern  HS_AppData_t HS_AppData;

#define HS_WAKEUP_PIPE            1
#define HS_EVENT_PIPE             2
#define HS_CMD_PIPE               3

/************************************************************************
** Function prototypes
*************************************************************************/
int32 CFE_SB_SubscribeHook(CFE_SB_MsgId_t MsgId, CFE_SB_PipeId_t PipeId);
int32 CFE_SB_SubscribeExHook(CFE_SB_MsgId_t MsgId, CFE_SB_PipeId_t PipeId, CFE_SB_Qos_t Quality, uint16 MsgLim);
int32 CFE_SB_CreatePipeHookFail(CFE_SB_PipeId_t *PipeIdPtr, uint16  Depth, char *PipeName);
int32 CFE_SB_CreatePipeHook(CFE_SB_PipeId_t *PipeIdPtr, uint16  Depth, char *PipeName);
int32 CFE_TBL_RegisterHook( CFE_TBL_Handle_t *TblHandlePtr,
                        const char *Name,
                        uint32  Size,
                        uint16  TblOptionFlags,
                        CFE_TBL_CallbackFuncPtr_t TblValidationFuncPtr );
void UTF_HS_LoadTablesFromGround(void); 
void UTF_HS_CallbackSync(void); 
void UTF_HS_IncIdle(void);
void UTF_HS_BadSub(void);

extern void HS_IdleTask(void); 
extern void HS_MarkIdleCallback(void);

typedef struct
{
  int32   UtilMult1;/**< \brief CPU Utilization Conversion Factor Multiplication 1 */
  int32   UtilDiv;/**< \brief CPU Utilization Conversion Factor Division */
  int32   UtilMult2;/**< \brief CPU Utilization Conversion Factor Multiplication 2 */

  uint32   UtilMask;/**< \brief Mask for determining Idle Tick length */
  uint32   UtilArrayIndex;/**< \brief Index for determining where to write in Util Array */
  uint32   UtilArrayMask;/**< \brief Mask for determining where to write in Util Array */
  uint32   UtilArray[HS_UTIL_TIME_DIAG_ARRAY_LENGTH];/**< \brief Array to store time stamps for determining idle tick length */

  uint32   ThisIdleTaskExec;/**< \brief Idle Task Exec Counter */
  uint32   LastIdleTaskExec;/**< \brief Idle Task Exec Counter at Previous Interval */
  uint32   LastIdleTaskInterval;/**< \brief Idle Task Increments during Previous Interval */
  uint32   UtilCycleCounter;/**< \brief Counter to determine when to monitor utilization */


   int32   IdleTaskRunStatus;/**< \brief HS Idle Task Run Status */
  uint32   IdleTaskID;/**< \brief HS Idle Task Task ID */
 
} HS_CustomData_t;

extern HS_CustomData_t HS_CustomData;

/************************************************************************
** HS Unit Test Main Routine
*************************************************************************/
int main(void)
{
    uint32 DevCtr;
    uint32 IsrCtr;

    /*******************************************************************/
    /* Add special commands to simplify the input script file sbsim.in */           
    /*******************************************************************/   
    UTF_add_special_command("LOAD_TABLES_FROM_GROUND", UTF_HS_LoadTablesFromGround);
    UTF_add_special_command("CALLBACK_SYNC", UTF_HS_CallbackSync);
    UTF_add_special_command("INC_IDLE", UTF_HS_IncIdle);
    UTF_add_special_command("BAD_SUB", UTF_HS_BadSub);

    /*******************************************************************/
    /* Add command pipes and associated script files                   */           
    /*******************************************************************/   
    UTF_add_input_file(HS_WAKEUP_PIPE, "wakeup.in");
    UTF_add_input_file(HS_EVENT_PIPE, "event.in");
    UTF_add_input_file(HS_CMD_PIPE, "cmd.in");


    /**************************************************/
    /* Call utility to register task with             */
    /*              Executive Services.                       */
    /**************************************************/
    UTF_ES_InitAppRecords();
    UTF_ES_AddAppRecord("HS_APP",0);    
    CFE_ES_RegisterApp();
    OS_TaskRegister();
    CFE_EVS_Register(NULL, 0, CFE_EVS_BINARY_FILTER);


    /**************************************************/
    /* Initialize Table Services data structures      */
    /**************************************************/
    CFE_ES_CDS_EarlyInit();
    CFE_TBL_EarlyInit();
    

    /******************************************************/
    /* Add a simulated on-board /cf directory           . */
    /* These directory is an actual folder on the local   */ 
    /* file system located in the unit_test directory     */
    /******************************************************/    
    UTF_add_volume("/", "cf",  FS_BASED, FALSE, FALSE, TRUE, "CF",  "/cf", 0);

    /******************************************************/
    /* Add the generic counters.                          */
    /******************************************************/    
    CFE_ES_RegisterGenCounter(&DevCtr, "DEV_X");
    CFE_ES_RegisterGenCounter(&IsrCtr, "ISR_Y");
    CFE_ES_SetGenCount(DevCtr, 254);
    CFE_ES_SetGenCount(IsrCtr, 18);

    /************************************************************************
    ** Start the Unit Test
    *************************************************************************/
    UTF_put_text("*************************\n");
    UTF_put_text("* HS Init Failure Tests *\n");
    UTF_put_text("*************************\n");
    UTF_put_text("\n");

    /*
    ** -> HS_AppMain -> HS_AppInit
    ** Test path that terminates HS due to failure during EVS registration 
    */
    UTF_put_text("Test Init with EVS Reg Failure \n");
    UTF_put_text("------------------------------ \n");   
    UTF_CFE_EVS_Set_Api_Return_Code(0,-1);    
    HS_AppMain();
    UTF_CFE_EVS_Use_Default_Api_Return_Code(0);
    UTF_put_text("\n");

    /*
    ** -> HS_AppMain -> HS_AppInit -> HS_SbInit (Pipe Creation)
    ** Test paths that terminates HS due to failure during CFE_SB_CreatePipe
    ** Use a custom hook for this as we have multiple pipes, then restore 
    */
    UTF_SB_set_function_hook(CFE_SB_CREATEPIPE_HOOK, (void *)&CFE_SB_CreatePipeHookFail);

    UTF_put_text("Test Init with Create CMD Pipe Failure \n");
    UTF_put_text("-------------------------------------- \n");
    HS_AppMain();
    UTF_put_text("\n");
    UTF_put_text("Test Init with Create EVENT Pipe Failure \n");
    UTF_put_text("---------------------------------------- \n");
    HS_AppMain();
    UTF_put_text("\n");
    UTF_put_text("Test Init with Create WAKEUP Pipe Failure \n");
    UTF_put_text("----------------------------------------- \n");
    HS_AppMain();
    UTF_put_text("\n");

    UTF_SB_set_function_hook(CFE_SB_CREATEPIPE_HOOK, (void *)NULL);
    
    /*
    ** -> HS_AppMain -> HS_AppInit -> HS_SbInit (Subscriptions)
    ** Test paths that terminates HS due to failure during CFE_SB_Subscribe
    ** Use a custom hook for this as we have multiple subs, then restore 
    */
    UTF_SB_set_function_hook(CFE_SB_SUBSCRIBE_HOOK, (void *)&CFE_SB_SubscribeHook);

    UTF_put_text("Test Init with HK Subscription Failure \n");
    UTF_put_text("-------------------------------------- \n");
    HS_AppMain();
    UTF_put_text("\n");
    UTF_put_text("Test Init with CMD Subscription Failure \n");
    UTF_put_text("--------------------------------------- \n");
    HS_AppMain();
    UTF_put_text("\n");
    UTF_put_text("Test Init with WAKEUP Subscription Failure \n");
    UTF_put_text("------------------------------------------ \n");
    HS_AppMain();
    UTF_put_text("\n");

    /*
    ** -> HS_AppMain 
    ** We're jumping forward to test this one too for now
    ** Updated to use SubscribeEx (for ExTREME) instead of Subscribe
    */

    UTF_SB_set_function_hook(CFE_SB_SUBSCRIBE_HOOK, (void *)NULL);
    UTF_SB_set_function_hook(CFE_SB_SUBSCRIBEEX_HOOK, (void *)&CFE_SB_SubscribeExHook);

    UTF_put_text("Test Init with Event Subscription Failure \n");
    UTF_put_text("----------------------------------------- \n");
    HS_AppMain();
    UTF_put_text("\n");   

    /*
    ** -> HS_AppMain -> HS_AppInit (CDS Failure to Restore)
    ** Test failure to restore CDS at startup -- fail out with event subscription
    ** failure as this does not cause a fatal error
    */
    UTF_put_text("Test Init with CDS Restoration Failure \n");
    UTF_put_text("(Fails out due to Event Subscription Failure) \n");
    UTF_put_text("-------------------------------------- \n");
    UTF_CFE_ES_Set_Api_Return_Code(CFE_ES_RESTOREFROMCDS_PROC,-1);    
    HS_AppMain();
    UTF_CFE_ES_Use_Default_Api_Return_Code(CFE_ES_RESTOREFROMCDS_PROC);
    UTF_put_text("\n");

    /*
    ** -> HS_AppMain -> HS_AppInit (CDS Corruption)
    ** Test failure to load CDS due to corruption at startup -- fail out with event subscription
    ** failure as this does not cause a fatal error
    */
    UTF_put_text("Test Init with CDS Corruption \n");
    UTF_put_text("(Fails out due to Event Subscription Failure) \n");
    UTF_put_text("----------------------------- \n");
    HS_AppData.CDSData.MaxResetsNot = 24;
    CFE_ES_CopyToCDS(HS_AppData.MyCDSHandle,&HS_AppData.CDSData);
    HS_AppMain();
    UTF_put_text("\n");

    /*
    ** -> HS_AppMain -> HS_AppInit (CDS Failure on Creation)
    ** Test failure to CDS Failure on Creation at startup -- fail out with event subscription
    ** failure as this does not cause a fatal error
    */
    UTF_put_text("Test Init with CDS Creation Failure \n");
    UTF_put_text("(Fails out due to Event Subscription Failure) \n");
    UTF_put_text("----------------------------------- \n");
    UTF_CFE_ES_Set_Api_Return_Code(CFE_ES_REGISTERCDS_PROC,-1);    
    HS_AppMain();
    UTF_CFE_ES_Use_Default_Api_Return_Code(CFE_ES_REGISTERCDS_PROC);
    UTF_put_text("\n");

    /*
    ** -> HS_AppMain -> HS_AppInit -> HS_IdleTaskInit (Child Task Creation Failure)
    ** Test failure to child task creation failure at startup -- fail out with event subscription
    ** failure as this does not cause a fatal error
    */
    UTF_put_text("Test Init with Child Task Creation Failure \n");
    UTF_put_text("(Fails out due to Event Subscription Failure) \n");
    UTF_put_text("----------------------------------- \n");
    UTF_CFE_ES_Set_Api_Return_Code(CFE_ES_CREATECHILDTASK_PROC,-1);    
    HS_AppMain();
    UTF_CFE_ES_Use_Default_Api_Return_Code(CFE_ES_CREATECHILDTASK_PROC);
    UTF_put_text("\n");

    /*
    ** -> HS_AppMain -> HS_AppInit -> HS_IdleTaskInit (Sync Callback Creation Failure)
    ** Test failure due to sync callback failure at startup -- fail out with event subscription
    ** failure as this does not cause a fatal error
    */
    UTF_put_text("Test Init with Sync Callback Failure \n");
    UTF_put_text("(Fails out due to Event Subscription Failure) \n");
    UTF_put_text("----------------------------------- \n");
    UTF_CFE_TIME_Set_Api_Return_Code(CFE_TIME_REGISTERSYNCHCALLBACK_PROC,-1);    
    HS_AppMain();
    UTF_CFE_TIME_Use_Default_Api_Return_Code(CFE_TIME_REGISTERSYNCHCALLBACK_PROC);
    UTF_put_text("\n");

    /*
    ** -> HS_AppMain -> HS_AppInit -> HS_TblInit (Loading/AcqPointering)
    ** Test failure to load tables at startup -- fail out with event subscription
    ** failure as this does not cause a fatal error
    */
    UTF_put_text("Test Init with Tbl Load Failures \n");
    UTF_put_text("(Fails out due to Event Subscription Failure) \n");
    UTF_put_text("-------------------------------- \n");
    UTF_CFE_TBL_Set_Api_Return_Code(CFE_TBL_LOAD_PROC,-1);    
    HS_AppMain();
    UTF_CFE_TBL_Use_Default_Api_Return_Code(CFE_TBL_LOAD_PROC);
    UTF_put_text("\n");

    /*
    ** -> HS_AppMain -> HS_AppInit -> HS_TblInit -> HS_AcquirePointers (GetAddress)
    ** Test failure to get table addresses -- fail out with event subscription
    ** failure as this does not cause a fatal error
    */
    UTF_put_text("Test Tbl GetAddress Failures \n");
    UTF_put_text("(Fails out due to Event Subscription Failure) \n");
    UTF_put_text("---------------------------- \n");
    UTF_CFE_TBL_Set_Api_Return_Code(CFE_TBL_GETADDRESS_PROC,-1);    
    UTF_CFE_SB_Set_Api_Return_Code(CFE_SB_UNSUBSCRIBE_PROC,-42);    
    HS_AppMain();
    UTF_CFE_TBL_Use_Default_Api_Return_Code(CFE_SB_UNSUBSCRIBE_PROC);    
    UTF_CFE_TBL_Use_Default_Api_Return_Code(CFE_TBL_GETADDRESS_PROC);
    UTF_put_text("\n");

    /*
    ** Stop failing out with event subscription error
    */
    UTF_SB_set_function_hook(CFE_SB_SUBSCRIBEEX_HOOK, (void *)NULL);

    /*
    ** -> HS_AppMain -> HS_AppInit -> HS_TblInit (Registration)
    ** Test paths that terminates HS due to failure during CFE_SB_Subscribe
    ** Use a custom hook for this as we have multiple tables, then restore 
    */
    UTF_TBL_set_function_hook(CFE_TBL_REGISTER_HOOK, (void *)&CFE_TBL_RegisterHook);   

    UTF_put_text("Test Init with AppMon Reg Failure \n");
    UTF_put_text("--------------------------------- \n");    
    HS_AppMain();
    UTF_put_text("\n");
    UTF_put_text("Test Init with EventMon Reg Failure \n");
    UTF_put_text("----------------------------------- \n");    
    HS_AppMain();
    UTF_put_text("\n");
    UTF_put_text("Test Init with MsgActs Reg Failure \n");
    UTF_put_text("---------------------------------- \n");    
    HS_AppMain();
    UTF_put_text("\n");
    UTF_put_text("Test Init with ExeCount Reg Failure \n");
    UTF_put_text("----------------------------------- \n");    
    HS_AppMain();
    UTF_put_text("\n");
    
    UTF_TBL_set_function_hook(CFE_TBL_REGISTER_HOOK, (void *)NULL);
    
    /*
    ** -> HS_AppMain
    ** Test SB read failure in main loop
    */
    UTF_SB_set_function_hook(CFE_SB_CREATEPIPE_HOOK, (void *)&CFE_SB_CreatePipeHook);   
    UTF_put_text("Test HS_AppMain with SB Failure \n");
    UTF_put_text("------------------------------- \n");
    UTF_CFE_SB_Set_Api_Return_Code(CFE_SB_RCVMSG_PROC,-42);    
    UTF_ES_InitAppRecords();
    UTF_ES_AddAppRecord("HS_APP",0);
    HS_AppMain();
    UTF_CFE_SB_Use_Default_Api_Return_Code(CFE_SB_RCVMSG_PROC);
    UTF_put_text("\n");

    /*
    ** Test HS Idle Task
    */
    HS_CustomData.UtilMask = 0x000F;
    HS_IdleTask();
    HS_CustomData.UtilArray[0] = 100;
    HS_CustomData.UtilArray[1] = 100;
    HS_CustomData.UtilArray[2] = 120;

    /*
    ** Test no errors path of HS main
    */
    UTF_SB_set_function_hook(CFE_SB_CREATEPIPE_HOOK, (void *)&CFE_SB_CreatePipeHook);   
    UTF_put_text("Test HS_AppMain with No Failures \n");
    UTF_put_text("-------------------------------- \n");
    UTF_ES_InitAppRecords();
    UTF_ES_AddAppRecord("HS_APP",0);
    UTF_ES_AddAppRecord("TASK_1",1);
    UTF_ES_AddAppRecord("TASK_2",2);
    UTF_ES_AddAppRecord("TASK_3",3);
    UTF_ES_AddAppRecord("TASK_4",4);
    UTF_ES_AddTaskRecord("CTSK_1", 1, 5);
    UTF_ES_AddTaskRecord("CTSK_2", 1, 6);
    HS_AppMain();
    UTF_put_text("\n");

    return 0;
}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Hook function for CFE_SB_Subscribe that will return an error    */
/* on some calls                                                                   */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 CFE_SB_SubscribeHook(CFE_SB_MsgId_t MsgId, CFE_SB_PipeId_t PipeId) 
{
    static uint32 Count = 0;

    Count++;
    
    if ((Count == 1)||/* used to fail the first subscibe call in HS_AppInit */
        (Count == 3)||/* used to fail the second subscibe call in HS_AppInit */
        (Count == 6))/* used to fail the third subscibe call in HS_AppInit */
    {
        return(CFE_SB_MAX_MSGS_MET);
    }else{
        return(CFE_SUCCESS);
    }
       
}/* end CFE_SB_SubscribeHook */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Hook function for CFE_SB_SubscribeEx that will return an error  */
/* on some calls                                                   */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 CFE_SB_SubscribeExHook(CFE_SB_MsgId_t MsgId, CFE_SB_PipeId_t PipeId, CFE_SB_Qos_t Quality, uint16 MsgLim) 
{
    return(CFE_SB_MAX_MSGS_MET);
       
}/* end CFE_SB_SubscribeExHook */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Hook function for CFE_SB_CreatePipe that will return an error    */
/* on some calls                                                                   */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 CFE_SB_CreatePipeHookFail(CFE_SB_PipeId_t *PipeIdPtr, uint16  Depth, char *PipeName)
{
    static uint32 Count = 0;

    Count++;
    
    if ((Count == 1)||/* used to fail the first create pipe call in HS_AppInit */
        (Count == 3)||/* used to fail the second create pipe call in HS_AppInit */
        (Count == 6))/* used to fail the third create pipe call in HS_AppInit */
    {
        return(-1);
    }else{
        return(CFE_SUCCESS);
    }
       
}/* end CFE_SB_CreatePipeHookFail */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Hook function for CFE_SB_CreatePipe that will set the correct   */
/* values for each pipe                                            */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 CFE_SB_CreatePipeHook(CFE_SB_PipeId_t *PipeIdPtr, uint16  Depth, char *PipeName)
{
    static uint32 Count = 0;

    Count++;
    
    if (Count == 4)
    {
        Count = 1;
    }
    if (Count == 1)
    {
        *PipeIdPtr = HS_CMD_PIPE;
    }
    if (Count == 2)
    {
        *PipeIdPtr = HS_EVENT_PIPE;
    }
    if (Count == 3)
    {
        *PipeIdPtr = HS_WAKEUP_PIPE;
    }
    return(CFE_SUCCESS);
      
}/* end CFE_SB_CreatePipeHook */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Hook function for CFE_TBL_Register that will return an error    */
/* on some calls                                                                   */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
int32 CFE_TBL_RegisterHook( CFE_TBL_Handle_t *TblHandlePtr,
                        const char *Name,
                        uint32  Size,
                        uint16  TblOptionFlags,
                        CFE_TBL_CallbackFuncPtr_t TblValidationFuncPtr ) 
{
    static uint32 Count = 0;

    Count++;
    
    if ((Count == 1)||/* used to fail the first register call in HS_TblInit */
        (Count == 3)||/* used to fail the second register call in HS_TblInit */
        (Count == 6)||/* used to fail the third register call in HS_TblInit */
        (Count == 10))/* used to fail the fourth register call in HS_TblInit */
    {
        return(CFE_TBL_ERR_INVALID_SIZE);
    }else{
       return(CFE_SUCCESS);
    }
       

}/* end CFE_TBL_RegisterHook */


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Function to simulate loading all tables from ground             */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void UTF_HS_LoadTablesFromGround(void)
{
    UTF_TBL_LoadTableFromGround("HS_APP.AppMon_Tbl",   "/cf/apps/hs_amt_bad.tbl");
    UTF_TBL_LoadTableFromGround("HS_APP.EventMon_Tbl", "/cf/apps/hs_emt_bad.tbl");
    UTF_TBL_LoadTableFromGround("HS_APP.MsgActs_Tbl",  "/cf/apps/hs_mat_bad.tbl");
#if HS_MAX_EXEC_CNT_SLOTS > 0
    UTF_TBL_LoadTableFromGround("HS_APP.ExeCount_Tbl", "/cf/apps/hs_xct_bad.tbl");
#endif
    return;

}/* end CFE_TBL_RegisterHook */

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Function to simulate the callback sync                          */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void UTF_HS_CallbackSync(void)
{
    HS_MarkIdleCallback();
    return; 
 
}/* end UTF_HS_CallbackSync */
 

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Function to simulate idle count increments                      */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void UTF_HS_IncIdle(void)
{
    static uint32 Count = 0;

    Count++;

    if(Count == 1)
    {
       HS_CustomData.ThisIdleTaskExec += 300;
       HS_CustomData.UtilMult2 = -11;
    }
    else if(Count == 2)
    {
       HS_CustomData.ThisIdleTaskExec += 976114036;
       HS_CustomData.UtilMult2 = 11;
    }else{
       HS_CustomData.ThisIdleTaskExec++;
    }
 
    return;

}/* end UTF_HS_IncIdle */
void UTF_HS_BadSub(void);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                 */
/* Function to test bad event command subscriptions                */
/*                                                                 */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
void UTF_HS_BadSub(void)
{
    static uint32 Count = 0;

    Count++;

    if((Count == 1) || (Count == 3))
    {
        UTF_CFE_SB_Set_Api_Return_Code(CFE_SB_SUBSCRIBEEX_PROC,-42);    
        UTF_CFE_SB_Set_Api_Return_Code(CFE_SB_UNSUBSCRIBE_PROC,-42);    
    }
    else
    {
        UTF_CFE_SB_Use_Default_Api_Return_Code(CFE_SB_SUBSCRIBEEX_PROC);
        UTF_CFE_SB_Use_Default_Api_Return_Code(CFE_SB_UNSUBSCRIBE_PROC);
    }

    return;

}/* end UTF_HS_BadSub */



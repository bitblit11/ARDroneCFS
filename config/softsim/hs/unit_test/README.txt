Overall Coverage Statistics
---------------------------

  With HS_MAX_EXEC_CNT_SLOTS = 32
   and HS_POST_PROCESSING_DELAY = 1

bash-2.05b$ gcov hs_app.c
100.00% of 196 source lines executed in file /home/aschoening/pwned/apps/hs/fsw/src/hs_app.c
Creating hs_app.c.gcov.
bash-2.05b$ gcov hs_cmds.c
 98.92% of 279 source lines executed in file /home/aschoening/pwned/apps/hs/fsw/src/hs_cmds.c
Creating hs_cmds.c.gcov.
bash-2.05b$ gcov hs_monitors.c
100.00% of 268 source lines executed in file /home/aschoening/pwned/apps/hs/fsw/src/hs_monitors.c
Creating hs_monitors.c.gcov.
bash-2.05b$ gcov hs_custom.c
100.00% of 146 source lines executed in file /home/aschoening/pwned/apps/hs/fsw/src/hs_custom.c
Creating hs_custom.c.gcov.

  With HS_MAX_EXEC_CNT_SLOTS = 0
   and HS_POST_PROCESSING_DELAY = 0

100.00% of 186 source lines executed in file /home/aschoening/pwned/apps/hs/fsw/src/hs_app.c
Creating hs_app.c.gcov.
bash-2.05b$ gcov hs_cmds.c
100.00% of 253 source lines executed in file /home/aschoening/pwned/apps/hs/fsw/src/hs_cmds.c
Creating hs_cmds.c.gcov.
bash-2.05b$ gcov hs_monitors.c
100.00% of 237 source lines executed in file /home/aschoening/pwned/apps/hs/fsw/src/hs_monitors.c
Creating hs_monitors.c.gcov.
bash-2.05b$ gcov hs_custom.c
100.00% of 146 source lines executed in file /home/aschoening/pwned/apps/hs/fsw/src/hs_custom.c
Creating hs_custom.c.gcov.

Comments on Functions with less than 100% Coverage
--------------------------------------------------

In hs_cmds.c,  HS_HousekeepingReq(CFE_SB_MsgPtr_t MessagePtr):

		#if HS_MAX_EXEC_CNT_SLOTS != 0
		        /*
		        ** Add the execution counters
		        */
         231            for(TableIndex = 0; TableIndex < HS_MAX_EXEC_CNT_SLOTS; TableIndex++)
		        {
		
         224                ExeCount = HS_INVALID_EXECOUNT;
		
         224                if((HS_AppData.ExeCountState == HS_STATE_ENABLED) &&
		               ((HS_AppData.XCTablePtr[TableIndex].ResourceType == HS_XCT_TYPE_APP_MAIN) ||
		                (HS_AppData.XCTablePtr[TableIndex].ResourceType == HS_XCT_TYPE_APP_CHILD)))
		            {
		
          35                    Status = OS_TaskGetIdByName(&TaskId, HS_AppData.XCTablePtr[TableIndex].ResourceName);
		
          35                    if (Status == OS_SUCCESS)
		                {
      ######                        Status = CFE_ES_GetTaskInfo(&TaskInfo, TaskId);
      ######                        if (Status == CFE_SUCCESS)
		                    {
      ######                            ExeCount = TaskInfo.ExecutionCounter;
		                    }
		
		                }
		
		            }
         189                else if((HS_AppData.ExeCountState == HS_STATE_ENABLED) &&
		               ((HS_AppData.XCTablePtr[TableIndex].ResourceType == HS_XCT_TYPE_DEVICE) ||
		                (HS_AppData.XCTablePtr[TableIndex].ResourceType == HS_XCT_TYPE_ISR)))
		            {
		
          14                    Status = CFE_ES_GetGenCounterIDByName(&TaskId, HS_AppData.XCTablePtr[TableIndex].ResourceName);
		
          14                    if (Status == CFE_SUCCESS)
		                {
          14                        CFE_ES_GetGenCount(TaskId, &ExeCount);
		                }
		
		            }
         224                HS_AppData.HkPacket.ExeCounts[TableIndex] = ExeCount;
		
		        }        
		
		#endif
These lines are not executed because OS_TaskGetIdByName is not fully implemented by UTF, nor can a hook be used to replace it. In addition, this function produces the error message "Task not registered before first call to OS_TaskGetIdByName" if OS_TaskRegister is not called first (which is called in utf_test_hs.c to eliminate this message); OS_TaskRegister is currently only called in UTF by CFE_ES_RegisterChildTask even though the real ES also makes this call in CFE_ES_RegisterApp. If HS_MAX_EXEC_CNT_SLOTS is set to 0, this code is conditionally compiled out such that hs_cmds.c will be 100% tested.


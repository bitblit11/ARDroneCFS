/*
**   Copyright © 2007-2014 United States Government as represented by the 
**   Administrator of the National Aeronautics and Space Administration. 
**   All Other Rights Reserved.  
**
**   This software was created at NASA's Goddard Space Flight Center.
**   This software is governed by the NASA Open Source Agreement and may be 
**   used, distributed and modified only pursuant to the terms of that 
**   agreement.
*/


/*
** Required header files.
*/
#include "cfe.h"
#include "cfe_es.h"
#include "cfe_es_apps.h"
#include "cfe_es_global.h"
#include "cfe_es_events.h"
#include "cfe_es_cds.h"
#include "cfe_es_cds_mempool.h"
#include "cfe_psp.h"
#include "cfe_es_log.h"


#include <string.h>
#include <stdio.h>
#include <stdarg.h>

CFE_ES_Global_t CFE_ES_Global;

int32 CFE_ES_RegisterGenCounter(uint32 *CounterIdPtr, const char *CounterName)
{
   int32 ReturnCode = CFE_ES_BAD_ARGUMENT;
   uint32 CheckPtr;
   int32 Status;
   uint32 i;

   Status = CFE_ES_GetGenCounterIDByName(&CheckPtr, CounterName);

   if ((CounterIdPtr != NULL) && (CounterName != NULL) && (Status != CFE_SUCCESS))
   {
      for ( i = 0; i < CFE_ES_MAX_GEN_COUNTERS; i++ )
      {
         if ( CFE_ES_Global.CounterTable[i].RecordUsed == FALSE )
         {
            strncpy((char *)CFE_ES_Global.CounterTable[i].CounterName,CounterName,OS_MAX_API_NAME);

            CFE_ES_Global.CounterTable[i].RecordUsed = TRUE;
            CFE_ES_Global.CounterTable[i].Counter = 0;
            *CounterIdPtr = i;
            break;
         }
      }
      if (i < CFE_ES_MAX_GEN_COUNTERS)
      {
         ReturnCode = CFE_SUCCESS;
      }
   }

   return ReturnCode;

}

/*
** Function: CFE_ES_DeleteGenCounter
**
** Purpose:  Delete a Generic Counter.
**
*/
int32 CFE_ES_DeleteGenCounter(uint32 CounterId)
{

   int32 Status = CFE_ES_BAD_ARGUMENT;

   if(CounterId < CFE_ES_MAX_GEN_COUNTERS) 
   {
      CFE_ES_Global.CounterTable[CounterId].RecordUsed = FALSE;
      CFE_ES_Global.CounterTable[CounterId].Counter = 0;
      Status = CFE_SUCCESS;
   }

   return Status;

} /* End of CFE_ES_DeleteGenCounter() */

/*
** Function: CFE_ES_IncrementGenCounter
**
** Purpose:  Increment a Generic Counter.
**
*/
int32 CFE_ES_IncrementGenCounter(uint32 CounterId)
{
   int32 Status = CFE_ES_BAD_ARGUMENT;

   if((CounterId < CFE_ES_MAX_GEN_COUNTERS) &&
      (CFE_ES_Global.CounterTable[CounterId].RecordUsed == TRUE))
   {
      CFE_ES_Global.CounterTable[CounterId].Counter++;
      Status = CFE_SUCCESS;
   }
   return Status;
   
} /* End of CFE_ES_IncrementGenCounter() */

/*
** Function: CFE_ES_SetGenCount
**
** Purpose:  Sets a Generic Counter's count.
**
*/
int32 CFE_ES_SetGenCount(uint32 CounterId, uint32 Count)
{
   int32 Status = CFE_ES_BAD_ARGUMENT;

   if((CounterId < CFE_ES_MAX_GEN_COUNTERS) &&
      (CFE_ES_Global.CounterTable[CounterId].RecordUsed == TRUE))
   {
      CFE_ES_Global.CounterTable[CounterId].Counter = Count;
      Status = CFE_SUCCESS;
   }
   return Status;
} /* End of CFE_ES_SetGenCount() */

/*
** Function: CFE_ES_GetGenCount
**
** Purpose:  Gets the value of a Generic Counter.
**
*/
int32 CFE_ES_GetGenCount(uint32 CounterId, uint32 *Count)
{
   int32 Status = CFE_ES_BAD_ARGUMENT;

   if((CounterId < CFE_ES_MAX_GEN_COUNTERS) &&
      (CFE_ES_Global.CounterTable[CounterId].RecordUsed == TRUE) &&
      (Count != NULL ))
   {
      *Count = CFE_ES_Global.CounterTable[CounterId].Counter;
      Status = CFE_SUCCESS;
   }
   return Status;
} /* End of CFE_ES_GetGenCount() */

int32 CFE_ES_GetGenCounterIDByName(uint32 *CounterIdPtr, char *CounterName)
{

   int32 Result = CFE_ES_BAD_ARGUMENT;
   int   i;

   /*
   ** Search the ES Generic Counter table for a counter with a matching name.
   */
   for ( i = 0; i < CFE_ES_MAX_GEN_COUNTERS; i++ )
   {
      if ( CFE_ES_Global.CounterTable[i].RecordUsed == TRUE )
      {
         if ( strncmp(CounterName, (char *)CFE_ES_Global.CounterTable[i].CounterName, OS_MAX_API_NAME) == 0 )
         {
            if(CounterIdPtr != NULL)
            {
               *CounterIdPtr = i;
               Result = CFE_SUCCESS;
            }
            break;
         }
      }
   } /* end for */
   
   return(Result);

} /* End of CFE_ES_GetGenCounterIDByName() */

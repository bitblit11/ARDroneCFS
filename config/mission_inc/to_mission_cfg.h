/*=======================================================================================
** File Name:  to_mission_cfg.h
**
** Title:  Mission Configuration Header File for TO Application
**
** $Author:    Mathew Benson
** $Revision:  $
** $Date:      2013-10-30
**
** Purpose:  This header file contains declartions and definitions of all TO's
**           mission-specific configurations.
**
** Modification History:
**   Date | Author | Description
**   ---------------------------
**   2013-10-30 | Mathew Benson | Build #: Code Started
**
**=====================================================================================*/
    
#ifndef _TO_MISSION_CFG_H_
#define _TO_MISSION_CFG_H_

/*
** Pragmas
*/

/*
** Local Defines
*/

/*
** Include Files
*/
#include "cfe.h"

#include "perf_ids.h"
#include "msg_ids.h"
#include "event_ids.h"
#include "cmd_codes.h"


/*
** Local Structure Declarations
*/

/*
 * Defines
 */
#define TO_MAX_TLM_SUBSCRIPTIONS 	280
#define TO_MAX_TLM_CLASS_QUEUES 	32
#define TO_MAX_TLM_CHANNELS			4
#define TO_CHILDTASK_MUTEX_NAME		"TO_TLMTASK_MUT"

/*
** External Global Variables
*/

/*
** Global Variables
*/

/*
** Local Variables
*/

/*
** Local Function Prototypes
*/

#endif /* _TO_MISSION_CFG_H_ */

/*=======================================================================================
** End of file to_mission_cfg.h
**=====================================================================================*/
    

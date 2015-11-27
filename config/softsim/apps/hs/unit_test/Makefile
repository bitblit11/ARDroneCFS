##############################################################################
## File:
##   $Id: Makefile 1.7 2011/10/17 16:44:05EDT aschoeni Exp  $
##
## Purpose:
##   Makefile for building the CFS Health and Safety (HS) UTF unit tests
##
##   $Log: Makefile  $
##   Revision 1.7 2011/10/17 16:44:05EDT aschoeni 
##   Updated Unit Tests
##   Revision 1.6 2010/11/17 17:08:44EST aschoeni 
##   updated to support cpu utilization monitoring
##   Revision 1.5 2010/05/25 18:54:59EDT aschoeni 
##   Updated to work with new UTF
##   Revision 1.4 2009/08/20 16:01:24EDT aschoeni 
##   Added cfe_psp watchdog file to build
##   Revision 1.3 2009/06/24 16:20:38EDT aschoeni 
##   Changed bsp_timer.o to cfe_psp_timer.o
##   Revision 1.2 2009/06/04 18:48:31EDT aschoeni 
##   Updated Makefiles based on new directory structure
##   Revision 1.1 2009/05/22 17:56:18EDT aschoeni 
##   Initial revision
##   Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/hs/fsw/unit_test/project.pj
##
##############################################################################
#
# Compiler/linker definitions
#
COMPILER=gcc
LINKER=gcc
#
# Compiler/linker options
#
DEFAULT_COPT := -Wall -Wstrict-prototypes -ansi -g 
COPT = -D_ix86_ -DSOFTWARE_LITTLE_BIT_ORDER -D_EL -DCLOCKS_PER_SEC=1000000 -DS_IFDIR=16384
LOPT=
#
# Options for gcov
#
GCOV_COPT= -fprofile-arcs -ftest-coverage
GCOV_LOPT= -pg -fprofile-arcs -ftest-coverage
#
###########################################################################
#
# Search path definitions
#
UTF_PATH=$(CFS_MISSION)/cfe/tools/utf
CFE_PATH=$(CFS_MISSION)/cfe/fsw/cfe-core
BUILD_PATH=$(CFS_MISSION)/build
OS_PATH=$(CFS_MISSION)/osal/src/
#
###########################################################################
#
# Source file path definitions
#
VPATH := .
VPATH += ..
VPATH += $(UTF_PATH)/src
VPATH += $(CFE_PATH)/src/sb
VPATH += $(CFE_PATH)/src/time
VPATH += $(CFE_PATH)/src/es
VPATH += $(CFE_PATH)/src/evs
VPATH += $(CFE_PATH)/src/fs
VPATH += $(CFE_PATH)/src/tbl
VPATH += $(OS_PATH)/arch/x86/pc/linux/bsp
VPATH += $(CFE_PSP_SRC)/pc-linux/src
VPATH += $(CFS_APP_SRC)/hs/fsw/src
#
###########################################################################
#
# Header file path definitions
#
INCLUDES := -I.
INCLUDES += -I..
INCLUDES += -I$(UTF_PATH)/inc
INCLUDES += -I$(BUILD_PATH)/inc
INCLUDES += -I$(BUILD_PATH)/mission_inc
INCLUDES += -I$(BUILD_PATH)/cpu1/inc
INCLUDES += -I$(BUILD_PATH)/cpu1/cfe/inc
INCLUDES += -I$(CFE_PATH)/os/inc
INCLUDES += -I$(CFE_PATH)/src/inc
INCLUDES += -I$(CFE_PATH)/src/time
INCLUDES += -I$(CFE_PATH)/src/sb
INCLUDES += -I$(CFE_PATH)/src/es
INCLUDES += -I$(CFE_PATH)/src/evs
INCLUDES += -I$(CFE_PATH)/src/fs
INCLUDES += -I$(CFE_PATH)/src/tbl
INCLUDES += -I$(OS_PATH)/os/inc
INCLUDES += -I$(OS_PATH)/arch/x86/pc/inc
INCLUDES += -I$(CFE_PSP_SRC)/inc
INCLUDES += -I$(CFE_PSP_SRC)/pc-linux/inc
INCLUDES += -I$(CFS_APP_SRC)/hs/fsw/src
INCLUDES += -I$(CFS_APP_SRC)/hs/fsw/mission_inc
INCLUDES += -I$(CFS_APP_SRC)/hs/fsw/platform_inc
#
###########################################################################
#
# UTF object files
#
UTF_OBJS := utf_osapi.o
UTF_OBJS += utf_cfe_psp_memory.o
UTF_OBJS += utf_cfe_psp_memrange.o
UTF_OBJS += utf_cfe_psp_memutils.o
UTF_OBJS += utf_cfe_psp_eeprom.o
UTF_OBJS += utf_cfe_psp_ram.o
UTF_OBJS += utf_cfe_psp_support.o
UTF_OBJS += utf_cfe_psp_port.o
#UTF_OBJS += utf_bsp_support.o
UTF_OBJS += utf_osfilesys.o
UTF_OBJS += utf_osfileapi.o
UTF_OBJS += utf_cfe_sb_api.o
UTF_OBJS += utf_cfe_time_api.o
UTF_OBJS += utf_cfe_time_utils.o
UTF_OBJS += utf_cfe_sb.o
UTF_OBJS += utf_sim.o
UTF_OBJS += utf_cfe_es_api.o
UTF_OBJS += utf_cfe_es_genctr.o
UTF_OBJS += utf_cfe_es_cds.o
UTF_OBJS += utf_cfe_esmempool.o
UTF_OBJS += utf_cfe_evs.o
UTF_OBJS += utf_cfe_tbl_api.o
UTF_OBJS += utf_cfe_tbl_internal.o
#
###########################################################################
#
# cFE object files
#
CFE_OBJS := ccsds.o
CFE_OBJS += cfe_sb_util.o
#CFE_OBJS += cfe_time_api.o
CFE_OBJS += cfe_es_cds_mempool.o
CFE_OBJS += cfe_fs_api.o
CFE_OBJS += cfe_psp_timer.o
CFE_OBJS += cfe_psp_watchdog.o
#
###########################################################################
#
# HS object files
#
HS_OBJS := hs_app.o
HS_OBJS += hs_cmds.o
HS_OBJS += hs_monitors.o
HS_OBJS += hs_custom.o

#
###########################################################################
#
# Rules to make the specified targets
#   
%.o: %.c
	$(COMPILER) -c $(COPT) $(DEFAULT_COPT) $(GCOV_COPT) $(INCLUDES) $<

%.bin: %.o
	$(LINKER) $(LOPT) $(GCOV_LOPT) $^ -o $*.bin

all: utf_test_hs.bin

utf_test_hs.bin: utf_test_hs.o $(UTF_OBJS) $(CFE_OBJS) $(HS_OBJS)

clean ::
	rm -f *.o *.bin *.da *.out *.bbg *.bb *.gcda *.gcno *.gcov
	
gcov ::
	@echo
	@gcov $(HS_OBJS:.o=.gcda) | sed 'N;s/\n/ /' | \
		sed -n '/File/p' | sed '/ads/d'  | \
		sed 's/ Lines executed:/ /; s/File/gcov:/; s/of//'
	@rm -f *.gcda *.gcno
	@echo	
#
###########################################################################
#
# end of file

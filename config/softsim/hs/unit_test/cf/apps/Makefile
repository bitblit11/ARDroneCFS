##############################################################################
## File:
##   $Id: Makefile 1.1 2010/11/17 17:01:29EST aschoeni Exp  $
##
## Purpose:
##   Makefile for building the CFS Health and Safety (HS) unit test tables
##
##   $Log: Makefile  $
##   Revision 1.1 2010/11/17 17:01:29EST aschoeni 
##   Initial revision
##   Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/hs/fsw/unit_test/cf/apps/project.pj
##   Revision 1.2 2009/06/04 18:48:32EDT aschoeni 
##   Updated Makefiles based on new directory structure
##   Revision 1.1 2009/05/22 17:54:09EDT aschoeni 
##   Initial revision
##   Member added to project c:/MKSDATA/MKS-REPOSITORY/CFS-REPOSITORY/hs/fsw/unit_test/cf/project.pj
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
COPT = -D_ix86_ -DSOFTWARE_LITTLE_BIT_ORDER -D_EL -DCLOCKS_PER_SEC=1000000
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
# HS object files
#
HS_OBJS := hs_amt_tbl.o
HS_OBJS += hs_emt_tbl.o
HS_OBJS += hs_xct_tbl.o
HS_OBJS += hs_mat_tbl.o
HS_OBJS += hs_amt_bad.o
HS_OBJS += hs_emt_bad.o
HS_OBJS += hs_xct_bad.o
HS_OBJS += hs_mat_bad.o
#
###########################################################################
#
# HS table files
#
HS_TBLS := hs_amt_tbl.tbl
HS_TBLS += hs_emt_tbl.tbl
HS_TBLS += hs_xct_tbl.tbl
HS_TBLS += hs_mat_tbl.tbl
HS_TBLS += hs_amt_bad.tbl
HS_TBLS += hs_emt_bad.tbl
HS_TBLS += hs_xct_bad.tbl
HS_TBLS += hs_mat_bad.tbl
#
###########################################################################
#
# Rules to make the specified targets
#   
%.o: %.c
	$(COMPILER) -c $(COPT) $(DEFAULT_COPT) $(GCOV_COPT) $(INCLUDES) $<

%.tbl: %.o
	$(CFS_MISSION)/cfe/tools/elf2cfetbl/elf2cfetbl $<

all: $(HS_OBJS) $(HS_TBLS)

clean ::
	rm -f *.o *.bin *.da *.out *.bbg *.bb *.tbl *.gcda *.gcno *.gcov
	
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


# -*- Makefile -*-
# $Id: Makefile,v 1.25 Broadcom SDK $
# $Copyright: Copyright 2012 Broadcom Corporation.
# This program is the proprietary software of Broadcom Corporation
# and/or its licensors, and may only be used, duplicated, modified
# or distributed pursuant to the terms and conditions of a separate,
# written license agreement executed between you and Broadcom
# (an "Authorized License").  Except as set forth in an Authorized
# License, Broadcom grants no license (express or implied), right
# to use, or waiver of any kind with respect to the Software, and
# Broadcom expressly reserves all rights in and to the Software
# and all intellectual property rights therein.  IF YOU HAVE
# NO AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS SOFTWARE
# IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY BROADCOM AND DISCONTINUE
# ALL USE OF THE SOFTWARE.  
#  
# Except as expressly set forth in the Authorized License,
#  
# 1.     This program, including its structure, sequence and organization,
# constitutes the valuable trade secrets of Broadcom, and you shall use
# all reasonable efforts to protect the confidentiality thereof,
# and to use this information only in connection with your use of
# Broadcom integrated circuit products.
#  
# 2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS
# PROVIDED "AS IS" AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES,
# REPRESENTATIONS OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY,
# OR OTHERWISE, WITH RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY
# DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY,
# NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES,
# ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
# CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING
# OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
# 
# 3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL
# BROADCOM OR ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL,
# INCIDENTAL, SPECIAL, INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER
# ARISING OUT OF OR IN ANY WAY RELATING TO YOUR USE OF OR INABILITY
# TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF
# THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR USD 1.00,
# WHICHEVER IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING
# ANY FAILURE OF ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.$
#
LOCALDIR = systems/linux/kernel/modules/bcm-diag

include ${SDK}/make/Make.config

DIAG = ${COND_LIB_BCMX_DIAG} libdiag.a

ifdef ROBO_CHIPS
DIAG += libdiagrobo.a
endif

ifdef ESW_CHIPS
DIAG += libdiag_esw.a
endif

ifdef SBX_CHIPS
DIAG += libdiag_sbx.a
endif

ifdef EA_CHIPS
DIAG += libdiag_ea.a
endif

ifdef DPP_CHIPS
DIAG += libdiag_dpp.a
endif

ifdef DFE_CHIPS
DIAG += libdiag_dfe.a libdiag_dcmn.a
else
ifdef DPP_CHIPS
DIAG += libdiag_dcmn.a
endif
endif

ifdef PORTLIB_SUPPORT
DIAG += libdiag_portlib.a
endif

DIAG_LIBS = \
	${DIAG}\
	${COND_LIB_PHYMOD_DIAG} \
	libkern.a \
	libsal_appl.a \
	${COND_LIB_EDITLINE} \
	${COND_LIB_DIAG_APS} \
	libsal_appl_plat.a 

BCM_LIBS = $(DIAG_LIBS) $(COND_LIB_ETH_DRV)
BCM_LIBS_BLD = $(addprefix $(LIBDIR)/,$(BCM_LIBS))
ifndef BUILD_MACSEC
BCM_LIBS_BLD += ${EXTERNAL_LIBS}
endif

ifeq ($(kernel_version),2_4)
MODULE = $(LIBDIR)/linux-bcm-diag.o
else
KERNEL_MODULE_DIR = kernel_module

THIS_MOD_NAME := linux-bcm-diag
MODULE = $(LIBDIR)/$(THIS_MOD_NAME).o
KMODULE = $(LIBDIR)/$(THIS_MOD_NAME).ko

build: $(MODULE) $(KMODULE)
endif

KBUILD_EXTRA_SYMBOLS := ${BLDDIR}/../bcm-core/kernel_module/Module.symvers
KBUILD_EXTRA_SYMBOLS += ${BLDDIR}/../uk-proxy/kernel_module/Module.symvers

# BCM Diag Shell

$(MODULE): $(BLDDIR)/.tree $(BOBJS) $(BCM_LIBS_BLD)
	$(LD) $(MODULE_LDFLAGS) -r -d $(BOBJS) --start-group $(BCM_LIBS_BLD) --end-group -o $@
ifneq ($(kernel_version),2_4)
$(KMODULE): $(MODULE)
	rm -fr $(BLDDIR)/$(KERNEL_MODULE_DIR)
	mkdir $(BLDDIR)/$(KERNEL_MODULE_DIR)
	cp ${SDK}/make/Makefile.linux-kmodule $(BLDDIR)/$(KERNEL_MODULE_DIR)/Makefile
	cat ${KBUILD_EXTRA_SYMBOLS} > $(BLDDIR)/$(KERNEL_MODULE_DIR)/Module.symvers
	MOD_NAME=$(THIS_MOD_NAME) $(MAKE) -C $(BLDDIR)/$(KERNEL_MODULE_DIR) $(THIS_MOD_NAME).ko
endif

# Make.depend is before clean:: so that Make.depend's clean:: runs first.

include ${SDK}/make/Make.depend

clean::
	$(RM) $(BLDDIR)/version.c $(BLDDIR)/version.o
	$(RM) $(BOBJS) $(MODULE)

ifneq ($(kernel_version),2_4)
.PHONY: build
endif

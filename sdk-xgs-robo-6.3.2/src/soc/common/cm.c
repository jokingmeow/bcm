/*
 * $Id: cm.c 1.296.2.3 Broadcom SDK $
 * $Copyright: Copyright 2012 Broadcom Corporation.
 * This program is the proprietary software of Broadcom Corporation
 * and/or its licensors, and may only be used, duplicated, modified
 * or distributed pursuant to the terms and conditions of a separate,
 * written license agreement executed between you and Broadcom
 * (an "Authorized License").  Except as set forth in an Authorized
 * License, Broadcom grants no license (express or implied), right
 * to use, or waiver of any kind with respect to the Software, and
 * Broadcom expressly reserves all rights in and to the Software
 * and all intellectual property rights therein.  IF YOU HAVE
 * NO AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS SOFTWARE
 * IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY BROADCOM AND DISCONTINUE
 * ALL USE OF THE SOFTWARE.  
 *  
 * Except as expressly set forth in the Authorized License,
 *  
 * 1.     This program, including its structure, sequence and organization,
 * constitutes the valuable trade secrets of Broadcom, and you shall use
 * all reasonable efforts to protect the confidentiality thereof,
 * and to use this information only in connection with your use of
 * Broadcom integrated circuit products.
 *  
 * 2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS
 * PROVIDED "AS IS" AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES,
 * REPRESENTATIONS OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY,
 * OR OTHERWISE, WITH RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY
 * DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY,
 * NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES,
 * ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 * CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING
 * OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
 * 
 * 3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL
 * BROADCOM OR ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL,
 * INCIDENTAL, SPECIAL, INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER
 * ARISING OUT OF OR IN ANY WAY RELATING TO YOUR USE OF OR INABILITY
 * TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF
 * THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR USD 1.00,
 * WHICHEVER IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING
 * ANY FAILURE OF ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.$
 *
 * File:        cm.c
 * Purpose:     Configuration Manager
 *
 * This module provides an OS-independent abstraction for the low-level
 * manipulation of StrataSwitch devices and other system resources
 * needed by the driver.
 *
 * See <soc/cmtypes.h> for a description and requirements of the vectors.
 */
#include <assert.h>
#include <sal/core/libc.h>
#include <sal/core/sync.h>
#include <soc/devids.h>
#include <soc/cmext.h>
#include <soc/cm.h>
#include <soc/drv.h>
#ifdef BCM_SBX_SUPPORT
#include <soc/sbx/sbx_drv.h>
#endif
#ifdef BCM_PETRA_SUPPORT
#include <soc/dpp/drv.h>
#endif
#ifdef BCM_DFE_SUPPORT
#include <soc/dfe/cmn/dfe_drv.h>
#endif
#include <soc/debug.h>

#include <sal/core/memlog.h>

cm_device_t                     soc_cm_device[SOC_MAX_NUM_DEVICES];
int                             soc_cm_device_count;

/*
 * Global array for debug flag names.
 *
 * For parsing, the uppercase letters should be mandatory while
 * the lowercase letters should be optional.
 *
 * NOTE: Keep this list in sync with socdebug.h
 */

char *soc_cm_debug_names[] = {
    "PCi",      /*  0: PCI reads/writes */
    "SChan",    /*  1: S-Channel operations */
    "SOCMEM",   /*  2: Memory table operations */
    "SYMTAB",   /*  3: Symbol parsing routines */
    "VERInet",  /*  4: Verilog PLI transactions */
    "L3",       /*  5: L3, DEFIP, IPMC */
    "INTr",     /*  6: Interrupt processing */
    "ARL",      /*  7: ARL DMA and poll routines */
    "ARLMon",   /*  8: Monitor ARL ins/del */
    "L2table",  /*  9: Debug software L2 table */
    "DMA",      /* 10: DMA operations */
    "POrt",     /* 11: Port operations */
    "PAcket",   /* 12: Loopback packet data */
    "TX",       /* 13: TX command */
    "RCLOAD",   /* 14: Echo cmds before exec */
    "TEsts",    /* 15: Verbose during tests */
    "VERbose",  /* 16: General verbose output */
    "MIIm",     /* 17: MIIM register operations */
    "PHY",      /* 18: PHY operations */
    "END",      /* 19: Show END driver output */
    "LInk",     /* 20: Show Link status changes */
    "ERRor",    /* 21: Print errors */
    "CounTeR",  /* 22: Counter DMA, etc */
    "IP",       /* 23: IP/Ethernet Stack */
    "STP",      /* 24: 802.1D Spanning Tree */
    "VLAN",     /* 25: VLAN gateway */
    "RX",       /* 26: Packet multiplexor */
    "WARN",     /* 27: Print warnings */
    "I2C",      /* 28: I2C driver */
    "REG",      /* 29: Chip register i/o */
    "MEM",      /* 30: Chip memory i/o */
    "STK"       /* 31: Stacking */
    /* No more possible */
};

/*
 * Table of all recognized chip IDs.
 *
 * There are fewer drivers than real chip IDs because some drivers
 * support more than one chip.  This table maps each real chip ID onto a
 * driver chip ID.  The driver IDs can be zero if equal to real IDs.
 *
 * Entries may be added to the table via soc_cm_id_to_driver_id_add().
 */

static soc_cm_device_info_t soc_device_info[] = {

#if defined(BCM_HERCULES15_SUPPORT)
    {   /* Hercules 1.5 with 8 ports */
        BCM5675_DEVICE_ID, BCM5675_A0_REV_ID,
        "BCM5675_A0",
        BCM5675_DEVICE_ID, BCM5675_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hercules 1.5 with 4 ports */
        BCM5676_DEVICE_ID, BCM5676_A0_REV_ID,
        "BCM5676_A0",
        BCM5675_DEVICE_ID, BCM5675_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hercules 1.5 with 8 ports */
        BCM5675_DEVICE_ID, BCM5675_A1_REV_ID,
        "BCM5675_A1",
        BCM5675_DEVICE_ID, BCM5675_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hercules 1.5 with 4 ports */
        BCM5676_DEVICE_ID, BCM5676_A1_REV_ID,
        "BCM5676_A1",
        BCM5675_DEVICE_ID, BCM5675_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_HERCULES15_SUPPORT */
#if defined(BCM_FIREBOLT_SUPPORT)
    {   /* Helix */
        BCM56300_DEVICE_ID, BCM56300_A0_REV_ID,
        "BCM56300_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56301_DEVICE_ID, BCM56301_A0_REV_ID,
        "BCM56301_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56302_DEVICE_ID, BCM56302_A0_REV_ID,
        "BCM56302_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56303_DEVICE_ID, BCM56303_A0_REV_ID,
        "BCM56303_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56304_DEVICE_ID, BCM56304_A0_REV_ID,
        "BCM56304_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56305_DEVICE_ID, BCM56305_A0_REV_ID,
        "BCM56305_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56306_DEVICE_ID, BCM56306_A0_REV_ID,
        "BCM56306_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56307_DEVICE_ID, BCM56307_A0_REV_ID,
        "BCM56307_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56308_DEVICE_ID, BCM56308_A0_REV_ID,
        "BCM56308_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56309_DEVICE_ID, BCM56309_A0_REV_ID,
        "BCM56309_A0",
        BCM56504_DEVICE_ID, BCM56503_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56300_DEVICE_ID, BCM56300_A1_REV_ID,
        "BCM56300_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56301_DEVICE_ID, BCM56301_A1_REV_ID,
        "BCM56301_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56302_DEVICE_ID, BCM56302_A1_REV_ID,
        "BCM56302_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56303_DEVICE_ID, BCM56303_A1_REV_ID,
        "BCM56303_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56304_DEVICE_ID, BCM56304_A1_REV_ID,
        "BCM56304_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56305_DEVICE_ID, BCM56305_A1_REV_ID,
        "BCM56305_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56306_DEVICE_ID, BCM56306_A1_REV_ID,
        "BCM56306_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56307_DEVICE_ID, BCM56307_A1_REV_ID,
        "BCM56307_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56308_DEVICE_ID, BCM56308_A1_REV_ID,
        "BCM56308_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56309_DEVICE_ID, BCM56309_A1_REV_ID,
        "BCM56309_A1",
        BCM56504_DEVICE_ID, BCM56503_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#if defined(BCM_FELIX_SUPPORT)
    {   /* Felix */
        BCM56100_DEVICE_ID, BCM56100_A0_REV_ID,
        "BCM56100_A0",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56101_DEVICE_ID, BCM56101_A0_REV_ID,
        "BCM56101_A0",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        "BCM56102_A0",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56105_DEVICE_ID, BCM56105_A0_REV_ID,
        "BCM56105_A0",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56106_DEVICE_ID, BCM56106_A0_REV_ID,
        "BCM56106_A0",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56107_DEVICE_ID, BCM56107_A0_REV_ID,
        "BCM56107_A0",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56100_DEVICE_ID, BCM56100_A1_REV_ID,
        "BCM56100_A1",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56101_DEVICE_ID, BCM56101_A1_REV_ID,
        "BCM56101_A1",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56102_DEVICE_ID, BCM56102_A1_REV_ID,
        "BCM56102_A1",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56105_DEVICE_ID, BCM56105_A1_REV_ID,
        "BCM56105_A1",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56106_DEVICE_ID, BCM56106_A1_REV_ID,
        "BCM56106_A1",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix */
        BCM56107_DEVICE_ID, BCM56107_A1_REV_ID,
        "BCM56107_A1",
        BCM56102_DEVICE_ID, BCM56102_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix15 */
        BCM56110_DEVICE_ID, BCM56110_A0_REV_ID,
        "BCM56110_A0",
        BCM56112_DEVICE_ID, BCM56112_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix15 */
        BCM56111_DEVICE_ID, BCM56111_A0_REV_ID,
        "BCM56111_A0",
        BCM56112_DEVICE_ID, BCM56112_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix15 */
        BCM56112_DEVICE_ID, BCM56112_A0_REV_ID,
        "BCM56112_A0",
        BCM56112_DEVICE_ID, BCM56112_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix15 */
        BCM56115_DEVICE_ID, BCM56115_A0_REV_ID,
        "BCM56115_A0",
        BCM56112_DEVICE_ID, BCM56112_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix15 */
        BCM56116_DEVICE_ID, BCM56116_A0_REV_ID,
        "BCM56116_A0",
        BCM56112_DEVICE_ID, BCM56112_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Felix15 */
        BCM56117_DEVICE_ID, BCM56117_A0_REV_ID,
        "BCM56117_A0",
        BCM56112_DEVICE_ID, BCM56112_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_FELIX_SUPPORT */
    {   
        BCM53300_DEVICE_ID, BCM53300_A0_REV_ID,
        "BCM53300_A0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM53301_DEVICE_ID, BCM53301_A0_REV_ID,
        "BCM53301_A0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM53302_DEVICE_ID, BCM53302_A0_REV_ID,
        "BCM53302_A0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   
        BCM53300_DEVICE_ID, BCM53300_A1_REV_ID,
        "BCM53300_A0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM53301_DEVICE_ID, BCM53301_A1_REV_ID,
        "BCM53301_A0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM53302_DEVICE_ID, BCM53302_A1_REV_ID,
        "BCM53302_A0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56300_DEVICE_ID, BCM56300_B0_REV_ID,
        "BCM56300_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56301_DEVICE_ID, BCM56301_B0_REV_ID,
        "BCM56301_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56302_DEVICE_ID, BCM56302_B0_REV_ID,
        "BCM56302_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56303_DEVICE_ID, BCM56303_B0_REV_ID,
        "BCM56303_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        "BCM56304_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56305_DEVICE_ID, BCM56305_B0_REV_ID,
        "BCM56305_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56306_DEVICE_ID, BCM56306_B0_REV_ID,
        "BCM56306_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56307_DEVICE_ID, BCM56307_B0_REV_ID,
        "BCM56307_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56308_DEVICE_ID, BCM56308_B0_REV_ID,
        "BCM56308_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56309_DEVICE_ID, BCM56309_B0_REV_ID,
        "BCM56309_B0",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56300_DEVICE_ID, BCM56300_B1_REV_ID,
        "BCM56300_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56301_DEVICE_ID, BCM56301_B1_REV_ID,
        "BCM56301_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56302_DEVICE_ID, BCM56302_B1_REV_ID,
        "BCM56302_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56303_DEVICE_ID, BCM56303_B1_REV_ID,
        "BCM56303_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56304_DEVICE_ID, BCM56304_B1_REV_ID,
        "BCM56304_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56305_DEVICE_ID, BCM56305_B1_REV_ID,
        "BCM56305_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56306_DEVICE_ID, BCM56306_B1_REV_ID,
        "BCM56306_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56307_DEVICE_ID, BCM56307_B1_REV_ID,
        "BCM56307_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56308_DEVICE_ID, BCM56308_B1_REV_ID,
        "BCM56308_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix */
        BCM56309_DEVICE_ID, BCM56309_B1_REV_ID,
        "BCM56309_B1",
        BCM56304_DEVICE_ID, BCM56304_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56310_DEVICE_ID, BCM56310_A0_REV_ID,
        "BCM56310_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56311_DEVICE_ID, BCM56311_A0_REV_ID,
        "BCM56311_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56312_DEVICE_ID, BCM56312_A0_REV_ID,
        "BCM56312_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56313_DEVICE_ID, BCM56313_A0_REV_ID,
        "BCM56313_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        "BCM56314_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56315_DEVICE_ID, BCM56315_A0_REV_ID,
        "BCM56315_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56316_DEVICE_ID, BCM56316_A0_REV_ID,
        "BCM56316_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56317_DEVICE_ID, BCM56317_A0_REV_ID,
        "BCM56317_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56318_DEVICE_ID, BCM56318_A0_REV_ID,
        "BCM56318_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix15 */
        BCM56319_DEVICE_ID, BCM56319_A0_REV_ID,
        "BCM56319_A0",
        BCM56314_DEVICE_ID, BCM56314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#ifndef EXCLUDE_BCM56324
    {   /* Helix2 */
        BCM56322_DEVICE_ID, BCM56322_A0_REV_ID,
        "BCM56322_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix2 */
        BCM56324_DEVICE_ID, BCM56324_A0_REV_ID,
        "BCM56324_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* EXCLUDE_BCM56324 */
    {   /* FB-Helix */
        BCM56404_DEVICE_ID, BCM56404_A0_REV_ID,
        "BCM56304_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56500_DEVICE_ID, BCM56500_A0_REV_ID,
        "BCM56500_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56501_DEVICE_ID, BCM56501_A0_REV_ID,
        "BCM56501_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56502_DEVICE_ID, BCM56502_A0_REV_ID,
        "BCM56502_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56503_DEVICE_ID, BCM56503_A0_REV_ID,
        "BCM56503_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        "BCM56504_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56505_DEVICE_ID, BCM56505_A0_REV_ID,
        "BCM56505_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56506_DEVICE_ID, BCM56506_A0_REV_ID,
        "BCM56506_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56507_DEVICE_ID, BCM56507_A0_REV_ID,
        "BCM56507_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56508_DEVICE_ID, BCM56508_A0_REV_ID,
        "BCM56508_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56509_DEVICE_ID, BCM56509_A0_REV_ID,
        "BCM56509_A0",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* FB-Helix */
        BCM56404_DEVICE_ID, BCM56404_A1_REV_ID,
        "BCM56304_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56500_DEVICE_ID, BCM56500_A1_REV_ID,
        "BCM56500_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56501_DEVICE_ID, BCM56501_A1_REV_ID,
        "BCM56501_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56502_DEVICE_ID, BCM56502_A1_REV_ID,
        "BCM56502_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56503_DEVICE_ID, BCM56503_A1_REV_ID,
        "BCM56503_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56504_DEVICE_ID, BCM56504_A1_REV_ID,
        "BCM56504_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56505_DEVICE_ID, BCM56505_A1_REV_ID,
        "BCM56505_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56506_DEVICE_ID, BCM56506_A1_REV_ID,
        "BCM56506_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56507_DEVICE_ID, BCM56507_A1_REV_ID,
        "BCM56507_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56508_DEVICE_ID, BCM56508_A1_REV_ID,
        "BCM56508_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt */
        BCM56509_DEVICE_ID, BCM56509_A1_REV_ID,
        "BCM56509_A1",
        BCM56504_DEVICE_ID, BCM56504_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56500_DEVICE_ID, BCM56500_B0_REV_ID,
        "BCM56500_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56501_DEVICE_ID, BCM56501_B0_REV_ID,
        "BCM56501_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56502_DEVICE_ID, BCM56502_B0_REV_ID,
        "BCM56502_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56503_DEVICE_ID, BCM56503_B0_REV_ID,
        "BCM56503_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        "BCM56504_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56505_DEVICE_ID, BCM56505_B0_REV_ID,
        "BCM56505_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56506_DEVICE_ID, BCM56506_B0_REV_ID,
        "BCM56506_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56507_DEVICE_ID, BCM56507_B0_REV_ID,
        "BCM56507_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56508_DEVICE_ID, BCM56508_B0_REV_ID,
        "BCM56508_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B0 */
        BCM56509_DEVICE_ID, BCM56509_B0_REV_ID,
        "BCM56509_B0",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56500_DEVICE_ID, BCM56500_B1_REV_ID,
        "BCM56500_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56501_DEVICE_ID, BCM56501_B1_REV_ID,
        "BCM56501_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56502_DEVICE_ID, BCM56502_B1_REV_ID,
        "BCM56502_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56503_DEVICE_ID, BCM56503_B1_REV_ID,
        "BCM56503_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56504_DEVICE_ID, BCM56504_B1_REV_ID,
        "BCM56504_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56505_DEVICE_ID, BCM56505_B1_REV_ID,
        "BCM56505_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56506_DEVICE_ID, BCM56506_B1_REV_ID,
        "BCM56506_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56507_DEVICE_ID, BCM56507_B1_REV_ID,
        "BCM56507_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56508_DEVICE_ID, BCM56508_B1_REV_ID,
        "BCM56508_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B1 */
        BCM56509_DEVICE_ID, BCM56509_B1_REV_ID,
        "BCM56509_B1",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56500_DEVICE_ID, BCM56500_B2_REV_ID,
        "BCM56500_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56501_DEVICE_ID, BCM56501_B2_REV_ID,
        "BCM56501_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56502_DEVICE_ID, BCM56502_B2_REV_ID,
        "BCM56502_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56503_DEVICE_ID, BCM56503_B2_REV_ID,
        "BCM56503_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56504_DEVICE_ID, BCM56504_B2_REV_ID,
        "BCM56504_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56505_DEVICE_ID, BCM56505_B2_REV_ID,
        "BCM56505_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56506_DEVICE_ID, BCM56506_B2_REV_ID,
        "BCM56506_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56507_DEVICE_ID, BCM56507_B2_REV_ID,
        "BCM56507_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56508_DEVICE_ID, BCM56508_B2_REV_ID,
        "BCM56508_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt B2 */
        BCM56509_DEVICE_ID, BCM56509_B2_REV_ID,
        "BCM56509_B2",
        BCM56504_DEVICE_ID, BCM56504_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_FIREBOLT_SUPPORT */

#if defined(BCM_RAPTOR_SUPPORT)
    {   /* Raptor */
        BCM56218X_DEVICE_ID, BCM56218X_A0_REV_ID,
        "BCM56218_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
/* VENDOR BROADCOM [ */
    {   /* Stag's Leap */
        BCM53610_DEVICE_ID, BCM53610_A0_REV_ID,
        "BCM53610_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
/* VENDOR BROADCOM ] */
    {   /* Raptor */
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        "BCM56218_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56219_DEVICE_ID, BCM56219_A0_REV_ID,
        "BCM56219_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56218R_DEVICE_ID, BCM56218R_A0_REV_ID,
        "BCM56218R_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56219R_DEVICE_ID, BCM56219R_A0_REV_ID,
        "BCM56219R_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56214_DEVICE_ID, BCM56214_A0_REV_ID,
        "BCM56214_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56215_DEVICE_ID, BCM56215_A0_REV_ID,
        "BCM56215_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56214R_DEVICE_ID, BCM56214R_A0_REV_ID,
        "BCM56214R_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56215R_DEVICE_ID, BCM56215R_A0_REV_ID,
        "BCM56215R_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56216_DEVICE_ID, BCM56216_A0_REV_ID,
        "BCM56216_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56217_DEVICE_ID, BCM56217_A0_REV_ID,
        "BCM56217_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56212_DEVICE_ID, BCM56212_A0_REV_ID,
        "BCM56212_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56213_DEVICE_ID, BCM56213_A0_REV_ID,
        "BCM56213_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM53718_DEVICE_ID, BCM53718_A0_REV_ID,
        "BCM53718_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM53714_DEVICE_ID, BCM53714_A0_REV_ID,
        "BCM53714_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM53716_DEVICE_ID, BCM53716_A0_REV_ID,
        "BCM53716_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56018_DEVICE_ID, BCM56018_A0_REV_ID,
        "BCM56018_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56014_DEVICE_ID, BCM56014_A0_REV_ID,
        "BCM56014_A0",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56218X_DEVICE_ID, BCM56218X_A1_REV_ID,
        "BCM56218_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
/* VENDOR BROADCOM [ */
    {   /* Stag's Leap */
        BCM53610_DEVICE_ID, BCM53610_A1_REV_ID,
        "BCM53610_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
/* VENDOR BROADCOM ] */
    {   /* Raptor */
        BCM56218_DEVICE_ID, BCM56218_A1_REV_ID,
        "BCM56218_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56219_DEVICE_ID, BCM56219_A1_REV_ID,
        "BCM56219_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56218R_DEVICE_ID, BCM56218R_A1_REV_ID,
        "BCM56218R_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56219R_DEVICE_ID, BCM56219R_A1_REV_ID,
        "BCM56219R_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56214_DEVICE_ID, BCM56214_A1_REV_ID,
        "BCM56214_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56215_DEVICE_ID, BCM56215_A1_REV_ID,
        "BCM56215_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56214R_DEVICE_ID, BCM56214R_A1_REV_ID,
        "BCM56214R_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56215R_DEVICE_ID, BCM56215R_A1_REV_ID,
        "BCM56215R_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56216_DEVICE_ID, BCM56216_A1_REV_ID,
        "BCM56216_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56217_DEVICE_ID, BCM56217_A1_REV_ID,
        "BCM56217_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56212_DEVICE_ID, BCM56212_A1_REV_ID,
        "BCM56212_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56213_DEVICE_ID, BCM56213_A1_REV_ID,
        "BCM56213_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM53718_DEVICE_ID, BCM53718_A1_REV_ID,
        "BCM53718_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM53714_DEVICE_ID, BCM53714_A1_REV_ID,
        "BCM53714_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM53716_DEVICE_ID, BCM53716_A1_REV_ID,
        "BCM53716_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56018_DEVICE_ID, BCM56018_A1_REV_ID,
        "BCM56018_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56014_DEVICE_ID, BCM56014_A1_REV_ID,
        "BCM56014_A1",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56218_DEVICE_ID, BCM56218_A2_REV_ID,
        "BCM56218_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56218X_DEVICE_ID, BCM56218X_A2_REV_ID,
        "BCM56218_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56219_DEVICE_ID, BCM56219_A2_REV_ID,
        "BCM56219_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56218R_DEVICE_ID, BCM56218R_A2_REV_ID,
        "BCM56218R_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56219R_DEVICE_ID, BCM56219R_A2_REV_ID,
        "BCM56219R_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56214_DEVICE_ID, BCM56214_A2_REV_ID,
        "BCM56214_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56215_DEVICE_ID, BCM56215_A2_REV_ID,
        "BCM56215_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56214R_DEVICE_ID, BCM56214R_A2_REV_ID,
        "BCM56214R_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56215R_DEVICE_ID, BCM56215R_A2_REV_ID,
        "BCM56215R_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56216_DEVICE_ID, BCM56216_A2_REV_ID,
        "BCM56216_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56217_DEVICE_ID, BCM56217_A2_REV_ID,
        "BCM56217_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56212_DEVICE_ID, BCM56212_A2_REV_ID,
        "BCM56212_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56213_DEVICE_ID, BCM56213_A2_REV_ID,
        "BCM56213_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM53718_DEVICE_ID, BCM53718_A2_REV_ID,
        "BCM53718_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM53714_DEVICE_ID, BCM53714_A2_REV_ID,
        "BCM53714_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM53716_DEVICE_ID, BCM53716_A2_REV_ID,
        "BCM53716_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56018_DEVICE_ID, BCM56018_A2_REV_ID,
        "BCM56018_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raptor */
        BCM56014_DEVICE_ID, BCM56014_A2_REV_ID,
        "BCM56014_A2",
        BCM56218_DEVICE_ID, BCM56218_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_RAPTOR_SUPPORT */

#if defined(BCM_GOLDWING_SUPPORT)
    {   /* Goldwing */
        BCM56580_DEVICE_ID, BCM56580_A0_REV_ID,
        "BCM56580_A0",
        BCM56800_DEVICE_ID, BCM56800_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_GOLDWING_SUPPORT */
#if defined(BCM_HUMV_SUPPORT)
    {   /* HUMV */
        BCM56700_DEVICE_ID, BCM56700_A0_REV_ID,
        "BCM56700_A0",
        BCM56800_DEVICE_ID, BCM56800_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* HUMV */
        BCM56701_DEVICE_ID, BCM56701_A0_REV_ID,
        "BCM56701_A0",
        BCM56800_DEVICE_ID, BCM56800_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_HUMV_SUPPORT */
#if defined(BCM_BRADLEY_SUPPORT)
    {   /* Bradley */
        BCM56800_DEVICE_ID, BCM56800_A0_REV_ID,
        "BCM56800_A0",
        BCM56800_DEVICE_ID, BCM56800_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Bradley */
        BCM56801_DEVICE_ID, BCM56801_A0_REV_ID,
        "BCM56801_A0",
        BCM56800_DEVICE_ID, BCM56800_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Bradley */
        BCM56802_DEVICE_ID, BCM56802_A0_REV_ID,
        "BCM56802_A0",
        BCM56800_DEVICE_ID, BCM56800_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Bradley */
        BCM56803_DEVICE_ID, BCM56803_A0_REV_ID,
        "BCM56803_A0",
        BCM56800_DEVICE_ID, BCM56800_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_BRADLEY_SUPPORT */
    {   /* Firebolt2 */
        BCM56510_DEVICE_ID, BCM56510_A0_REV_ID,
        "BCM56510_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt2 */
        BCM56511_DEVICE_ID, BCM56511_A0_REV_ID,
        "BCM56511_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt2 */
        BCM56512_DEVICE_ID, BCM56512_A0_REV_ID,
        "BCM56512_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt2 */
        BCM56513_DEVICE_ID, BCM56513_A0_REV_ID,
        "BCM56513_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt2 */
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        "BCM56514_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt2 */
        BCM56516_DEVICE_ID, BCM56516_A0_REV_ID,
        "BCM56516_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt2 */
        BCM56517_DEVICE_ID, BCM56517_A0_REV_ID,
        "BCM56517_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt2 */
        BCM56518_DEVICE_ID, BCM56518_A0_REV_ID,
        "BCM56518_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt2 */
        BCM56519_DEVICE_ID, BCM56519_A0_REV_ID,
        "BCM56519_A0",
        BCM56514_DEVICE_ID, BCM56514_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56620_DEVICE_ID, BCM56620_A0_REV_ID,
        "BCM56620_A0",
        BCM56680_DEVICE_ID, BCM56680_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56620_DEVICE_ID, BCM56620_A1_REV_ID,
        "BCM56620_A1",
        BCM56680_DEVICE_ID, BCM56680_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56620_DEVICE_ID, BCM56620_B0_REV_ID,
        "BCM56620_B0",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56620_DEVICE_ID, BCM56620_B1_REV_ID,
        "BCM56620_B1",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56620_DEVICE_ID, BCM56620_B2_REV_ID,
        "BCM56620_B2",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56624_DEVICE_ID, BCM56624_A0_REV_ID,
        "BCM56624_A0",
        BCM56624_DEVICE_ID, BCM56624_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56624_DEVICE_ID, BCM56624_A1_REV_ID,
        "BCM56624_A1",
        BCM56624_DEVICE_ID, BCM56624_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        "BCM56624_B0",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56624_DEVICE_ID, BCM56624_B1_REV_ID,
        "BCM56624_B1",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56624_DEVICE_ID, BCM56624_B2_REV_ID,
        "BCM56624_B2",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56626_DEVICE_ID, BCM56626_A0_REV_ID,
        "BCM56626_A0",
        BCM56624_DEVICE_ID, BCM56624_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56626_DEVICE_ID, BCM56626_A1_REV_ID,
        "BCM56626_A1",
        BCM56624_DEVICE_ID, BCM56624_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56626_DEVICE_ID, BCM56626_B0_REV_ID,
        "BCM56626_B0",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56626_DEVICE_ID, BCM56626_B1_REV_ID,
        "BCM56626_B1",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56626_DEVICE_ID, BCM56626_B2_REV_ID,
        "BCM56626_B2",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56628_DEVICE_ID, BCM56628_A0_REV_ID,
        "BCM56628_A0",
        BCM56624_DEVICE_ID, BCM56624_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56628_DEVICE_ID, BCM56628_A1_REV_ID,
        "BCM56628_A1",
        BCM56624_DEVICE_ID, BCM56624_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56628_DEVICE_ID, BCM56628_B0_REV_ID,
        "BCM56628_B0",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56628_DEVICE_ID, BCM56628_B1_REV_ID,
        "BCM56628_B1",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56628_DEVICE_ID, BCM56628_B2_REV_ID,
        "BCM56628_B2",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56629_DEVICE_ID, BCM56629_A0_REV_ID,
        "BCM56629_A0",
        BCM56624_DEVICE_ID, BCM56624_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56629_DEVICE_ID, BCM56629_A1_REV_ID,
        "BCM56629_A1",
        BCM56624_DEVICE_ID, BCM56624_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56629_DEVICE_ID, BCM56629_B0_REV_ID,
        "BCM56629_B0",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56629_DEVICE_ID, BCM56629_B1_REV_ID,
        "BCM56629_B1",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph */
        BCM56629_DEVICE_ID, BCM56629_B2_REV_ID,
        "BCM56629_B2",
        BCM56624_DEVICE_ID, BCM56624_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56680_DEVICE_ID, BCM56680_A0_REV_ID,
        "BCM56680_A0",
        BCM56680_DEVICE_ID, BCM56680_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56680_DEVICE_ID, BCM56680_A1_REV_ID,
        "BCM56680_A1",
        BCM56680_DEVICE_ID, BCM56680_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        "BCM56680_B0",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56680_DEVICE_ID, BCM56680_B1_REV_ID,
        "BCM56680_B1",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56680_DEVICE_ID, BCM56680_B2_REV_ID,
        "BCM56680_B2",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56684_DEVICE_ID, BCM56684_A0_REV_ID,
        "BCM56684_A0",
        BCM56680_DEVICE_ID, BCM56680_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56684_DEVICE_ID, BCM56684_A1_REV_ID,
        "BCM56684_A1",
        BCM56680_DEVICE_ID, BCM56680_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56684_DEVICE_ID, BCM56684_B0_REV_ID,
        "BCM56684_B0",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56684_DEVICE_ID, BCM56684_B1_REV_ID,
        "BCM56684_B1",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56684_DEVICE_ID, BCM56684_B2_REV_ID,
        "BCM56684_B2",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56686_DEVICE_ID, BCM56686_B0_REV_ID,
        "BCM56686_B0",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56686_DEVICE_ID, BCM56686_B1_REV_ID,
        "BCM56686_B1",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie */
        BCM56686_DEVICE_ID, BCM56686_B2_REV_ID,
        "BCM56686_B2",
        BCM56680_DEVICE_ID, BCM56680_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
# if defined(BCM_RAVEN_SUPPORT)
    {   /* Raven */

        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        "BCM56224_A0",
        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56225_DEVICE_ID, BCM56225_A0_REV_ID,
        "BCM56225_A0",
        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56226_DEVICE_ID, BCM56226_A0_REV_ID,
        "BCM56226_A0",
        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56227_DEVICE_ID, BCM56227_A0_REV_ID,
        "BCM56227_A0",
        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56228_DEVICE_ID, BCM56228_A0_REV_ID,
        "BCM56228_A0",
        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56229_DEVICE_ID, BCM56229_A0_REV_ID,
        "BCM56229_A0",
        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56024_DEVICE_ID, BCM56024_A0_REV_ID,
        "BCM56024_A0",
        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56025_DEVICE_ID, BCM56025_A0_REV_ID,
        "BCM56025_A0",
        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM53724_DEVICE_ID, BCM53724_A0_REV_ID,
        "BCM53724_A0",
        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM53726_DEVICE_ID, BCM53726_A0_REV_ID,
        "BCM53726_A0",
        BCM56224_DEVICE_ID, BCM56224_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        "BCM56224_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */
     
        BCM56225_DEVICE_ID, BCM56225_B0_REV_ID,
        "BCM56225_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56226_DEVICE_ID, BCM56226_B0_REV_ID,
        "BCM56226_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56227_DEVICE_ID, BCM56227_B0_REV_ID,
        "BCM56227_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56228_DEVICE_ID, BCM56228_B0_REV_ID,
        "BCM56228_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56229_DEVICE_ID, BCM56229_B0_REV_ID,
        "BCM56229_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56024_DEVICE_ID, BCM56024_B0_REV_ID,
        "BCM56024_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM56025_DEVICE_ID, BCM56025_B0_REV_ID,
        "BCM56025_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM53724_DEVICE_ID, BCM53724_B0_REV_ID,
        "BCM53724_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Raven */

        BCM53726_DEVICE_ID, BCM53726_B0_REV_ID,
        "BCM53726_B0",
        BCM56224_DEVICE_ID, BCM56224_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
#if defined(BCM_SCORPION_SUPPORT)
    {   /* Scorpion */
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        "BCM56820_A0",
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion */
        BCM56820_DEVICE_ID, BCM56820_B0_REV_ID,
        "BCM56820_B0",
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion */
        BCM56821_DEVICE_ID, BCM56821_A0_REV_ID,
        "BCM56821_A0",
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion */
        BCM56821_DEVICE_ID, BCM56821_B0_REV_ID,
        "BCM56821_B0",
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion */
        BCM56822_DEVICE_ID, BCM56822_A0_REV_ID,
        "BCM56822_A0",
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion */
        BCM56822_DEVICE_ID, BCM56822_B0_REV_ID,
        "BCM56822_B0",
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion */
        BCM56823_DEVICE_ID, BCM56823_A0_REV_ID,
        "BCM56823_A0",
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion */
        BCM56823_DEVICE_ID, BCM56823_B0_REV_ID,
        "BCM56823_B0",
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion */
        BCM56825_DEVICE_ID, BCM56825_B0_REV_ID,
        "BCM56825_B0",
        BCM56820_DEVICE_ID, BCM56820_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#if defined(BCM_CONQUEROR_SUPPORT)
    {   /* HUMV plus */
        BCM56720_DEVICE_ID, BCM56720_A0_REV_ID,
        "BCM56720_A0",
        BCM56725_DEVICE_ID, BCM56725_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* HUMV plus */
        BCM56720_DEVICE_ID, BCM56720_B0_REV_ID,
        "BCM56720_B0",
        BCM56725_DEVICE_ID, BCM56725_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* HUMV plus */
        BCM56721_DEVICE_ID, BCM56721_A0_REV_ID,
        "BCM56721_A0",
        BCM56725_DEVICE_ID, BCM56725_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* HUMV plus */
        BCM56721_DEVICE_ID, BCM56721_B0_REV_ID,
        "BCM56721_B0",
        BCM56725_DEVICE_ID, BCM56725_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Conqueror */
        BCM56725_DEVICE_ID, BCM56725_A0_REV_ID,
        "BCM56725_A0",
        BCM56725_DEVICE_ID, BCM56725_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Conqueror */
        BCM56725_DEVICE_ID, BCM56725_B0_REV_ID,
        "BCM56725_B0",
        BCM56725_DEVICE_ID, BCM56725_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_CONQUEROR_SUPPORT */
#endif

#if defined(BCM_HAWKEYE_SUPPORT)
    {   /* Hawkeye */
        BCM53312_DEVICE_ID, BCM53312_A0_REV_ID,
        "BCM53312_A0",
        BCM53314_DEVICE_ID, BCM53314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hawkeye */
        BCM53312_DEVICE_ID, BCM53312_B0_REV_ID,
        "BCM53312_B0",
        BCM53314_DEVICE_ID, BCM53314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hawkeye */
        BCM53313_DEVICE_ID, BCM53313_A0_REV_ID,
        "BCM53313_A0",
        BCM53314_DEVICE_ID, BCM53314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hawkeye */
        BCM53313_DEVICE_ID, BCM53313_B0_REV_ID,
        "BCM53313_B0",
        BCM53314_DEVICE_ID, BCM53314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hawkeye */
        BCM53314_DEVICE_ID, BCM53314_A0_REV_ID,
        "BCM53314_A0",
        BCM53314_DEVICE_ID, BCM53314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hawkeye */
        BCM53314_DEVICE_ID, BCM53314_B0_REV_ID,
        "BCM53314_B0",
        BCM53314_DEVICE_ID, BCM53314_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hawkeye EEE */
        BCM53322_DEVICE_ID, BCM53322_A0_REV_ID,
        "BCM53322_A0",
        BCM53324_DEVICE_ID, BCM53324_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hawkeye EEE */
        BCM53323_DEVICE_ID, BCM53323_A0_REV_ID,
        "BCM53323_A0",
        BCM53324_DEVICE_ID, BCM53324_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hawkeye EEE */
        BCM53324_DEVICE_ID, BCM53324_A0_REV_ID,
        "BCM53324_A0",
        BCM53324_DEVICE_ID, BCM53324_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_TRIUMPH2_SUPPORT)
    {   /* Triumph2 */

        BCM56630_DEVICE_ID, BCM56630_A0_REV_ID,
        "BCM56630_A0",
        BCM56524_DEVICE_ID, BCM56524_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph2 */

        BCM56630_DEVICE_ID, BCM56630_B0_REV_ID,
        "BCM56630_B0",
        BCM56524_DEVICE_ID, BCM56524_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph2 */

        BCM56634_DEVICE_ID, BCM56634_A0_REV_ID,
        "BCM56634_A0",
        BCM56634_DEVICE_ID, BCM56634_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph2 */

        BCM56634_DEVICE_ID, BCM56634_B0_REV_ID,
        "BCM56634_B0",
        BCM56634_DEVICE_ID, BCM56634_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph2 */

        BCM56636_DEVICE_ID, BCM56636_A0_REV_ID,
        "BCM56636_A0",
        BCM56634_DEVICE_ID, BCM56634_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph2 */

        BCM56636_DEVICE_ID, BCM56636_B0_REV_ID,
        "BCM56636_B0",
        BCM56634_DEVICE_ID, BCM56634_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph2 */

        BCM56638_DEVICE_ID, BCM56638_A0_REV_ID,
        "BCM56638_A0",
        BCM56634_DEVICE_ID, BCM56634_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph2 */

        BCM56638_DEVICE_ID, BCM56638_B0_REV_ID,
        "BCM56638_B0",
        BCM56634_DEVICE_ID, BCM56634_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph2 */

        BCM56639_DEVICE_ID, BCM56639_A0_REV_ID,
        "BCM56639_A0",
        BCM56634_DEVICE_ID, BCM56634_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph2 */

        BCM56639_DEVICE_ID, BCM56639_B0_REV_ID,
        "BCM56639_B0",
        BCM56634_DEVICE_ID, BCM56634_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt 3 */

        BCM56538_DEVICE_ID, BCM56538_B0_REV_ID,
        "BCM56538_B0",
        BCM56634_DEVICE_ID, BCM56634_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
#if defined(BCM_VALKYRIE2_SUPPORT)
    {   /* Valkyrie2 */

        BCM56685_DEVICE_ID, BCM56685_A0_REV_ID,
        "BCM56685_A0",
        BCM56685_DEVICE_ID, BCM56685_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie2 */

        BCM56685_DEVICE_ID, BCM56685_B0_REV_ID,
        "BCM56685_B0",
        BCM56685_DEVICE_ID, BCM56685_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie2 */

        BCM56689_DEVICE_ID, BCM56689_A0_REV_ID,
        "BCM56689_A0",
        BCM56685_DEVICE_ID, BCM56685_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Valkyrie2 */

        BCM56689_DEVICE_ID, BCM56689_B0_REV_ID,
        "BCM56689_B0",
        BCM56685_DEVICE_ID, BCM56685_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
#if defined(BCM_APOLLO_SUPPORT)
    {   /* Apollo */

        BCM56520_DEVICE_ID, BCM56520_A0_REV_ID,
        "BCM56520_A0",
        BCM56524_DEVICE_ID, BCM56524_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo */

        BCM56520_DEVICE_ID, BCM56520_B0_REV_ID,
        "BCM56520_B0",
        BCM56524_DEVICE_ID, BCM56524_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },

    {   /* Apollo */

        BCM56521_DEVICE_ID, BCM56521_A0_REV_ID,
        "BCM56521_A0",
        BCM56524_DEVICE_ID, BCM56524_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo */

        BCM56521_DEVICE_ID, BCM56521_B0_REV_ID,
        "BCM56521_B0",
        BCM56524_DEVICE_ID, BCM56524_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo */

        BCM56522_DEVICE_ID, BCM56522_A0_REV_ID,
        "BCM56522_A0",
        BCM56524_DEVICE_ID, BCM56524_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo */

        BCM56522_DEVICE_ID, BCM56522_B0_REV_ID,
        "BCM56522_B0",
        BCM56524_DEVICE_ID, BCM56524_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo */

        BCM56524_DEVICE_ID, BCM56524_A0_REV_ID,
        "BCM56524_A0",
        BCM56524_DEVICE_ID, BCM56524_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo */

        BCM56524_DEVICE_ID, BCM56524_B0_REV_ID,
        "BCM56524_B0",
        BCM56524_DEVICE_ID, BCM56524_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo */

        BCM56526_DEVICE_ID, BCM56526_A0_REV_ID,
        "BCM56526_A0",
        BCM56524_DEVICE_ID, BCM56524_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo */

        BCM56526_DEVICE_ID, BCM56526_B0_REV_ID,
        "BCM56526_B0",
        BCM56524_DEVICE_ID, BCM56524_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt 3 */

        BCM56534_DEVICE_ID, BCM56534_B0_REV_ID,
        "BCM56534_B0",
        BCM56524_DEVICE_ID, BCM56524_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_ENDURO_SUPPORT)
    {   /* Enduro */
        BCM56331_DEVICE_ID, BCM56331_A0_REV_ID,
        "BCM56331_A0",
        BCM56334_DEVICE_ID, BCM56334_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Enduro */
        BCM56331_DEVICE_ID, BCM56331_B0_REV_ID,
        "BCM56331_B0",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro */
        BCM56331_DEVICE_ID, BCM56331_B1_REV_ID,
        "BCM56331_B1",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro */
        BCM56333_DEVICE_ID, BCM56333_A0_REV_ID,
        "BCM56333_A0",
        BCM56334_DEVICE_ID, BCM56334_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Enduro */
        BCM56333_DEVICE_ID, BCM56333_B0_REV_ID,
        "BCM56333_B0",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Enduro */
        BCM56333_DEVICE_ID, BCM56333_B1_REV_ID,
        "BCM56333_B1",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Enduro - Default */
        BCM56334_DEVICE_ID, BCM56334_A0_REV_ID,
        "BCM56334_A0",
        BCM56334_DEVICE_ID, BCM56334_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro */
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        "BCM56334_B0",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro */
        BCM56334_DEVICE_ID, BCM56334_B1_REV_ID,
        "BCM56334_B1",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro */
        BCM56338_DEVICE_ID, BCM56338_A0_REV_ID,
        "BCM56338_A0",
        BCM56334_DEVICE_ID, BCM56334_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Enduro */
        BCM56338_DEVICE_ID, BCM56338_B0_REV_ID,
        "BCM56338_B0",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Enduro */
        BCM56338_DEVICE_ID, BCM56338_B1_REV_ID,
        "BCM56338_B1",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Helix3 */
        BCM56320_DEVICE_ID, BCM56320_A0_REV_ID,
        "BCM56320_A0",
        BCM56334_DEVICE_ID, BCM56334_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Helix3 */
        BCM56320_DEVICE_ID, BCM56320_B0_REV_ID,
        "BCM56320_B0",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Helix3 */
        BCM56320_DEVICE_ID, BCM56320_B1_REV_ID,
        "BCM56320_B1",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Helix3 */
        BCM56321_DEVICE_ID, BCM56321_A0_REV_ID,
        "BCM56321_A0",
        BCM56334_DEVICE_ID, BCM56334_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Helix3 */
        BCM56321_DEVICE_ID, BCM56321_B0_REV_ID,
        "BCM56321_B0",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {  /* Helix3 */
        BCM56321_DEVICE_ID, BCM56321_B1_REV_ID,
        "BCM56321_B1",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Stardust  */
        BCM56132_DEVICE_ID, BCM56132_A0_REV_ID,
        "BCM56132_A0",
        BCM56334_DEVICE_ID, BCM56334_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Stardust  */
        BCM56132_DEVICE_ID, BCM56132_B0_REV_ID,
        "BCM56132_B0",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Stardust  */
        BCM56132_DEVICE_ID, BCM56132_B1_REV_ID,
        "BCM56132_B1",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Stardust  */
        BCM56134_DEVICE_ID, BCM56134_A0_REV_ID,
        "BCM56134_A0",
        BCM56334_DEVICE_ID, BCM56334_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Stardust  */
        BCM56134_DEVICE_ID, BCM56134_B0_REV_ID,
        "BCM56134_B0",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Stardust  */
        BCM56134_DEVICE_ID, BCM56134_B1_REV_ID,
        "BCM56134_B1",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Dagger  */
        BCM56230_DEVICE_ID, BCM56230_B1_REV_ID,
        "BCM56230_B1",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Dagger  */
        BCM56231_DEVICE_ID, BCM56231_B1_REV_ID,
        "BCM56231_B1",
        BCM56334_DEVICE_ID, BCM56334_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_HURRICANE_SUPPORT)
    {   /* Hurricane */
        BCM56140_DEVICE_ID, BCM56140_A0_REV_ID,
        "BCM56140_A0",
        BCM56142_DEVICE_ID, BCM56142_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane */
        BCM56142_DEVICE_ID, BCM56142_A0_REV_ID,
        "BCM56142_A0",
        BCM56142_DEVICE_ID, BCM56142_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane */
        BCM56143_DEVICE_ID, BCM56143_A0_REV_ID,
        "BCM56143_A0",
        BCM56142_DEVICE_ID, BCM56142_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane */
        BCM56144_DEVICE_ID, BCM56144_A0_REV_ID,
        "BCM56144_A0",
        BCM56142_DEVICE_ID, BCM56142_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane */
        BCM56146_DEVICE_ID, BCM56146_A0_REV_ID,
        "BCM56146_A0",
        BCM56142_DEVICE_ID, BCM56142_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane */
        BCM56147_DEVICE_ID, BCM56147_A0_REV_ID,
        "BCM56147_A0",
        BCM56142_DEVICE_ID, BCM56142_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane */
        BCM56149_DEVICE_ID, BCM56149_A0_REV_ID,
        "BCM56149_A0",
        BCM56142_DEVICE_ID, BCM56142_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_HURRICANE2_SUPPORT)
    {   /* Hurricane 2 */
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        "BCM56150_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane 2 */
        BCM56151_DEVICE_ID, BCM56151_A0_REV_ID,
        "BCM56151_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Hurricane 2 */
        BCM56152_DEVICE_ID, BCM56152_A0_REV_ID,
        "BCM56152_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Wolfhound */
        BCM53342_DEVICE_ID, BCM53342_A0_REV_ID,
        "BCM53342_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Wolfhound */
        BCM53343_DEVICE_ID, BCM53343_A0_REV_ID,
        "BCM53343_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Wolfhound */
        BCM53344_DEVICE_ID, BCM53344_A0_REV_ID,
        "BCM53344_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Wolfhound */
        BCM53346_DEVICE_ID, BCM53346_A0_REV_ID,
        "BCM53346_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {    /* Wolfhound */
        BCM53347_DEVICE_ID, BCM53347_A0_REV_ID,
        "BCM53347_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Foxhound */
        BCM53333_DEVICE_ID, BCM53333_A0_REV_ID,
        "BCM53333_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Foxhound */
        BCM53334_DEVICE_ID, BCM53334_A0_REV_ID,
        "BCM53334_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Deerhound */
        BCM53393_DEVICE_ID, BCM53393_A0_REV_ID,
        "BCM53393_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Deerhound */
        BCM53394_DEVICE_ID, BCM53394_A0_REV_ID,
        "BCM53394_A0",
        BCM56150_DEVICE_ID, BCM56150_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_TRIDENT_SUPPORT)
    {   /* Trident */
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        "BCM56840_A0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56840_DEVICE_ID, BCM56840_A1_REV_ID,
        "BCM56840_A1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56840_DEVICE_ID, BCM56840_A2_REV_ID,
        "BCM56840_A2",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56840_DEVICE_ID, BCM56840_A3_REV_ID,
        "BCM56840_A3",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56840_DEVICE_ID, BCM56840_A4_REV_ID,
        "BCM56840_A4",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        "BCM56840_B0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56840_DEVICE_ID, BCM56840_B1_REV_ID,
        "BCM56840_B1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56841_DEVICE_ID, BCM56841_A0_REV_ID,
        "BCM56841_A0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56841_DEVICE_ID, BCM56841_A1_REV_ID,
        "BCM56841_A1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56841_DEVICE_ID, BCM56841_A2_REV_ID,
        "BCM56841_A2",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56841_DEVICE_ID, BCM56841_A3_REV_ID,
        "BCM56841_A3",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56841_DEVICE_ID, BCM56841_A4_REV_ID,
        "BCM56841_A4",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56841_DEVICE_ID, BCM56841_B0_REV_ID,
        "BCM56841_B0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56841_DEVICE_ID, BCM56841_B1_REV_ID,
        "BCM56841_B1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56843_DEVICE_ID, BCM56843_A0_REV_ID,
        "BCM56843_A0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56843_DEVICE_ID, BCM56843_A1_REV_ID,
        "BCM56843_A1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56843_DEVICE_ID, BCM56843_A2_REV_ID,
        "BCM56843_A2",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56843_DEVICE_ID, BCM56843_A3_REV_ID,
        "BCM56843_A3",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56843_DEVICE_ID, BCM56843_A4_REV_ID,
        "BCM56843_A4",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56843_DEVICE_ID, BCM56843_B0_REV_ID,
        "BCM56843_B0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56843_DEVICE_ID, BCM56843_B1_REV_ID,
        "BCM56843_B1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56845_DEVICE_ID, BCM56845_A0_REV_ID,
        "BCM56845_A0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56845_DEVICE_ID, BCM56845_A1_REV_ID,
        "BCM56845_A1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56845_DEVICE_ID, BCM56845_A2_REV_ID,
        "BCM56845_A2",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56845_DEVICE_ID, BCM56845_A3_REV_ID,
        "BCM56845_A3",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56845_DEVICE_ID, BCM56845_A4_REV_ID,
        "BCM56845_A4",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56845_DEVICE_ID, BCM56845_B0_REV_ID,
        "BCM56845_B0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident */
        BCM56845_DEVICE_ID, BCM56845_B1_REV_ID,
        "BCM56845_B1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56743_DEVICE_ID, BCM56743_A0_REV_ID,
        "BCM56743_A0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56743_DEVICE_ID, BCM56743_A1_REV_ID,
        "BCM56743_A1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56743_DEVICE_ID, BCM56743_A2_REV_ID,
        "BCM56743_A2",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56743_DEVICE_ID, BCM56743_A3_REV_ID,
        "BCM56743_A3",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56743_DEVICE_ID, BCM56743_A4_REV_ID,
        "BCM56743_A4",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56743_DEVICE_ID, BCM56743_B0_REV_ID,
        "BCM56743_B0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56743_DEVICE_ID, BCM56743_B1_REV_ID,
        "BCM56743_B1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56745_DEVICE_ID, BCM56745_A0_REV_ID,
        "BCM56745_A0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56745_DEVICE_ID, BCM56745_A1_REV_ID,
        "BCM56745_A1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56745_DEVICE_ID, BCM56745_A2_REV_ID,
        "BCM56745_A2",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56745_DEVICE_ID, BCM56745_A3_REV_ID,
        "BCM56745_A3",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56745_DEVICE_ID, BCM56745_A4_REV_ID,
        "BCM56745_A4",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56745_DEVICE_ID, BCM56745_B0_REV_ID,
        "BCM56745_B0",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan */
        BCM56745_DEVICE_ID, BCM56745_B1_REV_ID,
        "BCM56745_B1",
        BCM56840_DEVICE_ID, BCM56840_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56842_DEVICE_ID, BCM56842_A0_REV_ID,
        "BCM56842_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56842_DEVICE_ID, BCM56842_A1_REV_ID,
        "BCM56842_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56844_DEVICE_ID, BCM56844_A0_REV_ID,
        "BCM56844_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56844_DEVICE_ID, BCM56844_A1_REV_ID,
        "BCM56844_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56846_DEVICE_ID, BCM56846_A0_REV_ID,
        "BCM56846_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56846_DEVICE_ID, BCM56846_A1_REV_ID,
        "BCM56846_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56549_DEVICE_ID, BCM56549_A0_REV_ID,
        "BCM56549_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56053_DEVICE_ID, BCM56053_A0_REV_ID,
        "BCM56053_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56053_DEVICE_ID, BCM56053_A1_REV_ID,
        "BCM56053_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident Plus */
        BCM56549_DEVICE_ID, BCM56549_A1_REV_ID,
        "BCM56549_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan Plus */
        BCM56744_DEVICE_ID, BCM56744_A0_REV_ID,
        "BCM56744_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan Plus */
        BCM56744_DEVICE_ID, BCM56744_A1_REV_ID,
        "BCM56744_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan Plus */
        BCM56746_DEVICE_ID, BCM56746_A0_REV_ID,
        "BCM56746_A0",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan Plus */
        BCM56746_DEVICE_ID, BCM56746_A1_REV_ID,
        "BCM56746_A1",
        BCM56840_DEVICE_ID, BCM56840_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
#if defined(BCM_SHADOW_SUPPORT)
    {   /* Shadow */
        BCM88732_DEVICE_ID, BCM88732_A0_REV_ID,
        "BCM88732_A0",
        BCM88732_DEVICE_ID, BCM88732_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Shadow */
        BCM88732_DEVICE_ID, BCM88732_A1_REV_ID,
        "BCM88732_A1",
        BCM88732_DEVICE_ID, BCM88732_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Shadow */
        BCM88732_DEVICE_ID, BCM88732_A2_REV_ID,
        "BCM88732_A2",
        BCM88732_DEVICE_ID, BCM88732_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Shadow */
        BCM88732_DEVICE_ID, BCM88732_B0_REV_ID,
        "BCM88732_B0",
        BCM88732_DEVICE_ID, BCM88732_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Shadow */
        BCM88732_DEVICE_ID, BCM88732_B1_REV_ID,
        "BCM88732_B1",
        BCM88732_DEVICE_ID, BCM88732_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Shadow */
        BCM88732_DEVICE_ID, BCM88732_B2_REV_ID,
        "BCM88732_B2",
        BCM88732_DEVICE_ID, BCM88732_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_HELIX4_SUPPORT)
    {   /* FireScout */
        BCM56548_DEVICE_ID, BCM56548_A0_REV_ID,
        "BCM56548_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* FireScout */
        BCM56547_DEVICE_ID, BCM56547_A0_REV_ID,
        "BCM56547_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix4 */
        BCM56344_DEVICE_ID, BCM56344_A0_REV_ID,
        "BCM56344_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix4 */
        BCM56342_DEVICE_ID, BCM56342_A0_REV_ID,
        "BCM56342_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Helix4 */
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        "BCM56340_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Spiral */
        BCM56049_DEVICE_ID, BCM56049_A0_REV_ID,
        "BCM56049_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Spiral */
        BCM56048_DEVICE_ID, BCM56048_A0_REV_ID,
        "BCM56048_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Spiral */
        BCM56047_DEVICE_ID, BCM56047_A0_REV_ID,
        "BCM56047_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger */
        BCM56042_DEVICE_ID, BCM56042_A0_REV_ID,
        "BCM56042_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger */
        BCM56041_DEVICE_ID, BCM56041_A0_REV_ID,
        "BCM56041_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger */
        BCM56040_DEVICE_ID, BCM56040_A0_REV_ID,
        "BCM56040_A0",
        BCM56340_DEVICE_ID, BCM56340_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_TRIUMPH3_SUPPORT)
    {   /* Triumph3 */
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        "BCM56640_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56640_DEVICE_ID, BCM56640_A1_REV_ID,
        "BCM56640_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56640_DEVICE_ID, BCM56640_B0_REV_ID,
        "BCM56640_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56643_DEVICE_ID, BCM56643_A0_REV_ID,
        "BCM56643_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56643_DEVICE_ID, BCM56643_A1_REV_ID,
        "BCM56643_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56643_DEVICE_ID, BCM56643_B0_REV_ID,
        "BCM56643_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56644_DEVICE_ID, BCM56644_A0_REV_ID,
        "BCM56644_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56644_DEVICE_ID, BCM56644_A1_REV_ID,
        "BCM56644_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56644_DEVICE_ID, BCM56644_B0_REV_ID,
        "BCM56644_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56648_DEVICE_ID, BCM56648_A0_REV_ID,
        "BCM56648_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56648_DEVICE_ID, BCM56648_A1_REV_ID,
        "BCM56648_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56648_DEVICE_ID, BCM56648_B0_REV_ID,
        "BCM56648_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56649_DEVICE_ID, BCM56649_A0_REV_ID,
        "BCM56649_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56649_DEVICE_ID, BCM56649_A1_REV_ID,
        "BCM56649_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Triumph3 */
        BCM56649_DEVICE_ID, BCM56649_B0_REV_ID,
        "BCM56649_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt4 */
        BCM56545_DEVICE_ID, BCM56545_A0_REV_ID,
        "BCM56545_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt4 */
        BCM56545_DEVICE_ID, BCM56545_A1_REV_ID,
        "BCM56545_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt4 */
        BCM56545_DEVICE_ID, BCM56545_B0_REV_ID,
        "BCM56545_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt4 */
        BCM56546_DEVICE_ID, BCM56546_A0_REV_ID,
        "BCM56546_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt4 */
        BCM56546_DEVICE_ID, BCM56546_A1_REV_ID,
        "BCM56546_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Firebolt4 */
        BCM56546_DEVICE_ID, BCM56546_B0_REV_ID,
        "BCM56546_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56540_DEVICE_ID, BCM56540_A0_REV_ID,
        "BCM56540_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56540_DEVICE_ID, BCM56540_A1_REV_ID,
        "BCM56540_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56540_DEVICE_ID, BCM56540_B0_REV_ID,
        "BCM56540_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56541_DEVICE_ID, BCM56541_A0_REV_ID,
        "BCM56541_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56541_DEVICE_ID, BCM56541_A1_REV_ID,
        "BCM56541_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56541_DEVICE_ID, BCM56541_B0_REV_ID,
        "BCM56541_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56542_DEVICE_ID, BCM56542_A0_REV_ID,
        "BCM56542_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56542_DEVICE_ID, BCM56542_A1_REV_ID,
        "BCM56542_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56542_DEVICE_ID, BCM56542_B0_REV_ID,
        "BCM56542_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56544_DEVICE_ID, BCM56544_A0_REV_ID,
        "BCM56544_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56544_DEVICE_ID, BCM56544_A1_REV_ID,
        "BCM56544_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Apollo2 */
        BCM56544_DEVICE_ID, BCM56544_B0_REV_ID,
        "BCM56544_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger Plus */
        BCM56045_DEVICE_ID, BCM56045_A0_REV_ID,
        "BCM56045_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger Plus */
        BCM56045_DEVICE_ID, BCM56045_A1_REV_ID,
        "BCM56045_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger Plus */
        BCM56045_DEVICE_ID, BCM56045_B0_REV_ID,
        "BCM56045_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger Plus */
        BCM56046_DEVICE_ID, BCM56046_A0_REV_ID,
        "BCM56046_A0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger Plus */
        BCM56046_DEVICE_ID, BCM56046_A1_REV_ID,
        "BCM56046_A1",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Ranger Plus */
        BCM56046_DEVICE_ID, BCM56046_B0_REV_ID,
        "BCM56046_B0",
        BCM56640_DEVICE_ID, BCM56640_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_KATANA_SUPPORT)
    {   /* Katana */
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        "BCM56440_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana */
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        "BCM56440_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana */
        BCM56441_DEVICE_ID, BCM56441_A0_REV_ID,
        "BCM56441_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana */
        BCM56441_DEVICE_ID, BCM56441_B0_REV_ID,
        "BCM56441_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana */
        BCM56442_DEVICE_ID, BCM56442_A0_REV_ID,
        "BCM56442_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana */
        BCM56442_DEVICE_ID, BCM56442_B0_REV_ID,
        "BCM56442_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana */
        BCM56443_DEVICE_ID, BCM56443_A0_REV_ID,
        "BCM56443_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana */
        BCM56443_DEVICE_ID, BCM56443_B0_REV_ID,
        "BCM56443_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro-2 */
        BCM56445_DEVICE_ID, BCM56445_A0_REV_ID,
        "BCM56445_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro-2 */
        BCM56445_DEVICE_ID, BCM56445_B0_REV_ID,
        "BCM56445_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro-2 */
        BCM56446_DEVICE_ID, BCM56446_A0_REV_ID,
        "BCM56446_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro-2 */
        BCM56446_DEVICE_ID, BCM56446_B0_REV_ID,
        "BCM56446_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro-2 */
        BCM56447_DEVICE_ID, BCM56447_A0_REV_ID,
        "BCM56447_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro-2 */
        BCM56447_DEVICE_ID, BCM56447_B0_REV_ID,
        "BCM56447_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro-2 */
        BCM56448_DEVICE_ID, BCM56448_A0_REV_ID,
        "BCM56448_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Enduro-2 */
        BCM56448_DEVICE_ID, BCM56448_B0_REV_ID,
        "BCM56448_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana-FE */
        BCM56449_DEVICE_ID, BCM56449_A0_REV_ID,
        "BCM56449_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana-FE */
        BCM56449_DEVICE_ID, BCM56449_B0_REV_ID,
        "BCM56449_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber */
        BCM56240_DEVICE_ID, BCM56240_A0_REV_ID,
        "BCM56240_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber */
        BCM56240_DEVICE_ID, BCM56240_B0_REV_ID,
        "BCM56240_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber */
        BCM56241_DEVICE_ID, BCM56241_A0_REV_ID,
        "BCM56241_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber */
        BCM56241_DEVICE_ID, BCM56241_B0_REV_ID,
        "BCM56241_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber */
        BCM56242_DEVICE_ID, BCM56242_A0_REV_ID,
        "BCM56242_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber*/
        BCM56242_DEVICE_ID, BCM56242_B0_REV_ID,
        "BCM56242_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Saber */
        BCM56243_DEVICE_ID, BCM56243_A0_REV_ID,
        "BCM56243_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE) 
   },
    {   /* Saber */
        BCM56243_DEVICE_ID, BCM56243_B0_REV_ID,
        "BCM56243_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana-Access */
        BCM55440_DEVICE_ID, BCM55440_A0_REV_ID,
        "BCM55440_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana-Access */
        BCM55440_DEVICE_ID, BCM55440_B0_REV_ID,
        "BCM55440_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana-Access */
        BCM55441_DEVICE_ID, BCM55441_A0_REV_ID,
        "BCM55441_A0",
        BCM56440_DEVICE_ID, BCM56440_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },    
    {   /* Katana-Access */
        BCM55441_DEVICE_ID, BCM55441_B0_REV_ID,
        "BCM55441_B0",
        BCM56440_DEVICE_ID, BCM56440_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },    
#endif

#if defined(BCM_KATANA2_SUPPORT)
    {   /* Katana 2 */
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        "BCM56450_A0",
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2  */
        BCM56452_DEVICE_ID, BCM56452_A0_REV_ID,
        "BCM56452_A0",
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2  */
        BCM56454_DEVICE_ID, BCM56454_A0_REV_ID,
        "BCM56454_A0",
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2  */
        BCM56455_DEVICE_ID, BCM56455_A0_REV_ID,
        "BCM56455_A0",
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2  */
        BCM56456_DEVICE_ID, BCM56456_A0_REV_ID,
        "BCM56456_A0",
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2  */
        BCM56457_DEVICE_ID, BCM56457_A0_REV_ID,
        "BCM56457_A0",
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Katana 2  */
        BCM56458_DEVICE_ID, BCM56458_A0_REV_ID,
        "BCM56458_A0",
        BCM56450_DEVICE_ID, BCM56450_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif

#if defined(BCM_TRIDENT2_SUPPORT)
    {   /* Trident 2 */
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        "BCM56850_A0",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56850_DEVICE_ID, BCM56850_A1_REV_ID,
        "BCM56850_A1",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56850_DEVICE_ID, BCM56850_A2_REV_ID,
        "BCM56850_A2",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56851_DEVICE_ID, BCM56851_A0_REV_ID,
        "BCM56851_A0",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56851_DEVICE_ID, BCM56851_A1_REV_ID,
        "BCM56851_A1",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56851_DEVICE_ID, BCM56851_A2_REV_ID,
        "BCM56851_A2",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56852_DEVICE_ID, BCM56852_A0_REV_ID,
        "BCM56852_A0",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56852_DEVICE_ID, BCM56852_A1_REV_ID,
        "BCM56852_A1",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56852_DEVICE_ID, BCM56852_A2_REV_ID,
        "BCM56852_A2",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56853_DEVICE_ID, BCM56853_A0_REV_ID,
        "BCM56853_A0",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56853_DEVICE_ID, BCM56853_A1_REV_ID,
        "BCM56853_A1",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56853_DEVICE_ID, BCM56853_A2_REV_ID,
        "BCM56853_A2",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56854_DEVICE_ID, BCM56854_A0_REV_ID,
        "BCM56854_A0",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56854_DEVICE_ID, BCM56854_A1_REV_ID,
        "BCM56854_A1",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56854_DEVICE_ID, BCM56854_A2_REV_ID,
        "BCM56854_A2",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56855_DEVICE_ID, BCM56855_A0_REV_ID,
        "BCM56855_A0",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56855_DEVICE_ID, BCM56855_A1_REV_ID,
        "BCM56855_A1",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Trident 2 */
        BCM56855_DEVICE_ID, BCM56855_A2_REV_ID,
        "BCM56855_A2",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan 2 */
        BCM56750_DEVICE_ID, BCM56750_A0_REV_ID,
        "BCM56750_A0",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan 2 */
        BCM56750_DEVICE_ID, BCM56750_A1_REV_ID,
        "BCM56750_A1",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Titan 2 */
        BCM56750_DEVICE_ID, BCM56750_A2_REV_ID,
        "BCM56750_A2",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion 960 */
        BCM56830_DEVICE_ID, BCM56830_A0_REV_ID,
        "BCM56830_A0",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion 960 */
        BCM56830_DEVICE_ID, BCM56830_A1_REV_ID,
        "BCM56830_A1",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {   /* Scorpion 960 */
        BCM56830_DEVICE_ID, BCM56830_A2_REV_ID,
        "BCM56830_A2",
        BCM56850_DEVICE_ID, BCM56850_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif /* BCM_TRIDENT2_SUPPORT */

#if defined(BCM_ROBO_SUPPORT)
    {
        BCM5324_PHYID_LOW, BCM5324_A0_REV_ID,
        "BCM5324_A0",
        0, 0,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },    
    {
        BCM5324_PHYID_LOW, BCM5324_A1_REV_ID,
        "BCM5324_A1",
        BCM5324_PHYID_LOW, BCM5324_A1_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },    
    {
        BCM5324_PHYID_LOW, BCM5324_A2_REV_ID,
        "BCM5324_A2",
        BCM5324_PHYID_LOW, BCM5324_A1_REV_ID,    
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },    
    {
        BCM5396_DEVICE_ID, BCM5396_A0_REV_ID,
        "BCM5396_A0",
        0, 0,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM5389_DEVICE_ID, BCM5389_A0_REV_ID,
        "BCM5389_A0",
        0, 0,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM5389_A1_DEVICE_ID, BCM5389_A1_REV_ID,
        "BCM5389_A1",
        BCM5389_DEVICE_ID, BCM5389_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM5398_DEVICE_ID, BCM5398_A0_REV_ID,
        "BCM5398_A0",
        0, 0,        
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM5348_DEVICE_ID, BCM5348_A0_REV_ID,
        "BCM5348_A0",
        0, 0,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM5397_DEVICE_ID, BCM5397_A0_REV_ID,
        "BCM5397_A0",
        0, 0,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM5347_DEVICE_ID, BCM5347_A0_REV_ID,
        "BCM5347_A0",
        0, 0,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    /* bcm5348_A1 */
    {
        BCM5348_DEVICE_ID, BCM5348_A1_REV_ID,
        "BCM5348_A1",
        BCM5348_DEVICE_ID, BCM5348_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm5347_A1 */
    {
        BCM5347_DEVICE_ID, BCM5348_A1_REV_ID,
        "BCM5347_A1",
        BCM5347_DEVICE_ID, BCM5348_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM5395_PHYID_LOW, BCM5395_A0_REV_ID,
        "BCM5395_A0",
        0, 0,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53242_A0 */
    {
        BCM53242_DEVICE_ID, BCM53242_A0_REV_ID,
        "BCM53242_A0",
        0, 0,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53262_A0 */
    {
        BCM53262_DEVICE_ID, BCM53262_A0_REV_ID,
        "BCM53262_A0",
        0, 0,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53242_B0 */
    {
        BCM53242_DEVICE_ID, BCM53242_B0_REV_ID,
        "BCM53242_B0",
        BCM53242_DEVICE_ID, BCM53242_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53262_B0 */
    {
        BCM53262_DEVICE_ID, BCM53262_B0_REV_ID,
        "BCM53262_B0",
        BCM53262_DEVICE_ID, BCM53242_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53242_B1 */
    {
        BCM53242_DEVICE_ID, BCM53242_B1_REV_ID,
        "BCM53242_B1",
        BCM53242_DEVICE_ID, BCM53242_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53262_B1 */
    {
        BCM53262_DEVICE_ID, BCM53262_B1_REV_ID,
        "BCM53262_B1",
        BCM53262_DEVICE_ID, BCM53242_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53115_A0 */
    {
        BCM53115_DEVICE_ID, BCM53115_A0_REV_ID,
        "BCM53115_A0",
        0, 0,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53115_A1 */
    {
        BCM53115_DEVICE_ID, BCM53115_A1_REV_ID,
        "BCM53115_A1",
        BCM53115_DEVICE_ID, BCM53115_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53115_B0 */
    {
        BCM53115_DEVICE_ID, BCM53115_B0_REV_ID,
        "BCM53115_B0",
        BCM53115_DEVICE_ID, BCM53115_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53115_B1 */
    {
        BCM53115_DEVICE_ID, BCM53115_B1_REV_ID,
        "BCM53115_B1",
        BCM53115_DEVICE_ID, BCM53115_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53115_C0 */
    {
        BCM53115_DEVICE_ID, BCM53115_C0_REV_ID,
        "BCM53115_C0",
        BCM53115_DEVICE_ID, BCM53115_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53118_A0 */
    {
        BCM53118_DEVICE_ID, BCM53118_A0_REV_ID,
        "BCM53118_A0",
        0, 0,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53118_B0 */
    {
        BCM53118_DEVICE_ID, BCM53118_B0_REV_ID,
        "BCM53118_B0",
        BCM53118_DEVICE_ID, BCM53118_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53118_B1 */
    {
        BCM53118_DEVICE_ID, BCM53118_B1_REV_ID,
        "BCM53118_B1",
        BCM53118_DEVICE_ID, BCM53118_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
#ifdef BCM_TB_SUPPORT
    /* ThunderBolt */
    {
        BCM53286_DEVICE_ID, BCM53280_A0_REV_ID,
        "BCM53286_A0",
        BCM53280_DEVICE_ID, BCM53280_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53288_DEVICE_ID, BCM53280_A0_REV_ID,
        "BCM53288_A0",
        BCM53280_DEVICE_ID, BCM53280_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53284_DEVICE_ID, BCM53280_A0_REV_ID,
        "BCM53284_A0",
        BCM53280_DEVICE_ID, BCM53280_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53283_DEVICE_ID, BCM53280_A0_REV_ID,
        "BCM53283_A0",
        BCM53280_DEVICE_ID, BCM53280_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53282_DEVICE_ID, BCM53280_A0_REV_ID,
        "BCM53282_A0",
        BCM53280_DEVICE_ID, BCM53280_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53286_DEVICE_ID, BCM53280_B0_REV_ID,
        "BCM53286_B0",
        BCM53280_DEVICE_ID, BCM53280_B0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53288_DEVICE_ID, BCM53280_B0_REV_ID,
        "BCM53288_B0",
        BCM53280_DEVICE_ID, BCM53280_B0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53284_DEVICE_ID, BCM53280_B0_REV_ID,
        "BCM53284_B0",
        BCM53280_DEVICE_ID, BCM53280_B0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53283_DEVICE_ID, BCM53280_B0_REV_ID,
        "BCM53283_B0",
        BCM53280_DEVICE_ID, BCM53280_B0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53282_DEVICE_ID, BCM53280_B0_REV_ID,
        "BCM53282_B0",
        BCM53280_DEVICE_ID, BCM53280_B0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53286_DEVICE_ID, BCM53280_B1_REV_ID,
        "BCM53286_B1",
        BCM53280_DEVICE_ID, BCM53280_B0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53288_DEVICE_ID, BCM53280_B1_REV_ID,
        "BCM53288_B1",
        BCM53280_DEVICE_ID, BCM53280_B0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53284_DEVICE_ID, BCM53280_B1_REV_ID,
        "BCM53284_B1",
        BCM53280_DEVICE_ID, BCM53280_B0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53283_DEVICE_ID, BCM53280_B1_REV_ID,
        "BCM53283_B1",
        BCM53280_DEVICE_ID, BCM53280_B0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53282_DEVICE_ID, BCM53280_B1_REV_ID,
        "BCM53282_B1",
        BCM53280_DEVICE_ID, BCM53280_B0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53286_DEVICE_ID, BCM53280_B2_REV_ID,
        "BCM53286_B2",
        BCM53280_DEVICE_ID, BCM53280_B0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53288_DEVICE_ID, BCM53280_B2_REV_ID,
        "BCM53288_B2",
        BCM53280_DEVICE_ID, BCM53280_B0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53284_DEVICE_ID, BCM53280_B2_REV_ID,
        "BCM53284_B2",
        BCM53280_DEVICE_ID, BCM53280_B0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53283_DEVICE_ID, BCM53280_B2_REV_ID,
        "BCM53283_B2",
        BCM53280_DEVICE_ID, BCM53280_B0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53282_DEVICE_ID, BCM53280_B2_REV_ID,
        "BCM53282_B2",
        BCM53280_DEVICE_ID, BCM53280_B0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },

#endif
    /* bcm53101_A0 */
    {
        BCM53101_DEVICE_ID, BCM53101_A0_REV_ID,
        "BCM53101_A0",
        BCM53101_DEVICE_ID, BCM53101_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53101_B0 */
    {
        BCM53101_DEVICE_ID, BCM53101_B0_REV_ID,
        "BCM53101_B0",
        BCM53101_DEVICE_ID, BCM53101_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
#ifdef BCM_53125    
    /* bcm53125_A0 */
    {
        BCM53125_DEVICE_ID, BCM53125_A0_REV_ID,
        "BCM53125_A0",
        BCM53125_DEVICE_ID, BCM53125_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53125_B0 */
    {
        BCM53125_DEVICE_ID, BCM53125_B0_REV_ID,
        "BCM53125_B0",
        BCM53125_DEVICE_ID, BCM53125_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
#endif /* BCM_53125 */  
#ifdef BCM_POLAR_SUPPORT
    /* bcm89500_A0 */
    {
        BCM89500_DEVICE_ID, BCM89500_A0_REV_ID,
        "BCM89500_A0",
        BCM89500_DEVICE_ID, BCM89500_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm89501_A0 */
    {
        BCM89501_DEVICE_ID, BCM89500_A0_REV_ID,
        "BCM89501_A0",
        BCM89500_DEVICE_ID, BCM89500_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm89200_A0 */
    {
        BCM89200_DEVICE_ID, BCM89500_A0_REV_ID,
        "BCM89200_A0",
        BCM89500_DEVICE_ID, BCM89500_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm89500_B0 */
    {
        BCM89500_DEVICE_ID, BCM89500_B0_REV_ID,
        "BCM89500_B0",
        BCM89500_DEVICE_ID, BCM89500_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm89501_B0 */
    {
        BCM89501_DEVICE_ID, BCM89500_B0_REV_ID,
        "BCM89501_B0",
        BCM89500_DEVICE_ID, BCM89500_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm89200_B0 */
    {
        BCM89200_DEVICE_ID, BCM89500_B0_REV_ID,
        "BCM89200_B0",
        BCM89500_DEVICE_ID, BCM89500_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
#endif /* BCM_POLAR_SUPPORT */  
#ifdef BCM_53128
    /* bcm53128_A0 */
    {
        BCM53128_DEVICE_ID, BCM53128_A0_REV_ID,
        "BCM53128_A0",
        BCM53128_DEVICE_ID, BCM53128_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53128_B0 */
    {
        BCM53128_DEVICE_ID, BCM53128_B0_REV_ID,
        "BCM53128_B0",
        BCM53128_DEVICE_ID, BCM53128_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
#endif /* BCM_53128 */    
#ifdef BCM_VO_SUPPORT
    /* Voyager */
    {
        BCM53604_DEVICE_ID, BCM53600_A0_REV_ID,
        "BCM53604_A0",
        BCM53600_DEVICE_ID, BCM53600_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53603_DEVICE_ID, BCM53600_A0_REV_ID,
        "BCM53603_A0",
        BCM53600_DEVICE_ID, BCM53600_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53602_DEVICE_ID, BCM53600_A0_REV_ID,
        "BCM53602_A0",
        BCM53600_DEVICE_ID, BCM53600_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    {
        BCM53606_DEVICE_ID, BCM53600_A0_REV_ID,
        "BCM53606_A0",
        BCM53600_DEVICE_ID, BCM53600_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
#endif
#ifdef BCM_NORTHSTAR_SUPPORT
    /* bcm53010_A0 */
    {
        BCM53010_DEVICE_ID, BCM53010_A0_REV_ID,
        "BCM53010_A0",
        BCM53010_DEVICE_ID, BCM53010_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53011_A0 */
    {
        BCM53011_DEVICE_ID, BCM53010_A0_REV_ID,
        "BCM53011_A0",
        BCM53010_DEVICE_ID, BCM53010_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53012_A0 */
    {
        BCM53012_DEVICE_ID, BCM53010_A0_REV_ID,
        "BCM53012_A0",
        BCM53010_DEVICE_ID, BCM53010_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53010_A2 */
    {
        BCM53010_DEVICE_ID, BCM53010_A2_REV_ID,
        "BCM53010_A2",
        BCM53010_DEVICE_ID, BCM53010_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53011_A2 */
    {
        BCM53011_DEVICE_ID, BCM53010_A2_REV_ID,
        "BCM53011_A2",
        BCM53010_DEVICE_ID, BCM53010_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53012_A2 */
    {
        BCM53012_DEVICE_ID, BCM53010_A2_REV_ID,
        "BCM53012_A2",
        BCM53010_DEVICE_ID, BCM53010_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53017_A0 */
    {
        BCM53017_DEVICE_ID, BCM53018_A0_REV_ID,
        "BCM53017_A0",
        BCM53010_DEVICE_ID, BCM53010_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53018_A0 */
    {
        BCM53018_DEVICE_ID, BCM53018_A0_REV_ID,
        "BCM53018_A0",
        BCM53010_DEVICE_ID, BCM53010_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53019_A0 */
    {
        BCM53019_DEVICE_ID, BCM53018_A0_REV_ID,
        "BCM53019_A0",
        BCM53010_DEVICE_ID, BCM53010_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
#endif /* BCM_NORTHSTAR_SUPPORT */
#ifdef BCM_NORTHSTARPLUS_SUPPORT
    /* bcm53022_A0 */
    {
        BCM53022_DEVICE_ID, BCM53020_A0_REV_ID,
        "BCM53022_A0",
        BCM53020_DEVICE_ID, BCM53020_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53023_A0 */
    {
        BCM53023_DEVICE_ID, BCM53020_A0_REV_ID,
        "BCM53023_A0",
        BCM53020_DEVICE_ID, BCM53020_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm53025_A0 */
    {
        BCM53025_DEVICE_ID, BCM53020_A0_REV_ID,
        "BCM53025_A0",
        BCM53020_DEVICE_ID, BCM53020_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm58622_A0 */
    {
        BCM58622_DEVICE_ID, BCM53020_A0_REV_ID,
        "BCM58622_A0",
        BCM53020_DEVICE_ID, BCM53020_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm58623_A0 */
    {
        BCM58623_DEVICE_ID, BCM53020_A0_REV_ID,
        "BCM58623_A0",
        BCM53020_DEVICE_ID, BCM53020_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm58625_A0 */
    {
        BCM58625_DEVICE_ID, BCM53020_A0_REV_ID,
        "BCM58625_A0",
        BCM53020_DEVICE_ID, BCM53020_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
     /* bcm58522_A0 */
    {
        BCM58522_DEVICE_ID, BCM53020_A0_REV_ID,
        "BCM58522_A0",
        BCM53020_DEVICE_ID, BCM53020_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
    /* bcm58525_A0 */
    {
        BCM58525_DEVICE_ID, BCM53020_A0_REV_ID,
        "BCM58525_A0",
        BCM53020_DEVICE_ID, BCM53020_A0_REV_ID,
        (SOC_SPI_DEV_TYPE | SOC_SWITCH_DEV_TYPE),
    },
#endif /* BCM_NORTHSTARPLUS_SUPPORT */
        /* device of (out of band) ethernet controller */
    {
        BCM4713_DEVICE_ID, BCM4713_A0_REV_ID,
        "BCM4713_A0",
        0, 0,
        (SOC_PCI_DEV_TYPE | SOC_ETHER_DEV_TYPE)
    },    
    /* device of (out of band) ethernet controller */
    {
        BCM4713_DEVICE_ID, BCM4713_A9_REV_ID,
        "BCM4713_A9",
        BCM4713_DEVICE_ID, BCM4713_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_ETHER_DEV_TYPE)
    },
#if defined(IPROC_CMICD)
    {
        BCM53010_GMAC_DEVICE_ID, BCM53010_A0_REV_ID,
        "BCM53010_A0",
        BCM53010_GMAC_DEVICE_ID, BCM53010_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_ETHER_DEV_TYPE)
    },
#else /* defined(KEYSTONE) */
    {
        BCM53000_GMAC_DEVICE_ID, BCM53000_A0_REV_ID,
        "BCM53000_A0",
        BCM53000_GMAC_DEVICE_ID, BCM53000_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_ETHER_DEV_TYPE)
    },
#endif
#endif
#if defined(BCM_KSCPU_SUPPORT)
    /* CPU device */
    {
        BCM53000PCIE_DEVICE_ID, BCM53000_A0_REV_ID,
        "BCM53000_A0",
        BCM53000PCIE_DEVICE_ID, BCM53000_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_CPU_DEV_TYPE)
    },
#endif
#ifdef BCM_SBX_SUPPORT
    {
        QE2000_DEVICE_ID, QE2000_A1_REV_ID,
        "QE2000_A1",
        QE2000_DEVICE_ID, QE2000_A1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        QE2000_DEVICE_ID, QE2000_A2_REV_ID,
        "QE2000_A2",
        QE2000_DEVICE_ID, QE2000_A1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        QE2000_DEVICE_ID, QE2000_A3_REV_ID,
        "QE2000_A3",
        QE2000_DEVICE_ID, QE2000_A1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BME3200_DEVICE_ID, BME3200_A0_REV_ID,
        "BME3200_A0",
        BME3200_DEVICE_ID, BME3200_A0_REV_ID,
        (SOC_EB_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BME3200_DEVICE_ID, BME3200_B0_REV_ID,
        "BME3200_B0",
        BME3200_DEVICE_ID, BME3200_B0_REV_ID,
        (SOC_EB_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88020_DEVICE_ID, BCM88020_A0_REV_ID,
        "BCM88020_A0",
        BCM88020_DEVICE_ID, BCM88020_A2_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88020_DEVICE_ID, BCM88020_A1_REV_ID,
        "BCM88020_A1",
        BCM88020_DEVICE_ID, BCM88020_A2_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88020_DEVICE_ID, BCM88020_A2_REV_ID,
        "BCM88020_A2",
        BCM88020_DEVICE_ID, BCM88020_A2_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88025_DEVICE_ID, BCM88025_A0_REV_ID,
        "BCM88025_A0",
        BCM88025_DEVICE_ID, BCM88025_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88130_DEVICE_ID, BCM88130_A0_REV_ID,
        "BCM88130_A0",
        BCM88130_DEVICE_ID, BCM88130_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88130_DEVICE_ID, BCM88130_A1_REV_ID,
        "BCM88130_A1",
        BCM88130_DEVICE_ID, BCM88130_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88130_DEVICE_ID, BCM88130_B0_REV_ID,
        "BCM88130_B0",
        BCM88130_DEVICE_ID, BCM88130_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        PLX9656_DEVICE_ID, PLX9656_REV_ID,
        "PLX9656",
        PLX9656_DEVICE_ID, PLX9656_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        PLX9056_DEVICE_ID, PLX9056_REV_ID,
        "PLX9056",
        PLX9056_DEVICE_ID, PLX9056_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
#ifdef BCM_CALADAN3_SUPPORT
    {
        BCM88030_DEVICE_ID, BCM88030_A0_REV_ID,
        "BCM88030_A0",
        BCM88030_DEVICE_ID, BCM88030_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88030_DEVICE_ID, BCM88030_A1_REV_ID,
        "BCM88030_A1",
        BCM88030_DEVICE_ID, BCM88030_A1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88030_DEVICE_ID, BCM88030_B0_REV_ID,
        "BCM88030_B0",
        BCM88030_DEVICE_ID, BCM88030_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
#ifdef BCM_SIRIUS_SUPPORT
    {
        BCM88230_DEVICE_ID, BCM88230_A0_REV_ID,
        "BCM88230_A0",
        BCM88230_DEVICE_ID, BCM88230_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88231_DEVICE_ID, BCM88231_A0_REV_ID,
        "BCM88231_A0",
        BCM88230_DEVICE_ID, BCM88230_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88235_DEVICE_ID, BCM88235_A0_REV_ID,
        "BCM88235_A0",
        BCM88230_DEVICE_ID, BCM88230_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88236_DEVICE_ID, BCM88236_A0_REV_ID,
        "BCM88236_A0",
        BCM88230_DEVICE_ID, BCM88230_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88239_DEVICE_ID, BCM88239_A0_REV_ID,
        "BCM88239_A0",
        BCM88230_DEVICE_ID, BCM88230_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM56613_DEVICE_ID, BCM56613_A0_REV_ID,
        "BCM56613_A0",
        BCM88230_DEVICE_ID, BCM88230_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM56931_DEVICE_ID, BCM56931_A0_REV_ID,
        "BCM56931_A0",
        BCM88230_DEVICE_ID, BCM88230_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM56936_DEVICE_ID, BCM56936_A0_REV_ID,
        "BCM56936_A0",
        BCM88230_DEVICE_ID, BCM88230_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88230_DEVICE_ID, BCM88230_B0_REV_ID,
        "BCM88230_B0",
        BCM88230_DEVICE_ID, BCM88230_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88231_DEVICE_ID, BCM88231_B0_REV_ID,
        "BCM88231_B0",
        BCM88230_DEVICE_ID, BCM88230_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88235_DEVICE_ID, BCM88235_B0_REV_ID,
        "BCM88235_B0",
        BCM88230_DEVICE_ID, BCM88230_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88236_DEVICE_ID, BCM88236_B0_REV_ID,
        "BCM88236_B0",
        BCM88230_DEVICE_ID, BCM88230_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88239_DEVICE_ID, BCM88239_B0_REV_ID,
        "BCM88239_B0",
        BCM88230_DEVICE_ID, BCM88230_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM56613_DEVICE_ID, BCM56613_B0_REV_ID,
        "BCM56613_B0",
        BCM88230_DEVICE_ID, BCM88230_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM56931_DEVICE_ID, BCM56931_B0_REV_ID,
        "BCM56931_B0",
        BCM88230_DEVICE_ID, BCM88230_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM56936_DEVICE_ID, BCM56936_B0_REV_ID,
        "BCM56936_B0",
        BCM88230_DEVICE_ID, BCM88230_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88230_DEVICE_ID, BCM88230_C0_REV_ID,
        "BCM88230_C0",
        BCM88230_DEVICE_ID, BCM88230_C0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88231_DEVICE_ID, BCM88231_C0_REV_ID,
        "BCM88231_C0",
        BCM88230_DEVICE_ID, BCM88230_C0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88235_DEVICE_ID, BCM88235_C0_REV_ID,
        "BCM88235_C0",
        BCM88230_DEVICE_ID, BCM88230_C0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88236_DEVICE_ID, BCM88236_C0_REV_ID,
        "BCM88236_C0",
        BCM88230_DEVICE_ID, BCM88230_C0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88239_DEVICE_ID, BCM88239_C0_REV_ID,
        "BCM88239_C0",
        BCM88230_DEVICE_ID, BCM88230_C0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM56613_DEVICE_ID, BCM56613_C0_REV_ID,
        "BCM56613_C0",
        BCM88230_DEVICE_ID, BCM88230_C0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM56931_DEVICE_ID, BCM56931_C0_REV_ID,
        "BCM56931_C0",
        BCM88230_DEVICE_ID, BCM88230_C0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM56936_DEVICE_ID, BCM56936_C0_REV_ID,
        "BCM56936_C0",
        BCM88230_DEVICE_ID, BCM88230_C0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
#ifdef BCM_PETRA_SUPPORT
    {
        PETRAB_DEVICE_ID, PETRAB_A0_REV_ID,
        "PETRAB_A0",
        PETRAB_DEVICE_ID, PETRAB_A0_REV_ID,
        (SOC_EB_DEV_TYPE | SOC_SWITCH_DEV_TYPE | SOC_PCI_DEV_TYPE)
    },
    {
        ARAD_DEVICE_ID, ARAD_A0_REV_ID,
        "ARAD_A0",
        ARAD_DEVICE_ID, ARAD_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        ARAD_DEVICE_ID, ARAD_B0_REV_ID,
        "ARAD_B0",
        ARAD_DEVICE_ID, ARAD_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        ARAD_DEVICE_ID, ARAD_B1_REV_ID,
        "ARAD_B1",
        ARAD_DEVICE_ID, ARAD_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        ARADPLUS_DEVICE_ID, ARADPLUS_A0_REV_ID,
        "ARADPLUS_A0",
        ARADPLUS_DEVICE_ID, ARADPLUS_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    /* JERICHO-2-P3 */
    {
        JERICHO2_DEVICE_ID, JERICHO2_P3_REV_ID,
        "JERICHO2_P3",
        JERICHO2_DEVICE_ID, JERICHO2_P3_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88350_DEVICE_ID, BCM88350_B1_REV_ID,
        "BCM88350_B1",
        BCM88350_DEVICE_ID, BCM88350_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88351_DEVICE_ID, BCM88351_B1_REV_ID,
        "BCM88351_B1",
        BCM88351_DEVICE_ID, BCM88351_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88450_DEVICE_ID, BCM88450_B1_REV_ID,
        "BCM88450_B1",
        BCM88450_DEVICE_ID, BCM88450_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88451_DEVICE_ID, BCM88451_B1_REV_ID,
        "BCM88451_B1",
        BCM88451_DEVICE_ID, BCM88451_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88550_DEVICE_ID, BCM88550_B1_REV_ID,
        "BCM88550_B1",
        BCM88550_DEVICE_ID, BCM88550_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88551_DEVICE_ID, BCM88551_B1_REV_ID,
        "BCM88551_B1",
        BCM88551_DEVICE_ID, BCM88551_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
     {
        BCM88552_DEVICE_ID, BCM88552_B1_REV_ID,
        "BCM88552_B1",
        BCM88552_DEVICE_ID, BCM88552_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88651_DEVICE_ID, BCM88651_B1_REV_ID,
        "BCM88651_B1",
        BCM88651_DEVICE_ID, BCM88651_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88654_DEVICE_ID, BCM88654_B1_REV_ID,
        "BCM88654_B1",
        BCM88654_DEVICE_ID, BCM88654_B1_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88360_DEVICE_ID, BCM88360_A0_REV_ID,
        "BCM88360_A0",
        BCM88360_DEVICE_ID, BCM88360_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88361_DEVICE_ID, BCM88361_A0_REV_ID,
        "BCM88361_A0",
        BCM88361_DEVICE_ID, BCM88361_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88460_DEVICE_ID, BCM88460_A0_REV_ID,
        "BCM88460_A0",
        BCM88460_DEVICE_ID, BCM88460_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88461_DEVICE_ID, BCM88461_A0_REV_ID,
        "BCM88461_A0",
        BCM88461_DEVICE_ID, BCM88461_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88560_DEVICE_ID, BCM88560_A0_REV_ID,
        "BCM88560_A0",
        BCM88560_DEVICE_ID, BCM88560_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88561_DEVICE_ID, BCM88561_A0_REV_ID,
        "BCM88561_A0",
        BCM88561_DEVICE_ID, BCM88561_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
     {
        BCM88562_DEVICE_ID, BCM88562_A0_REV_ID,
        "BCM88562_A0",
        BCM88562_DEVICE_ID, BCM88562_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88661_DEVICE_ID, BCM88661_A0_REV_ID,
        "BCM88661_A0",
        BCM88661_DEVICE_ID, BCM88661_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        BCM88664_DEVICE_ID, BCM88664_A0_REV_ID,
        "BCM88664_A0",
        BCM88664_DEVICE_ID, BCM88664_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)

    },
    {
        ACP_PCI_DEVICE_ID, ACP_PCI_REV_ID,
        "ACP",
        ACP_PCI_DEVICE_ID, ACP_PCI_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
#ifdef BCM_DFE_SUPPORT
    {
        BCM88750_DEVICE_ID, BCM88750_A0_REV_ID,
        "BCM88750_A0",
        BCM88750_DEVICE_ID, BCM88750_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88750_DEVICE_ID, BCM88750_B0_REV_ID,
        "BCM88750_B0",
        BCM88750_DEVICE_ID, BCM88750_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88754_DEVICE_ID, BCM88754_A0_REV_ID,
        "BCM88754_A0",
        BCM88754_DEVICE_ID, BCM88754_A0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
    {
        BCM88755_DEVICE_ID, BCM88755_B0_REV_ID,
        "BCM88755_B0",
        BCM88755_DEVICE_ID, BCM88755_B0_REV_ID,
        (SOC_PCI_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif
#ifdef BCM_EA_SUPPORT   
#ifdef BCM_TK371X_SUPPORT
    {
        TK371X_DEVICE_ID, TK371X_A0_REV_ID,
        "TK371X_A0",
        TK371X_DEVICE_ID, TK371X_A0_REV_ID,
        (SOC_ET_DEV_TYPE | SOC_SWITCH_DEV_TYPE)
    },
#endif  /* BCM_TK371X_SUPPORT */ 
#endif    
};


/* Various control structures */

static int                      _soc_cm_init = 0;
static soc_cm_init_t            _soc_cm_init_data = { NULL, NULL, NULL };

#define AINIT()                 if (_soc_cm_init == 0) return SOC_E_INIT

/*
 * Function:    _soc_cm_find_device     (private)
 * Purpose:     Search the device table for matching device. 
 *              
 * Parameters:  dev_id - the device id of the device.
 *              rev_id - the revision id of the device.
 *
 * Returns:     NULL - device not found
 *              non-NULL - pointer to soc_cm_device_info_t table entry
 * 
 * Note:        The return value is a pointer to soc_cm_device_info_t.
 *              Positive values are valid, and should not be interpreted as error.
 *              If no device is found, NULL is returned.
 *
 * Notes:       An exact match for metal spin is not required.
 *              This routine will return the driver with the highest
 *              available metal spin.  This allows the driver to run
 *              forward-compatibly on subsequent metal spins.
 */

static const soc_cm_device_info_t *
_soc_cm_find_device(uint16 dev_id, uint16 rev_id)
{
    int                 i, tries;

    for (tries = 0; tries < 16; tries++) {
        for (i = 0; i < COUNTOF(soc_device_info); i++) {
            if (soc_device_info[i].dev_id == dev_id &&
                soc_device_info[i].rev_id == rev_id) {
                return &soc_device_info[i];
            }
        }

        if ((rev_id & 0xf) == 0) {
            rev_id |= 0xf;
        } else {
            rev_id--;
        }
    }

    return NULL;
}




/******************************************************************
 *
 *                      SOC CM CLIENT ROUTINES
 *
 * These routines are the CLIENT interface to the SOC configuration 
 * manager. The driver itself may not ca    ll these functions. 
 *
 *
 *****************************************************************/
 

/*
 * Function:    soc_cm_deinit
 * Purpose:     Deinitialize the SOC configuration manager interface
 * Parameters:  None
 *
 * Returns:     SOC_E_XXX
 */
int
soc_cm_deinit(void)
{
    sal_memset(&_soc_cm_init_data, 0, sizeof(_soc_cm_init_data));

    _soc_cm_init = 0;

    return SOC_E_NONE;
}

/*
 * Function:    soc_cm_init
 * Purpose:     Initialize the SOC configuration manager interface
 * Parameters:  init_data - initialization data. See <soc/cmtypes.h>
 *
 * Returns:     SOC_E_XXX
 *
 * Notes:
 */
int
soc_cm_init(soc_cm_init_t *init_data)
{
    if (_soc_cm_init == 0) {
        _soc_cm_init_data = *init_data;
        sal_memset(soc_cm_device, 0, sizeof(soc_cm_device));

        _soc_cm_init = 1;
    }

    return SOC_E_NONE;
}


/*
 * Function:    soc_cm_get_device_name
 * Purpose:     Return the symbolic name of a device. 
 *              
 * Parameters:  dev_id - the device id of the device.
 *              rev_id - the revision id of the device.
 *
 * Returns:     Static string
 * 
 * Note:        The return value is a device name.
 *              String values are valid, and should not be interpreted as error.
 *              If no device is found, "UNKNOWN" is returned.
 */

const char *
soc_cm_get_device_name(uint16 dev_id, uint8 rev_id)
{
    const soc_cm_device_info_t *info;

    if ((info = _soc_cm_find_device(dev_id, rev_id)) != NULL) {
        return info->dev_name;
    } else {
        return "UNKNOWN";
    }
}

/*
 * Function:    soc_cm_device_supported
 * Purpose:     Determines whether the specified chip ID is known.
 *              
 * Parameters:  dev_id - the device id of the device.
 *              rev_id - the revision id of the device.
 *
 * Returns:     SOC_E_NONE if the device is known.
 *              SOC_E_UNAVAIL if the device is not known.
 */

int
soc_cm_device_supported(uint16 dev_id, uint8 rev_id)
{
    AINIT();

    if (_soc_cm_find_device(dev_id, rev_id) == NULL) {
        return SOC_E_UNAVAIL;
    }

    return SOC_E_NONE;
}

/*
 * Function:    soc_cm_device_create_id
 * Purpose:     Create a driver device. 
 *              
 * Parameters:  dev_id - the device id of the device.
 *              rev_id - the revision id of the device.
 *              cookie - private client pointer you wish
 *                       to have passed back to you when
 *                       driver operations occur. 
 *
 * Returns:     SOC_E_XXX
 * 
 * Note:        The return value is device handle.  
 *              positive values are valid, and should not be interpreted as error.
 *              Negative values indicate an error.
 *
 * Notes:       See <soc/cmext.h> for a complete description
 *              of driver creation/initialization.
 */


int
soc_cm_device_create_id(uint16 dev_id, uint16 rev_id, void *cookie, int dev)
{
    const soc_cm_device_info_t *info;
    cm_device_t null_device;
    int dev_idx;

    AINIT();

    /*
     * User must verify soc_cm_device_supported() before trying to
     * attach.
     */

    if ((info = _soc_cm_find_device(dev_id, rev_id)) == NULL) {
        return SOC_E_UNAVAIL;
    }

    /*  Allocate device id. */ 
    sal_memset(&null_device, 0, sizeof(cm_device_t));
    if (-1 == dev) {
        for (dev_idx = 0; dev_idx < SOC_MAX_NUM_DEVICES; dev_idx++) {
            if (0 == sal_memcmp(&CMDEV(dev_idx), &null_device,
                                sizeof(cm_device_t))) {
                dev = dev_idx;
                break;
            }
        }
        if (-1 == dev) {
            return SOC_E_UNIT;
        }
    } else {
        if (0 != sal_memcmp(&CMDEV(dev), &null_device, sizeof(cm_device_t))) {
            return SOC_E_EXISTS;
        }
    }

    /*
     * The chip ID passed by the user is not necessarily equal to that
     * in table, although it may differ ONLY by metal spin.
     */

    CMDEV(dev).dev.dev = dev;
    CMDEV(dev).dev.info = info;
    CMDEV(dev).dev.cookie = cookie;
    CMDEV(dev).dev.dev_id = dev_id;           /* Record chip ID passed by user */
    CMDEV(dev).dev.rev_id = rev_id;

    soc_cm_device_count++;

    /* Keep soc_ndev in sync */
    soc_all_ndev = soc_cm_device_count;
    if (info->dev_type & SOC_SWITCH_DEV_TYPE) {
        soc_ndev ++;
#if defined(BCM_ROBO_SUPPORT)
        
        if (soc_mii_unit < 0) {
        soc_mii_unit = dev;
        }
#endif
    }

    return dev;
}

/*
 * Function:    soc_cm_device_create
 * Purpose:     Create a driver device. 
 *              
 * Parameters:  dev_id - the device id of the device.
 *              rev_id - the revision id of the device.
 *              cookie - private client pointer you wish
 *                       to have passed back to you when
 *                       driver operations occur. 
 *
 * Returns:     SOC_E_XXX
 *
 * Notes:
 *
 *      See <soc/cmext.h> for a complete description
 *      of driver creation/initialization.
 */


int
soc_cm_device_create(uint16 dev_id, uint16 rev_id, void *cookie)
{
    int dev = -1;
    int rv;

    rv = soc_cm_device_create_id(dev_id, rev_id, cookie, dev);
    if (SOC_FAILURE(rv)) {
        return (rv);
    }
    return rv;
}


/*
 * Function:    soc_cm_device_init
 * Purpose:     Initialize a SOC device. 
 *              
 * Parameters:  dev - device handle (returned by soc_cm_device_create())
 *              vectors - device access vectors
 *
 * Returns:     SOC_E_XXX
 *
 * Notes:
 *
 *      See <soc/cmtypes.h> for a complete description
 *      of driver creation/initialization.
 */

int
soc_cm_device_init(int dev, soc_cm_device_vectors_t *vectors)
{
    AINIT();

    if (CMVEC(dev).interrupt_connect == NULL || !CMVEC(dev).init) {
        CMVEC(dev).init = 1;
#define REQUIRE(vName) if (! vectors->vName) return SOC_E_PARAM
        REQUIRE(interrupt_connect);
        REQUIRE(interrupt_disconnect);
#ifdef  SOC_CM_MEMORY_BASE
        REQUIRE(base_address);
        if (vectors->base_address !=
            (SOC_CM_MEMORY_BASE + (SOC_CM_MEMORY_OFFSET*dev))) {
            soc_cm_print("soc_cm_device_init: ERROR: dev %d "
                         "compiled in base address (%#x) "
                         "does not match run time (%#x)\n",
                         dev,
                         SOC_CM_MEMORY_BASE + (SOC_CM_MEMORY_OFFSET*dev),
                         PTR_TO_INT(vectors->base_address));
            return SOC_E_PARAM;
        }
#else
#ifdef  SOC_CM_MEMORY
        REQUIRE(base_address);
#else
#ifdef  SOC_CM_FUNCTION
        REQUIRE(read);
        REQUIRE(write);
#else
        if (vectors->base_address == 0) {
            REQUIRE(read);
            REQUIRE(write);
        }
#endif  /* SOC_CM_FUNCTION */
#endif  /* SOC_CM_MEMORY */
#endif  /* SOC_CM_MEMORY_BASE */
        if (vectors->bus_type & SOC_PCI_DEV_TYPE) {
            REQUIRE(pci_conf_read);
            REQUIRE(pci_conf_write);
        }
        REQUIRE(salloc);
        REQUIRE(sfree);
#ifdef BCM_ROBO_SUPPORT
        REQUIRE(spi_read);
        REQUIRE(spi_write);
        REQUIRE(bus_type);
#endif

#undef REQUIRE

        CMVEC(dev) = *vectors;

        /* Initialize SOC driver here */
        if (CMDEV(dev).dev.info->dev_type & SOC_SWITCH_DEV_TYPE) {
                if (CMDEV(dev).dev.info->dev_type & SOC_SPI_DEV_TYPE) {                    
#if defined(BCM_ROBO_SUPPORT)
                    return soc_robo_attach(dev);
#else
                    soc_cm_debug(DK_ERR,"ERROR: ROBO devices should not be here !");
#endif
                } else if (CMDEV(dev).dev.info->dev_type & SOC_ET_DEV_TYPE) {         
#if defined(BCM_TK371X_SUPPORT)
                    return soc_ea_pre_attach(dev);
#else
                    soc_cm_debug(DK_ERR,"ERROR: EA devices should not be here !");
#endif /* BCM_TK371X_SUPPORT */
                } else if (CMDEV(dev).dev.info->dev_type & SOC_EMMI_DEV_TYPE){
                    soc_cm_debug(DK_ERR,"ERROR: EA devices should not be here !");                                    
                }else {
#if defined(BCM_SBX_SUPPORT)
                    if (SOC_IS_SBX_TYPE(CMDEV(dev).dev.info->dev_id)) {
                        return soc_sbx_attach(dev); 
                    }
#endif

#if defined(BCM_PETRA_SUPPORT)
                    if (SOC_IS_DPP_TYPE(CMDEV(dev).dev.info->dev_id)


                    ) {
                        return soc_dpp_attach(dev);
                }
#endif
#if defined(BCM_DFE_SUPPORT)
                    if (SOC_IS_DFE_TYPE(CMDEV(dev).dev.info->dev_id))
                    {
                        return soc_dfe_attach(dev);
                    } 
#endif  
#if defined(BCM_ESW_SUPPORT) 
                    return soc_attach(dev); 
#endif
            }
                
        } else if (CMDEV(dev).dev.info->dev_type & SOC_ETHER_DEV_TYPE) {
#if defined(BCM_ROBO_SUPPORT) || defined(BCM_TK371X_SUPPORT)
            return soc_eth_dma_attach(dev);
#else
            soc_cm_debug(DK_ERR,"ERROR: ROBO devices should not be here !");
#endif
#if defined(BCM_KSCPU_SUPPORT)
        } else if (CMDEV(dev).dev.info->dev_type & SOC_CPU_DEV_TYPE) {
            return SOC_E_NONE;
#endif
        }
            return SOC_E_UNIT;
    } else { 
        /* Device already initialized */
        return SOC_E_UNIT;
    }
}


/*
 * Function:    soc_cm_device_destroy
 * Purpose:     Destroy a SOC driver.
 *              
 * Parameters:  dev - device handle (returned by soc_cm_device_create())
 *
 * Returns:     SOC_E_XXX
 *
 * Notes:
 */

int
soc_cm_device_destroy(int dev)
{
    const soc_cm_device_info_t *info;
    int rv = 0;

    AINIT();

    if (!CMDEV(dev).dev.info) {
        return SOC_E_UNIT;
    }

    /* Initialize SOC driver here */
    if (CMDEV(dev).dev.info->dev_type & SOC_SWITCH_DEV_TYPE) {
        if (CMDEV(dev).dev.info->dev_type & SOC_SPI_DEV_TYPE) {                    
#if defined(BCM_ROBO_SUPPORT)
            rv = soc_robo_detach(dev);
#else
            soc_cm_debug(DK_ERR,"ERROR: ROBO devices should not be here !");
            rv = SOC_E_INTERNAL;
#endif
        } else if (CMDEV(dev).dev.info->dev_type & SOC_ET_DEV_TYPE) {
#if defined(BCM_EA_SUPPORT)
#if defined(BCM_TK371X_SUPPORT)
            soc_cm_print("FIXME: TBD: Call soc_ea_deattach(dev) here!\n");
            rv = soc_ea_detach(dev);
#endif
#else
            soc_cm_debug(DK_ERR,"ERROR: EA devices should not be here !");
            rv = SOC_E_INTERNAL;
#endif
        } else {
#if defined(BCM_SBX_SUPPORT)
            if (SOC_IS_SBX_TYPE(CMDEV(dev).dev.info->dev_id)) {
                rv = soc_sbx_detach(dev);
            } else {
#endif
#if defined(BCM_PETRA_SUPPORT)
            if (SOC_IS_DPP_TYPE(CMDEV(dev).dev.info->dev_id)) {
                rv = soc_dpp_detach(dev);
            } else {
#endif /* BCM_PETRA_SUPPORT */
#if defined(BCM_DFE_SUPPORT)
            if (SOC_IS_DFE_TYPE(CMDEV(dev).dev.info->dev_id)) {
                rv = soc_dfe_detach(dev);
            } else {
#endif /* BCM_DFE_SUPPORT */
#if defined(BCM_ESW_SUPPORT)        
                rv = soc_detach(dev); 
#endif
#if defined(BCM_DFE_SUPPORT)
            }
#endif
#if defined(BCM_PETRA_SUPPORT)
            }
#endif
#if defined(BCM_SBX_SUPPORT)
            }
#endif


#if !defined(BCM_ESW_SUPPORT) && !defined(BCM_SBX_SUPPORT) && !defined(BCM_PETRA_SUPPORT) && !defined(BCM_DFE_SUPPORT)
            soc_cm_debug(DK_ERR,"ERROR: ESW devices should not be here !");
            rv = SOC_E_INTERNAL;
#endif
        }
    } else if (CMDEV(dev).dev.info->dev_type & SOC_ETHER_DEV_TYPE) {
#if defined(BCM_ROBO_SUPPORT) || defined(BCM_TK371X_SUPPORT)
        rv = soc_eth_dma_detach(dev);
#else
        soc_cm_debug(DK_ERR,"ERROR: ROBO devices should not be here !");
        rv = SOC_E_INTERNAL;
#endif
#if defined(BCM_KSCPU_SUPPORT)
    } else if (CMDEV(dev).dev.info->dev_type & SOC_CPU_DEV_TYPE) {
            return SOC_E_NONE;
#endif
    } else {
        rv = SOC_E_INTERNAL;
    }

    info = _soc_cm_find_device(CMDEV(dev).dev.dev_id, 
                               CMDEV(dev).dev.rev_id);
    if (NULL == info) {
        return SOC_E_UNAVAIL;
    }

    /* Reset device structure.*/
    if (info->dev_type & SOC_SWITCH_DEV_TYPE) {
        soc_ndev--;
    }
    soc_cm_device_count--;
    /* Keep soc_ndev in sync */
    soc_all_ndev = soc_cm_device_count;

    sal_memset(&CMDEV(dev), 0, sizeof(cm_device_t));

    CMVEC(dev).interrupt_connect = NULL;
    CMVEC(dev).init = 0;

    return rv;
}



/******************************************************************
 *
 *                      SOC CM INTERNAL ROUTINES
 *
 * These routines are the DRIVER interface to the SOC configuration 
 * manager. These should be used only be the driver. 
 *
 *
 *****************************************************************/



/*
 * Function:    soc_cm_get_name
 * Purpose:     returns the symbolic name of the device.
 *              
 * Parameters:  dev - device handle
 *
 * Returns:     symbolic name of this device.
 * 
 * Note:        The return value is symbolic name of this device.  
 *              String values are valid, and should not be interpreted as error.
 *              Negative values indicate an error.
 */

const char *
soc_cm_get_name(int dev)
{
    return CMDEV(dev).dev.info->dev_name;
}


/*
 * Function:    soc_cm_get_dev_type
 * Purpose:     returns the type of the device.
 *      
 * Parameters:  dev - device handle
 *
 * Returns:     uint32 of the type of this device.
 * 
 * Note:        The return value is the type of this device.  
 *              Positive values are valid, and should not be interpreted as error.
 *              Negative values indicate an error.
 */

uint32
soc_cm_get_dev_type(int dev)
{
    return CMDEV(dev).dev.info->dev_type;
}


/*
 * Function:    soc_cm_get_id
 * Purpose:     Returns the real device and revision ids for this device.
 *              
 * Parameters:  dev_id - (OUTPUT) receives device id.
 *              rev_id - (OUTPUT) receives revision id.
 *
 * Returns:     SOC_E_NONE. 
 */

int
soc_cm_get_id(int dev, uint16 *dev_id, uint8 *rev_id)
{
    AINIT();

    if (dev_id) {
        *dev_id = CMDEV(dev).dev.dev_id;
    }

    if (rev_id) {
        *rev_id = CMDEV(dev).dev.rev_id;
    }

    return SOC_E_NONE;
}

/*
 * Function:    soc_cm_get_id_driver
 * Purpose:     Returns the device and revision ids of the driver to
 *              use to handle this device.
 *              
 * Parameters:  dev_id - (OUTPUT) receives device id.
 *              rev_id - (OUTPUT) receives revision id.
 *
 * Returns:     SOC_E_NONE - success
 *              SOC_E_NOT_FOUND - chip not supported
 *
 * Notes:       Several different real chip IDs may use the same driver.
 *              This routine maps real chip ID to driver chip ID.
 */

int
soc_cm_get_id_driver(uint16 dev_id, uint8 rev_id,
                     uint16 *dev_id_driver, uint8 *rev_id_driver)
{
    const soc_cm_device_info_t *info;

    if ((info = _soc_cm_find_device(dev_id, rev_id)) == NULL) {
        return SOC_E_NOT_FOUND;
    }

    if (info->dev_id_driver == 0) {
        /* This found dev/rev pair describes a regsfile */
        *dev_id_driver = info->dev_id;
        *rev_id_driver = info->rev_id;
    } else {
        /* Found info not a regsfile type, so get associated regsfile */
        *dev_id_driver = info->dev_id_driver;
        *rev_id_driver = info->rev_id_driver;
    }

    return SOC_E_NONE;
}

/*
 * Function:    soc_cm_get_num_devices
 * Purpose:     Returns the total number of created devices.
 *              
 * Parameters:  None
 *
 * Returns:     Total devices created.
 * 
 * Note:        The return value is the number of devices created.  
 *              Positive values are valid, and should not be interpreted as error.
 *              Negative values indicate an error.
 */


int
soc_cm_get_num_devices(void)
{
    return soc_cm_device_count;
}

/*
 * Function:    soc_cm_get_rcpu_cfg
 * Purpose:     Returns RCPU configurations of the device.
 *              
 * Parameters:  dev - device handle
 *              rcpu_cfg - (OUTPUT) RCPU configurations.
 *
 * Returns:     SOC_E_XXX 
 */
#ifdef INCLUDE_RCPU
int
soc_cm_get_rcpu_cfg(int dev, soc_rcpu_cfg_t *rcpu_cfg)
{
    if (NULL == CMDEV(dev).dev.cookie) {
        return SOC_E_PARAM;
    }
    *rcpu_cfg = *(soc_rcpu_cfg_t *)CMDEV(dev).dev.cookie;
    return SOC_E_NONE;
}
int
soc_cm_set_rcpu_cfg(int dev, soc_rcpu_cfg_t *rcpu_cfg)
{
    CMDEV(dev).dev.cookie = (void *)rcpu_cfg;
    return SOC_E_NONE;
}
int
soc_cm_set_rcpu_trans_tpr(int dev, rcpu_trans_ptr_t *rcpu_tp)
{
    CMVEC(dev).rcpu_tp = rcpu_tp;
    return SOC_E_NONE;
}
#endif /* INCLUDE_RCPU */
/*
 * Function:    soc_cm_interrupt_connect
 * Purpose:     Used by the driver to connect its interrupt handler 
 *              the device.
 *              
 * Parameters:  dev     - device handle
 *              handler - interrupt handler
 *              data    - isr data.
 *
 * Returns:     0 if successful
 *              <0 if failed. 
 */

int
soc_cm_interrupt_connect(int dev, soc_cm_isr_func_t handler, void *data)
{
    return CMVEC(dev).interrupt_connect(&CMDEV(dev).dev, handler, data);
}

/*
 * Function:    soc_cm_interrupt_disconnect
 * Purpose:     Used by the driver to disconnect its interrupt handler.
 *              
 * Parameters:  dev - device handle
 *
 * Returns:     0 if successful
 *              <0 if failed. 
 */

int
soc_cm_interrupt_disconnect(int dev)
{
    return CMVEC(dev).interrupt_disconnect(&CMDEV(dev).dev);
}

/*
 * Function:    soc_cm_salloc
 * Purpose:     Allocate shareable memory for communication with the device.
 *              
 * Parameters:  dev     - device handle 
 *              size    - amount of memory in bytes.
 *              name    - name of this memory (for debugging purposes only)
 *
 * Returns:     Pointer to the memory if successful, otherwise NULL.
 * 
 * Note:        The return value is a pointer to the memory.  
 *              Positive values are valid, and should not be interpreted as error.
 *              If unsuccesful, NULL is returned.
 */
void *
soc_cm_salloc(int dev, int size, const char *name)
{
    void *ptr;
    ptr = CMVEC(dev).salloc(&CMDEV(dev).dev, size, name);

    MEMLOG_ALLOC("soc_cm_salloc", ptr, size, name);

    return ptr;
}

/*
 * Function:    soc_cm_sfree
 * Purpose:     Free shared memory previously allocated with soc_cm_salloc
 *              
 * Parameters:  dev     - device handle
 *              ptr     - shared memory pointer.
 *
 * Returns:     None.
 */

void
soc_cm_sfree(int dev, void *ptr)
{
    MEMLOG_FREE("soc_cm_free", ptr);

    CMVEC(dev).sfree(&CMDEV(dev).dev, ptr);
}

/*
 * Function:    soc_cm_sflush
 * Purpose:     Perform a cache flush on a memory region, if required.
 *              
 * Parameters:  dev     - device handle
 *              addr    - memory region
 *              length  - size of region
 *
 * Returns:     SOC_E_XXX
 */

int
soc_cm_sflush(int dev, void *addr, int length)
{
    if (CMVEC(dev).sflush) {
        return CMVEC(dev).sflush(&CMDEV(dev).dev, addr, length);
    }

    return SOC_E_NONE;
}

/*
 * Function:    soc_cm_sinval
 * Purpose:     Invalidate a memory region, if required. 
 *              
 * Parameters:  dev     - device handle
 *              addr    - memory region
 *              length  - size of region
 *
 * Returns:     SOC_E_XXX
 */

int
soc_cm_sinval(int dev, void *addr, int length)
{
    if (CMVEC(dev).sinval) {
        return CMVEC(dev).sinval(&CMDEV(dev).dev, addr, length);
    }

    return SOC_E_NONE;
}

/*
 * Function:    soc_cm_l2p
 * Purpose:     Perform a logical (CPU relative) to
 *              physical (chip relative) address translation.
 *              
 * Parameters:  dev     - device handle
 *              addr    - address to translate.
 *
 * Returns:     The translated address.
 * 
 * Note:        The return value is the translated address.  
 *              Positive values are valid, and should not be interpreted as error.
 *
 *              This translation occurs in the context of driver <->
 *              chip communications. * This means that this function may
 *              have to provide more than * a virtual mapping
 *              translation -- if the device is configured to use * a
 *              different physical *bus* address as well, then this
 *              function must provide that also.
 *
 *              The intent here is to share the memory in question with
 *              the hardware, * so this function must return an address
 *              that makes sense with respect to the hardware, as well.
 */

sal_paddr_t
soc_cm_l2p(int dev, void *addr)
{
        if (CMVEC(dev).l2p) {
            return CMVEC(dev).l2p(&CMDEV(dev).dev, addr);
        }

        return (sal_paddr_t)(sal_vaddr_t)addr;

}

/*
 * Function:    soc_cm_p2l
 * Purpose:     Perform a physical (chip relative) to logical
 *              (CPU relative) address translation.
 *              
 * Parameters:  dev     - device handle
 *              addr    - address to translate.
 *
 * Returns:     The logical address.
 * 
 * Note:        The return value is the logical address.  
 *              Positive values are valid, and should not be interpreted as error.
 *
 *              See soc_cm_p2l() (above) for requirements.
 */

void*
soc_cm_p2l(int dev, sal_paddr_t addr)
{
    if (CMVEC(dev).p2l) {
        return CMVEC(dev).p2l(&CMDEV(dev).dev, addr);
    }

    return (void *)(sal_vaddr_t)addr;
}

/*
 * Function:    soc_cm_spi_read
 * Purpose:     Perform a device register read via spi interface
 *      
 * Parameters:  dev     - device handle
 *              addr    - address to read.
 *              buf     - a buffer to store the data of the read register.
 *              len     - length to read.
 *
 * Returns:     -1 if error, otherwise 0 (or actual bytes read)
 */

int
soc_cm_spi_read(int dev, uint32 addr, uint8 *buf, int len)
{
    if (CMVEC(dev).spi_read) {
        return CMVEC(dev).spi_read(&CMDEV(dev).dev, addr, buf, len);
    }

    return -1;
}

/*
 * Function:    soc_cm_spi_write
 * Purpose:     Perform a device register write via spi interface
 *      
 * Parameters:  dev     - device handle
 *              addr    - address to write.
 *              buf     - a buffer to store the data of the write register.
 *              len     - length to write.
 *
 * Returns:     -1 if error, otherwise 0 (or actual bytes written)
 */

int
soc_cm_spi_write(int dev, uint32 addr, uint8 *buf, int len)
{
    if (CMVEC(dev).spi_write) {
        return CMVEC(dev).spi_write(&CMDEV(dev).dev, addr, buf, len);
    }

    return -1;
}

/*
 * Function:    soc_cm_iproc_read
 * Purpose:     Read iProc register outside CMIC
 *      
 * Parameters:  dev     - device handle
 *              addr    - address to read 
 *
 * Returns:     Register value
 */

uint32
soc_cm_iproc_read(int dev, uint32 addr)
{
    if (CMVEC(dev).iproc_read) {
        return CMVEC(dev).iproc_read(&CMDEV(dev).dev, addr);
    }

    return 0;
}

/*
 * Function:    soc_cm_iproc_write
 * Purpose:     Write iProc register outside CMIC
 *      
 * Parameters:  dev     - device handle
 *              addr    - address to write
 *              val     - register value
 *
 * Returns:     None
 */

void
soc_cm_iproc_write(int dev, uint32 addr, uint32 val)
{
    if (CMVEC(dev).iproc_write) {
        CMVEC(dev).iproc_write(&CMDEV(dev).dev, addr, val);
    }

    return;
}

/*
 * Note:        The return value is the bus type.  
 *              Positive values are valid, and should not be interpreted as error.
 */

uint32
soc_cm_get_bus_type(int dev)
{
    return CMVEC(dev).bus_type;
}

/*
 * Function:    soc_cm_pci_conf_write
 * Purpose:     Perform a pci config write
 *      
 * Parameters:  dev     - device handle
 *              addr    - address to write.
 *              data    - double word to write
 *
 * Returns:     None
 */

void
soc_cm_pci_conf_write(int dev, uint32 addr, uint32 data)
{
    if (CMVEC(dev).pci_conf_write) {
        CMVEC(dev).pci_conf_write(&CMDEV(dev).dev, addr, data);
    }

    return;
}

/*
 * Function:    soc_cm_get_endian
 * Purpose:     Returns the required endian configuration for this device.
 *              
 * Parameters:  dev     - device handle
 *              pio     - (OUTPUT) receives the PIO endian configuration.
 *              packet  - (OUTPUT) receives the PACKET endian configuration.
 *              other   - (OUTPUT) receives the OTHER endian configuration.
 *
 * Returns:     SOC_E_XXX
 */

int
soc_cm_get_endian(int dev, int *pio, int *packet, int *other)
{
    *pio = CMVEC(dev).big_endian_pio;
    *packet = CMVEC(dev).big_endian_packet;
    *other = CMVEC(dev).big_endian_other;
    return SOC_E_NONE;
}

/*
 * Function:    soc_cm_print
 * Purpose:     Direct a message from the driver.
 *              
 * Parameters:  format  - printf-style format specifier
 *              ...     - format args 
 *
 * Returns:     SOC_E_XXX
 */

int
soc_cm_print(const char *format, ...)
{
    int rc; 
    va_list vargs;

    if (_soc_cm_init_data.debug_out == NULL) {
        return 0;
    }

    va_start(vargs, format);
    rc = _soc_cm_init_data.debug_out(0, format, vargs);
    va_end(vargs); 

    return rc; 
}

/*
 * Function:    soc_cm_vprint
 * Purpose:     Direct a message from the driver.
 *              
 * Parameters:  format  - vprintf-style format specifier
 *              vargs   - va_list 
 *
 * Returns:     SOC_E_XXX
 */

int
soc_cm_vprint(const char *format, va_list vargs)
{
    int rc; 

    if (_soc_cm_init_data.debug_out == NULL) {
        return 0;
    }

    rc = _soc_cm_init_data.debug_out(0, format, vargs);

    return rc; 
}

/*
 * Function:    soc_cm_debug
 * Purpose:     Direct debug output from the driver.
 *              
 * Parameters:  flags   - debug flags
 *              format  - printf-style format specifier. 
 *              ...     - format args
 *
 * Returns:     SOC_E_XXX
 */

int
soc_cm_debug(uint32 flags, const char *format, ...)
{
    int rc; 
    va_list vargs;

    if (_soc_cm_init_data.debug_out == NULL) {
        return 0;
    }

    va_start(vargs, format);
    rc = _soc_cm_init_data.debug_out(flags, format, vargs);
    va_end(vargs);

    return rc; 
}

/*
 * Function:    soc_cm_debug_check
 * Purpose:     Returns whether the debug specified debug state is active.
 *              
 * Parameters:  flags - debug flags representing the state in question.
 *
 * Returns:     TRUE if active, FALSE if inactive.
 * 
 * Note:        The return value is TRUE or FALSE.  
 *              Positive values are valid, and should not be interpreted as error.
 *              If FALSE, 0 is returned.
 */

int
soc_cm_debug_check(uint32 flags)
{
    if (_soc_cm_init_data.debug_check == NULL) {
        return 0;
    }
    return _soc_cm_init_data.debug_check(flags);
}

/*
 * Function:    soc_cm_dump
 * Purpose:     Output configuration information about this device.
 *              
 * Parameters:  dev - device handle
 *
 * Returns:     SOC_E_NONE
 */

int
soc_cm_dump(int dev)
{
    if (_soc_cm_init_data.debug_dump != NULL) {
        return _soc_cm_init_data.debug_dump(&CMDEV(dev).dev);
    }

    /* No dump vector provided -- output what little information we have */
    soc_cm_print("CM: Base=%p\n", (void *)CMVEC(dev).base_address);

    return SOC_E_NONE;
}

/*
 * Function:    soc_cm_config_var_get
 * Purpose:     Gets the value a register should be initialized with when the
 *              during chip initialization.
 *              
 * Parameters:  dev     - device handle
 *              name    - name of the register
 *
 * Returns:     A string version of the value.
 * 
 * Note:        The return value a string version of reg value.  
 *              String values are valid, and should not be interpreted as error.
 *              If not found, NULL is returned.
 */

char *
soc_cm_config_var_get(int dev, const char *name)
{
    if (CMVEC(dev).config_var_get == NULL) {
        return NULL;
    }
    return CMVEC(dev).config_var_get(&CMDEV(dev).dev, name);
}


/* Provided as a back door for current work-around requirements.
 * 
 * Note:        The return value is the base address.  
 *              Positive values are valid, and should not be interpreted as error.
 */

sal_vaddr_t
soc_cm_get_base_address(int dev)
{
    return CMVEC(dev).base_address;
}

/* Debug routine to display info about known chips 
 *
 * Returns:      None.
 */
void
soc_cm_display_known_devices(void)
{
    int                 i;
    uint16              dev_id_driver = 0;
    uint8               rev_id_driver = 0;

    soc_cm_print("%-8s%-16s%-16s%-16s\n",
                 "Index", "Chip", "Chip   Dev/Rev", "Driver Dev/Rev");

    for (i = 0; i < COUNTOF(soc_device_info); i++) {
        soc_cm_get_id_driver(soc_device_info[i].dev_id,
                             soc_device_info[i].rev_id,
                             &dev_id_driver, &rev_id_driver);

        soc_cm_print("%-8d%-16s0x%04x 0x%02x     0x%04x 0x%02x\n",
                     i,
                     soc_device_info[i].dev_name,
                     soc_device_info[i].dev_id,
                     soc_device_info[i].rev_id,
                     dev_id_driver,
                     rev_id_driver);
    }
}

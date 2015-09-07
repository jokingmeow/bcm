/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated from the registers file.
 * Edits to this file will be lost when it is regenerated.
 *
 * $Id: $
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
 * File:        allmems_w.i
 * Purpose:     Independent memory descriptions.
 */

#if defined(BCM_88640_A0)
    { /* SOC_MEM_INT_WAFAHALFARADDRSTATUSm */ 
        /* mem            WAFAHALFARADDRSTATUSm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ NULL,
        /* index_min   */ 0,
        /* index_max   */ 7,
        /* minblock    */ 33,
        /* maxblock    */ 33,
        /* blocks      */ 0,
        /* blocks_hi   */ 0x2,
        /* base        */ 0x14000000,
        /* gran        */ 1,
        /* bytes       */ 2,
        /* nFields     */ 2,
        /* *fields     */ soc_WAFAHALFARADDRSTATUSm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_88640_A0)
    { /* SOC_MEM_INT_WAFAHALFBRADDRSTATUSm */ 
        /* mem            WAFAHALFBRADDRSTATUSm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ NULL,
        /* index_min   */ 0,
        /* index_max   */ 7,
        /* minblock    */ 33,
        /* maxblock    */ 33,
        /* blocks      */ 0,
        /* blocks_hi   */ 0x2,
        /* base        */ 0x2c000000,
        /* gran        */ 1,
        /* bytes       */ 2,
        /* nFields     */ 2,
        /* *fields     */ soc_WAFAHALFBRADDRSTATUSm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_88640_A0)
    { /* SOC_MEM_INT_WAFBHALFARADDRSTATUSm */ 
        /* mem            WAFBHALFARADDRSTATUSm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ NULL,
        /* index_min   */ 0,
        /* index_max   */ 7,
        /* minblock    */ 33,
        /* maxblock    */ 33,
        /* blocks      */ 0,
        /* blocks_hi   */ 0x2,
        /* base        */ 0x18000000,
        /* gran        */ 1,
        /* bytes       */ 2,
        /* nFields     */ 2,
        /* *fields     */ soc_WAFAHALFARADDRSTATUSm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_88640_A0)
    { /* SOC_MEM_INT_WAFBHALFBRADDRSTATUSm */ 
        /* mem            WAFBHALFBRADDRSTATUSm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ NULL,
        /* index_min   */ 0,
        /* index_max   */ 7,
        /* minblock    */ 33,
        /* maxblock    */ 33,
        /* blocks      */ 0,
        /* blocks_hi   */ 0x2,
        /* base        */ 0x30000000,
        /* gran        */ 1,
        /* bytes       */ 2,
        /* nFields     */ 2,
        /* *fields     */ soc_WAFAHALFBRADDRSTATUSm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_88640_A0)
    { /* SOC_MEM_INT_WAFCHALFARADDRSTATUSm */ 
        /* mem            WAFCHALFARADDRSTATUSm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ NULL,
        /* index_min   */ 0,
        /* index_max   */ 7,
        /* minblock    */ 33,
        /* maxblock    */ 33,
        /* blocks      */ 0,
        /* blocks_hi   */ 0x2,
        /* base        */ 0x1c000000,
        /* gran        */ 1,
        /* bytes       */ 2,
        /* nFields     */ 2,
        /* *fields     */ soc_WAFAHALFARADDRSTATUSm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_88640_A0)
    { /* SOC_MEM_INT_WAFCHALFBRADDRSTATUSm */ 
        /* mem            WAFCHALFBRADDRSTATUSm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ NULL,
        /* index_min   */ 0,
        /* index_max   */ 7,
        /* minblock    */ 33,
        /* maxblock    */ 33,
        /* blocks      */ 0,
        /* blocks_hi   */ 0x2,
        /* base        */ 0x34000000,
        /* gran        */ 1,
        /* bytes       */ 2,
        /* nFields     */ 2,
        /* *fields     */ soc_WAFAHALFBRADDRSTATUSm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_88640_A0)
    { /* SOC_MEM_INT_WAFDHALFARADDRSTATUSm */ 
        /* mem            WAFDHALFARADDRSTATUSm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ NULL,
        /* index_min   */ 0,
        /* index_max   */ 7,
        /* minblock    */ 33,
        /* maxblock    */ 33,
        /* blocks      */ 0,
        /* blocks_hi   */ 0x2,
        /* base        */ 0x20000000,
        /* gran        */ 1,
        /* bytes       */ 2,
        /* nFields     */ 2,
        /* *fields     */ soc_WAFAHALFARADDRSTATUSm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_88640_A0)
    { /* SOC_MEM_INT_WAFDHALFBRADDRSTATUSm */ 
        /* mem            WAFDHALFBRADDRSTATUSm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ NULL,
        /* index_min   */ 0,
        /* index_max   */ 7,
        /* minblock    */ 33,
        /* maxblock    */ 33,
        /* blocks      */ 0,
        /* blocks_hi   */ 0x2,
        /* base        */ 0x38000000,
        /* gran        */ 1,
        /* bytes       */ 2,
        /* nFields     */ 2,
        /* *fields     */ soc_WAFAHALFBRADDRSTATUSm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_88640_A0)
    { /* SOC_MEM_INT_WAFEHALFARADDRSTATUSm */ 
        /* mem            WAFEHALFARADDRSTATUSm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ NULL,
        /* index_min   */ 0,
        /* index_max   */ 7,
        /* minblock    */ 33,
        /* maxblock    */ 33,
        /* blocks      */ 0,
        /* blocks_hi   */ 0x2,
        /* base        */ 0x24000000,
        /* gran        */ 1,
        /* bytes       */ 2,
        /* nFields     */ 2,
        /* *fields     */ soc_WAFAHALFARADDRSTATUSm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_88640_A0)
    { /* SOC_MEM_INT_WAFEHALFBRADDRSTATUSm */ 
        /* mem            WAFEHALFBRADDRSTATUSm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ NULL,
        /* index_min   */ 0,
        /* index_max   */ 7,
        /* minblock    */ 33,
        /* maxblock    */ 33,
        /* blocks      */ 0,
        /* blocks_hi   */ 0x2,
        /* base        */ 0x3c000000,
        /* gran        */ 1,
        /* bytes       */ 2,
        /* nFields     */ 2,
        /* *fields     */ soc_WAFAHALFBRADDRSTATUSm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_88640_A0)
    { /* SOC_MEM_INT_WAFFHALFARADDRSTATUSm */ 
        /* mem            WAFFHALFARADDRSTATUSm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ NULL,
        /* index_min   */ 0,
        /* index_max   */ 7,
        /* minblock    */ 33,
        /* maxblock    */ 33,
        /* blocks      */ 0,
        /* blocks_hi   */ 0x2,
        /* base        */ 0x28000000,
        /* gran        */ 1,
        /* bytes       */ 2,
        /* nFields     */ 2,
        /* *fields     */ soc_WAFAHALFARADDRSTATUSm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_88640_A0)
    { /* SOC_MEM_INT_WAFFHALFBRADDRSTATUSm */ 
        /* mem            WAFFHALFBRADDRSTATUSm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ NULL,
        /* index_min   */ 0,
        /* index_max   */ 7,
        /* minblock    */ 33,
        /* maxblock    */ 33,
        /* blocks      */ 0,
        /* blocks_hi   */ 0x2,
        /* base        */ 0x40000000,
        /* gran        */ 1,
        /* bytes       */ 2,
        /* nFields     */ 2,
        /* *fields     */ soc_WAFAHALFBRADDRSTATUSm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_88640_A0)
    { /* SOC_MEM_INT_WAFHALFAWADDRm */ 
        /* mem            WAFHALFAWADDRm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ NULL,
        /* index_min   */ 0,
        /* index_max   */ 47,
        /* minblock    */ 33,
        /* maxblock    */ 33,
        /* blocks      */ 0,
        /* blocks_hi   */ 0x2,
        /* base        */ 0x0c000000,
        /* gran        */ 1,
        /* bytes       */ 1,
        /* nFields     */ 1,
        /* *fields     */ soc_WAFHALFAWADDRm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_88640_A0)
    { /* SOC_MEM_INT_WAFHALFBWADDRm */ 
        /* mem            WAFHALFBWADDRm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ NULL,
        /* index_min   */ 0,
        /* index_max   */ 47,
        /* minblock    */ 33,
        /* maxblock    */ 33,
        /* blocks      */ 0,
        /* blocks_hi   */ 0x2,
        /* base        */ 0x10000000,
        /* gran        */ 1,
        /* bytes       */ 1,
        /* nFields     */ 1,
        /* *fields     */ soc_WAFHALFBWADDRm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_88640_A0)
    { /* SOC_MEM_INT_WDFMEMm */ 
        /* mem            WDFMEMm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ NULL,
        /* index_min   */ 0,
        /* index_max   */ 1023,
        /* minblock    */ 26,
        /* maxblock    */ 26,
        /* blocks      */ 0x4000000,
        /* blocks_hi   */ 0,
        /* base        */ 0x00000000,
        /* gran        */ 1,
        /* bytes       */ 67,
        /* nFields     */ 7,
        /* *fields     */ soc_WDFMEMm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_88640_A0)
    { /* SOC_MEM_INT_WDMm */ 
        /* mem            WDMm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ NULL,
        /* index_min   */ 0,
        /* index_max   */ 511,
        /* minblock    */ 14,
        /* maxblock    */ 14,
        /* blocks      */ 0x4000,
        /* blocks_hi   */ 0,
        /* base        */ 0x00000000,
        /* gran        */ 1,
        /* bytes       */ 2,
        /* nFields     */ 1,
        /* *fields     */ soc_WDMm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_56634_A0) || defined(BCM_56634_B0)
    { /* SOC_MEM_INT_WLAN_SVP_TABLEm */ 
        /* mem            WLAN_SVP_TABLEm */
        /* flags       */ SOC_MEM_FLAG_VALID |
                          SOC_MEM_FLAG_CACHABLE |
                          SOC_MEM_FLAG_SER_ECC_CORRECTABLE,     /* 0x122 */
        /* cmp_fn      */ _soc_mem_cmp_undef,
        /* *null_entry */ _soc_mem_entry_null_zeroes,
        /* index_min   */ 0,
        /* index_max   */ 2047,
        /* minblock    */ 9,
        /* maxblock    */ 9,
        /* blocks      */ 0x200,
        /* blocks_hi   */ 0,
        /* base        */ 0x020b0000,
        /* gran        */ 1,
        /* bytes       */ 5,
        /* nFields     */ 9,
        /* *fields     */ soc_WLAN_SVP_TABLEm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_56524_A0) || defined(BCM_56524_B0)
    { /* SOC_MEM_INT_WLAN_SVP_TABLE_BCM56524_A0m */ 
        /* mem            WLAN_SVP_TABLEm */
        /* flags       */ SOC_MEM_FLAG_VALID |
                          SOC_MEM_FLAG_CACHABLE |
                          SOC_MEM_FLAG_SER_ECC_CORRECTABLE,     /* 0x122 */
        /* cmp_fn      */ _soc_mem_cmp_undef,
        /* *null_entry */ _soc_mem_entry_null_zeroes,
        /* index_min   */ 0,
        /* index_max   */ 2047,
        /* minblock    */ 8,
        /* maxblock    */ 8,
        /* blocks      */ 0x100,
        /* blocks_hi   */ 0,
        /* base        */ 0x020b0000,
        /* gran        */ 1,
        /* bytes       */ 5,
        /* nFields     */ 9,
        /* *fields     */ soc_WLAN_SVP_TABLEm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_56685_A0) || defined(BCM_56685_B0)
    { /* SOC_MEM_INT_WLAN_SVP_TABLE_BCM56685_A0m */ 
        /* mem            WLAN_SVP_TABLEm */
        /* flags       */ SOC_MEM_FLAG_VALID |
                          SOC_MEM_FLAG_CACHABLE |
                          SOC_MEM_FLAG_SER_ECC_CORRECTABLE,     /* 0x122 */
        /* cmp_fn      */ _soc_mem_cmp_undef,
        /* *null_entry */ _soc_mem_entry_null_zeroes,
        /* index_min   */ 0,
        /* index_max   */ 2047,
        /* minblock    */ 6,
        /* maxblock    */ 6,
        /* blocks      */ 0x40,
        /* blocks_hi   */ 0,
        /* base        */ 0x020b0000,
        /* gran        */ 1,
        /* bytes       */ 5,
        /* nFields     */ 9,
        /* *fields     */ soc_WLAN_SVP_TABLEm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_88230_A0) || defined(BCM_88230_B0) || \
    defined(BCM_88230_C0)
    { /* SOC_MEM_INT_WRED_AVG_QUEUE_LENGTHm */ 
        /* mem            WRED_AVG_QUEUE_LENGTHm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ _soc_mem_entry_null_zeroes,
        /* index_min   */ 0,
        /* index_max   */ 32767,
        /* minblock    */ 27,
        /* maxblock    */ 27,
        /* blocks      */ 0x8000000,
        /* blocks_hi   */ 0,
        /* base        */ 0x05000000,
        /* gran        */ 1,
        /* bytes       */ 4,
        /* nFields     */ 4,
        /* *fields     */ soc_WRED_AVG_QUEUE_LENGTHm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_88230_A0) || defined(BCM_88230_B0) || \
    defined(BCM_88230_C0)
    { /* SOC_MEM_INT_WRED_CURVEm */ 
        /* mem            WRED_CURVEm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ _soc_mem_entry_null_zeroes,
        /* index_min   */ 0,
        /* index_max   */ 2047,
        /* minblock    */ 27,
        /* maxblock    */ 27,
        /* blocks      */ 0x8000000,
        /* blocks_hi   */ 0,
        /* base        */ 0x04000000,
        /* gran        */ 1,
        /* bytes       */ 10,
        /* nFields     */ 8,
        /* *fields     */ soc_WRED_CURVEm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */

#if defined(BCM_88230_A0) || defined(BCM_88230_B0) || \
    defined(BCM_88230_C0)
    { /* SOC_MEM_INT_WRED_STATEm */ 
        /* mem            WRED_STATEm */
        /* flags       */ SOC_MEM_FLAG_VALID,   /* 0x2 */
        /* cmp_fn      */ NULL,
        /* *null_entry */ _soc_mem_entry_null_zeroes,
        /* index_min   */ 0,
        /* index_max   */ 32767,
        /* minblock    */ 27,
        /* maxblock    */ 27,
        /* blocks      */ 0x8000000,
        /* blocks_hi   */ 0,
        /* base        */ 0x03000000,
        /* gran        */ 1,
        /* bytes       */ 6,
        /* nFields     */ 11,
        /* *fields     */ soc_WRED_STATEm_fields,
        /* *views      */ NULL,
        /* snoop_cb    */ NULL, 
        /* snoop_user_data */ NULL, 
        /* snoop_flags */ 0,
    },
#endif /* chips */


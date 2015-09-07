/*
 * $Id: stat.h 1.15 Broadcom SDK $
 * 
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
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated.
 * Edits to this file will be lost when it is regenerated.
 */

#ifndef __BCMX_STAT_H__
#define __BCMX_STAT_H__

#include <bcm/types.h>
#include <bcmx/bcmx.h>
#include <bcm/stat.h>

/* Initialize the Statistics module. */
extern int bcmx_stat_init(void);

/* Clear the port-based statistics for the indicated device port. */
extern int bcmx_stat_clear(
    bcmx_lport_t port);

/* Synchronize software counters with hardware. */
extern int bcmx_stat_sync(void);

/* Get the specified statistics from the device. */
extern int bcmx_stat_get(
    bcmx_lport_t port, 
    bcm_stat_val_t type, 
    uint64 *value);

/* Get the specified statistics from the device. */
extern int bcmx_stat_get32(
    bcmx_lport_t port, 
    bcm_stat_val_t type, 
    uint32 *value);

/* Get the specified statistics. */
extern int bcmx_stat_multi_get(
    bcm_gport_t port, 
    int nstat, 
    bcm_stat_val_t *stat_arr, 
    uint64 *value_arr);

/* 
 * Get the specified statistics.  The 64-bit values may be truncated to
 * fit.
 */
extern int bcmx_stat_multi_get32(
    bcm_gport_t port, 
    int nstat, 
    bcm_stat_val_t *stat_arr, 
    uint32 *value_arr);

/* Set/get debug counter to count certain packet types. */
extern int bcmx_stat_custom_set(
    bcmx_lport_t port, 
    bcm_stat_val_t type, 
    uint32 flags);

/* Set/get debug counter to count certain packet types. */
extern int bcmx_stat_custom_get(
    bcmx_lport_t port, 
    bcm_stat_val_t type, 
    uint32 *flags);

/* Add a certain packet type to debug counter to count. */
extern int bcmx_stat_custom_add(
    bcmx_lport_t port, 
    bcm_stat_val_t type, 
    bcm_custom_stat_trigger_t trigger);

/* Delete the specified packet type from debug counter. */
extern int bcmx_stat_custom_delete(
    bcmx_lport_t port, 
    bcm_stat_val_t type, 
    bcm_custom_stat_trigger_t trigger);

/* Delete all packet types from debug counter. */
extern int bcmx_stat_custom_delete_all(
    bcmx_lport_t port, 
    bcm_stat_val_t type);

/* Check if specified packet types is part of debug counter. */
extern int bcmx_stat_custom_check(
    bcmx_lport_t port, 
    bcm_stat_val_t type, 
    bcm_custom_stat_trigger_t trigger, 
    int *result);

#endif /* __BCMX_STAT_H__ */

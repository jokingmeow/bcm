/*
 * $Id: qos.h 1.8 Broadcom SDK $
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

#ifndef __BCMX_QOS_H__
#define __BCMX_QOS_H__

#include <bcm/types.h>
#include <bcmx/bcmx.h>
#include <bcm/qos.h>

/* QoS Map Structure */
typedef bcm_qos_map_t bcmx_qos_map_t;

/* Initialize the QoS Map structure. */
extern void bcmx_qos_map_t_init(
    bcmx_qos_map_t *qos_map);

/* Initialize the QoS subsystem. */
extern int bcmx_qos_init(void);

/* Detach the QoS software module. */
extern int bcmx_qos_detach(void);

extern int bcmx_qos_map_create(
    uint32 flags, 
    int *map_id);

extern int bcmx_qos_map_destroy(
    int map_id);

extern int bcmx_qos_map_add(
    uint32 flags, 
    bcmx_qos_map_t *map, 
    int map_id);

extern int bcmx_qos_map_delete(
    uint32 flags, 
    bcmx_qos_map_t *map, 
    int map_id);

extern int bcmx_qos_map_multi_get(
    uint32 flags, 
    int map_id, 
    int array_size, 
    bcmx_qos_map_t *array, 
    int *array_count);

extern int bcmx_qos_port_map_set(
    bcm_gport_t port, 
    int ing_map, 
    int egr_map);

extern int bcmx_qos_port_map_get(
    bcm_gport_t port, 
    int *ing_map, 
    int *egr_map);

extern int bcmx_qos_port_vlan_map_set(
    bcm_gport_t port, 
    bcm_vlan_t vid, 
    int ing_map, 
    int egr_map);

extern int bcmx_qos_port_vlan_map_get(
    bcm_gport_t port, 
    bcm_vlan_t vid, 
    int *ing_map, 
    int *egr_map);

extern int bcmx_qos_multi_get(
    int array_size, 
    int *map_ids_array, 
    int *flags_array, 
    int *array_count);

#endif /* __BCMX_QOS_H__ */

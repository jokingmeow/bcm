/*
 * $Id: 1b1e8dcec3c4fdc23469952520389f309af78a31 $
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

#ifndef __BCMX_TRUNK_H__
#define __BCMX_TRUNK_H__

#include <bcm/types.h>
#include <bcmx/bcmx.h>
#include <bcmx/lplist.h>
#include <bcm/trunk.h>

/* 
 * Trunk group port addition structure, describes all the ports to be
 * added to a trunk group.
 */
typedef struct bcmx_trunk_add_info_s {
    int psc;                /* Port selection criteria. */
    int ipmc_psc;           /* Port selection criteria for software IPMC trunk
                               resolution. */
    bcmx_lport_t dlf_port;  /* DLF/broadcast port for trunk group. */
    bcmx_lport_t mc_port;   /* Multicast port for trunk group. */
    bcmx_lport_t ipmc_port; /* IPMC port for trunk group. */
    bcmx_lplist_t ports;    /* Ports in trunk. */
} bcmx_trunk_add_info_t;

/* Trunk Member structure */
typedef bcm_trunk_member_t bcmx_trunk_member_t;

/* Initialize bcmx_trunk_add_info_t and allocate port list. */
extern void bcmx_trunk_add_info_t_init(
    bcmx_trunk_add_info_t *trunk_add_info);

/* Deallocate port list in bcmx_trunk_add_info_t. */
extern void bcmx_trunk_add_info_t_free(
    bcmx_trunk_add_info_t *trunk_add_info);

/* Initialize the Trunk Member structure. */
extern void bcmx_trunk_member_t_init(
    bcmx_trunk_member_t *trunk_member);

/* Initialize the Trunk module. */
extern int bcmx_trunk_init(void);

/* Shut down the Trunk module. */
extern int bcmx_trunk_detach(void);

/* 
 * Create the software data structure for a new trunk, using next
 * available trunk ID.
 */
extern int bcmx_trunk_create(
    bcm_trunk_t *tid);

/* 
 * Create the software data structure for a new trunk, using the
 * specified trunk ID.
 */
extern int bcmx_trunk_create_id(
    bcm_trunk_t tid);

/* Backward compatibility. */
#define bcmx_trunk_create_with_tid  bcmx_trunk_create_id 

/* Get a trunk's Port Selection Criteria (PSC). */
extern int bcmx_trunk_psc_get(
    bcm_trunk_t tid, 
    int *psc);

/* Set a trunk's Port Selection Criteria (PSC). */
extern int bcmx_trunk_psc_set(
    bcm_trunk_t tid, 
    int psc);

/* Gets the system trunk limits. */
extern int bcmx_trunk_chip_info_get(
    bcm_trunk_chip_info_t *ta_info);

/* Get the current parameters for the specified trunk group. */
extern int bcmx_trunk_get(
    bcm_trunk_t tid, 
    bcmx_trunk_add_info_t *t_data);

/* Add ports to a trunk group. */
extern int bcmx_trunk_set(
    bcm_trunk_t tid, 
    bcmx_trunk_add_info_t *add_info);

/* Removes a trunk group. */
extern int bcmx_trunk_destroy(
    bcm_trunk_t tid);

/* Add the specified trunk group to an existing MAC multicast entry. */
extern int bcmx_trunk_mcast_join(
    bcm_trunk_t tid, 
    bcm_vlan_t vid, 
    bcm_mac_t mac);

/* 
 * Retrieve the current bitmap of ports for which switching is enabled
 * for trunking.
 */
extern int bcmx_trunk_egress_get(
    bcm_trunk_t tid, 
    bcmx_lplist_t *lplist);

/* Restrict trunk traffic only to specified trunk member ports. */
extern int bcmx_trunk_egress_set(
    bcm_trunk_t tid, 
    bcmx_lplist_t lplist);

/* Get the trunk group ID for a given system port. */
extern int bcmx_trunk_find(
    bcmx_lport_t port, 
    bcm_trunk_t *tid);

/* Assign the failover port list for a specific trunk port. */
extern int bcmx_trunk_failover_set(
    bcm_trunk_t tid, 
    bcm_gport_t failport, 
    int psc, 
    uint32 flags, 
    int count, 
    bcm_gport_t *fail_to_array);

/* Retrieve the failover port list for a specific trunk port. */
extern int bcmx_trunk_failover_get(
    bcm_trunk_t tid, 
    bcm_gport_t failport, 
    int *psc, 
    uint32 *flags, 
    int array_size, 
    bcm_gport_t *fail_to_array, 
    int *array_count);

/* Add a member to a trunk group */
extern int bcmx_trunk_member_add(
    bcm_trunk_t tid, 
    bcmx_trunk_member_t *member);

/* Delete a member from a trunk group */
extern int bcmx_trunk_member_delete(
    bcm_trunk_t tid, 
    bcmx_trunk_member_t *member);

/* Delete all members from a trunk group */
extern int bcmx_trunk_member_delete_all(
    bcm_trunk_t tid);

/* Assign a set of members to a trunk group */
extern int bcmx_trunk_member_set(
    bcm_trunk_t tid, 
    int member_count, 
    bcmx_trunk_member_t *member_array);

/* Get members of a trunk group */
extern int bcmx_trunk_member_get(
    bcm_trunk_t tid, 
    int member_max, 
    bcmx_trunk_member_t *member_array, 
    int *member_count);

#endif /* __BCMX_TRUNK_H__ */

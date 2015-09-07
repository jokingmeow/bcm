/*
 * $Id: failover.h 1.21 Broadcom SDK $
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

#ifndef __BCM_FAILOVER_H__
#define __BCM_FAILOVER_H__

#include <bcm/types.h>

/* BCM_FAILOVER_* flags. */
#define BCM_FAILOVER_WITH_ID        (1 << 0)   /* flag to create a failover
                                                  object whose Id is passed */
#define BCM_FAILOVER_REPLACE        (1 << 1)   /* flag to update a failover
                                                  object whose Id is passed */
#define BCM_FAILOVER_CLEAR          (1 << 2)   /* flag to clear the failover
                                                  state */
#define BCM_FAILOVER_LOOKUP_DISABLE (1 << 3)   /* flag to enable flooding by
                                                  disabling l2 lookup */
#define BCM_FAILOVER_LEARN_DISABLE  (1 << 4)   /* flag to disable learning while
                                                  failover is in progress */
#define BCM_FAILOVER_ID_LOCAL       -2         /* failover ID */
#define BCM_FAILOVER_L2_LOOKUP      (1 << 5)   /* flag to create a failover
                                                  object for L2 lookup (fast
                                                  flush) */

/* Invalid L3 Ingress Interface */
#define BCM_FAILOVER_INVALID    0xFFFF     /* Invalid Failover Index */

#if defined(INCLUDE_L3)
/* Failover Element Structure. */
typedef struct bcm_failover_element_s {
    uint32 flags;               /* flags */
    bcm_gport_t port;           /* MPLS/MiM/VLAN gport */
    bcm_failover_t failover_id; /* Failover Object Index. */
    bcm_if_t intf;              /* Egress Object index. */
} bcm_failover_element_t;
#endif

#if defined(INCLUDE_L3)
/* Initialize the Failover element structure. */
extern void bcm_failover_element_t_init(
    bcm_failover_element_t *failover);
#endif

#ifndef BCM_HIDE_DISPATCHABLE

#if defined(INCLUDE_L3)
/* Initialize failover module. */
extern int bcm_failover_init(
    int unit);
#endif

#if defined(INCLUDE_L3)
/* Detach failover module. */
extern int bcm_failover_cleanup(
    int unit);
#endif

#if defined(INCLUDE_L3)
/* Create a failover object. */
extern int bcm_failover_create(
    int unit, 
    uint32 flags, 
    bcm_failover_t *failover_id);
#endif

#if defined(INCLUDE_L3)
/* Destroy a failover object. */
extern int bcm_failover_destroy(
    int unit, 
    bcm_failover_t failover_id);
#endif

#if defined(INCLUDE_L3)
/* 
 * Set a failover object to enable or disable (note that failover object
 * 0 is reserved.
 */
extern int bcm_failover_set(
    int unit, 
    bcm_failover_t failover_id, 
    int enable);
#endif

#if defined(INCLUDE_L3)
/* 
 * Set a failover object to enable or disable (note that failover object
 * 0 is reserved.
 */
extern int bcm_failover_status_set(
    int unit, 
    bcm_failover_element_t *failover, 
    int enable);
#endif

#if defined(INCLUDE_L3)
/* Get the enable status of a failover object. */
extern int bcm_failover_get(
    int unit, 
    bcm_failover_t failover_id, 
    int *enable);
#endif

#if defined(INCLUDE_L3)
/* 
 * Get a failover object to enable or disable (note that failover object
 * 0 is reserved.
 */
extern int bcm_failover_status_get(
    int unit, 
    bcm_failover_element_t *failover, 
    int *enable);
#endif

#endif /* BCM_HIDE_DISPATCHABLE */

/* Failover Ring Structure. */
typedef struct bcm_failover_ring_s {
    uint32 flags;                   /* flags */
    bcm_vlan_vector_t vlan_vector;  /* List of Vlans. */
    bcm_gport_t port0;              /* VLAN gport */
    bcm_gport_t port1;              /* VLAN gport */
} bcm_failover_ring_t;

/* Initialize the Failover ring structure. */
extern void bcm_failover_ring_t_init(
    bcm_failover_ring_t *failover);

#ifndef BCM_HIDE_DISPATCHABLE

/* Set the failover ring configuration. */
extern int bcm_failover_ring_config_set(
    int unit, 
    bcm_failover_ring_t *failover_ring);

/* Get the failover ring configuration. */
extern int bcm_failover_ring_config_get(
    int unit, 
    bcm_failover_ring_t *failover_ring);

#endif /* BCM_HIDE_DISPATCHABLE */

#endif /* __BCM_FAILOVER_H__ */

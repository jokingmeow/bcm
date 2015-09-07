/*
 * $Id: ipmc.h 1.28 Broadcom SDK $
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

#ifndef __BCMX_IPMC_H__
#define __BCMX_IPMC_H__

#if defined(INCLUDE_L3)

#include <bcm/types.h>
#include <bcmx/bcmx.h>
#include <bcmx/lplist.h>
#include <bcm/ipmc.h>

/* IPMC address type. */
typedef struct bcmx_ipmc_addr_s {
    bcm_ip_t s_ip_addr;             /* IPv4 Source address. */
    bcm_ip_t mc_ip_addr;            /* IPv4 Destination address. */
    bcm_ip6_t s_ip6_addr;           /* IPv6 Source address. */
    bcm_ip6_t mc_ip6_addr;          /* IPv6 Destination address. */
    bcm_vlan_t vid;                 /* VLAN identifier. */
    bcm_vrf_t vrf;                  /* Virtual Router Instance. */
    bcm_cos_t cos;                  /* COS based on dst IP multicast addr. */
    bcmx_lplist_t l2_ports;         /* L2 Port list. */
    bcmx_lplist_t l2_untag_ports;   /* L2 Untag port list. */
    bcmx_lplist_t l3_ports;         /* L3 Port list. */
    int ts;                         /* Source port or TGID bit. */
    bcmx_lport_t port_tgid;         /* Source port or TGID. */
    int v;                          /* Valid bit. */
    int ipmc_index;                 /* Use this index to program IPMC table for
                                       XGS chips based on flags value. For SBX
                                       chips it is the Multicast Group index */
    uint32 flags;                   /* See BCM_IPMC_XXX flag definitions. */
    int lookup_class;               /* Classification lookup class ID. */
} bcmx_ipmc_addr_t;

/* Initialize the IPMC subsystem. */
extern int bcmx_ipmc_init(void);

/* Detach the IPMC subsystem. */
extern int bcmx_ipmc_detach(void);

/* Enable/disable IPMC support. */
extern int bcmx_ipmc_enable(
    int enable);

/* Initialize bcmx_ipmc_addr_t and allocate port lists. */
extern void bcmx_ipmc_addr_t_init(
    bcmx_ipmc_addr_t *data);

/* Deallocate port lists in bcmx_ipmc_addr_t. */
extern void bcmx_ipmc_addr_t_free(
    bcmx_ipmc_addr_t *data);

/* Backward compatibility. */
#define bcmx_ipmc_addr_free     bcmx_ipmc_addr_t_free 

/* Add new IPMC group. */
extern int bcmx_ipmc_add(
    bcmx_ipmc_addr_t *data);

/* Find info of an IPMC group. */
extern int bcmx_ipmc_find(
    bcmx_ipmc_addr_t *data);

/* Remove IPMC group. */
extern int bcmx_ipmc_remove(
    bcmx_ipmc_addr_t *data);

/* Remove all IPMC groups. */
extern int bcmx_ipmc_remove_all(void);

/* Reinitialize/clear the egress IP multicast configuration. */
extern int bcmx_ipmc_egress_port_init(void);

/* Configure the IP Multicast egress properties. */
extern int bcmx_ipmc_egress_port_set(
    bcmx_lport_t port, 
    const bcm_mac_t mac, 
    int untag, 
    bcm_vlan_t vid, 
    int ttl_threshold);

/* Get the egress IP multicast configuration properties. */
extern int bcmx_ipmc_egress_port_get(
    bcmx_lport_t port, 
    bcm_mac_t mac, 
    int *untag, 
    bcm_vlan_t *vid, 
    int *ttl_threshold);

/* Get the combined IP multicast statistics. */
extern int bcmx_ipmc_counters_get(
    bcmx_lport_t port, 
    bcm_ipmc_counters_t *counters);

/* Age unused ipmc table entries. */
extern int bcmx_ipmc_age(
    uint32 flags, 
    bcm_ipmc_traverse_cb age_cb, 
    void *user_data);

/* 
 * Traverse through the ipmc table and run callback at each valid ipmc
 * entry.
 */
extern int bcmx_ipmc_traverse(
    uint32 flags, 
    bcm_ipmc_traverse_cb cb, 
    void *user_data);

#endif /* defined(INCLUDE_L3) */

#endif /* __BCMX_IPMC_H__ */

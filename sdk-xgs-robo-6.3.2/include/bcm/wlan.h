/*
 * $Id: wlan.h 1.16 Broadcom SDK $
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

#ifndef __BCM_WLAN_H__
#define __BCM_WLAN_H__

#if defined(INCLUDE_L3)

#include <bcm/types.h>
#include <bcm/multicast.h>
#include <bcm/l3.h>
#include <bcm/tunnel.h>

/* WLAN Port Flags. */
#define BCM_WLAN_PORT_WITH_ID               0x00000001 
#define BCM_WLAN_PORT_REPLACE               0x00000002 
#define BCM_WLAN_PORT_DROP                  0x00000004 
#define BCM_WLAN_PORT_NETWORK               0x00000008 
#define BCM_WLAN_PORT_BSSID                 0x00000010 
#define BCM_WLAN_PORT_BSSID_RADIO           0x00000020 
#define BCM_WLAN_PORT_MATCH_TUNNEL          0x00000040 
#define BCM_WLAN_PORT_EGRESS_CLIENT_MULTICAST 0x00000080 
#define BCM_WLAN_PORT_EGRESS_BSSID          0x00000100 
#define BCM_WLAN_PORT_EGRESS_TUNNEL_REMOTE  0x00000200 
#define BCM_WLAN_PORT_ROAM_ENABLE           0x00000400 

/* WLAN Port structure. */
typedef struct bcm_wlan_port_s {
    uint32 flags;               /* Configuration flags */
    bcm_gport_t wlan_port_id;   /* WLAN port number */
    bcm_gport_t port;           /* Physical port / trunk. */
    int if_class;               /* Interface class ID. */
    bcm_mac_t bssid;            /* BSSID */
    int radio;                  /* Radio ID */
    bcm_gport_t match_tunnel;   /* Ingress Tunnel ID */
    bcm_gport_t egress_tunnel;  /* Egress Tunnel ID */
    uint16 client_multicast;    /* Client multicast bitmap */
    bcm_if_t encap_id;          /* Encap identifier. */
} bcm_wlan_port_t;

/* WLAN Client Database Flags. */
#define BCM_WLAN_CLIENT_REPLACE     0x00000001 
#define BCM_WLAN_CLIENT_ROAMED_IN   0x00000002 
#define BCM_WLAN_CLIENT_ROAMED_OUT  0x00000004 
#define BCM_WLAN_CLIENT_AUTHORIZED  0x00000008 
#define BCM_WLAN_CLIENT_CAPTIVE     0x00000010 

/* WLAN Client structure. */
typedef struct bcm_wlan_client_s {
    uint32 flags;               /* Configuration flags */
    bcm_gport_t wlan_port_id;   /* WLAN port number */
    bcm_mac_t mac;              /* Client MAC Address */
    bcm_gport_t home_agent;     /* The home agent */
    bcm_gport_t wtp;            /* The access point */
} bcm_wlan_client_t;

/* Initialize the WLAN port structure. */
extern void bcm_wlan_port_t_init(
    bcm_wlan_port_t *wlan_port);

/* Initialize the WLAN client structure. */
extern void bcm_wlan_client_t_init(
    bcm_wlan_client_t *wlan_client);

#ifndef BCM_HIDE_DISPATCHABLE

/* Initialize the BCM WLAN subsystem. */
extern int bcm_wlan_init(
    int unit);

/* Detach the WLAN software module. */
extern int bcm_wlan_detach(
    int unit);

/* bcm_wlan_port_add */
extern int bcm_wlan_port_add(
    int unit, 
    bcm_wlan_port_t *info);

/* bcm_wlan_port_delete */
extern int bcm_wlan_port_delete(
    int unit, 
    bcm_gport_t wlan_port_id);

/* bcm_wlan_port_delete_all */
extern int bcm_wlan_port_delete_all(
    int unit);

/* bcm_mim_port_get */
extern int bcm_wlan_port_get(
    int unit, 
    bcm_gport_t wlan_port_id, 
    bcm_wlan_port_t *info);

#endif /* BCM_HIDE_DISPATCHABLE */

/* WLAN port callback function prototype. */
typedef int (*bcm_wlan_port_traverse_cb)(
    int unit, 
    bcm_wlan_port_t *info, 
    void *user_data);

#ifndef BCM_HIDE_DISPATCHABLE

/* bcm_wlan_port_traverse */
extern int bcm_wlan_port_traverse(
    int unit, 
    bcm_wlan_port_traverse_cb cb, 
    void *user_data);

/* bcm_wlan_client_add */
extern int bcm_wlan_client_add(
    int unit, 
    bcm_wlan_client_t *info);

/* bcm_wlan_client_delete */
extern int bcm_wlan_client_delete(
    int unit, 
    bcm_mac_t mac);

/* bcm_wlan_client_delete_all */
extern int bcm_wlan_client_delete_all(
    int unit);

/* bcm_wlan_client_get */
extern int bcm_wlan_client_get(
    int unit, 
    bcm_mac_t mac, 
    bcm_wlan_client_t *info);

#endif /* BCM_HIDE_DISPATCHABLE */

/* WLAN client callback function prototype. */
typedef int (*bcm_wlan_client_traverse_cb)(
    int unit, 
    bcm_wlan_client_t *info, 
    void *user_data);

#ifndef BCM_HIDE_DISPATCHABLE

/* bcm_wlan_client_traverse */
extern int bcm_wlan_client_traverse(
    int unit, 
    bcm_wlan_client_traverse_cb cb, 
    void *user_data);

/* Set the tunneling initiator parameters for a WLAN tunnel. */
extern int bcm_wlan_tunnel_initiator_create(
    int unit, 
    bcm_tunnel_initiator_t *info);

/* Delete an outgoing WLAN tunnel. */
extern int bcm_wlan_tunnel_initiator_destroy(
    int unit, 
    bcm_gport_t wlan_tunnel_id);

/* Get the tunnel properties for an outgoing WLAN tunnel. */
extern int bcm_wlan_tunnel_initiator_get(
    int unit, 
    bcm_tunnel_initiator_t *info);

#endif /* defined(INCLUDE_L3) */

#endif /* BCM_HIDE_DISPATCHABLE */

#endif /* __BCM_WLAN_H__ */

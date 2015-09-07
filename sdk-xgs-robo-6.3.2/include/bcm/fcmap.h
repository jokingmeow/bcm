/*
 * $Id: fcmap.h 1.14 Broadcom SDK $
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

#ifndef __BCM_FCMAP_H__
#define __BCM_FCMAP_H__

#if defined(INCLUDE_FCMAP)

#include <bcm/types.h>
#include <bfcmap.h>

typedef _shr_bfcmap_dev_addr_t bcm_fcmap_dev_addr_t;

typedef enum bcm_fcmap_dir_e {
    BCM_FCMAP_DIR_EGRESS = _SHR_BFCMAP_DIR_EGRESS, 
    BCM_FCMAP_DIR_INGRESS = _SHR_BFCMAP_DIR_INGRESS 
} bcm_fcmap_dir_t;

typedef enum bcm_fcmap_core_e {
    BCM_FCMAP_CORE_BCM84756 = _SHR_BFCMAP_CORE_BCM84756 
} bcm_fcmap_core_t;

typedef enum bcm_fcmap_port_mode_e {
    BCM_FCMAP_FCOE_TO_FC_MODE = _SHR_BFCMAP_FCOE_TO_FC_MODE, 
    BCM_FCMAP_FCOE_TO_FCOE_MODE = _SHR_BFCMAP_FCOE_TO_FCOE_MODE 
} bcm_fcmap_port_mode_t;

typedef enum bcm_fcmap_port_speed_e {
    BCM_FCMAP_PORT_SPEED_AN = _SHR_BFCMAP_PORT_SPEED_AN, 
    BCM_FCMAP_PORT_SPEED_2GBPS = _SHR_BFCMAP_PORT_SPEED_2GBPS, 
    BCM_FCMAP_PORT_SPEED_4GBPS = _SHR_BFCMAP_PORT_SPEED_4GBPS, 
    BCM_FCMAP_PORT_SPEED_8GBPS = _SHR_BFCMAP_PORT_SPEED_8GBPS, 
    BCM_FCMAP_PORT_SPEED_16GBPS = _SHR_BFCMAP_PORT_SPEED_16GBPS, 
    BCM_FCMAP_PORT_SPEED_AN_2GBPS = _SHR_BFCMAP_PORT_SPEED_AN_2GBPS, 
    BCM_FCMAP_PORT_SPEED_AN_4GBPS = _SHR_BFCMAP_PORT_SPEED_AN_4GBPS, 
    BCM_FCMAP_PORT_SPEED_AN_8GBPS = _SHR_BFCMAP_PORT_SPEED_AN_8GBPS, 
    BCM_FCMAP_PORT_SPEED_AN_16GBPS = _SHR_BFCMAP_PORT_SPEED_AN_16GBPS, 
    BCM_FCMAP_PORT_SPEED_MAX_COUNT = _SHR_BFCMAP_PORT_SPEED_MAX_COUNT 
} bcm_fcmap_port_speed_t;

typedef enum bcm_fcmap_port_state_e {
    BCM_FCMAP_PORT_STATE_INIT = _SHR_BFCMAP_PORT_STATE_INIT, 
    BCM_FCMAP_PORT_STATE_RESET = _SHR_BFCMAP_PORT_STATE_RESET, 
    BCM_FCMAP_PORT_STATE_ACTIVE = _SHR_BFCMAP_PORT_STATE_ACTIVE, 
    BCM_FCMAP_PORT_STATE_LINKDOWN = _SHR_BFCMAP_PORT_STATE_LINKDOWN, 
    BCM_FCMAP_PORT_STATE_DISABLE = _SHR_BFCMAP_PORT_STATE_DISABLE, 
    BCM_FCMAP_PORT_STATE_MAX_COUNT = _SHR_BFCMAP_PORT_STATE_MAX_COUNT 
} bcm_fcmap_port_state_t;

typedef enum bcm_fcmap_encap_mac_address_e {
    BCM_FCMAP_ENCAP_FCOE_FPMA = _SHR_BFCMAP_ENCAP_FCOE_FPMA, 
    BCM_FCMAP_ENCAP_FCOE_ETH_ADDRESS_NULL = _SHR_BFCMAP_ENCAP_FCOE_ETH_ADDRESS_NULL, 
    BCM_FCMAP_ENCAP_FCOE_ETH_ADDRESS_USER = _SHR_BFCMAP_ENCAP_FCOE_ETH_ADDRESS_USER 
} bcm_fcmap_encap_mac_address_t;

typedef enum bcm_fcmap_8g_fw_on_active_e {
    BCM_FCMAP_8G_FW_ON_ACTIVE_ARBFF = _SHR_BFCMAP_8G_FW_ON_ACTIVE_ARBFF, 
    BCM_FCMAP_8G_FW_ON_ACTIVE_IDLE = _SHR_BFCMAP_8G_FW_ON_ACTIVE_IDLE 
} bcm_fcmap_8g_fw_on_active_t;

typedef bfcmap_dev_io_f bcm_fcmap_dev_io_t;

typedef _shr_bfcmap_port_config_t bcm_fcmap_port_config_t;

#ifndef BCM_HIDE_DISPATCHABLE

/*  Set FCMAP Port configuration. */
extern int bcm_fcmap_port_config_set(
    int unit, 
    bcm_port_t port, 
    bcm_fcmap_port_config_t *cfg);

/*  Get current FCMAP Port configuration. */
extern int bcm_fcmap_port_config_get(
    int unit, 
    bcm_port_t port, 
    bcm_fcmap_port_config_t *cfg);

/*  Set Speed attribute of the FC port. */
extern int bcm_fcmap_port_speed_set(
    int unit, 
    bcm_port_t port, 
    bcm_fcmap_port_speed_t speed);

/*  Issues Link reset on the FC port. */
extern int bcm_fcmap_port_link_reset(
    int unit, 
    bcm_port_t port);

/*  Disables the FC port. Transmitter is turned off. */
extern int bcm_fcmap_port_shutdown(
    int unit, 
    bcm_port_t port);

/*  Enable the FC port, turn on the transmitter and restart the AN. */
extern int bcm_fcmap_port_enable(
    int unit, 
    bcm_port_t port);

#endif /* BCM_HIDE_DISPATCHABLE */

/*  Prototype for Port interation callback function. */
typedef int (*bcm_fcmap_port_traverse_cb)(
    int unit, 
    bcm_port_t port, 
    bcm_fcmap_core_t dev_core, 
    bcm_fcmap_dev_addr_t dev_addr, 
    int dev_port, 
    bcm_fcmap_dev_io_t devio_f, 
    void *user_data);

#ifndef BCM_HIDE_DISPATCHABLE

/* 
 *  Iterates over all the FCMAP ports and calls user provided callback
 * function for each port.
 */
extern int bcm_fcmap_port_traverse(
    int unit, 
    bcm_fcmap_port_traverse_cb callbk, 
    void *user_data);

#endif /* BCM_HIDE_DISPATCHABLE */

typedef _shr_bfcmap_vlan_vsan_map_t bcm_fcmap_vlan_vsan_map_t;

#ifndef BCM_HIDE_DISPATCHABLE

/*  Add FCMAP VLAN - VSAN MAP entry. */
extern int bcm_fcmap_vlan_map_add(
    int unit, 
    bcm_port_t port, 
    bcm_fcmap_vlan_vsan_map_t *vlan);

/*  Get FCMAP VLAN - VSAN MAP entry. */
extern int bcm_fcmap_vlan_map_get(
    int unit, 
    bcm_port_t port, 
    bcm_fcmap_vlan_vsan_map_t *vlan);

/*  Delete FCMAP VLAN - VSAN MAP entry. */
extern int bcm_fcmap_vlan_map_delete(
    int unit, 
    bcm_port_t port, 
    bcm_fcmap_vlan_vsan_map_t *vlan);

#endif /* BCM_HIDE_DISPATCHABLE */

typedef enum bcm_fcmap_event_e {
    BCM_FCMAP_EVENT_FC_LINK_INIT = _SHR_BFCMAP_EVENT_FC_LINK_INIT, 
    BCM_FCMAP_EVENT_FC_LINK_RESET = _SHR_BFCMAP_EVENT_FC_LINK_RESET, 
    BCM_FCMAP_EVENT_FC_LINK_DOWN = _SHR_BFCMAP_EVENT_FC_LINK_DOWN, 
    BCM_FCMAP_EVENT_FC_R_T_TIMEOUT = _SHR_BFCMAP_EVENT_FC_R_T_TIMEOUT, 
    BCM_FCMAP_EVENT_FC_E_D_TIMEOUT = _SHR_BFCMAP_EVENT_FC_E_D_TIMEOUT 
} bcm_fcmap_event_t;

/*  Prototype for the event callback function. */
typedef int (*bcm_fcmap_event_cb)(
    int unit, 
    bcm_port_t port, 
    bcm_fcmap_event_t event, 
    void *user_data);

#ifndef BCM_HIDE_DISPATCHABLE

/*  Register user event handler callback function. */
extern int bcm_fcmap_event_register(
    int unit, 
    bcm_fcmap_event_cb cb, 
    void *user_data);

/*  Unregister user event handler callback function. */
extern int bcm_fcmap_event_unregister(
    int unit, 
    bcm_fcmap_event_cb cb);

/*  Enables/Diable handling of the FCMAP event. */
extern int bcm_fcmap_event_enable_set(
    int unit, 
    bcm_fcmap_event_t t, 
    int enable);

/*  Return the current event hanler status for specified event. */
extern int bcm_fcmap_event_enable_get(
    int unit, 
    bcm_fcmap_event_t t, 
    int *enable);

#endif /* BCM_HIDE_DISPATCHABLE */

typedef enum bcm_fcmap_stat_e {
    bcm_fc_rxdebug0 = _shr_fc_rxdebug0, 
    bcm_fc_rxdebug1 = _shr_fc_rxdebug1, 
    bcm_fc_rxunicastpkts = _shr_fc_rxunicastpkts, 
    bcm_fc_rxgoodframes = _shr_fc_rxgoodframes, 
    bcm_fc_rxbcastpkts = _shr_fc_rxbcastpkts, 
    bcm_fc_rxbbcredit0 = _shr_fc_rxbbcredit0, 
    bcm_fc_rxinvalidcrc = _shr_fc_rxinvalidcrc, 
    bcm_fc_rxframetoolong = _shr_fc_rxframetoolong, 
    bcm_fc_rxtruncframes = _shr_fc_rxtruncframes, 
    bcm_fc_rxdelimitererr = _shr_fc_rxdelimitererr, 
    bcm_fc_rxothererr = _shr_fc_rxothererr, 
    bcm_fc_rxruntframes = _shr_fc_rxruntframes, 
    bcm_fc_rxlipcount = _shr_fc_rxlipcount, 
    bcm_fc_rxnoscount = _shr_fc_rxnoscount, 
    bcm_fc_rxerrframes = _shr_fc_rxerrframes, 
    bcm_fc_rxdropframes = _shr_fc_rxdropframes, 
    bcm_fc_rxlinkfail = _shr_fc_rxlinkfail, 
    bcm_fc_rxlosssync = _shr_fc_rxlosssync, 
    bcm_fc_rxlosssig = _shr_fc_rxlosssig, 
    bcm_fc_rxprimseqerr = _shr_fc_rxprimseqerr, 
    bcm_fc_rxinvalidword = _shr_fc_rxinvalidword, 
    bcm_fc_rxinvalidset = _shr_fc_rxinvalidset, 
    bcm_fc_rxencodedisparity = _shr_fc_rxencodedisparity, 
    bcm_fc_rxbyt = _shr_fc_rxbyt, 
    bcm_fc_txdebug0 = _shr_fc_txdebug0, 
    bcm_fc_txdebug1 = _shr_fc_txdebug1, 
    bcm_fc_txunicastpkts = _shr_fc_txunicastpkts, 
    bcm_fc_txbcastpkts = _shr_fc_txbcastpkts, 
    bcm_fc_txbbcredit0 = _shr_fc_txbbcredit0, 
    bcm_fc_txgoodframes = _shr_fc_txgoodframes, 
    bcm_fc_txfifounderrun = _shr_fc_txfifounderrun, 
    bcm_fc_txdropframes = _shr_fc_txdropframes, 
    bcm_fc_txbyt = _shr_fc_txbyt, 
    bcm_fcmap_stat__count = _shr_bfcmap_stat__count 
} bcm_fcmap_stat_t;

#ifndef BCM_HIDE_DISPATCHABLE

/*  Crear all the stats for the specified port. */
extern int bcm_fcmap_stat_clear(
    int unit, 
    bcm_port_t port);

/*  Return the current statistics for the specified counter. */
extern int bcm_fcmap_stat_get(
    int unit, 
    bcm_port_t port, 
    bcm_fcmap_stat_t stat, 
    uint64 *val);

/*  Return the current statistics for the specified counter. */
extern int bcm_fcmap_stat_get32(
    int unit, 
    bcm_port_t port, 
    bcm_fcmap_stat_t stat, 
    uint32 *val);

#endif /* defined(INCLUDE_FCMAP) */

#endif /* BCM_HIDE_DISPATCHABLE */

#endif /* __BCM_FCMAP_H__ */

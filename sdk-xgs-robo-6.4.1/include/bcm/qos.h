/*
 * $Id: bfd0177373f5565f939fc2860feec38e227f3be9 $
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

#ifndef __BCM_QOS_H__
#define __BCM_QOS_H__

#include <bcm/types.h>
#include <bcm/multicast.h>
#include <bcm/l3.h>

/* QoS Configuration Flags. */
#define BCM_QOS_MAP_WITH_ID         0x0001     
#define BCM_QOS_MAP_REPLACE         0x0002     
#define BCM_QOS_MAP_L2              0x0004     
#define BCM_QOS_MAP_L2_OUTER_TAG    BCM_QOS_MAP_L2 
#define BCM_QOS_MAP_L2_INNER_TAG    0x0008     
#define BCM_QOS_MAP_L2_UNTAGGED     0x0010     
#define BCM_QOS_MAP_L2_VLAN_PCP     0x0020     
#define BCM_QOS_MAP_L3              0x0040     
#define BCM_QOS_MAP_IPV4            BCM_QOS_MAP_L3 
#define BCM_QOS_MAP_IPV6            0x0080     
#define BCM_QOS_MAP_MPLS            0x0100     
#define BCM_QOS_MAP_ENCAP           0x0200     
#define BCM_QOS_MAP_INGRESS         0x0400     
#define BCM_QOS_MAP_EGRESS          0x0800     
#define BCM_QOS_MAP_MPLS_ELSP       0x1000     
#define BCM_QOS_MAP_MIM_ITAG        0x2000     
#define BCM_QOS_MAP_QUEUE           0x4000     
#define BCM_QOS_MAP_POLICER         0x8000     
#define BCM_QOS_MAP_PACKET_INVALID  0x10000    
#define BCM_QOS_MAP_IGNORE_OFFSET   0x20000    
#define BCM_QOS_MAP_OPCODE          0x40000    
#define BCM_QOS_MAP_L2_ETAG         0x80000    
#define BCM_QOS_MAP_L2_VLAN_ETAG    0x100000   
#define BCM_QOS_MAP_MPLS_PHP        0x200000   
#define BCM_QOS_MAP_SUBPORT         0x400000   
#define BCM_QOS_MAP_L3_L2           0x800000   
#define BCM_QOS_MAP_VFT             0x1000000  
#define BCM_QOS_MAP_VSAN            0x2000000  

/* QoS Map structure */
typedef struct bcm_qos_map_s {
    uint8 pkt_pri;              /* Packet priority */
    uint8 pkt_cfi;              /* Packet CFI */
    int dscp;                   /* Packet DSCP */
    int exp;                    /* Packet EXP */
    int int_pri;                /* Internal priority */
    bcm_color_t color;          /* Color */
    int remark_int_pri;         /* (internal) remarking priority */
    bcm_color_t remark_color;   /* (internal) remark color */
    int policer_offset;         /* Offset based on pri/cos to fetch a policer */
    int queue_offset;           /* Offset based on int_pri to fetch cosq for
                                   subscriber ports */
    int port_offset;            /* Offset based on port connection for indexing
                                   into the action table */
    uint8 etag_pcp;             /* ETAG PCP field */
    uint8 etag_de;              /* ETAG DE field */
} bcm_qos_map_t;

/* Initialize the QoS Map structure. */
extern void bcm_qos_map_t_init(
    bcm_qos_map_t *qos_map);

#ifndef BCM_HIDE_DISPATCHABLE

/* Initialize the BCM QoS subsystem. */
extern int bcm_qos_init(
    int unit);

/* Detach the QoS software module. */
extern int bcm_qos_detach(
    int unit);

/* bcm_qos_map_create */
extern int bcm_qos_map_create(
    int unit, 
    uint32 flags, 
    int *map_id);

/* bcm_qos_map_destroy */
extern int bcm_qos_map_destroy(
    int unit, 
    int map_id);

/* bcm_qos_map_add */
extern int bcm_qos_map_add(
    int unit, 
    uint32 flags, 
    bcm_qos_map_t *map, 
    int map_id);

/* bcm_qos_map_multi_get */
extern int bcm_qos_map_multi_get(
    int unit, 
    uint32 flags, 
    int map_id, 
    int array_size, 
    bcm_qos_map_t *array, 
    int *array_count);

/* bcm_qos_map_delete */
extern int bcm_qos_map_delete(
    int unit, 
    uint32 flags, 
    bcm_qos_map_t *map, 
    int map_id);

/* bcm_qos_port_map_set */
extern int bcm_qos_port_map_set(
    int unit, 
    bcm_gport_t port, 
    int ing_map, 
    int egr_map);

/* bcm_qos_port_map_type_get */
extern int bcm_qos_port_map_type_get(
    int unit, 
    bcm_gport_t port, 
    uint32 flags, 
    int *map_id);

/* bcm_qos_port_map_get */
extern int bcm_qos_port_map_get(
    int unit, 
    bcm_gport_t port, 
    int *ing_map, 
    int *egr_map);

/* bcm_qos_port_vlan_map_set */
extern int bcm_qos_port_vlan_map_set(
    int unit, 
    bcm_port_t port, 
    bcm_vlan_t vid, 
    int ing_map, 
    int egr_map);

/* bcm_qos_port_vlan_map_get */
extern int bcm_qos_port_vlan_map_get(
    int unit, 
    bcm_port_t port, 
    bcm_vlan_t vid, 
    int *ing_map, 
    int *egr_map);

/* bcm_qos_multi_get */
extern int bcm_qos_multi_get(
    int unit, 
    int array_size, 
    int *map_ids_array, 
    int *flags_array, 
    int *array_count);

#endif /* BCM_HIDE_DISPATCHABLE */

#endif /* __BCM_QOS_H__ */

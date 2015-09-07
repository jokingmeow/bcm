/*
 * $Id: c4b838bbc39d82187d26afee38b85970b63e54c5 $
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

#ifndef __ROBO_STAT_H__
#define __ROBO_STAT_H__


/* 
 * Statistics counters.
 * 
 * Note: the following RFC 2465 MIBs are not supported:
 * 
 *   snmpIpv6IfStatsInTooBigErrors,
 *   snmpIpv6IfStatsInNoRoutes,
 *   snmpIpv6IfStatsInUnknownProtos,
 *   snmpIpv6IfStatsInTruncatedPkts,
 *   snmpIpv6IfStatsInDelivers,
 *   snmpIpv6IfStatsOutRequests,
 *   snmpIpv6IfStatsOutFragOKs,
 *   snmpIpv6IfStatsOutFragFails,
 *   snmpIpv6IfStatsOutFragCreates,
 *   snmpIpv6IfStatsReasmReqds,
 *   snmpIpv6IfStatsReasmOKs,
 *   snmpIpv6IfStatsReasmFails,
 */
typedef enum drv_stat_val_e {
    DRV_SNMP_IF_IN_OCTETS = 0,          /* RFC 1213 */
    DRV_SNMP_IF_IN_UCAST_PKTS = 1,      /* RFC 1213 */
    DRV_SNMP_IF_IN_N_UCAST_PKTS = 2,    /* RFC 1213 */
    DRV_SNMP_IF_IN_DISCARDS = 3,        /* RFC 1213 */
    DRV_SNMP_IF_IN_ERRORS = 4,          /* RFC 1213 */
    DRV_SNMP_IF_IN_UNKNOWN_PROTOS = 5,  /* RFC 1213 */
    DRV_SNMP_IF_OUT_OCTETS = 6,         /* RFC 1213 */
    DRV_SNMP_IF_OUT_UCAST_PKTS = 7,     /* RFC 1213 */
    DRV_SNMP_IF_OUT_N_UCAST_PKTS = 8,   /* RFC 1213 */
    DRV_SNMP_IF_OUT_DISCARDS = 9,       /* RFC 1213 */
    DRV_SNMP_IF_OUT_ERRORS = 10,        /* RFC 1213 */
    DRV_SNMP_IF_OUT_Q_LEN = 11,         /* RFC 1213 */
    DRV_SNMP_IP_IN_RECEIVES = 12,       /* RFC 1213 */
    DRV_SNMP_IP_IN_HDR_ERRORS = 13,     /* RFC 1213 */
    DRV_SNMP_IP_FORW_DATAGRAMS = 14,    /* RFC 1213 */
    DRV_SNMP_IP_IN_DISCARDS = 15,       /* RFC 1213 */
    DRV_SNMP_DOT1D_BASE_PORT_DELAY_EXCEEDED_DISCARDS = 16, /* RFC 1493 */
    DRV_SNMP_DOT1D_BASE_PORT_MTU_EXCEEDED_DISCARDS = 17, /* RFC 1493 */
    DRV_SNMP_DOT1D_TP_PORT_IN_FRAMES = 18, /* RFC 1493 */
    DRV_SNMP_DOT1D_TP_PORT_OUT_FRAMES = 19, /* RFC 1493 */
    DRV_SNMP_DOT1D_PORT_IN_DISCARDS = 20, /* RFC 1493 */
    DRV_SNMP_ETHER_STATS_DROP_EVENTS = 21, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_MULTICAST_PKTS = 22, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_BROADCAST_PKTS = 23, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_UNDERSIZE_PKTS = 24, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_FRAGMENTS = 25, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_PKTS64_OCTETS = 26, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_PKTS65TO127_OCTETS = 27, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_PKTS128TO255_OCTETS = 28, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_PKTS256TO511_OCTETS = 29, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_PKTS512TO1023_OCTETS = 30, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_PKTS1024TO1518_OCTETS = 31, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_OVERSIZE_PKTS = 32, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_RX_OVERSIZE_PKTS = 33, /* Rx component of
                                           snmpEtherStatsOversizePkts */
    DRV_SNMP_ETHER_TX_OVERSIZE_PKTS = 34, /* Tx component of
                                           snmpEtherStatsOversizePkts */
    DRV_SNMP_ETHER_STATS_JABBERS = 35,  /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_OCTETS = 36,   /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_PKTS = 37,     /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_COLLISIONS = 38, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_CRC_ALIGN_ERRORS = 39, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_TX_NO_ERRORS = 40, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_RX_NO_ERRORS = 41, /* RFC 1757 (EtherStat) */
    DRV_SNMP_DOT3_STATS_ALIGNMENT_ERRORS = 42, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_FCS_ERRORS = 43, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_SINGLE_COLLISION_FRAMES = 44, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_MULTIPLE_COLLISION_FRAMES = 45, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_SQET_TEST_ERRORS = 46, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_DEFERRED_TRANSMISSIONS = 47, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_LATE_COLLISIONS = 48, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_EXCESSIVE_COLLISIONS = 49, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_INTERNAL_MAC_TRANSMIT_ERRORS = 50, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_CARRIER_SENSE_ERRORS = 51, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_FRAME_TOO_LONGS = 52, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_INTERNAL_MAC_RECEIVE_ERRORS = 53, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_SYMBOL_ERRORS = 54, /* RFC 2665 */
    DRV_SNMP_DOT3_CONTROL_IN_UNKNOWN_OPCODES = 55, /* RFC 2665 */
    DRV_SNMP_DOT3_IN_PAUSE_FRAMES = 56, /* RFC 2665 */
    DRV_SNMP_DOT3_OUT_PAUSE_FRAMES = 57, /* RFC 2665 */
    DRV_SNMP_IF_HC_IN_OCTETS = 58,      /* RFC 2233 */
    DRV_SNMP_IF_HC_IN_UCAST_PKTS = 59,  /* RFC 2233 */
    DRV_SNMP_IF_HC_IN_MULTICAST_PKTS = 60, /* RFC 2233 */
    DRV_SNMP_IF_HC_IN_BROADCAST_PKTS = 61, /* RFC 2233 */
    DRV_SNMP_IF_HC_OUT_OCTETS = 62,     /* RFC 2233 */
    DRV_SNMP_IF_HC_OUT_UCAST_PKTS = 63, /* RFC 2233 */
    DRV_SNMP_IF_HC_OUT_MULTICAST_PKTS = 64, /* RFC 2233 */
    DRV_SNMP_IF_HC_OUT_BROADCAST_PCKTS = 65, /* RFC 2233 */
    DRV_SNMP_IPV6_IF_STATS_IN_RECEIVES = 66, /* RFC 2465 */
    DRV_SNMP_IPV6_IF_STATS_IN_HDR_ERRORS = 67, /* RFC 2465 */
    DRV_SNMP_IPV6_IF_STATS_IN_ADDR_ERRORS = 68, /* RFC 2465 */
    DRV_SNMP_IPV6_IF_STATS_IN_DISCARDS = 69, /* RFC 2465 */
    DRV_SNMP_IPV6_IF_STATS_OUT_FORW_DATAGRAMS = 70, /* RFC 2465 */
    DRV_SNMP_IPV6_IF_STATS_OUT_DISCARDS = 71, /* RFC 2465 */
    DRV_SNMP_IPV6_IF_STATS_IN_MCAST_PKTS = 72, /* RFC 2465 */
    DRV_SNMP_IPV6_IF_STATS_OUT_MCAST_PKTS = 73, /* RFC 2465 */
    DRV_SNMP_IF_IN_BROADCAST_PKTS = 74, /* RFC 1573 */
    DRV_SNMP_IF_IN_MULTICAST_PKTS = 75, /* RFC 1573 */
    DRV_SNMP_IF_OUT_BROADCAST_PKTS = 76, /* RFC 1573 */
    DRV_SNMP_IF_OUT_MULTICAST_PKTS = 77, /* RFC 1573 */
    DRV_SNMP_IEEE8021_PFC_REQUESTS = 78, /* IEEE 802.1bb */
    DRV_SNMP_IEEE8021_PFC_INDICATIONS = 79, /* IEEE 802.1bb */
    DRV_SNMP_BCM_RECEIVED_UNDERSIZE_PKTS = 80, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_UNDERSIZE_PKTS = 81, /* Broadcom-specific */
    DRV_SNMP_BCM_IPMC_BRIDGED_PCKTS = 82, /* Broadcom-specific */
    DRV_SNMP_BCM_IPMC_ROUTED_PCKTS = 83, /* Broadcom-specific */
    DRV_SNMP_BCM_IPMC_IN_DROPPED_PCKTS = 84, /* Broadcom-specific */
    DRV_SNMP_BCM_IPMC_OUT_DROPPED_PCKTS = 85, /* Broadcom-specific */
    DRV_SNMP_BCM_ETHER_STATS_PKTS1519TO1522_OCTETS = 86, /* Broadcom-specific */
    DRV_SNMP_BCM_ETHER_STATS_PKTS1522TO2047_OCTETS = 87, /* Broadcom-specific */
    DRV_SNMP_BCM_ETHER_STATS_PKTS2048TO4095_OCTETS = 88, /* Broadcom-specific */
    DRV_SNMP_BCM_ETHER_STATS_PKTS4095TO9216_OCTETS = 89, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS64_OCTETS = 90, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS65TO127_OCTETS = 91, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS128TO255_OCTETS = 92, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS256TO511_OCTETS = 93, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS512TO1023_OCTETS = 94, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS1024TO1518_OCTETS = 95, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS1519TO2047_OCTETS = 96, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS2048TO4095_OCTETS = 97, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS4095TO9216_OCTETS = 98, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS64_OCTETS = 99, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS65TO127_OCTETS = 100, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS128TO255_OCTETS = 101, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS256TO511_OCTETS = 102, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS512TO1023_OCTETS = 103, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS1024TO1518_OCTETS = 104, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS1519TO2047_OCTETS = 105, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS2048TO4095_OCTETS = 106, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS4095TO9216_OCTETS = 107, /* Broadcom-specific */
    DRV_SNMP_BCM_TX_CONTROL_CELLS = 108, /* Fabric TX Control cells counter.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_TX_DATA_CELLS = 109,   /* Fabric TX Data cell counter.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_TX_DATA_BYTES = 110,   /* Fabric TX Data byte counter.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_CRC_ERRORS = 111,   /* Fabric RX CRC errors counter.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_FEC_CORRECTABLE = 112, /* Fabric RX LFEC/FEC correctable error.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_BEC_CRC_ERRORS = 113, /* Fabric RX BEC crc error.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_DISPARITY_ERRORS = 114, /* Fabric RX 8b/10b disparity errors.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_CONTROL_CELLS = 115, /* Fabric RX Control cells counter.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_DATA_CELLS = 116,   /* Fabric RX Data cell counter.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_DATA_BYTES = 117,   /* Fabric RX Data byte counter.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_DROPPED_RETRANSMITTED_CONTROL = 118, /* Fabric RX dropped retransmitted
                                           control. (Broadcom-specific) */
    DRV_SNMP_BCM_TX_BEC_RETRANSMIT = 119, /* Fabric TX BEC retransmit.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_BEC_RETRANSMIT = 120, /* Fabric RX BEC retransmit.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_TX_ASYN_FIFO_RATE = 121, /* Fabric TX Asyn fifo rate at units of
                                           40 bits. (Broadcom-specific) */
    DRV_SNMP_BCM_RX_ASYN_FIFO_RATE = 122, /* Fabric RX Asyn fifo rate at units of
                                           40 bits. (Broadcom-specific) */
    DRV_SNMP_BCM_RX_FEC_UNCORRECTABLE = 123, /* Fabric RX LFEC/FEC uncorrectable
                                           erros. (Broadcom-specific) */
    DRV_SNMP_BCM_RX_BEC_RX_FAULT = 124, /* Fabric RX BEC RX fault.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_CODE_ERRORS = 125,  /* Fabric RX 8b/10b code errors.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_LLFC_PRIMARY = 126, /* Fabric RX LLFC Primary.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_LLFC_SECONDARY = 127, /* Fabric RX LLFC Secondary.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_CUSTOM_RECEIVE0 = 128, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_RECEIVE1 = 129, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_RECEIVE2 = 130, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_RECEIVE3 = 131, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_RECEIVE4 = 132, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_RECEIVE5 = 133, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_RECEIVE6 = 134, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_RECEIVE7 = 135, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_RECEIVE8 = 136, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT0 = 137, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT1 = 138, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT2 = 139, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT3 = 140, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT4 = 141, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT5 = 142, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT6 = 143, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT7 = 144, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT8 = 145, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT9 = 146, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT10 = 147, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT11 = 148, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT12 = 149, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT13 = 150, /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT14 = 151, /* Broadcom-specific */
    DRV_SNMP_DOT3_STATS_IN_RANGE_LENGTH_ERROR = 152, /* RFC 1284 */
    DRV_SNMP_DOT3_OMP_EMULATION_CRC8_ERRORS = 153, /* RFC 4837 */
    DRV_SNMP_DOT3_MPCP_RX_GATE = 154,   /* RFC 4837 */
    DRV_SNMP_DOT3_MPCP_RX_REGISTER = 155, /* RFC 4837 */
    DRV_SNMP_DOT3_MPCP_TX_REG_REQUEST = 156, /* RFC 4837 */
    DRV_SNMP_DOT3_MPCP_TX_REG_ACK = 157, /* RFC 4837 */
    DRV_SNMP_DOT3_MPCP_TX_REPORT = 158, /* RFC 4837 */
    DRV_SNMP_DOT3_EPON_FEC_CORRECTED_BLOCKS = 159, /* RFC 4837 */
    DRV_SNMP_DOT3_EPON_FEC_UNCORRECTABLE_BLOCKS = 160, /* RFC 4837 */
    DRV_SNMP_BCM_PON_IN_DROPPED_OCTETS = 161, /* Broadcom-specific */
    DRV_SNMP_BCM_PON_OUT_DROPPED_OCTETS = 162, /* Broadcom-specific */
    DRV_SNMP_BCM_PON_IN_DELAYED_OCTETS = 163, /* Broadcom-specific */
    DRV_SNMP_BCM_PON_OUT_DELAYED_OCTETS = 164, /* Broadcom-specific */
    DRV_SNMP_BCM_PON_IN_DELAYED_HUNDRED_US = 165, /* Broadcom-specific */
    DRV_SNMP_BCM_PON_OUT_DELAYED_HUNDRED_US = 166, /* Broadcom-specific */
    DRV_SNMP_BCM_PON_IN_FRAME_ERRORS = 167, /* Broadcom-specific */
    DRV_SNMP_BCM_PON_IN_OAM_FRAMES = 168, /* Broadcom-specific */
    DRV_SNMP_BCM_PON_OUT_OAM_FRAMES = 169, /* Broadcom-specific */
    DRV_SNMP_BCM_PON_OUT_UNUSED_OCTETS = 170, /* Broadcom-specific */
    DRV_SNMP_BCM_ETHER_STATS_PKTS9217TO16383_OCTETS = 171, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS9217TO16383_OCTETS = 172, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS9217TO16383_OCTETS = 173, /* Broadcom-specific */
    DRV_SNMP_BCM_RX_VLAN_TAG_FRAME = 174, /* Broadcom-specific */
    DRV_SNMP_BCM_RX_DOUBLE_VLAN_TAG_FRAME = 175, /* Broadcom-specific */
    DRV_SNMP_BCM_TX_VLAN_TAG_FRAME = 176, /* Broadcom-specific */
    DRV_SNMP_BCM_TX_DOUBLE_VLAN_TAG_FRAME = 177, /* Broadcom-specific */
    DRV_SNMP_BCM_RX_P_F_C_CONTROL_FRAME = 178, /* PFC Receive Control Frame */
    DRV_SNMP_BCM_TX_P_F_C_CONTROL_FRAME = 179, /* PFC Transmit Control Frame */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY0 = 180, /* Receive PFC Frame Priority 0 XON to
                                           XOFF */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY1 = 181, /* Receive PFC Frame Priority 1 XON to
                                           XOFF */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY2 = 182, /* Receive PFC Frame Priority 2 XON to
                                           XOFF */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY3 = 183, /* Receive PFC Frame Priority 3 XON to
                                           XOFF */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY4 = 184, /* Receive PFC Frame Priority 4 XON to
                                           XOFF */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY5 = 185, /* Receive PFC Frame Priority 5 XON to
                                           XOFF */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY6 = 186, /* Receive PFC Frame Priority 6 XON to
                                           XOFF */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY7 = 187, /* Receive PFC Frame Priority 7 XON to
                                           XOFF */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY0 = 188, /* Receive PFC Frame Priority 0 */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY1 = 189, /* Receive PFC Frame Priority 1 */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY2 = 190, /* Receive PFC Frame Priority 2 */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY3 = 191, /* Receive PFC Frame Priority 3 */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY4 = 192, /* Receive PFC Frame Priority 4 */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY5 = 193, /* Receive PFC Frame Priority 5 */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY6 = 194, /* Receive PFC Frame Priority 6 */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY7 = 195, /* Receive PFC Frame Priority 7 */
    DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY0 = 196, /* Transmit PFC Frame Priority 0 */
    DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY1 = 197, /* Transmit PFC Frame Priority 1 */
    DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY2 = 198, /* Transmit PFC Frame Priority 2 */
    DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY3 = 199, /* Transmit PFC Frame Priority 3 */
    DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY4 = 200, /* Transmit PFC Frame Priority 4 */
    DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY5 = 201, /* Transmit PFC Frame Priority 5 */
    DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY6 = 202, /* Transmit PFC Frame Priority 6 */
    DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY7 = 203, /* Transmit PFC Frame Priority 7 */
    DRV_SNMP_FCM_PORT_CLASS3_RX_FRAMES = 204, /* RFC 4044 */
    DRV_SNMP_FCM_PORT_CLASS3_TX_FRAMES = 205, /* RFC 4044 */
    DRV_SNMP_FCM_PORT_CLASS3_DISCARDS = 206, /* RFC 4044 */
    DRV_SNMP_FCM_PORT_CLASS2_RX_FRAMES = 207, /* RFC 4044 */
    DRV_SNMP_FCM_PORT_CLASS2_TX_FRAMES = 208, /* RFC 4044 */
    DRV_SNMP_FCM_PORT_CLASS2_DISCARDS = 209, /* RFC 4044 */
    DRV_SNMP_FCM_PORT_INVALID_CRCS = 210, /* RFC 4044 */
    DRV_SNMP_FCM_PORT_DELIMITER_ERRORS = 211, /* RFC 4044 */
    DRV_SNMP_VAL_COUNT = 212 
} drv_stat_val_t;

#define DRV_STAT_NAME_INITIALIZER \
{ \
    "DRV_SNMP_IF_IN_OCTETS", \
    "DRV_SNMP_IF_IN_UCAST_PKTS", \
    "DRV_SNMP_IF_IN_N_UCAST_PKTS", \
    "DRV_SNMP_IF_IN_DISCARDS", \
    "DRV_SNMP_IF_IN_ERRORS", \
    "DRV_SNMP_IF_IN_UNKNOWN_PROTOS", \
    "DRV_SNMP_IF_OUT_OCTETS", \
    "DRV_SNMP_IF_OUT_UCAST_PKTS", \
    "DRV_SNMP_IF_OUT_N_UCAST_PKTS", \
    "DRV_SNMP_IF_OUT_DISCARDS", \
    "DRV_SNMP_IF_OUT_ERRORS", \
    "DRV_SNMP_IF_OUT_Q_LEN", \
    "DRV_SNMP_IP_IN_RECEIVES", \
    "DRV_SNMP_IP_IN_HDR_ERRORS", \
    "DRV_SNMP_IP_FORW_DATAGRAMS", \
    "DRV_SNMP_IP_IN_DISCARDS", \
    "DRV_SNMP_DOT1D_BASE_PORT_DELAY_EXCEEDED_DISCARDS", \
    "DRV_SNMP_DOT1D_BASE_PORT_MTU_EXCEEDED_DISCARDS", \
    "DRV_SNMP_DOT1D_TP_PORT_IN_FRAMES", \
    "DRV_SNMP_DOT1D_TP_PORT_OUT_FRAMES", \
    "DRV_SNMP_DOT1D_PORT_IN_DISCARDS", \
    "DRV_SNMP_ETHER_STATS_DROP_EVENTS", \
    "DRV_SNMP_ETHER_STATS_MULTICAST_PKTS", \
    "DRV_SNMP_ETHER_STATS_BROADCAST_PKTS", \
    "DRV_SNMP_ETHER_STATS_UNDERSIZE_PKTS", \
    "DRV_SNMP_ETHER_STATS_FRAGMENTS", \
    "DRV_SNMP_ETHER_STATS_PKTS64_OCTETS", \
    "DRV_SNMP_ETHER_STATS_PKTS65TO127_OCTETS", \
    "DRV_SNMP_ETHER_STATS_PKTS128TO255_OCTETS", \
    "DRV_SNMP_ETHER_STATS_PKTS256TO511_OCTETS", \
    "DRV_SNMP_ETHER_STATS_PKTS512TO1023_OCTETS", \
    "DRV_SNMP_ETHER_STATS_PKTS1024TO1518_OCTETS", \
    "DRV_SNMP_ETHER_STATS_OVERSIZE_PKTS", \
    "DRV_SNMP_ETHER_RX_OVERSIZE_PKTS", \
    "DRV_SNMP_ETHER_TX_OVERSIZE_PKTS", \
    "DRV_SNMP_ETHER_STATS_JABBERS", \
    "DRV_SNMP_ETHER_STATS_OCTETS", \
    "DRV_SNMP_ETHER_STATS_PKTS", \
    "DRV_SNMP_ETHER_STATS_COLLISIONS", \
    "DRV_SNMP_ETHER_STATS_CRC_ALIGN_ERRORS", \
    "DRV_SNMP_ETHER_STATS_TX_NO_ERRORS", \
    "DRV_SNMP_ETHER_STATS_RX_NO_ERRORS", \
    "DRV_SNMP_DOT3_STATS_ALIGNMENT_ERRORS", \
    "DRV_SNMP_DOT3_STATS_FCS_ERRORS", \
    "DRV_SNMP_DOT3_STATS_SINGLE_COLLISION_FRAMES", \
    "DRV_SNMP_DOT3_STATS_MULTIPLE_COLLISION_FRAMES", \
    "DRV_SNMP_DOT3_STATS_SQET_TEST_ERRORS", \
    "DRV_SNMP_DOT3_STATS_DEFERRED_TRANSMISSIONS", \
    "DRV_SNMP_DOT3_STATS_LATE_COLLISIONS", \
    "DRV_SNMP_DOT3_STATS_EXCESSIVE_COLLISIONS", \
    "DRV_SNMP_DOT3_STATS_INTERNAL_MAC_TRANSMIT_ERRORS", \
    "DRV_SNMP_DOT3_STATS_CARRIER_SENSE_ERRORS", \
    "DRV_SNMP_DOT3_STATS_FRAME_TOO_LONGS", \
    "DRV_SNMP_DOT3_STATS_INTERNAL_MAC_RECEIVE_ERRORS", \
    "DRV_SNMP_DOT3_STATS_SYMBOL_ERRORS", \
    "DRV_SNMP_DOT3_CONTROL_IN_UNKNOWN_OPCODES", \
    "DRV_SNMP_DOT3_IN_PAUSE_FRAMES", \
    "DRV_SNMP_DOT3_OUT_PAUSE_FRAMES", \
    "DRV_SNMP_IF_HC_IN_OCTETS", \
    "DRV_SNMP_IF_HC_IN_UCAST_PKTS", \
    "DRV_SNMP_IF_HC_IN_MULTICAST_PKTS", \
    "DRV_SNMP_IF_HC_IN_BROADCAST_PKTS", \
    "DRV_SNMP_IF_HC_OUT_OCTETS", \
    "DRV_SNMP_IF_HC_OUT_UCAST_PKTS", \
    "DRV_SNMP_IF_HC_OUT_MULTICAST_PKTS", \
    "DRV_SNMP_IF_HC_OUT_BROADCAST_PCKTS", \
    "DRV_SNMP_IPV6_IF_STATS_IN_RECEIVES", \
    "DRV_SNMP_IPV6_IF_STATS_IN_HDR_ERRORS", \
    "DRV_SNMP_IPV6_IF_STATS_IN_ADDR_ERRORS", \
    "DRV_SNMP_IPV6_IF_STATS_IN_DISCARDS", \
    "DRV_SNMP_IPV6_IF_STATS_OUT_FORW_DATAGRAMS", \
    "DRV_SNMP_IPV6_IF_STATS_OUT_DISCARDS", \
    "DRV_SNMP_IPV6_IF_STATS_IN_MCAST_PKTS", \
    "DRV_SNMP_IPV6_IF_STATS_OUT_MCAST_PKTS", \
    "DRV_SNMP_IF_IN_BROADCAST_PKTS", \
    "DRV_SNMP_IF_IN_MULTICAST_PKTS", \
    "DRV_SNMP_IF_OUT_BROADCAST_PKTS", \
    "DRV_SNMP_IF_OUT_MULTICAST_PKTS", \
    "DRV_SNMP_IEEE8021_PFC_REQUESTS", \
    "DRV_SNMP_IEEE8021_PFC_INDICATIONS", \
    "DRV_SNMP_BCM_RECEIVED_UNDERSIZE_PKTS", \
    "DRV_SNMP_BCM_TRANSMITTED_UNDERSIZE_PKTS", \
    "DRV_SNMP_BCM_IPMC_BRIDGED_PCKTS", \
    "DRV_SNMP_BCM_IPMC_ROUTED_PCKTS", \
    "DRV_SNMP_BCM_IPMC_IN_DROPPED_PCKTS", \
    "DRV_SNMP_BCM_IPMC_OUT_DROPPED_PCKTS", \
    "DRV_SNMP_BCM_ETHER_STATS_PKTS1519TO1522_OCTETS", \
    "DRV_SNMP_BCM_ETHER_STATS_PKTS1522TO2047_OCTETS", \
    "DRV_SNMP_BCM_ETHER_STATS_PKTS2048TO4095_OCTETS", \
    "DRV_SNMP_BCM_ETHER_STATS_PKTS4095TO9216_OCTETS", \
    "DRV_SNMP_BCM_RECEIVED_PKTS64_OCTETS", \
    "DRV_SNMP_BCM_RECEIVED_PKTS65TO127_OCTETS", \
    "DRV_SNMP_BCM_RECEIVED_PKTS128TO255_OCTETS", \
    "DRV_SNMP_BCM_RECEIVED_PKTS256TO511_OCTETS", \
    "DRV_SNMP_BCM_RECEIVED_PKTS512TO1023_OCTETS", \
    "DRV_SNMP_BCM_RECEIVED_PKTS1024TO1518_OCTETS", \
    "DRV_SNMP_BCM_RECEIVED_PKTS1519TO2047_OCTETS", \
    "DRV_SNMP_BCM_RECEIVED_PKTS2048TO4095_OCTETS", \
    "DRV_SNMP_BCM_RECEIVED_PKTS4095TO9216_OCTETS", \
    "DRV_SNMP_BCM_TRANSMITTED_PKTS64_OCTETS", \
    "DRV_SNMP_BCM_TRANSMITTED_PKTS65TO127_OCTETS", \
    "DRV_SNMP_BCM_TRANSMITTED_PKTS128TO255_OCTETS", \
    "DRV_SNMP_BCM_TRANSMITTED_PKTS256TO511_OCTETS", \
    "DRV_SNMP_BCM_TRANSMITTED_PKTS512TO1023_OCTETS", \
    "DRV_SNMP_BCM_TRANSMITTED_PKTS1024TO1518_OCTETS", \
    "DRV_SNMP_BCM_TRANSMITTED_PKTS1519TO2047_OCTETS", \
    "DRV_SNMP_BCM_TRANSMITTED_PKTS2048TO4095_OCTETS", \
    "DRV_SNMP_BCM_TRANSMITTED_PKTS4095TO9216_OCTETS", \
    "DRV_SNMP_BCM_TX_CONTROL_CELLS", \
    "DRV_SNMP_BCM_TX_DATA_CELLS", \
    "DRV_SNMP_BCM_TX_DATA_BYTES", \
    "DRV_SNMP_BCM_RX_CRC_ERRORS", \
    "DRV_SNMP_BCM_RX_FEC_CORRECTABLE", \
    "DRV_SNMP_BCM_RX_BEC_CRC_ERRORS", \
    "DRV_SNMP_BCM_RX_DISPARITY_ERRORS", \
    "DRV_SNMP_BCM_RX_CONTROL_CELLS", \
    "DRV_SNMP_BCM_RX_DATA_CELLS", \
    "DRV_SNMP_BCM_RX_DATA_BYTES", \
    "DRV_SNMP_BCM_RX_DROPPED_RETRANSMITTED_CONTROL", \
    "DRV_SNMP_BCM_TX_BEC_RETRANSMIT", \
    "DRV_SNMP_BCM_RX_BEC_RETRANSMIT", \
    "DRV_SNMP_BCM_TX_ASYN_FIFO_RATE", \
    "DRV_SNMP_BCM_RX_ASYN_FIFO_RATE", \
    "DRV_SNMP_BCM_RX_FEC_UNCORRECTABLE", \
    "DRV_SNMP_BCM_RX_BEC_RX_FAULT", \
    "DRV_SNMP_BCM_RX_CODE_ERRORS", \
    "DRV_SNMP_BCM_RX_LLFC_PRIMARY", \
    "DRV_SNMP_BCM_RX_LLFC_SECONDARY", \
    "DRV_SNMP_BCM_CUSTOM_RECEIVE0", \
    "DRV_SNMP_BCM_CUSTOM_RECEIVE1", \
    "DRV_SNMP_BCM_CUSTOM_RECEIVE2", \
    "DRV_SNMP_BCM_CUSTOM_RECEIVE3", \
    "DRV_SNMP_BCM_CUSTOM_RECEIVE4", \
    "DRV_SNMP_BCM_CUSTOM_RECEIVE5", \
    "DRV_SNMP_BCM_CUSTOM_RECEIVE6", \
    "DRV_SNMP_BCM_CUSTOM_RECEIVE7", \
    "DRV_SNMP_BCM_CUSTOM_RECEIVE8", \
    "DRV_SNMP_BCM_CUSTOM_TRANSMIT0", \
    "DRV_SNMP_BCM_CUSTOM_TRANSMIT1", \
    "DRV_SNMP_BCM_CUSTOM_TRANSMIT2", \
    "DRV_SNMP_BCM_CUSTOM_TRANSMIT3", \
    "DRV_SNMP_BCM_CUSTOM_TRANSMIT4", \
    "DRV_SNMP_BCM_CUSTOM_TRANSMIT5", \
    "DRV_SNMP_BCM_CUSTOM_TRANSMIT6", \
    "DRV_SNMP_BCM_CUSTOM_TRANSMIT7", \
    "DRV_SNMP_BCM_CUSTOM_TRANSMIT8", \
    "DRV_SNMP_BCM_CUSTOM_TRANSMIT9", \
    "DRV_SNMP_BCM_CUSTOM_TRANSMIT10", \
    "DRV_SNMP_BCM_CUSTOM_TRANSMIT11", \
    "DRV_SNMP_BCM_CUSTOM_TRANSMIT12", \
    "DRV_SNMP_BCM_CUSTOM_TRANSMIT13", \
    "DRV_SNMP_BCM_CUSTOM_TRANSMIT14", \
    "DRV_SNMP_DOT3_STATS_IN_RANGE_LENGTH_ERROR", \
    "DRV_SNMP_DOT3_OMP_EMULATION_CRC8_ERRORS", \
    "DRV_SNMP_DOT3_MPCP_RX_GATE", \
    "DRV_SNMP_DOT3_MPCP_RX_REGISTER", \
    "DRV_SNMP_DOT3_MPCP_TX_REG_REQUEST", \
    "DRV_SNMP_DOT3_MPCP_TX_REG_ACK", \
    "DRV_SNMP_DOT3_MPCP_TX_REPORT", \
    "DRV_SNMP_DOT3_EPON_FEC_CORRECTED_BLOCKS", \
    "DRV_SNMP_DOT3_EPON_FEC_UNCORRECTABLE_BLOCKS", \
    "DRV_SNMP_BCM_PON_IN_DROPPED_OCTETS", \
    "DRV_SNMP_BCM_PON_OUT_DROPPED_OCTETS", \
    "DRV_SNMP_BCM_PON_IN_DELAYED_OCTETS", \
    "DRV_SNMP_BCM_PON_OUT_DELAYED_OCTETS", \
    "DRV_SNMP_BCM_PON_IN_DELAYED_HUNDRED_US", \
    "DRV_SNMP_BCM_PON_OUT_DELAYED_HUNDRED_US", \
    "DRV_SNMP_BCM_PON_IN_FRAME_ERRORS", \
    "DRV_SNMP_BCM_PON_IN_OAM_FRAMES", \
    "DRV_SNMP_BCM_PON_OUT_OAM_FRAMES", \
    "DRV_SNMP_BCM_PON_OUT_UNUSED_OCTETS", \
    "DRV_SNMP_BCM_ETHER_STATS_PKTS9217TO16383_OCTETS", \
    "DRV_SNMP_BCM_RECEIVED_PKTS9217TO16383_OCTETS", \
    "DRV_SNMP_BCM_TRANSMITTED_PKTS9217TO16383_OCTETS", \
    "DRV_SNMP_BCM_RX_VLAN_TAG_FRAME", \
    "DRV_SNMP_BCM_RX_DOUBLE_VLAN_TAG_FRAME", \
    "DRV_SNMP_BCM_TX_VLAN_TAG_FRAME", \
    "DRV_SNMP_BCM_TX_DOUBLE_VLAN_TAG_FRAME", \
    "DRV_SNMP_BCM_RX_P_F_C_CONTROL_FRAME", \
    "DRV_SNMP_BCM_TX_P_F_C_CONTROL_FRAME", \
    "DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY0", \
    "DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY1", \
    "DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY2", \
    "DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY3", \
    "DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY4", \
    "DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY5", \
    "DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY6", \
    "DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY7", \
    "DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY0", \
    "DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY1", \
    "DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY2", \
    "DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY3", \
    "DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY4", \
    "DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY5", \
    "DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY6", \
    "DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY7", \
    "DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY0", \
    "DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY1", \
    "DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY2", \
    "DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY3", \
    "DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY4", \
    "DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY5", \
    "DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY6", \
    "DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY7", \
    "DRV_SNMP_FCM_PORT_CLASS3_RX_FRAMES", \
    "DRV_SNMP_FCM_PORT_CLASS3_TX_FRAMES", \
    "DRV_SNMP_FCM_PORT_CLASS3_DISCARDS", \
    "DRV_SNMP_FCM_PORT_CLASS2_RX_FRAMES", \
    "DRV_SNMP_FCM_PORT_CLASS2_TX_FRAMES", \
    "DRV_SNMP_FCM_PORT_CLASS2_DISCARDS", \
    "DRV_SNMP_FCM_PORT_INVALID_CRCS", \
    "DRV_SNMP_FCM_PORT_DELIMITER_ERRORS"  \
}
#endif /* __ROBO_STAT_H__ */

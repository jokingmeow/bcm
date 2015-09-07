/*
 * $Id: robo_stat.h 1.12 Broadcom SDK $
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
    DRV_SNMP_IF_IN_OCTETS,              /* RFC 1213 */
    DRV_SNMP_IF_IN_UCAST_PKTS,          /* RFC 1213 */
    DRV_SNMP_IF_IN_N_UCAST_PKTS,        /* RFC 1213 */
    DRV_SNMP_IF_IN_DISCARDS,            /* RFC 1213 */
    DRV_SNMP_IF_IN_ERRORS,              /* RFC 1213 */
    DRV_SNMP_IF_IN_UNKNOWN_PROTOS,      /* RFC 1213 */
    DRV_SNMP_IF_OUT_OCTETS,             /* RFC 1213 */
    DRV_SNMP_IF_OUT_UCAST_PKTS,         /* RFC 1213 */
    DRV_SNMP_IF_OUT_N_UCAST_PKTS,       /* RFC 1213 */
    DRV_SNMP_IF_OUT_DISCARDS,           /* RFC 1213 */
    DRV_SNMP_IF_OUT_ERRORS,             /* RFC 1213 */
    DRV_SNMP_IF_OUT_Q_LEN,              /* RFC 1213 */
    DRV_SNMP_IP_IN_RECEIVES,            /* RFC 1213 */
    DRV_SNMP_IP_IN_HDR_ERRORS,          /* RFC 1213 */
    DRV_SNMP_IP_FORW_DATAGRAMS,         /* RFC 1213 */
    DRV_SNMP_IP_IN_DISCARDS,            /* RFC 1213 */
    DRV_SNMP_DOT1D_BASE_PORT_DELAY_EXCEEDED_DISCARDS, /* RFC 1493 */
    DRV_SNMP_DOT1D_BASE_PORT_MTU_EXCEEDED_DISCARDS, /* RFC 1493 */
    DRV_SNMP_DOT1D_TP_PORT_IN_FRAMES,   /* RFC 1493 */
    DRV_SNMP_DOT1D_TP_PORT_OUT_FRAMES,  /* RFC 1493 */
    DRV_SNMP_DOT1D_PORT_IN_DISCARDS,    /* RFC 1493 */
    DRV_SNMP_ETHER_STATS_DROP_EVENTS,   /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_MULTICAST_PKTS, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_BROADCAST_PKTS, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_UNDERSIZE_PKTS, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_FRAGMENTS,     /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_PKTS64_OCTETS, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_PKTS65TO127_OCTETS, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_PKTS128TO255_OCTETS, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_PKTS256TO511_OCTETS, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_PKTS512TO1023_OCTETS, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_PKTS1024TO1518_OCTETS, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_OVERSIZE_PKTS, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_RX_OVERSIZE_PKTS,    /* Rx component of
                                           snmpEtherStatsOversizePkts */
    DRV_SNMP_ETHER_TX_OVERSIZE_PKTS,    /* Tx component of
                                           snmpEtherStatsOversizePkts */
    DRV_SNMP_ETHER_STATS_JABBERS,       /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_OCTETS,        /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_PKTS,          /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_COLLISIONS,    /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_CRC_ALIGN_ERRORS, /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_TX_NO_ERRORS,  /* RFC 1757 (EtherStat) */
    DRV_SNMP_ETHER_STATS_RX_NO_ERRORS,  /* RFC 1757 (EtherStat) */
    DRV_SNMP_DOT3_STATS_ALIGNMENT_ERRORS, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_FCS_ERRORS,     /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_SINGLE_COLLISION_FRAMES, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_MULTIPLE_COLLISION_FRAMES, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_SQET_TEST_ERRORS, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_DEFERRED_TRANSMISSIONS, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_LATE_COLLISIONS, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_EXCESSIVE_COLLISIONS, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_INTERNAL_MAC_TRANSMIT_ERRORS, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_CARRIER_SENSE_ERRORS, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_FRAME_TOO_LONGS, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_INTERNAL_MAC_RECEIVE_ERRORS, /* RFC 2665 */
    DRV_SNMP_DOT3_STATS_SYMBOL_ERRORS,  /* RFC 2665 */
    DRV_SNMP_DOT3_CONTROL_IN_UNKNOWN_OPCODES, /* RFC 2665 */
    DRV_SNMP_DOT3_IN_PAUSE_FRAMES,      /* RFC 2665 */
    DRV_SNMP_DOT3_OUT_PAUSE_FRAMES,     /* RFC 2665 */
    DRV_SNMP_IF_HC_IN_OCTETS,           /* RFC 2233 */
    DRV_SNMP_IF_HC_IN_UCAST_PKTS,       /* RFC 2233 */
    DRV_SNMP_IF_HC_IN_MULTICAST_PKTS,   /* RFC 2233 */
    DRV_SNMP_IF_HC_IN_BROADCAST_PKTS,   /* RFC 2233 */
    DRV_SNMP_IF_HC_OUT_OCTETS,          /* RFC 2233 */
    DRV_SNMP_IF_HC_OUT_UCAST_PKTS,      /* RFC 2233 */
    DRV_SNMP_IF_HC_OUT_MULTICAST_PKTS,  /* RFC 2233 */
    DRV_SNMP_IF_HC_OUT_BROADCAST_PCKTS, /* RFC 2233 */
    DRV_SNMP_IPV6_IF_STATS_IN_RECEIVES, /* RFC 2465 */
    DRV_SNMP_IPV6_IF_STATS_IN_HDR_ERRORS, /* RFC 2465 */
    DRV_SNMP_IPV6_IF_STATS_IN_ADDR_ERRORS, /* RFC 2465 */
    DRV_SNMP_IPV6_IF_STATS_IN_DISCARDS, /* RFC 2465 */
    DRV_SNMP_IPV6_IF_STATS_OUT_FORW_DATAGRAMS, /* RFC 2465 */
    DRV_SNMP_IPV6_IF_STATS_OUT_DISCARDS, /* RFC 2465 */
    DRV_SNMP_IPV6_IF_STATS_IN_MCAST_PKTS, /* RFC 2465 */
    DRV_SNMP_IPV6_IF_STATS_OUT_MCAST_PKTS, /* RFC 2465 */
    DRV_SNMP_IF_IN_BROADCAST_PKTS,      /* RFC 1573 */
    DRV_SNMP_IF_IN_MULTICAST_PKTS,      /* RFC 1573 */
    DRV_SNMP_IF_OUT_BROADCAST_PKTS,     /* RFC 1573 */
    DRV_SNMP_IF_OUT_MULTICAST_PKTS,     /* RFC 1573 */
    DRV_SNMP_IEEE8021_PFC_REQUESTS,     /* IEEE 802.1bb */
    DRV_SNMP_IEEE8021_PFC_INDICATIONS,  /* IEEE 802.1bb */
    DRV_SNMP_BCM_RECEIVED_UNDERSIZE_PKTS, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_UNDERSIZE_PKTS, /* Broadcom-specific */
    DRV_SNMP_BCM_IPMC_BRIDGED_PCKTS,    /* Broadcom-specific */
    DRV_SNMP_BCM_IPMC_ROUTED_PCKTS,     /* Broadcom-specific */
    DRV_SNMP_BCM_IPMC_IN_DROPPED_PCKTS, /* Broadcom-specific */
    DRV_SNMP_BCM_IPMC_OUT_DROPPED_PCKTS, /* Broadcom-specific */
    DRV_SNMP_BCM_ETHER_STATS_PKTS1519TO1522_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_ETHER_STATS_PKTS1522TO2047_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_ETHER_STATS_PKTS2048TO4095_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_ETHER_STATS_PKTS4095TO9216_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS64_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS65TO127_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS128TO255_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS256TO511_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS512TO1023_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS1024TO1518_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS1519TO2047_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS2048TO4095_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS4095TO9216_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS64_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS65TO127_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS128TO255_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS256TO511_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS512TO1023_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS1024TO1518_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS1519TO2047_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS2048TO4095_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS4095TO9216_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_TX_CONTROL_CELLS,      /* Fabric TX Control cells counter.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_TX_DATA_CELLS,         /* Fabric TX Data cell counter.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_TX_DATA_BYTES,         /* Fabric TX Data byte counter.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_CRC_ERRORS,         /* Fabric RX CRC errors counter.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_FEC_CORRECTABLE,    /* Fabric RX LFEC/FEC correctable error.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_BEC_CRC_ERRORS,     /* Fabric RX BEC crc error.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_DISPARITY_ERRORS,   /* Fabric RX 8b/10b disparity errors.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_CONTROL_CELLS,      /* Fabric RX Control cells counter.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_DATA_CELLS,         /* Fabric RX Data cell counter.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_DATA_BYTES,         /* Fabric RX Data byte counter.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_DROPPED_RETRANSMITTED_CONTROL, /* Fabric RX dropped retransmitted
                                           control. (Broadcom-specific) */
    DRV_SNMP_BCM_TX_BEC_RETRANSMIT,     /* Fabric TX BEC retransmit.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_BEC_RETRANSMIT,     /* Fabric RX BEC retransmit.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_TX_ASYN_FIFO_RATE,     /* Fabric TX Asyn fifo rate at units of
                                           40 bits. (Broadcom-specific) */
    DRV_SNMP_BCM_RX_ASYN_FIFO_RATE,     /* Fabric RX Asyn fifo rate at units of
                                           40 bits. (Broadcom-specific) */
    DRV_SNMP_BCM_RX_FEC_UNCORRECTABLE,  /* Fabric RX LFEC/FEC uncorrectable
                                           erros. (Broadcom-specific) */
    DRV_SNMP_BCM_RX_BEC_RX_FAULT,       /* Fabric RX BEC RX fault.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_CODE_ERRORS,        /* Fabric RX 8b/10b code errors.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_LLFC_PRIMARY,       /* Fabric RX LLFC Primary.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_RX_LLFC_SECONDARY,     /* Fabric RX LLFC Secondary.
                                           (Broadcom-specific) */
    DRV_SNMP_BCM_CUSTOM_RECEIVE0,       /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_RECEIVE1,       /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_RECEIVE2,       /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_RECEIVE3,       /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_RECEIVE4,       /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_RECEIVE5,       /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_RECEIVE6,       /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_RECEIVE7,       /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_RECEIVE8,       /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT0,      /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT1,      /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT2,      /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT3,      /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT4,      /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT5,      /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT6,      /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT7,      /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT8,      /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT9,      /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT10,     /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT11,     /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT12,     /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT13,     /* Broadcom-specific */
    DRV_SNMP_BCM_CUSTOM_TRANSMIT14,     /* Broadcom-specific */
    DRV_SNMP_DOT3_STATS_IN_RANGE_LENGTH_ERROR, /* RFC 1284 */
    DRV_SNMP_DOT3_OMP_EMULATION_CRC8_ERRORS, /* RFC 4837 */
    DRV_SNMP_DOT3_MPCP_RX_GATE,         /* RFC 4837 */
    DRV_SNMP_DOT3_MPCP_RX_REGISTER,     /* RFC 4837 */
    DRV_SNMP_DOT3_MPCP_TX_REG_REQUEST,  /* RFC 4837 */
    DRV_SNMP_DOT3_MPCP_TX_REG_ACK,      /* RFC 4837 */
    DRV_SNMP_DOT3_MPCP_TX_REPORT,       /* RFC 4837 */
    DRV_SNMP_DOT3_EPON_FEC_CORRECTED_BLOCKS, /* RFC 4837 */
    DRV_SNMP_DOT3_EPON_FEC_UNCORRECTABLE_BLOCKS, /* RFC 4837 */
    DRV_SNMP_BCM_PON_IN_DROPPED_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_PON_OUT_DROPPED_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_PON_IN_DELAYED_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_PON_OUT_DELAYED_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_PON_IN_DELAYED_HUNDRED_US, /* Broadcom-specific */
    DRV_SNMP_BCM_PON_OUT_DELAYED_HUNDRED_US, /* Broadcom-specific */
    DRV_SNMP_BCM_PON_IN_FRAME_ERRORS,   /* Broadcom-specific */
    DRV_SNMP_BCM_PON_IN_OAM_FRAMES,     /* Broadcom-specific */
    DRV_SNMP_BCM_PON_OUT_OAM_FRAMES,    /* Broadcom-specific */
    DRV_SNMP_BCM_PON_OUT_UNUSED_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_ETHER_STATS_PKTS9217TO16383_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_RECEIVED_PKTS9217TO16383_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_TRANSMITTED_PKTS9217TO16383_OCTETS, /* Broadcom-specific */
    DRV_SNMP_BCM_RX_VLAN_TAG_FRAME,     /* Broadcom-specific */
    DRV_SNMP_BCM_RX_DOUBLE_VLAN_TAG_FRAME, /* Broadcom-specific */
    DRV_SNMP_BCM_TX_VLAN_TAG_FRAME,     /* Broadcom-specific */
    DRV_SNMP_BCM_TX_DOUBLE_VLAN_TAG_FRAME, /* Broadcom-specific */
    DRV_SNMP_BCM_RX_P_F_C_CONTROL_FRAME, /* PFC Receive Control Frame */
    DRV_SNMP_BCM_TX_P_F_C_CONTROL_FRAME, /* PFC Transmit Control Frame */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY0, /* Receive PFC Frame Priority 0 XON to
                                           XOFF */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY1, /* Receive PFC Frame Priority 1 XON to
                                           XOFF */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY2, /* Receive PFC Frame Priority 2 XON to
                                           XOFF */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY3, /* Receive PFC Frame Priority 3 XON to
                                           XOFF */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY4, /* Receive PFC Frame Priority 4 XON to
                                           XOFF */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY5, /* Receive PFC Frame Priority 5 XON to
                                           XOFF */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY6, /* Receive PFC Frame Priority 6 XON to
                                           XOFF */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_XON_PRIORITY7, /* Receive PFC Frame Priority 7 XON to
                                           XOFF */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY0, /* Receive PFC Frame Priority 0 */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY1, /* Receive PFC Frame Priority 1 */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY2, /* Receive PFC Frame Priority 2 */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY3, /* Receive PFC Frame Priority 3 */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY4, /* Receive PFC Frame Priority 4 */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY5, /* Receive PFC Frame Priority 5 */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY6, /* Receive PFC Frame Priority 6 */
    DRV_SNMP_BCM_RX_P_F_C_FRAME_PRIORITY7, /* Receive PFC Frame Priority 7 */
    DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY0, /* Transmit PFC Frame Priority 0 */
    DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY1, /* Transmit PFC Frame Priority 1 */
    DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY2, /* Transmit PFC Frame Priority 2 */
    DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY3, /* Transmit PFC Frame Priority 3 */
    DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY4, /* Transmit PFC Frame Priority 4 */
    DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY5, /* Transmit PFC Frame Priority 5 */
    DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY6, /* Transmit PFC Frame Priority 6 */
    DRV_SNMP_BCM_TX_P_F_C_FRAME_PRIORITY7, /* Transmit PFC Frame Priority 7 */
    DRV_SNMP_FCM_PORT_CLASS3_RX_FRAMES, /* RFC 4044 */
    DRV_SNMP_FCM_PORT_CLASS3_TX_FRAMES, /* RFC 4044 */
    DRV_SNMP_FCM_PORT_CLASS3_DISCARDS,  /* RFC 4044 */
    DRV_SNMP_FCM_PORT_CLASS2_RX_FRAMES, /* RFC 4044 */
    DRV_SNMP_FCM_PORT_CLASS2_TX_FRAMES, /* RFC 4044 */
    DRV_SNMP_FCM_PORT_CLASS2_DISCARDS,  /* RFC 4044 */
    DRV_SNMP_FCM_PORT_INVALID_CRCS,     /* RFC 4044 */
    DRV_SNMP_FCM_PORT_DELIMITER_ERRORS, /* RFC 4044 */
    DRV_SNMP_VAL_COUNT 
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

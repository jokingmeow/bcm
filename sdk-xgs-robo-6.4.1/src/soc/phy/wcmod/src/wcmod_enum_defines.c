/*
 * $Id: wcmod_enum_defines.c,v 1.10 Broadcom SDK $
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
 */
#include <sal/types.h>
/* FILE: wcmod_enum_defines.c */
/* DATE: Mon Jun 13 10:28:56 PDT 2011 */


/* This file is automatically generated. Do not modify it. Modify the
 * inc/enum_desc.txt to change enums, elems, or comments. For issues about
 * the process that creates this file contact the wcmod development team.
 */

#include "wcmod_enum_defines.h"

char* e2s_wcmod_lane_select [CNT_wcmod_lane_select] = {
  "WCMOD_LANE_0_0_0_1" ,
  "WCMOD_LANE_0_0_1_0" ,
  "WCMOD_LANE_0_0_1_1" ,
  "WCMOD_LANE_0_1_0_0" ,
  "WCMOD_LANE_0_1_0_1" ,
  "WCMOD_LANE_0_1_1_0" ,
  "WCMOD_LANE_0_1_1_1" ,
  "WCMOD_LANE_1_0_0_0" ,
  "WCMOD_LANE_1_0_0_1" ,
  "WCMOD_LANE_1_0_1_0" ,
  "WCMOD_LANE_1_0_1_1" ,
  "WCMOD_LANE_1_1_0_0" ,
  "WCMOD_LANE_1_1_0_1" ,
  "WCMOD_LANE_1_1_1_0" ,
  "WCMOD_LANE_1_1_1_1" ,
  "WCMOD_LANE_BCST" ,
  "WCMOD_LANE_0_0_0_1_0_0_0_0" ,
  "WCMOD_LANE_0_0_1_0_0_0_0_0" ,
  "WCMOD_LANE_0_1_0_0_0_0_0_0" ,
  "WCMOD_LANE_1_0_0_0_0_0_0_0" ,
  "WCMOD_LANE_0_0_0_1_0_0_0_1" ,
  "WCMOD_LANE_1_1_1_1_1_1_1_1" ,
  "WCMOD_LANE_ILLEGAL" 
}; /* e2s_wcmod_lane_select */

int e2n_wcmod_lane_select [CNT_wcmod_lane_select] = {
  1 ,
  2 ,
  3 ,
  4 ,
  5 ,
  6 ,
  7 ,
  8 ,
  9 ,
  10 ,
  11 ,
  12 ,
  13 ,
  14 ,
  15 ,
  15 ,
  16,
  32,
  64,
  128,
  17,
  255,
  0 
}; /* e2n_wcmod_lane_select */

char* e2s_wcmod_spd_intfc_set [CNT_wcmod_spd_intfc_set] = {
  "WCMOD_SPD_ZERO" ,
  "WCMOD_SPD_10_SGMII" ,
  "WCMOD_SPD_100_SGMII" ,
  "WCMOD_SPD_100_FX" ,
  "WCMOD_SPD_1000_SGMII" ,
  "WCMOD_SPD_2000" ,
  "WCMOD_SPD_1000_FIBER" ,
  "WCMOD_SPD_2500" ,
  "WCMOD_SPD_5000" ,
  "WCMOD_SPD_6000" ,
  "WCMOD_SPD_10000_HI" ,
  "WCMOD_SPD_10000" ,
  "WCMOD_SPD_12000_HI" ,
  "WCMOD_SPD_12500" ,
  "WCMOD_SPD_13000" ,
  "WCMOD_SPD_15000" ,
  "WCMOD_SPD_16000" ,
  "WCMOD_SPD_5000_SINGLE" ,
  "WCMOD_SPD_6364_SINGLE" ,
  "WCMOD_SPD_20000" ,
  "WCMOD_SPD_21000" ,
  "WCMOD_SPD_25455" ,
  "WCMOD_SPD_10000_HI_DXGXS" ,
  "WCMOD_SPD_10000_DXGXS" ,
  "WCMOD_SPD_10500_HI_DXGXS" ,
  "WCMOD_SPD_10500_DXGXS" ,
  "WCMOD_SPD_12773_HI_DXGXS" ,
  "WCMOD_SPD_12773_DXGXS" ,
  "WCMOD_SPD_31500" ,
  "WCMOD_SPD_40G" ,
  "WCMOD_SPD_42G" ,
  "WCMOD_SPD_10000_XFI" ,
  "WCMOD_SPD_10000_SFI" ,
  "WCMOD_SPD_10600_XFI_HG" ,
  "WCMOD_SPD_20000_SCR" ,
  "WCMOD_SPD_10000_HI_DXGXS_SCR" ,
  "WCMOD_SPD_10000_DXGXS_SCR" ,
  "WCMOD_SPD_X2_10000" ,
  "WCMOD_SPD_X2_23000" ,
  "WCMOD_SPD_20000_HI_DXGXS" ,
  "WCMOD_SPD_40G_KR4" ,
  "WCMOD_SPD_40G_CR4" ,
  "WCMOD_SPD_15750_HI_DXGXS" ,
  "WCMOD_SPD_21G_HI_DXGXS" ,
  "WCMOD_SPD_R2_12000" ,
  "WCMOD_SPD_PCSBYP_3P125G" ,
  "WCMOD_SPD_PCSBYP_5G" ,
  "WCMOD_SPD_PCSBYP_5P75G" ,
  "WCMOD_SPD_PCSBYP_6P25G" ,
  "WCMOD_SPD_PCSBYP_10P3125" ,
  "WCMOD_SPD_PCSBYP_10P9375" ,
  "WCMOD_SPD_PCSBYP_11P5" ,
  "WCMOD_SPD_11P5" ,
  "WCMOD_SPD_PCSBYP_12P5" ,
  "WCMOD_SPD_12P5" ,
  "WCMOD_SPD_40G_XLAUI" ,
  "WCMOD_SPD_42G_XLAUI" ,
  "WCMOD_SPD_42G_KR4" ,
  "WCMOD_SPD_20G_DXGXS" ,
  "WCMOD_SPD_20G_KR2" ,
  "WCMOD_SPD_20G_CR2" ,
  "WCMOD_SPD_100G_CR10" ,
  "WCMOD_SPD_120G_CR12" ,
  "WCMOD_SPD_CUSTOM_BYPASS",
  "WCMOD_SPD_1G_QSGMII" ,
  "WCMOD_SPD_48G",
  "WCMOD_SPD_20G_DXGXS_SCR" ,
  "WCMOD_SPD_ILLEGAL" 
}; /* e2s_wcmod_spd_intfc_set */

int e2n_wcmod_spd_intfc_set [CNT_wcmod_spd_intfc_set] = {
  0 ,
  10 ,
  100 ,
  100 ,
  1000 ,
  1000 ,
  1000 ,
  2500 ,
  5000 ,
  6000 ,
  10000 ,
  10000 ,
  12000 ,
  12500 ,
  13000 ,
  15000 ,
  16000 ,
  5000 ,
  6364 ,
  20000 ,
  21000 ,
  25455 ,
  10000 ,
  10000 ,
  10500 ,
  10500 ,
  12773 ,
  12773 ,
  31500 ,
  40000 ,
  42000 ,
  10000 ,
  10000 ,
  10500 ,
  20000 ,
  10000 ,
  10000 ,
  10000 ,
  23000 ,
  20000 ,
  40000 ,
  40000 ,
  15750 ,
  20000 ,
  12000 ,
  3125 ,
  5000,
  5750 ,
  6250 ,
  10312 ,
  10937 ,
  11500 ,
  11500 ,
  12500 ,
  12500 ,
  40000 ,
  42000 ,
  42000 ,
  20000 ,
  20000 ,
  20000 ,
  100000 ,
  120000 ,
  9999 ,
  1000,
  48000,
  20000,
  0 
}; /* e2n_wcmod_spd_intfc_set */

char* e2s_wcmod_mdio_type [CNT_wcmod_mdio_type] = {
  "WCMOD_MDIO_CL22" ,
  "WCMOD_MDIO_CL45" ,
  "WCMOD_MDIO_CL22_IEEE" ,
  "WCMOD_MDIO_PCB" ,
  "WCMOD_MDIO_ILLEGAL" 
}; /* e2s_wcmod_mdio_type */

char* e2s_wcmod_port_type [CNT_wcmod_port_type] = {
  "WCMOD_COMBO" ,
  "WCMOD_INDEPENDENT" ,
  "WCMOD_DXGXS" ,
  "WCMOD_PORT_MODE_ILLEGAL" 
}; /* e2s_wcmod_port_type */

char* e2s_wcmod_os_type [CNT_wcmod_os_type] = {
  "WCMOD_OS1" ,
  "WCMOD_OS3" ,
  "WCMOD_OS5" ,
  "WCMOD_OS6" ,
  "WCMOD_OS_IND_LANE" ,
  "WCMOD_OS8" ,
  "WCMOD_OS_ILLEGAL" 
}; /* e2s_wcmod_os_type */

char* e2s_wcmod_duplex_type [CNT_wcmod_duplex_type] = {
  "WCMOD_SIMPLEX" ,
  "WCMOD_HALF_DUPLEX" ,
  "WCMOD_DUPLEX" ,
  "WCMOD_DUPLEX_ILLEGAL" 
}; /* e2s_wcmod_duplex_type */

char* e2s_wcmod_diag_type [CNT_wcmod_diag_type] = {
  "WCMOD_DIAG_GENERAL" ,
  "WCMOD_DIAG_LINK" ,
  "WCMOD_DIAG_ANEG" ,
  "WCMOD_DIAG_TFC" ,
  "WCMOD_DIAG_DFE" ,
  "WCMOD_DIAG_SLICERS" ,
  "WCMOD_DIAG_TX_AMPS" ,
  "WCMOD_DIAG_TX_TAPS" ,
  "WCMOD_DIAG_RX_TAPS" ,
  "WCMOD_DIAG_IEEE" ,
  "WCMOD_DIAG_TOPOLOGY" ,
  "WCMOD_DIAG_EEE" ,
  "WCMOD_DIAG_EYE" ,
  "WCMOD_DIAG_SPEED" ,
  "WCMOD_DIAG_TX_LOOPBACK" ,
  "WCMOD_DIAG_RX_LOOPBACK" ,
  "WCMOD_DIAG_RX_PPM" ,
  "WCMOD_DIAG_PRBS" ,
  "WCMOD_DIAG_RX_SIGDET" ,
  "WCMOD_DIAG_POLARITY",
  "WCMOD_DIAG_RX_PCS_BYPASS_LOOPBACK" ,
  "WCMOD_DIAG_PRBS_DECOUPLE_TX" ,
  "WCMOD_DIAG_PRBS_DECOUPLE_RX" ,
  "WCMOD_DIAG_ALL" ,
  "WCMOD_DIAG_ILLEGAL" 
}; /* e2s_wcmod_diag_type */

char* e2s_wcmod_model_type [CNT_wcmod_model_type] = {
  "WCMOD_WC" ,
  "WCMOD_WC_A0" ,
  "WCMOD_WC_A1" ,
  "WCMOD_WC_A2" ,
  "WCMOD_WC_B0" ,
  "WCMOD_WC_B1" ,
  "WCMOD_WC_B2" ,
  "WCMOD_WC_C0" ,
  "WCMOD_WC_C1" ,
  "WCMOD_WC_C2" ,
  "WCMOD_WC_D0" ,
  "WCMOD_WC_D1" ,
  "WCMOD_WC_D2" ,
  "WCMOD_XN" ,
  "WCMOD_WL" ,
  "WCMOD_WL_A0" ,
  "WCMOD_QS" ,
  "WCMOD_QS_A0" ,
  "WCMOD_QS_B0" ,
  "WCMOD_MODEL_TYPE_ILLEGAL" 
}; /* e2s_wcmod_model_type */

char* e2s_wcmod_an_type [CNT_wcmod_an_type] = {
  "WCMOD_CL73" ,
  "WCMOD_CL37" ,
  "WCMOD_CL73_BAM" ,
  "WCMOD_CL37_BAM" ,
  "WCMOD_AN_TYPE_ILLEGAL" 
}; /* e2s_wcmod_an_type */

char* e2s_wcmod_tech_ability [CNT_wcmod_tech_ability] = {
  "WCMOD_ABILITY_1G_KX" ,
  "WCMOD_ABILITY_10G_KX4" ,
  "WCMOD_ABILITY_10G_KR" ,
  "WCMOD_ABILITY_40G_KR4" ,
  "WCMOD_ABILITY_40G_CR4" ,
  "WCMOD_ABILITY_100G_CR10" ,
  "WCMOD_ABILITY_2P5G" ,
  "WCMOD_ABILITY_5G_X4" ,
  "WCMOD_ABILITY_6G_X4" ,
  "WCMOD_ABILITY_10G_HIGIG" ,
  "WCMOD_ABILITY_10G_CX4" ,
  "WCMOD_ABILITY_12G_X4" ,
  "WCMOD_ABILITY_12P5_X4" ,
  "WCMOD_ABILITY_13G_X4" ,
  "WCMOD_ABILITY_15G_X4" ,
  "WCMOD_ABILITY_16G_X4" ,
  "WCMOD_ABILITY_20G_X4" ,
  "WCMOD_ABILITY_40G" ,
  "WCMOD_ABILITY_31P5G" ,
  "WCMOD_ABILITY_25P455G" ,
  "WCMOD_ABILITY_21G_X4" ,
  "WCMOD_ABILITY_20G_X4S" ,
  "WCMOD_ABILITY_10G_DXGXS_HIGIG" ,
  "WCMOD_ABILITY_10G_DXGXS" ,
  "WCMOD_ABILITY_10P5G_DXGXS" ,
  "WCMOD_ABILITY_12P5_DXGXS" ,
  "WCMOD_ABILITY_20G_KR2_HIGIG" ,
  "WCMOD_ABILITY_20G_KR2" ,
  "WCMOD_ABILITY_15P75G_R2" ,
  "WCMOD_ABILITY_ILLEGAL" 
}; /* e2s_wcmod_tech_ability */

int e2n_wcmod_tech_ability [CNT_wcmod_tech_ability] = {
  0x5 ,
  0x6 ,
  0x7 ,
  0x8 ,
  0x9 ,
  0xa ,
  0x100 ,
  0x101 ,
  0x102 ,
  0x103 ,
  0x104 ,
  0x105 ,
  0x106 ,
  0x107 ,
  0x108 ,
  0x109 ,
  0x10a ,
  0x305 ,
  0x307 ,
  0x308 ,
  0x309 ,
  0x400 ,
  0x401 ,
  0x402 ,
  0x403 ,
  0x404 ,
  0x405 ,
  0x406 ,
  0x407 ,
  0x999 
}; /* e2n_wcmod_tech_ability */

char* e2s_wcmod_eye_direction [CNT_wcmod_eye_direction] = {
  "WCMOD_EYE_VU" ,
  "WCMOD_EYE_VD" ,
  "WCMOD_EYE_HL" ,
  "WCMOD_EYE_HR" ,
  "WCMOD_EYE_ILLEGAL" 
}; /* e2s_wcmod_eye_direction */


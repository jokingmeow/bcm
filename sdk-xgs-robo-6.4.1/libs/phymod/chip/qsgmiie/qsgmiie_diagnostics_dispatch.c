/*
 *         
 * $Id: phymod.xml,v 1.1.2.5 Broadcom SDK $
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
 *     
 * DO NOT EDIT THIS FILE!
 *
 */

#include <phymod/phymod.h>
#include <phymod/phymod_diagnostics.h>
#include <phymod/phymod_diagnostics_dispatch.h>

#ifdef PHYMOD_QSGMIIE_SUPPORT

#include <phymod/chip/qsgmiie_diagnostics.h>

__phymod_diagnostics__dispatch__t__ phymod_diagnostics_qsgmiie_diagnostics_driver = {

    qsgmiie_phy_rx_slicer_position_set,
    qsgmiie_phy_rx_slicer_position_get,
    qsgmiie_phy_rx_slicer_position_max_get,
    qsgmiie_phy_prbs_config_set,
    qsgmiie_phy_prbs_config_get,
    qsgmiie_phy_prbs_enable_set,
    qsgmiie_phy_prbs_enable_get,
    qsgmiie_phy_prbs_status_get,
    qsgmiie_phy_pattern_config_set,
    qsgmiie_phy_pattern_config_get,
    qsgmiie_phy_pattern_enable_set,
    qsgmiie_phy_pattern_enable_get,
    qsgmiie_core_diagnostics_get,
    qsgmiie_phy_diagnostics_get,
    NULL, /* phymod_phy_pmd_info_dump */
    NULL, /* phymod_phy_pcs_info_dump */
    NULL, /* phymod_phy_meas_lowber_eye */
    NULL, /* phymod_phy_display_lowber_eye */
    NULL, /* phymod_phy_pmd_ber_end_cmd */
    NULL, /* phymod_phy_meas_eye_scan_start */
    NULL, /* phymod_phy_read_eye_scan_stripe */
    NULL, /* phymod_phy_display_eye_scan_header */
    NULL, /* phymod_phy_display_eye_scan_stripe */
    NULL, /* phymod_phy_display_eye_scan_footer */
    NULL, /* phymod_phy_meas_eye_scan_done */
    NULL, /* phymod_phy_eye_scan_debug_info_dump */
};

#endif /* PHYMOD_QSGMIIE_SUPPORT */

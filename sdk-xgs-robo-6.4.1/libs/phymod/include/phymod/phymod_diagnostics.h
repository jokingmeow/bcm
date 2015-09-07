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

#ifndef _PHYMOD_DIAGNOSTICS_H__H_
#define _PHYMOD_DIAGNOSTICS_H__H_

#include <phymod/phymod_definitions.h>
#include <phymod/phymod.h>
typedef struct phymod_slicer_position_s {
    uint32_t horizontal;
    uint32_t vertical;
} phymod_slicer_position_t;

/* phymod_slicer_position_t initialization and validation */
int phymod_slicer_position_t_validate(const phymod_slicer_position_t* phymod_slicer_position);
int phymod_slicer_position_t_init(phymod_slicer_position_t* phymod_slicer_position);

/*! 
 * @brief Flags for phymod_phy_rx_slicer_position_set/get APIs 
 */ 
#define PHYMOD_SLICER_FLAGS_LIVE_LINK 0x1 /**< Use the live-link slicer */

/*! 
 * phymod_phy_rx_slicer_position_set
 *
 * @brief Set/get slicer position 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  flags           - 
 * @param [in]  position        - Slicer location to set
 */
int phymod_phy_rx_slicer_position_set(const phymod_phy_access_t* phy, uint32_t flags, const phymod_slicer_position_t* position);
/*! 
 * phymod_phy_rx_slicer_position_get
 *
 * @brief Set/get slicer position 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  flags           - 
 * @param [out]  position        - Current slicer position
 */
int phymod_phy_rx_slicer_position_get(const phymod_phy_access_t* phy, uint32_t flags, phymod_slicer_position_t* position);

/*! 
 * phymod_phy_rx_slicer_position_max_get
 *
 * @brief Get slicer range limitation 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  flags           - 
 * @param [in]  position_min    - Slicer minimum position
 * @param [in]  position_max    - Slicer maxumum position
 */
int phymod_phy_rx_slicer_position_max_get(const phymod_phy_access_t* phy, uint32_t flags, const phymod_slicer_position_t* position_min, const phymod_slicer_position_t* position_max);


/*!
 * @enum phymod_prbs_poly_e
 * @brief PRBS polynomial 
 */ 
typedef enum phymod_prbs_poly_e {
    phymodPrbsPoly7 = 0,
    phymodPrbsPoly9,
    phymodPrbsPoly11,
    phymodPrbsPoly15,
    phymodPrbsPoly23,
    phymodPrbsPoly31,
    phymodPrbsPoly58,
    phymodPrbsPolyCount
} phymod_prbs_poly_t;

#ifdef PHYMOD_DIAG
extern enum_mapping_t phymod_prbs_poly_t_mapping[];
#endif /*PHYMOD_DIAGNOSTICS_DIAG*/

/* phymod_prbs_poly_t validation */
int phymod_prbs_poly_t_validate(phymod_prbs_poly_t phymod_prbs_poly);
/*! 
 * @brief RX/TX selector. no flags means both 
 */ 
#define PHYMOD_PRBS_DIRECTION_RX 0x1 /**< Config RX */
#define PHYMOD_PRBS_DIRECTION_TX 0x2 /**< Config TX */

#define PHYMOD_PRBS_DIRECTION_RX_SET(flags) (flags |= PHYMOD_PRBS_DIRECTION_RX)
#define PHYMOD_PRBS_DIRECTION_TX_SET(flags) (flags |= PHYMOD_PRBS_DIRECTION_TX)

#define PHYMOD_PRBS_DIRECTION_IS_RX(flags) (flags & PHYMOD_PRBS_DIRECTION_RX ? 1 : 0)
#define PHYMOD_PRBS_DIRECTION_IS_TX(flags) (flags & PHYMOD_PRBS_DIRECTION_TX ? 1 : 0)


/*!
 * @struct phymod_prbs_s
 * @brief PRBS control 
 */ 
typedef struct phymod_prbs_s {
    phymod_prbs_poly_t poly;
    uint32_t invert;
} phymod_prbs_t;

/* phymod_prbs_t initialization and validation */
int phymod_prbs_t_validate(const phymod_prbs_t* phymod_prbs);
int phymod_prbs_t_init(phymod_prbs_t* phymod_prbs);

/*! 
 * phymod_phy_prbs_config_set
 *
 * @brief set/get PRBS configuration 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  flags           - see PHYMOD_PRBS_DIRECTION_
 * @param [in]  prbs            - PRBS configuration to set
 */
int phymod_phy_prbs_config_set(const phymod_phy_access_t* phy, uint32_t flags , const phymod_prbs_t* prbs);
/*! 
 * phymod_phy_prbs_config_get
 *
 * @brief set/get PRBS configuration 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  flags           - see PHYMOD_PRBS_DIRECTION_
 * @param [out]  prbs            - PRBS configuration
 */
int phymod_phy_prbs_config_get(const phymod_phy_access_t* phy, uint32_t flags , phymod_prbs_t* prbs);

/*! 
 * phymod_phy_prbs_enable_set
 *
 * @brief Set/get PRBS enable state 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  flags           - see PHYMOD_PRBS_DIRECTION_
 * @param [in]  enable          - Enable \ disable PRBS
 */
int phymod_phy_prbs_enable_set(const phymod_phy_access_t* phy, uint32_t flags , uint32_t enable);
/*! 
 * phymod_phy_prbs_enable_get
 *
 * @brief Set/get PRBS enable state 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  flags           - see PHYMOD_PRBS_DIRECTION_
 * @param [out]  enable          - PRBS state
 */
int phymod_phy_prbs_enable_get(const phymod_phy_access_t* phy, uint32_t flags , uint32_t* enable);


/*!
 * @struct phymod_prbs_status_s
 * @brief PRBS control 
 */ 
typedef struct phymod_prbs_status_s {
    uint32_t prbs_lock; /**< Whether PRBS is currently locked */
    uint32_t prbs_lock_loss; /**< Whether PRBS was unlocked since last call */
    uint32_t error_count; /**< PRBS errors count */
} phymod_prbs_status_t;

/* phymod_prbs_status_t initialization and validation */
int phymod_prbs_status_t_validate(const phymod_prbs_status_t* phymod_prbs_status);
int phymod_prbs_status_t_init(phymod_prbs_status_t* phymod_prbs_status);

/*! 
 * @brief Flags for phymod_phy_prbs_status_get API 
 */ 
#define PHYMOD_PRBS_STATUS_FLAGS_CLEAR_ON_READ 0x1 /**< Clear error counter on read */

/*! 
 * phymod_phy_prbs_status_get
 *
 * @brief Get PRBS Status 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  flags           - 
 * @param [out]  prbs_status     - PRBS status
 */
int phymod_phy_prbs_status_get(const phymod_phy_access_t* phy, uint32_t flags, phymod_prbs_status_t* prbs_status);

typedef struct phymod_pattern_s {
    uint32_t pattern_len;
    uint32_t* pattern; /**< Pattern to set */
} phymod_pattern_t;

/* phymod_pattern_t initialization and validation */
int phymod_pattern_t_validate(const phymod_pattern_t* phymod_pattern);
int phymod_pattern_t_init(phymod_pattern_t* phymod_pattern);

/*! 
 * phymod_phy_pattern_config_set
 *
 * @brief Set/get pattern state 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  pattern         - Pattern Configuration
 */
int phymod_phy_pattern_config_set(const phymod_phy_access_t* phy, const phymod_pattern_t* pattern);
/*! 
 * phymod_phy_pattern_config_get
 *
 * @brief Set/get pattern state 
 *
 * @param [in]  phy             - phy access information
 * @param [out]  pattern         - Pattern Configuration
 */
int phymod_phy_pattern_config_get(const phymod_phy_access_t* phy, phymod_pattern_t* pattern);

/*! 
 * phymod_phy_pattern_enable_set
 *
 * @brief Set/get pattern state 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  enable          - Enable \ disable pattern send \ receive
 * @param [in]  pattern         - Pattern Configuration
 */
int phymod_phy_pattern_enable_set(const phymod_phy_access_t* phy, uint32_t enable, const phymod_pattern_t* pattern);
/*! 
 * phymod_phy_pattern_enable_get
 *
 * @brief Set/get pattern state 
 *
 * @param [in]  phy             - phy access information
 * @param [out]  enable          - Pattern state
 */
int phymod_phy_pattern_enable_get(const phymod_phy_access_t* phy, uint32_t* enable);

typedef struct phymod_core_diagnostics_s {
    uint32_t temperature;
    uint32_t pll_range;
} phymod_core_diagnostics_t;

/* phymod_core_diagnostics_t initialization and validation */
int phymod_core_diagnostics_t_validate(const phymod_core_diagnostics_t* phymod_core_diagnostics);
int phymod_core_diagnostics_t_init(phymod_core_diagnostics_t* phymod_core_diagnostics);

/*! 
 * phymod_core_diagnostics_get
 *
 * @brief Get core diagnostics information 
 *
 * @param [in]  core            - core access information
 * @param [out]  diag            - Core diagnostics information
 */
int phymod_core_diagnostics_get(const phymod_core_access_t* core, phymod_core_diagnostics_t* diag);

typedef struct phymod_diag_slicer_offset_s {
    uint32_t offset_pe;
    uint32_t offset_ze;
    uint32_t offset_me;
    uint32_t offset_po;
    uint32_t offset_zo;
    uint32_t offset_mo;
} phymod_diag_slicer_offset_t;

/* phymod_diag_slicer_offset_t initialization and validation */
int phymod_diag_slicer_offset_t_validate(const phymod_diag_slicer_offset_t* phymod_diag_slicer_offset);
int phymod_diag_slicer_offset_t_init(phymod_diag_slicer_offset_t* phymod_diag_slicer_offset);

typedef struct phymod_diag_eyescan_s {
    uint32_t heye_left;
    uint32_t heye_right;
    uint32_t veye_upper;
    uint32_t veye_lower;
} phymod_diag_eyescan_t;

/* phymod_diag_eyescan_t initialization and validation */
int phymod_diag_eyescan_t_validate(const phymod_diag_eyescan_t* phymod_diag_eyescan);
int phymod_diag_eyescan_t_init(phymod_diag_eyescan_t* phymod_diag_eyescan);


/*!
 * @enum phymod_osr_mode_e
 * @brief over sample modes 
 */ 
typedef enum phymod_osr_mode_e {
    phymodOversampleMode1 = 0,
    phymodOversampleMode2,
    phymodOversampleMode3,
    phymodOversampleMode3P3,
    phymodOversampleMode4,
    phymodOversampleMode5,
    phymodOversampleMode8,
    phymodOversampleMode8P25,
    phymodOversampleMode10,
    phymodOversampleModeCount
} phymod_osr_mode_t;

#ifdef PHYMOD_DIAG
extern enum_mapping_t phymod_osr_mode_t_mapping[];
#endif /*PHYMOD_DIAGNOSTICS_DIAG*/

/* phymod_osr_mode_t validation */
int phymod_osr_mode_t_validate(phymod_osr_mode_t phymod_osr_mode);

/*!
 * @enum phymod_pmd_mode_e
 * @brief pmd modes 
 */ 
typedef enum phymod_pmd_mode_e {
    phymodPmdModeOs = 0,
    phymodPmdModeOsDfe,
    phymodPmdModeBrDfe,
    phymodPmdModeCount
} phymod_pmd_mode_t;

#ifdef PHYMOD_DIAG
extern enum_mapping_t phymod_pmd_mode_t_mapping[];
#endif /*PHYMOD_DIAGNOSTICS_DIAG*/

/* phymod_pmd_mode_t validation */
int phymod_pmd_mode_t_validate(phymod_pmd_mode_t phymod_pmd_mode);
typedef struct phymod_phy_diagnostics_s {
    uint32_t signal_detect;
    uint32_t vga_bias_reduced;
    uint32_t postc_metric;
    phymod_osr_mode_t osr_mode;
    phymod_pmd_mode_t pmd_mode;
    uint32_t rx_lock;
    uint32_t rx_ppm;
    uint32_t tx_ppm;
    uint32_t clk90_offset;
    uint32_t clkp1_offset;
    uint32_t p1_lvl;
    uint32_t m1_lvl;
    uint32_t dfe1_dcd;
    uint32_t dfe2_dcd;
    uint32_t slicer_target;
    phymod_diag_slicer_offset_t slicer_offset;
    phymod_diag_eyescan_t eyescan;
    uint32_t state_machine_status;
} phymod_phy_diagnostics_t;

/* phymod_phy_diagnostics_t initialization and validation */
int phymod_phy_diagnostics_t_validate(const phymod_phy_diagnostics_t* phymod_phy_diagnostics);
int phymod_phy_diagnostics_t_init(phymod_phy_diagnostics_t* phymod_phy_diagnostics);

typedef struct phymod_phy_eyescan_options_s {
    uint32_t linerate_in_khz;
    uint16_t timeout_in_milliseconds;
    int8_t horz_max;
    int8_t horz_min;
    int8_t hstep;
    int8_t vert_max;
    int8_t vert_min;
    int8_t vstep;
    int8_t mode;
} phymod_phy_eyescan_options_t;

/* phymod_phy_eyescan_options_t initialization and validation */
int phymod_phy_eyescan_options_t_validate(const phymod_phy_eyescan_options_t* phymod_phy_eyescan_options);
int phymod_phy_eyescan_options_t_init(phymod_phy_eyescan_options_t* phymod_phy_eyescan_options);

/*! 
 * phymod_phy_diagnostics_get
 *
 * @brief Get phy diagnostics information 
 *
 * @param [in]  phy             - phy access information
 * @param [out]  diag            - 
 */
int phymod_phy_diagnostics_get(const phymod_phy_access_t* phy, phymod_phy_diagnostics_t* diag);

/*! 
 * phymod_phy_pmd_info_dump
 *
 * @brief Get phy diagnostics information 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  type            - 
 */
int phymod_phy_pmd_info_dump(const phymod_phy_access_t* phy, char* type);

/*! 
 * phymod_phy_pcs_info_dump
 *
 * @brief Get phy diagnostics information 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  type            - 
 */
int phymod_phy_pcs_info_dump(const phymod_phy_access_t* phy, char* type);

/*! 
 * phymod_phy_meas_lowber_eye
 *
 * @brief Get phy diagnostics information 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  eyescan_options   - 
 * @param [in]  buffer          - 
 */
int phymod_phy_meas_lowber_eye(const phymod_phy_access_t* phy, phymod_phy_eyescan_options_t eyescan_options, uint32_t* buffer);

/*! 
 * phymod_phy_display_lowber_eye
 *
 * @brief Get phy diagnostics information 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  eyescan_options   - 
 * @param [in]  buffer          - 
 */
int phymod_phy_display_lowber_eye(const phymod_phy_access_t* phy, phymod_phy_eyescan_options_t eyescan_options, uint32_t* buffer);

/*! 
 * phymod_phy_pmd_ber_end_cmd
 *
 * @brief Get phy diagnostics information 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  supp_info       - 
 * @param [in]  timeout_ms      - 
 */
int phymod_phy_pmd_ber_end_cmd(const phymod_phy_access_t* phy, uint8_t supp_info, uint32_t timeout_ms);

/*! 
 * phymod_phy_meas_eye_scan_start
 *
 * @brief Get phy diagnostics information 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  direction       - 
 */
int phymod_phy_meas_eye_scan_start(const phymod_phy_access_t* phy, uint8_t direction);

/*! 
 * phymod_phy_read_eye_scan_stripe
 *
 * @brief Get phy diagnostics information 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  buffer          - 
 * @param [out]  status          - 
 */
int phymod_phy_read_eye_scan_stripe(const phymod_phy_access_t* phy, uint32_t* buffer, uint16_t* status);

/*! 
 * phymod_phy_display_eye_scan_header
 *
 * @brief Get phy diagnostics information 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  i               - 
 */
int phymod_phy_display_eye_scan_header(const phymod_phy_access_t* phy, int8_t i);

/*! 
 * phymod_phy_display_eye_scan_stripe
 *
 * @brief Get phy diagnostics information 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  y               - 
 * @param [in]  buffer          - 
 */
int phymod_phy_display_eye_scan_stripe(const phymod_phy_access_t* phy, int8_t y, uint32_t* buffer);

/*! 
 * phymod_phy_display_eye_scan_footer
 *
 * @brief Get phy diagnostics information 
 *
 * @param [in]  phy             - phy access information
 * @param [in]  i               - 
 */
int phymod_phy_display_eye_scan_footer(const phymod_phy_access_t* phy, int8_t i);

/*! 
 * phymod_phy_meas_eye_scan_done
 *
 * @brief Get phy diagnostics information 
 *
 * @param [in]  phy             - phy access information
 */
int phymod_phy_meas_eye_scan_done(const phymod_phy_access_t* phy);

/*! 
 * phymod_phy_eye_scan_debug_info_dump
 *
 * @brief Get phy diagnostics information 
 *
 * @param [in]  phy             - phy access information
 */
int phymod_phy_eye_scan_debug_info_dump(const phymod_phy_access_t* phy);

#endif /*_PHYMOD_DIAGNOSTICS_H_*/

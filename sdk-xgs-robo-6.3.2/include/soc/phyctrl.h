/*
 * $Id: phyctrl.h 1.170 Broadcom SDK $
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
 * File:        phyctrl.h
 *
 * Data structures and function prototypes for PHY register access.
 */

#ifndef _SOC_PHYCTRL_H_
#define _SOC_PHYCTRL_H_
#include <shared/port.h>
#include <sal/core/time.h>
#include <soc/portmode.h>
#include <soc/port_ability.h>
#include <soc/types.h>

/* PHY specific control settings */
typedef enum soc_phy_control_e {
    SOC_PHY_CONTROL_WAN            = _SHR_PORT_PHY_CONTROL_WAN,
    SOC_PHY_CONTROL_PREEMPHASIS    = _SHR_PORT_PHY_CONTROL_PREEMPHASIS,
    SOC_PHY_CONTROL_DRIVER_CURRENT = _SHR_PORT_PHY_CONTROL_DRIVER_CURRENT,
    SOC_PHY_CONTROL_PRE_DRIVER_CURRENT =
                          _SHR_PORT_PHY_CONTROL_PRE_DRIVER_CURRENT,
    SOC_PHY_CONTROL_EQUALIZER_BOOST =
                          _SHR_PORT_PHY_CONTROL_EQUALIZER_BOOST,
    SOC_PHY_CONTROL_INTERFACE = _SHR_PORT_PHY_CONTROL_INTERFACE,
    SOC_PHY_CONTROL_INTERFACE_MAX = _SHR_PORT_PHY_CONTROL_INTERFACE_MAX,
    SOC_PHY_CONTROL_MACSEC_SWITCH_FIXED =
                            _SHR_PORT_PHY_CONTROL_MACSEC_SWITCH_FIXED,
    SOC_PHY_CONTROL_MACSEC_SWITCH_FIXED_SPEED =
                            _SHR_PORT_PHY_CONTROL_MACSEC_SWITCH_FIXED_SPEED,
    SOC_PHY_CONTROL_MACSEC_SWITCH_FIXED_DUPLEX =
                            _SHR_PORT_PHY_CONTROL_MACSEC_SWITCH_FIXED_DUPLEX,
    SOC_PHY_CONTROL_MACSEC_SWITCH_FIXED_PAUSE =
                            _SHR_PORT_PHY_CONTROL_MACSEC_SWITCH_FIXED_PAUSE,
    SOC_PHY_CONTROL_MACSEC_PAUSE_RX_FORWARD =
                            _SHR_PORT_PHY_CONTROL_MACSEC_PAUSE_RX_FORWARD,
    SOC_PHY_CONTROL_MACSEC_PAUSE_TX_FORWARD =
                            _SHR_PORT_PHY_CONTROL_MACSEC_PAUSE_TX_FORWARD,
    SOC_PHY_CONTROL_MACSEC_LINE_IPG =
                            _SHR_PORT_PHY_CONTROL_MACSEC_LINE_IPG,
    SOC_PHY_CONTROL_MACSEC_SWITCH_IPG =
                             _SHR_PORT_PHY_CONTROL_MACSEC_SWITCH_IPG,
    SOC_PHY_CONTROL_LONGREACH_SPEED =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_SPEED,
    SOC_PHY_CONTROL_LONGREACH_PAIRS =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_PAIRS,
    SOC_PHY_CONTROL_LONGREACH_GAIN =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_GAIN,
    SOC_PHY_CONTROL_LONGREACH_AUTONEG =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_AUTONEG,
    SOC_PHY_CONTROL_LONGREACH_LOCAL_ABILITY =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_LOCAL_ABILITY,
    SOC_PHY_CONTROL_LONGREACH_REMOTE_ABILITY =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_REMOTE_ABILITY,
    SOC_PHY_CONTROL_LONGREACH_CURRENT_ABILITY =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_CURRENT_ABILITY,
    SOC_PHY_CONTROL_LONGREACH_MASTER =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_MASTER,
    SOC_PHY_CONTROL_LONGREACH_ACTIVE =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_ACTIVE,
    SOC_PHY_CONTROL_LONGREACH_ENABLE =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_ENABLE,
    SOC_PHY_CONTROL_LOOPBACK_EXTERNAL =
                             _SHR_PORT_PHY_CONTROL_LOOPBACK_EXTERNAL,
    SOC_PHY_CONTROL_CLOCK_ENABLE =
                             _SHR_PORT_PHY_CONTROL_CLOCK_ENABLE,
    SOC_PHY_CONTROL_CLOCK_SECONDARY_ENABLE =
                             _SHR_PORT_PHY_CONTROL_CLOCK_SECONDARY_ENABLE,
    SOC_PHY_CONTROL_CLOCK_FREQUENCY =
                             _SHR_PORT_PHY_CONTROL_CLOCK_FREQUENCY,
    SOC_PHY_CONTROL_PORT_PRIMARY =
                             _SHR_PORT_PHY_CONTROL_PORT_PRIMARY,
    SOC_PHY_CONTROL_PORT_OFFSET =
                             _SHR_PORT_PHY_CONTROL_PORT_OFFSET,
    SOC_PHY_CONTROL_PRE_PREEMPHASIS= _SHR_PORT_PHY_CONTROL_PRE_PREEMPHASIS,
    SOC_PHY_CONTROL_ENCODING       = _SHR_PORT_PHY_CONTROL_ENCODING,
    SOC_PHY_CONTROL_SCRAMBLER      = _SHR_PORT_PHY_CONTROL_SCRAMBLER,
    SOC_PHY_CONTROL_PRBS_POLYNOMIAL= _SHR_PORT_PHY_CONTROL_PRBS_POLYNOMIAL,
    SOC_PHY_CONTROL_PRBS_TX_INVERT_DATA =
                                     _SHR_PORT_PHY_CONTROL_PRBS_TX_INVERT_DATA,
    SOC_PHY_CONTROL_PRBS_TX_ENABLE = _SHR_PORT_PHY_CONTROL_PRBS_TX_ENABLE,
    SOC_PHY_CONTROL_PRBS_RX_ENABLE = _SHR_PORT_PHY_CONTROL_PRBS_RX_ENABLE,
    SOC_PHY_CONTROL_PRBS_RX_STATUS = _SHR_PORT_PHY_CONTROL_PRBS_RX_STATUS,
    SOC_PHY_CONTROL_SERDES_DRIVER_TUNE =
                                     _SHR_PORT_PHY_CONTROL_SERDES_DRIVER_TUNE,
    SOC_PHY_CONTROL_SERDES_DRIVER_EQUALIZATION_TUNE_STATUS_FAR_END =
          _SHR_PORT_PHY_CONTROL_SERDES_DRIVER_EQUALIZATION_TUNE_STATUS_FAR_END,
    SOC_PHY_CONTROL_8B10B          = _SHR_PORT_PHY_CONTROL_8B10B,
    SOC_PHY_CONTROL_64B66B          = _SHR_PORT_PHY_CONTROL_64B66B,
    SOC_PHY_CONTROL_POWER          = _SHR_PORT_PHY_CONTROL_POWER,
    SOC_PHY_CONTROL_POWER_AUTO_SLEEP_TIME =
                                _SHR_PORT_PHY_CONTROL_POWER_AUTO_SLEEP_TIME,
    SOC_PHY_CONTROL_POWER_AUTO_WAKE_TIME =
                                _SHR_PORT_PHY_CONTROL_POWER_AUTO_WAKE_TIME,
    SOC_PHY_CONTROL_LINKDOWN_TRANSMIT =
                                _SHR_PORT_PHY_CONTROL_LINKDOWN_TRANSMIT,
    SOC_PHY_CONTROL_EDC_CONFIG = _SHR_PORT_PHY_CONTROL_EDC_CONFIG,
    SOC_PHY_CONTROL_EDC_MODE   = _SHR_PORT_PHY_CONTROL_EDC_MODE,
    SOC_PHY_CONTROL_EEE =          _SHR_PORT_PHY_CONTROL_EEE,
    SOC_PHY_CONTROL_EEE_AUTO =     _SHR_PORT_PHY_CONTROL_EEE_AUTO,
    SOC_PHY_CONTROL_EEE_AUTO_IDLE_THRESHOLD =
                            _SHR_PORT_PHY_CONTROL_EEE_AUTO_IDLE_THRESHOLD,
    SOC_PHY_CONTROL_EEE_AUTO_BUFFER_LIMIT =
                            _SHR_PORT_PHY_CONTROL_EEE_AUTO_BUFFER_LIMIT,
    SOC_PHY_CONTROL_EEE_AUTO_FIXED_LATENCY =
                            _SHR_PORT_PHY_CONTROL_EEE_AUTO_FIXED_LATENCY,
    SOC_PHY_CONTROL_EEE_TRANSMIT_WAKE_TIME =
                            _SHR_PORT_PHY_CONTROL_EEE_TRANSMIT_WAKE_TIME,
    SOC_PHY_CONTROL_EEE_RECEIVE_WAKE_TIME =
                            _SHR_PORT_PHY_CONTROL_EEE_RECEIVE_WAKE_TIME,
    SOC_PHY_CONTROL_EEE_TRANSMIT_SLEEP_TIME =
                            _SHR_PORT_PHY_CONTROL_EEE_TRANSMIT_SLEEP_TIME,
    SOC_PHY_CONTROL_EEE_RECEIVE_SLEEP_TIME=
                            _SHR_PORT_PHY_CONTROL_EEE_RECEIVE_SLEEP_TIME,
    SOC_PHY_CONTROL_EEE_TRANSMIT_QUIET_TIME =
                            _SHR_PORT_PHY_CONTROL_EEE_TRANSMIT_QUIET_TIME,
    SOC_PHY_CONTROL_EEE_RECEIVE_QUIET_TIME =
                            _SHR_PORT_PHY_CONTROL_EEE_RECEIVE_QUIET_TIME,
    SOC_PHY_CONTROL_EEE_TRANSMIT_REFRESH_TIME =
                            _SHR_PORT_PHY_CONTROL_EEE_TRANSMIT_REFRESH_TIME,
    SOC_PHY_CONTROL_EEE_TRANSMIT_EVENTS =
                            _SHR_PORT_PHY_CONTROL_EEE_TRANSMIT_EVENTS,
    SOC_PHY_CONTROL_EEE_TRANSMIT_DURATION =
                            _SHR_PORT_PHY_CONTROL_EEE_TRANSMIT_DURATION,
    SOC_PHY_CONTROL_EEE_RECEIVE_EVENTS =
                            _SHR_PORT_PHY_CONTROL_EEE_RECEIVE_EVENTS,
    SOC_PHY_CONTROL_EEE_RECEIVE_DURATION =
                            _SHR_PORT_PHY_CONTROL_EEE_RECEIVE_DURATION,
    SOC_PHY_CONTROL_EEE_STATISTICS_CLEAR =
                            _SHR_PORT_PHY_CONTROL_EEE_STATISTICS_CLEAR,
    SOC_PHY_CONTROL_SERDES_TUNE_MARGIN_MAX =
                            _SHR_PORT_PHY_CONTROL_SERDES_TUNE_MARGIN_MAX,
    SOC_PHY_CONTROL_SERDES_TUNE_MARGIN_MODE =
                            _SHR_PORT_PHY_CONTROL_SERDES_TUNE_MARGIN_MODE,
    SOC_PHY_CONTROL_SERDES_TUNE_MARGIN_VALUE =
                            _SHR_PORT_PHY_CONTROL_SERDES_TUNE_MARGIN_VALUE,
    SOC_PHY_CONTROL_PARALLEL_DETECTION =
                            _SHR_PORT_PHY_CONTROL_PARALLEL_DETECTION,
    SOC_PHY_CONTROL_PARALLEL_DETECTION_10G =
                            _SHR_PORT_PHY_CONTROL_PARALLEL_DETECTION_10G,
    SOC_PHY_CONTROL_LOOPBACK_INTERNAL =
                            _SHR_PORT_PHY_CONTROL_LOOPBACK_INTERNAL,
    SOC_PHY_CONTROL_LOOPBACK_REMOTE =
                            _SHR_PORT_PHY_CONTROL_LOOPBACK_REMOTE,
    SOC_PHY_CONTROL_LOOPBACK_REMOTE_PCS_BYPASS =
                            _SHR_PORT_PHY_CONTROL_LOOPBACK_REMOTE_PCS_BYPASS,
    SOC_PHY_CONTROL_FORWARD_ERROR_CORRECTION =
                            _SHR_PORT_PHY_CONTROL_FORWARD_ERROR_CORRECTION,
    SOC_PHY_CONTROL_CUSTOM1 =
                            _SHR_PORT_PHY_CONTROL_CUSTOM1,
    SOC_PHY_CONTROL_BERT_PATTERN = _SHR_PORT_PHY_CONTROL_BERT_PATTERN,
    SOC_PHY_CONTROL_BERT_RUN     = _SHR_PORT_PHY_CONTROL_BERT_RUN,
    SOC_PHY_CONTROL_BERT_PACKET_SIZE = _SHR_PORT_PHY_CONTROL_BERT_PACKET_SIZE,
    SOC_PHY_CONTROL_BERT_IPG = _SHR_PORT_PHY_CONTROL_BERT_IPG,
    SOC_PHY_CONTROL_BERT_TX_PACKETS = _SHR_PORT_PHY_CONTROL_BERT_TX_PACKETS,
    SOC_PHY_CONTROL_BERT_RX_PACKETS = _SHR_PORT_PHY_CONTROL_BERT_RX_PACKETS,
    SOC_PHY_CONTROL_BERT_RX_ERROR_BITS =
               _SHR_PORT_PHY_CONTROL_BERT_RX_ERROR_BITS,
    SOC_PHY_CONTROL_BERT_RX_ERROR_BYTES =
               _SHR_PORT_PHY_CONTROL_BERT_RX_ERROR_BYTES,
    SOC_PHY_CONTROL_BERT_RX_ERROR_PACKETS =
               _SHR_PORT_PHY_CONTROL_BERT_RX_ERROR_PACKETS,
    SOC_PHY_CONTROL_PREEMPHASIS_LANE0 = _SHR_PORT_PHY_CONTROL_PREEMPHASIS_LANE0,
    SOC_PHY_CONTROL_PREEMPHASIS_LANE1 = _SHR_PORT_PHY_CONTROL_PREEMPHASIS_LANE1,
    SOC_PHY_CONTROL_PREEMPHASIS_LANE2 = _SHR_PORT_PHY_CONTROL_PREEMPHASIS_LANE2,
    SOC_PHY_CONTROL_PREEMPHASIS_LANE3 = _SHR_PORT_PHY_CONTROL_PREEMPHASIS_LANE3,
    SOC_PHY_CONTROL_DRIVER_CURRENT_LANE0 = _SHR_PORT_PHY_CONTROL_DRIVER_CURRENT_LANE0,
    SOC_PHY_CONTROL_DRIVER_CURRENT_LANE1 = _SHR_PORT_PHY_CONTROL_DRIVER_CURRENT_LANE1,
    SOC_PHY_CONTROL_DRIVER_CURRENT_LANE2 = _SHR_PORT_PHY_CONTROL_DRIVER_CURRENT_LANE2,
    SOC_PHY_CONTROL_DRIVER_CURRENT_LANE3 = _SHR_PORT_PHY_CONTROL_DRIVER_CURRENT_LANE3,
    SOC_PHY_CONTROL_PRE_DRIVER_CURRENT_LANE0 =
                          _SHR_PORT_PHY_CONTROL_PRE_DRIVER_CURRENT_LANE0,
    SOC_PHY_CONTROL_PRE_DRIVER_CURRENT_LANE1 =
                          _SHR_PORT_PHY_CONTROL_PRE_DRIVER_CURRENT_LANE1,
    SOC_PHY_CONTROL_PRE_DRIVER_CURRENT_LANE2 =
                          _SHR_PORT_PHY_CONTROL_PRE_DRIVER_CURRENT_LANE2,
    SOC_PHY_CONTROL_PRE_DRIVER_CURRENT_LANE3 =
                          _SHR_PORT_PHY_CONTROL_PRE_DRIVER_CURRENT_LANE3,
    SOC_PHY_CONTROL_TX_LANE_SQUELCH =
                _SHR_PORT_PHY_CONTROL_TX_LANE_SQUELCH,
    SOC_PHY_CONTROL_DRIVER_POST2_CURRENT =
                _SHR_PORT_PHY_CONTROL_DRIVER_POST2_CURRENT,
    SOC_PHY_CONTROL_RX_PPM =
                _SHR_PORT_PHY_CONTROL_RX_PPM,
    SOC_PHY_CONTROL_RX_PEAK_FILTER =
                _SHR_PORT_PHY_CONTROL_RX_PEAK_FILTER,
    SOC_PHY_CONTROL_RX_LOW_FREQ_PEAK_FILTER =
                _SHR_PORT_PHY_CONTROL_RX_LOW_FREQ_PEAK_FILTER,
    SOC_PHY_CONTROL_RX_VGA =
                _SHR_PORT_PHY_CONTROL_RX_VGA,
    SOC_PHY_CONTROL_RX_TAP1 =
                _SHR_PORT_PHY_CONTROL_RX_TAP1,
    SOC_PHY_CONTROL_RX_TAP2 =
                _SHR_PORT_PHY_CONTROL_RX_TAP2,
    SOC_PHY_CONTROL_RX_TAP3 =
                _SHR_PORT_PHY_CONTROL_RX_TAP3,
    SOC_PHY_CONTROL_RX_TAP4 =
                _SHR_PORT_PHY_CONTROL_RX_TAP4,
    SOC_PHY_CONTROL_RX_TAP5 =
                _SHR_PORT_PHY_CONTROL_RX_TAP5,
    SOC_PHY_CONTROL_RX_VGA_RELEASE =
                _SHR_PORT_PHY_CONTROL_RX_VGA_RELEASE,
    SOC_PHY_CONTROL_RX_TAP1_RELEASE =
                _SHR_PORT_PHY_CONTROL_RX_TAP1_RELEASE,
    SOC_PHY_CONTROL_RX_TAP2_RELEASE =
                _SHR_PORT_PHY_CONTROL_RX_TAP2_RELEASE,
    SOC_PHY_CONTROL_RX_TAP3_RELEASE =
                _SHR_PORT_PHY_CONTROL_RX_TAP3_RELEASE,
    SOC_PHY_CONTROL_RX_TAP4_RELEASE =
                _SHR_PORT_PHY_CONTROL_RX_TAP4_RELEASE,
    SOC_PHY_CONTROL_RX_TAP5_RELEASE =
                _SHR_PORT_PHY_CONTROL_RX_TAP5_RELEASE,
    SOC_PHY_CONTROL_RX_PLUS1_SLICER =
                _SHR_PORT_PHY_CONTROL_RX_PLUS1_SLICER,
    SOC_PHY_CONTROL_RX_MINUS1_SLICER =
                _SHR_PORT_PHY_CONTROL_RX_MINUS1_SLICER,
    SOC_PHY_CONTROL_RX_D_SLICER =
                _SHR_PORT_PHY_CONTROL_RX_D_SLICER,
    SOC_PHY_CONTROL_RX_SIGNAL_DETECT =
                _SHR_PORT_PHY_CONTROL_RX_SIGNAL_DETECT,
    SOC_PHY_CONTROL_RX_SEQ_DONE =
                        _SHR_PORT_PHY_CONTROL_RX_SEQ_DONE,
    SOC_PHY_CONTROL_RX_POLARITY =
                        _SHR_PORT_PHY_CONTROL_RX_POLARITY,
    SOC_PHY_CONTROL_TX_POLARITY =
                        _SHR_PORT_PHY_CONTROL_TX_POLARITY,
    SOC_PHY_CONTROL_RX_RESET =
                        _SHR_PORT_PHY_CONTROL_RX_RESET,
    SOC_PHY_CONTROL_TX_RESET =
                        _SHR_PORT_PHY_CONTROL_TX_RESET,
    SOC_PHY_CONTROL_CL72 =
                        _SHR_PORT_PHY_CONTROL_CL72,
    SOC_PHY_CONTROL_CL72_STATUS =
                        _SHR_PORT_PHY_CONTROL_CL72_STATUS,
    SOC_PHY_CONTROL_LANE_SWAP =
                        _SHR_PORT_PHY_CONTROL_LANE_SWAP,
    SOC_PHY_CONTROL_DUMP =
                        _SHR_PORT_PHY_CONTROL_DUMP,
    SOC_PHY_CONTROL_TX_PATTERN_20BIT =
                        _SHR_PORT_PHY_CONTROL_TX_PATTERN_20BIT,
    SOC_PHY_CONTROL_TX_PATTERN_256BIT =
                        _SHR_PORT_PHY_CONTROL_TX_PATTERN_256BIT,
    SOC_PHY_CONTROL_TX_PATTERN_DATA0 =
                        _SHR_PORT_PHY_CONTROL_TX_PATTERN_DATA0,
    SOC_PHY_CONTROL_TX_PATTERN_DATA1 =
                        _SHR_PORT_PHY_CONTROL_TX_PATTERN_DATA1,
    SOC_PHY_CONTROL_TX_PATTERN_DATA2 =
                        _SHR_PORT_PHY_CONTROL_TX_PATTERN_DATA2,
    SOC_PHY_CONTROL_TX_PATTERN_DATA3 =
                        _SHR_PORT_PHY_CONTROL_TX_PATTERN_DATA3,
    SOC_PHY_CONTROL_TX_PATTERN_DATA4 =
                        _SHR_PORT_PHY_CONTROL_TX_PATTERN_DATA4,
    SOC_PHY_CONTROL_TX_PATTERN_DATA5 =
                        _SHR_PORT_PHY_CONTROL_TX_PATTERN_DATA5,
    SOC_PHY_CONTROL_TX_PATTERN_DATA6 =
                        _SHR_PORT_PHY_CONTROL_TX_PATTERN_DATA6,
    SOC_PHY_CONTROL_TX_PATTERN_DATA7 =
                        _SHR_PORT_PHY_CONTROL_TX_PATTERN_DATA7,
    SOC_PHY_CONTROL_PHASE_INTERP =
            _SHR_PORT_PHY_CONTROL_PHASE_INTERP,
    SOC_PHY_CONTROL_DLL_POWER_AUTO = _SHR_PORT_PHY_CONTROL_DLL_POWER_AUTO,
    SOC_PHY_CONTROL_TX_PPM_ADJUST = _SHR_PORT_PHY_CONTROL_TX_PPM_ADJUST,
    SOC_PHY_CONTROL_FIRMWARE_MODE =
                        _SHR_PORT_PHY_CONTROL_FIRMWARE_MODE,
    SOC_PHY_CONTROL_VCO_FREQ = _SHR_PORT_PHY_CONTROL_VCO_FREQ ,
    SOC_PHY_CONTROL_PLL_DIVIDER = _SHR_PORT_PHY_CONTROL_PLL_DIVIDER ,
    SOC_PHY_CONTROL_OVERSAMPLE_MODE = _SHR_PORT_PHY_CONTROL_OVERSAMPLE_MODE,
    SOC_PHY_CONTROL_REF_CLK = _SHR_PORT_PHY_CONTROL_REF_CLK,
    SOC_PHY_CONTROL_SOFTWARE_RX_LOS = _SHR_PORT_PHY_CONTROL_SOFTWARE_RX_LOS,
    SOC_PHY_CONTROL_PRBS_DECOUPLED_TX_ENABLE =
                        _SHR_PORT_PHY_CONTROL_PRBS_DECOUPLED_TX_ENABLE,
    SOC_PHY_CONTROL_PRBS_DECOUPLED_TX_INVERT_DATA =
                        _SHR_PORT_PHY_CONTROL_PRBS_DECOUPLED_TX_INVERT_DATA,
    SOC_PHY_CONTROL_PRBS_DECOUPLED_TX_POLYNOMIAL =
                        _SHR_PORT_PHY_CONTROL_PRBS_DECOUPLED_TX_POLYNOMIAL,
    SOC_PHY_CONTROL_PRBS_DECOUPLED_RX_ENABLE =
                        _SHR_PORT_PHY_CONTROL_PRBS_DECOUPLED_RX_ENABLE,
    SOC_PHY_CONTROL_PRBS_DECOUPLED_RX_INVERT_DATA =
                        _SHR_PORT_PHY_CONTROL_PRBS_DECOUPLED_RX_INVERT_DATA,
    SOC_PHY_CONTROL_PRBS_DECOUPLED_RX_POLYNOMIAL =
                        _SHR_PORT_PHY_CONTROL_PRBS_DECOUPLED_RX_POLYNOMIAL,
    SOC_PHY_CONTROL_RX_PEAK_FILTER_TEMP_COMP = _SHR_PORT_PHY_CONTROL_RX_PEAK_FILTER_TEMP_COMP,
    SOC_PHY_CONTROL_CL73_FSM_AUTO_RECOVER = _SHR_PORT_PHY_CONTROL_CL73_FSM_AUTO_RECOVER,
    SOC_PHY_CONTROL_RX_SEQ_TOGGLE = _SHR_PORT_PHY_CONTROL_RX_SEQ_TOGGLE,
    SOC_PHY_CONTROL_DRIVER_SUPPLY = _SHR_PORT_PHY_CONTROL_DRIVER_SUPPLY,
    SOC_PHY_CONTROL_AUTONEG_MODE = _SHR_PORT_PHY_CONTROL_AUTONEG_MODE,
    SOC_PHY_CONTROL_HG2_BCM_CODEC_ENABLE = _SHR_PORT_PHY_CONTROL_HG2_BCM_CODEC_ENABLE,
    SOC_PHY_CONTROL_COUNT           /* always last */
} soc_phy_control_t;

typedef enum soc_phy_control_longreach_ability_e {
    SOC_PHY_CONTROL_LONGREACH_ABILITY_NONE =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_ABILITY_NONE,
    SOC_PHY_CONTROL_LONGREACH_ABILITY_10M_1PAIR =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_ABILITY_10M_1PAIR,
    SOC_PHY_CONTROL_LONGREACH_ABILITY_10M_2PAIR =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_ABILITY_10M_2PAIR,
    SOC_PHY_CONTROL_LONGREACH_ABILITY_20M_1PAIR =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_ABILITY_20M_1PAIR,
    SOC_PHY_CONTROL_LONGREACH_ABILITY_20M_2PAIR =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_ABILITY_20M_2PAIR,
    SOC_PHY_CONTROL_LONGREACH_ABILITY_25M_1PAIR =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_ABILITY_25M_1PAIR,
    SOC_PHY_CONTROL_LONGREACH_ABILITY_25M_2PAIR =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_ABILITY_25M_2PAIR,
    SOC_PHY_CONTROL_LONGREACH_ABILITY_33M_1PAIR =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_ABILITY_33M_1PAIR,
    SOC_PHY_CONTROL_LONGREACH_ABILITY_33M_2PAIR =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_ABILITY_33M_2PAIR,
    SOC_PHY_CONTROL_LONGREACH_ABILITY_50M_1PAIR =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_ABILITY_50M_1PAIR,
    SOC_PHY_CONTROL_LONGREACH_ABILITY_50M_2PAIR =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_ABILITY_50M_2PAIR,
    SOC_PHY_CONTROL_LONGREACH_ABILITY_100M_1PAIR =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_ABILITY_100M_1PAIR,
    SOC_PHY_CONTROL_LONGREACH_ABILITY_100M_2PAIR =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_ABILITY_100M_2PAIR,
    SOC_PHY_CONTROL_LONGREACH_ABILITY_100M_4PAIR =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_ABILITY_100M_4PAIR,
    SOC_PHY_CONTROL_LONGREACH_ABILITY_PAUSE_RX =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_ABILITY_PAUSE_RX,
    SOC_PHY_CONTROL_LONGREACH_ABILITY_PAUSE_TX =
                             _SHR_PORT_PHY_CONTROL_LONGREACH_ABILITY_PAUSE_TX
} soc_phy_control_longreach_ability_t;

typedef enum soc_phy_control_power_e {
    SOC_PHY_CONTROL_POWER_FULL = _SHR_PORT_PHY_CONTROL_POWER_FULL,
    SOC_PHY_CONTROL_POWER_LOW  = _SHR_PORT_PHY_CONTROL_POWER_LOW,
    SOC_PHY_CONTROL_POWER_AUTO = _SHR_PORT_PHY_CONTROL_POWER_AUTO,
    /*
       Power mode added(SDK-30895). Requirement is to disable Auto Power Down
       without changing Tx bias current
    */
    SOC_PHY_CONTROL_POWER_AUTO_DISABLE= _SHR_PORT_PHY_CONTROL_POWER_AUTO_DISABLE,
    SOC_PHY_CONTROL_POWER_AUTO_FULL= _SHR_PORT_PHY_CONTROL_POWER_AUTO_FULL,
    SOC_PHY_CONTROL_POWER_AUTO_LOW= _SHR_PORT_PHY_CONTROL_POWER_AUTO_LOW

} soc_phy_control_power_t;

typedef enum soc_phy_control_edc_config_e {
    SOC_PHY_CONTROL_EDC_CONFIG_NONE = _SHR_PORT_PHY_CONTROL_EDC_CONFIG_NONE,
    SOC_PHY_CONTROL_EDC_CONFIG_HARDWARE =
                               _SHR_PORT_PHY_CONTROL_EDC_CONFIG_HARDWARE,
    SOC_PHY_CONTROL_EDC_CONFIG_SOFTWARE =
                               _SHR_PORT_PHY_CONTROL_EDC_CONFIG_SOFTWARE
} soc_phy_control_edc_config_t;

typedef enum soc_phy_control_fec_e {
    SOC_PHY_CONTROL_FEC_OFF = _SHR_PORT_PHY_CONTROL_FEC_OFF,
    SOC_PHY_CONTROL_FEC_ON  = _SHR_PORT_PHY_CONTROL_FEC_ON,
    SOC_PHY_CONTROL_FEC_AUTO = _SHR_PORT_PHY_CONTROL_FEC_AUTO
} soc_phy_control_fec_t;

typedef enum soc_phy_control_bert_pattern_e {
    SOC_PHY_CONTROL_BERT_CRPAT = _SHR_PORT_PHY_CONTROL_BERT_CRPAT,
    SOC_PHY_CONTROL_BERT_CJPAT = _SHR_PORT_PHY_CONTROL_BERT_CJPAT
} soc_phy_control_bert_pattern_t;

typedef enum soc_phy_control_driver_supply_e {
    SOC_PHY_CONTROL_DRIVER_SUPPLY_1_5V_1_0V	   = _SHR_PORT_PHY_CONTROL_DRIVER_SUPPLY_1_5V_1_0V,
    SOC_PHY_CONTROL_DRIVER_SUPPLY_1_0V_700MV   = _SHR_PORT_PHY_CONTROL_DRIVER_SUPPLY_1_0V_700MV,
    SOC_PHY_CONTROL_DRIVER_SUPPLY_1_5V_700MV   = _SHR_PORT_PHY_CONTROL_DRIVER_SUPPLY_1_5V_700MV
} soc_port_phy_control_driver_supply_t;

typedef enum soc_phy_control_encoding_e {
    phyControlEncoding8b10b,
    phyControlEncoding64b66b
} soc_phy_control_encoding_t;

typedef enum soc_phy_control_firmware_mode_e {
    SOC_PHY_FIRMWARE_DEFAULT        = _SHR_PORT_PHY_FIRMWARE_DEFAULT,
    SOC_PHY_FIRMWARE_SFP_OPT_SR4    = _SHR_PORT_PHY_FIRMWARE_SFP_OPT_SR4,
    SOC_PHY_FIRMWARE_SFP_DAC        = _SHR_PORT_PHY_FIRMWARE_SFP_DAC,
    SOC_PHY_FIRMWARE_XLAUI          = _SHR_PORT_PHY_FIRMWARE_XLAUI,
    SOC_PHY_FIRMWARE_FORCE_OSDFE    = _SHR_PORT_PHY_FIRMWARE_FORCE_OSDFE,
    SOC_PHY_FIRMWARE_FORCE_BRDFE    = _SHR_PORT_PHY_FIRMWARE_FORCE_BRDFE,
    SOC_PHY_FIRMWARE_SW_CL72        = _SHR_PORT_PHY_FIRMWARE_SW_CL72,
    SOC_PHY_FIRMWARE_CL72_WITHOUT_AN= _SHR_PORT_PHY_FIRMWARE_CL72_WITHOUT_AN
} soc_phy_control_firmware_mode_t;

typedef enum soc_phy_control_autoneg_mode_e {
    SOC_PHY_CONTROL_AUTONEG_MODE_CL37     = _SHR_PORT_PHY_CONTROL_AUTONEG_MODE_CL37,
    SOC_PHY_CONTROL_AUTONEG_MODE_CL37_BAM = _SHR_PORT_PHY_CONTROL_AUTONEG_MODE_CL37_BAM,
    SOC_PHY_CONTROL_AUTONEG_MODE_CL73     = _SHR_PORT_PHY_CONTROL_AUTONEG_MODE_CL73,
    SOC_PHY_CONTROL_AUTONEG_MODE_CL73_BAM = _SHR_PORT_PHY_CONTROL_AUTONEG_MODE_CL73_BAM,
    SOC_PHY_CONTROL_AUTONEG_MODE_CL37_CL73 = _SHR_PORT_PHY_CONTROL_AUTONEG_MODE_CL37_CL73,
    SOC_PHY_CONTROL_AUTONEG_MODE_CL37_CL73_BAM = _SHR_PORT_PHY_CONTROL_AUTONEG_MODE_CL37_CL73_BAM,
    SOC_PHY_CONTROL_AUTONEG_MODE_CL37_BAM_CL73 = _SHR_PORT_PHY_CONTROL_AUTONEG_MODE_CL37_BAM_CL73,
    SOC_PHY_CONTROL_AUTONEG_MODE_CL37_BAM_CL73_BAM = _SHR_PORT_PHY_CONTROL_AUTONEG_MODE_CL37_BAM_CL73_BAM
} soc_phy_control_autoneg_mode_t;

typedef enum soc_phy_event_e {
    phyEventInterface,
    phyEventDuplex,
    phyEventSpeed,
    phyEventStop,
    phyEventResume,
    phyEventAutoneg,
    phyEventTxFifoReset,
    phyEventMacLoopback,
    phyEventCount            /* Always last */
} soc_phy_event_t;

#define PHY_EVENT_STRING {"Interface", \
                          "Duplex", \
                          "Speed", \
                          "Stop", \
                          "Resume", \
                          "Autoneg"}

/* PHY_STOP flag to use with phyEventStop and phyEventResume */
#define PHY_STOP_MAC_DIS        (0x01)
#define PHY_STOP_PHY_DIS        (0x02)
#define PHY_STOP_DRAIN          (0x04)
#define PHY_STOP_DUPLEX_CHG     (0x08)
#define PHY_STOP_SPEED_CHG      (0x10)
#define PHY_STOP_COPPER         (0x20)

/*for pcs bypass non-canned speed */
#define SOC_PHY_NON_CANNED_SPEED 9999

/* device specific PHYCTRL flags */
#define PHYCTRL_MDIO_ADDR_SHARE (1 << 0) /*use base address of phy to access lanes */
#define PHYCTRL_MDIO_CL45       (1 << 1) /*use MDIO CL45 to access device */
#define PHYCTRL_INIT_DONE       (1 << 2) /*lane initialization is done */
#define PHYCTRL_MDIO_BCST       (1 << 3) /* capable of MDIO ucode broadcast */
#define PHYCTRL_UCODE_BCST_DONE (1 << 4) /* ucode broadcast done */
#define PHYCTRL_ANEG_INIT_DONE  (1 << 5) /* autoneg initialization is done */
#define PHYCTRL_SYS_SIDE_CTRL    (1 << 6) /* Select system side for control set/get operations */
#define PHYCTRL_CHAINED_PHY_CTRL (1 << 7) /* Select the chained phy for control set/get operations */
#define PHYCTRL_IS_PORT0         (1 << 8) /* Indicates is 1st port of chip */


/* bit 31:29 used for init state */
#define PHYCTRL_INIT_STATE_DEFAULT 0
#define PHYCTRL_INIT_STATE_PASS1   1
#define PHYCTRL_INIT_STATE_PASS2   2
#define PHYCTRL_INIT_STATE_PASS3   3
#define PHYCTRL_INIT_MASK          0x7
#define PHYCTRL_INIT_SHFT          29
#define PHYCTRL_INIT_STATE(_pc)     ((((_pc)->flags) >> PHYCTRL_INIT_SHFT) & PHYCTRL_INIT_MASK)
#define PHYCTRL_INIT_STATE_SET(_pc,_st) ((_pc)->flags = ((_pc)->flags & \
    (~(PHYCTRL_INIT_MASK << PHYCTRL_INIT_SHFT))) | \
    (((_st) & PHYCTRL_INIT_MASK) << PHYCTRL_INIT_SHFT))

/* control commands used by firmware_set for ucode broadcast. Internal use only */
/* Command should be executed once. Assume all devices in bcst mode */
#define PHYCTRL_UCODE_BCST_ONEDEV  0x10000

/* Command is executed on each device. Assume all devices in non-bcst mode */
#define PHYCTRL_UCODE_BCST_ALLDEV  0x20000

/* setup the broadcast mode for firmware download */
#define PHYCTRL_UCODE_BCST_SETUP   (0 | PHYCTRL_UCODE_BCST_ALLDEV)

/* Prepare micro-controller ready for firmware broadcast */
#define PHYCTRL_UCODE_BCST_uC_SETUP  (1 | PHYCTRL_UCODE_BCST_ONEDEV)

/* Re-Enable MDIO broadcast mode */
#define PHYCTRL_UCODE_BCST_ENABLE  (2 | PHYCTRL_UCODE_BCST_ALLDEV)

/* Load firmware */
#define PHYCTRL_UCODE_BCST_LOAD    (3 | PHYCTRL_UCODE_BCST_ONEDEV)

/* Verify firmware download */
#define PHYCTRL_UCODE_BCST_END     (4 | PHYCTRL_UCODE_BCST_ALLDEV)

/* device specific phy_mode values */
#define PHYCTRL_QSGMII_CORE_PORT  8
#define PHYCTRL_MULTI_CORE_PORT   7
#define PHYCTRL_LANE_MODE_CUSTOM_3p125MHZ  6
#define PHYCTRL_LANE_MODE_CUSTOM1 5
#define PHYCTRL_LANE_MODE_CUSTOM  4
#define PHYCTRL_ONE_LANE_PORT     3
#define PHYCTRL_DUAL_LANE_PORT    2
#define PHYCTRL_QUAD_LANE_PORT    1

#define SOC_MAX_NUM_PHYS_PER_CHIP 8

#define PHY_OFFSET_VALID(x)     (((x) >= 0) && ((x) < SOC_MAX_NUM_PHYS_PER_CHIP))

#define SOC_PHYCTRL_PHYN_MAX_LIMIT  (_SHR_PHY_GPORT_PHYN_PORT_PHYN_MASK)

/* Put PHY chip information here. */
typedef struct soc_phy_chip_info_s {
    int     primary;
    int     offset;
    int     offset_to_port[SOC_MAX_NUM_PHYS_PER_CHIP];
} soc_phy_chip_info_t;

/* Put extra PHY information for each port here. */
typedef struct soc_phy_info_s {
    uint16      phy_id0;        /* PHY ID0 Register */
    uint16      phy_id1;        /* PHY ID1 Register */
    uint16      phy_addr;       /* PHY address to use for MII ops */
    uint16      phy_addr_int;   /* Internal PHY address if applicable */
    char        *phy_name;      /* Short name of PHY */
    uint32      phy_flags;      /* Logical OR among PHY_FLAGS_xxx */
    sal_usecs_t an_timeout;     /* Autoneg timeout (from property) */
    soc_phy_chip_info_t *chip_info;
} soc_phy_info_t;

/* phy diag function parameters */
#define PHY_DIAG_INSTANCE(_dev,_intf, _lane)  (((_dev) << 8) | \
             ((_intf) << 4) | (_lane))
#define PHY_DIAG_INST_DEV(_inst)  (((_inst) >> 8) & 0xf)
#define PHY_DIAG_INST_INTF(_inst) (((_inst) >> 4) & 0xf)
#define PHY_DIAG_INST_LN(_inst)   ((_inst) & 0xf)
#define PHY_DIAG_INST_INTF_LN(_inst)   ((_inst) & 0xff)
#define PHY_DIAG_INTF_DFLT     0   /* line side interface, default */
#define PHY_DIAG_INTF_LINE     1   /* line side interface, default */
#define PHY_DIAG_INTF_SYS      2   /* system side interface */
#define PHY_DIAG_DEV_DFLT      0   /* internal PHY device, default */
#define PHY_DIAG_DEV_INT       1   /* internal PHY device, default */
#define PHY_DIAG_DEV_EXT       2   /* external PHY device, default */
#define PHY_DIAG_LN_DFLT       0   /* default lane */
#define PHY_DIAG_LN_ALL        0xf /* apply to all lanes */

#define PHY_DIAG_INT      PHY_DIAG_INSTANCE(PHY_DIAG_DEV_INT, \
                PHY_DIAG_INTF_LINE,PHY_DIAG_LN_DFLT)
#define PHY_DIAG_EXT      PHY_DIAG_INSTANCE(PHY_DIAG_DEV_EXT, \
                PHY_DIAG_INTF_LINE,PHY_DIAG_LN_DFLT)
#define PHY_DIAG_EXT_SYS  PHY_DIAG_INSTANCE(PHY_DIAG_DEV_EXT, \
                PHY_DIAG_INTF_SYS,PHY_DIAG_LN_DFLT)
#define PHY_DIAG_INST_DEFAULT  PHY_DIAG_INSTANCE(PHY_DIAG_DEV_DFLT, \
                PHY_DIAG_INTF_DFLT,PHY_DIAG_LN_DFLT)
#define PHY_DIAG_INT_LANE(_ln) PHY_DIAG_INSTANCE(PHY_DIAG_DEV_INT, \
                PHY_DIAG_INTF_LINE,(_ln))
#define PHY_DIAG_EXT_LANE(_ln)  PHY_DIAG_INSTANCE(PHY_DIAG_DEV_EXT, \
                PHY_DIAG_INTF_LINE,(_ln))
#define PHY_DIAG_EXT_SYS_LANE(_ln)  PHY_DIAG_INSTANCE(PHY_DIAG_DEV_EXT, \
                PHY_DIAG_INTF_SYS,(_ln))

/* Parameter op_type  */
#define PHY_DIAG_CTRL_GET    0  /* a get action */
#define PHY_DIAG_CTRL_SET    1  /* a set action  */
#define PHY_DIAG_CTRL_CMD    2  /* a seqeunce of command actions, */

/* Parameter op_cmd  */
typedef enum phy_diag_ctrl_e {
    PHY_DIAG_CTRL_START = 0x08000000,
    PHY_DIAG_CTRL_EYE_MARGIN_VEYE = PHY_DIAG_CTRL_START,
    PHY_DIAG_CTRL_EYE_MARGIN_VEYE_UP,
    PHY_DIAG_CTRL_EYE_MARGIN_VEYE_DOWN,
    PHY_DIAG_CTRL_EYE_MARGIN_HEYE_LEFT,
    PHY_DIAG_CTRL_EYE_MARGIN_HEYE_RIGHT,
    PHY_DIAG_CTRL_DSC,
    PHY_DIAG_CTRL_PROG_DATA,
    PHY_DIAG_CTRL_EYE_MARGIN_LIVE_LINK,
    PHY_DIAG_CTRL_EYE_MARGIN_PRBS,
    PHY_DIAG_CTRL_EYE_ENABLE_LIVELINK,
    PHY_DIAG_CTRL_EYE_DISABLE_LIVELINK,
    PHY_DIAG_CTRL_EYE_ENABLE_DEADLINK,
    PHY_DIAG_CTRL_EYE_DISABLE_DEADLINK,
    PHY_DIAG_CTRL_EYE_SET_VOFFSET,
    PHY_DIAG_CTRL_EYE_SET_HOFFSET,
    PHY_DIAG_CTRL_EYE_GET_MAX_VOFFSET,
    PHY_DIAG_CTRL_EYE_GET_MIN_VOFFSET,
    PHY_DIAG_CTRL_EYE_GET_INIT_VOFFSET,
    PHY_DIAG_CTRL_EYE_GET_MAX_LEFT_HOFFSET,
    PHY_DIAG_CTRL_EYE_GET_MAX_RIGHT_HOFFSET,
    PHY_DIAG_CTRL_EYE_START_LIVELINK,
    PHY_DIAG_CTRL_EYE_START_DEADLINK,
    PHY_DIAG_CTRL_EYE_STOP_LIVELINK,
    PHY_DIAG_CTRL_EYE_CLEAR_LIVELINK,
    PHY_DIAG_CTRL_EYE_READ_LIVELINK,
    PHY_DIAG_CTRL_EYE_READ_DEADLINK,
    PHY_DIAG_CTRL_MFG_HYB_CANC,
    PHY_DIAG_CTRL_MFG_DENC,
    PHY_DIAG_CTRL_MFG_TX_ON,
    PHY_DIAG_CTRL_MFG_EXIT,
    PHY_DIAG_CTRL_STATE_TRACE1,
    PHY_DIAG_CTRL_STATE_TRACE2,
    PHY_DIAG_CTRL_STATE_WHEREAMI,
    PHY_DIAG_CTRL_STATE_TEMP,
    PHY_DIAG_CTRL_PEEK,
    PHY_DIAG_CTRL_POKE,
    PHY_DIAG_CTRL_LOAD_UC,
    PHY_DIAG_CTRL_LAST
} phy_diag_ctrl_t;

extern soc_phy_info_t *phy_port_info[SOC_MAX_NUM_DEVICES];
extern soc_port_t *phy_rmap[SOC_MAX_NUM_DEVICES];
extern int (*soc_phy_cb_xlate_port_func)(int, int *);

#define PHY_MIN_REG             0
#define PHY_MAX_REG             0x1f

/* PHY address per MDIO Bus */
#define PHY_ADDR_MIN            0
#define PHY_ADDR_MAX            31

/*
 * phy_addr encoding
 * bit7, 1: internal MDIO bus, 0: external MDIO bus
 * bit9,8,6,5, mdio bus number
 * bit4-0,   mdio addresses
 */
#define PHY_ID_BUS_UPPER_MASK     0x300
#define PHY_ID_BUS_UPPER_SHIFT    0x6
#define PHY_ID_BUS_LOWER_MASK     0x60
#define PHY_ID_BUS_LOWER_SHIFT    5
#define PHY_ID_BUS_NUM(_id)   ((((_id) & PHY_ID_BUS_UPPER_MASK) >> \
        PHY_ID_BUS_UPPER_SHIFT) | (((_id) & PHY_ID_BUS_LOWER_MASK) >> \
        PHY_ID_BUS_LOWER_SHIFT))

/* phy address now uses bit9,8 and bit6,5 as bus number */
#define EXT_PHY_ADDR_MAX        (256*4) /* value in 2's order */

#define PHY_ADDR_TO_PORT(unit, phy_addr) (phy_rmap[unit][phy_addr & (EXT_PHY_ADDR_MAX -1)])
#define SOC_PHY_INFO(unit, port)     (phy_port_info[unit][port])
#define PHY_ID0_REG(unit, port)      (SOC_PHY_INFO(unit, port).phy_id0)
#define PHY_ID1_REG(unit, port)      (SOC_PHY_INFO(unit, port).phy_id1)
#define PHY_ADDR(unit, port)         (SOC_PHY_INFO(unit, port).phy_addr)
#define PHY_ADDR_INT(unit, port)     (SOC_PHY_INFO(unit, port).phy_addr_int)
#define PHY_NAME(unit, port)         (SOC_PHY_INFO(unit, port).phy_name)
#define PHY_FLAGS(unit, port)        (SOC_PHY_INFO(unit, port).phy_flags)
#define PHY_AN_TIMEOUT(unit, port)   (SOC_PHY_INFO(unit, port).an_timeout)

#define PHY_FLAGS_COPPER           (1 << 0)  /* copper medium */
#define PHY_FLAGS_FIBER            (1 << 1)  /* fiber medium */
#define PHY_FLAGS_PASSTHRU         (1 << 2)  /* serdes passthru (5690) */
#define PHY_FLAGS_10B              (1 << 3)  /* ten bit interface (TBI) */
#define PHY_FLAGS_5421S            (1 << 4)  /* True if PHY is a 5421S */
#define PHY_FLAGS_DISABLE          (1 << 5)  /* True if PHY is disabled */
#define PHY_FLAGS_C45              (1 << 6)  /* True if PHY uses clause 45
                                              * MIIM */
#define PHY_FLAGS_100FX            (1 << 7)  /* True if PHY at 100FX
                                              * (for 5482S) */
#define PHY_FLAGS_MEDIUM_CHANGE    (1 << 8)  /* True if PHY medium changed
                                              * between copper and fiber */
#define PHY_FLAGS_SERDES_FIBER     (1 << 9)  /* True if use internal serdes
                                              * phy */
#define PHY_FLAGS_WAN              (1 << 10) /* WAN mode */
#define PHY_FLAGS_SGMII_AUTONEG    (1 << 11) /* Use SGMII autoneg between
                                              * internal SerDes and external
                                              * PHY */
#define PHY_FLAGS_EXTERNAL_PHY     (1 << 12) /* Port has external PHY */
#define PHY_FLAGS_FORCED_SGMII     (1 << 13) /* Interface between internal and
                                              * external PHY is always SGMII */
#define PHY_FLAGS_FORCED_COPPER    (1 << 14) /* Forced media to copper */
#define PHY_FLAGS_C73              (1 << 15) /* Auto-negotiation for Backplane
                                              * Ethernet (clause 73) */
#define PHY_FLAGS_INDEPENDENT_LANE (1 << 16) /* Treat each XGXS lane as
                                              * independent lane. */
#define PHY_FLAGS_SINGLE_LANE      (1 << 17) /* Use only lane 0 of XGXS core. */

#define PHY_FLAGS_PRIMARY_SERDES    (1<<18)

#define PHY_FLAGS_SECONDARY_SERDES (1<<19)

#define PHY_FLAGS_INIT_DONE        (1<<20)

#define PHY_FLAGS_HC65_FABRIC      (1<<21)   /* True if PHY used for SBX */
                                             /* fabric links */

#define PHY_FLAGS_EEE_CAPABLE      (1<<22)

#define PHY_FLAGS_EEE_ENABLED      (1<<23)

#define PHY_FLAGS_EEE_MODE         (1<<24)

#define PHY_FLAGS_BR               (1<<25)

#define PHY_FLAGS_HS_CAPABLE       (1<<26)

#define PHY_FLAGS_CHAINED          (1<<27)

#define PHY_FLAGS_REPEATER		   (1<<28)		/* PHY is a repeater */

#define PHY_FLAGS_SUPPORT_DUAL_RATE (1<<29)

#define PHY_FLAGS_SERVICE_INT_PHY_LINK_GET  (1<<30)

#define PHY_FLAGS_SET(unit, port, flags) \
            (PHY_FLAGS(unit, port) |= (flags))
#define PHY_FLAGS_CLR(unit, port, flags) \
            (PHY_FLAGS(unit, port) &= ~(flags))
#define PHY_FLAGS_TST(unit, port, flags) \
            ((PHY_FLAGS(unit, port) & (flags)) == (flags))
#define PHY_FLAGS_CLR_ALL(unit, port) \
            (PHY_FLAGS(unit, port) = 0)
#define PHY_COPPER_MODE(unit, port)        PHY_FLAGS_TST(unit, port, \
                                                         PHY_FLAGS_COPPER)
#define PHY_FIBER_MODE(unit, port)         PHY_FLAGS_TST(unit, port, \
                                                         PHY_FLAGS_FIBER)
#define PHY_PASSTHRU_MODE(unit, port)      PHY_FLAGS_TST(unit, port, \
                                                         PHY_FLAGS_PASSTHRU)
#define PHY_TBI_MODE(unit, port)           PHY_FLAGS_TST(unit, port, \
                                                         PHY_FLAGS_10B)
#define PHY_5421S_MODE(unit, port)         PHY_FLAGS_TST(unit, port, \
                                                         PHY_FLAGS_5421S)
#define PHY_DISABLED_MODE(unit, port)      PHY_FLAGS_TST(unit, port, \
                                                         PHY_FLAGS_DISABLE)
#define PHY_CLAUSE45_MODE(unit, port)      PHY_FLAGS_TST(unit, port, \
                                                         PHY_FLAGS_C45)
#define PHY_FIBER_100FX_MODE(unit, port)   PHY_FLAGS_TST(unit, port, \
                                                         PHY_FLAGS_100FX)
#define PHY_MEDIUM_CHANGED(unit, port)     PHY_FLAGS_TST(unit, port, \
                                                        PHY_FLAGS_MEDIUM_CHANGE)
#define PHY_SERDES_FIBER_MODE(unit, port)  PHY_FLAGS_TST(unit, port, \
                                                         PHY_FLAGS_SERDES_FIBER)
#define PHY_WAN_MODE(unit, port)           PHY_FLAGS_TST(unit, port, \
                                                         PHY_FLAGS_WAN)
#define PHY_SGMII_AUTONEG_MODE(unit, port) PHY_FLAGS_TST(unit, port, \
                                                        PHY_FLAGS_SGMII_AUTONEG)
#define PHY_EXTERNAL_MODE(unit, port)      PHY_FLAGS_TST(unit, port, \
                                                         PHY_FLAGS_EXTERNAL_PHY)
#define PHY_FORCED_SGMII_MODE(unit, port)  PHY_FLAGS_TST(unit, port, \
                                                         PHY_FLAGS_FORCED_SGMII)
#define PHY_FORCED_COPPER_MODE(unit, port) PHY_FLAGS_TST(unit, port, \
                                                        PHY_FLAGS_FORCED_COPPER)
#define PHY_CLAUSE73_MODE(unit, port)      PHY_FLAGS_TST(unit, port, \
                                                         PHY_FLAGS_C73)
#define PHY_INDEPENDENT_LANE_MODE(unit, port) PHY_FLAGS_TST(unit, port, \
                                                     PHY_FLAGS_INDEPENDENT_LANE)
#define PHY_SINGLE_LANE_MODE(unit, port)   PHY_FLAGS_TST(unit, port, \
                                                        PHY_FLAGS_SINGLE_LANE)
#define PHY_PRIMARY_SERDES_MODE(unit, port)  PHY_FLAGS_TST(unit, port, \
                                                        PHY_FLAGS_PRIMARY_SERDES)
#define PHY_SECONDARY_SERDES_MODE(unit, port)  PHY_FLAGS_TST(unit, port, \
                                                        PHY_FLAGS_SECONDARY_SERDES)
#define PHY_HC65_FABRIC_MODE(unit, port)   PHY_FLAGS_TST(unit, port, \
                                                        PHY_FLAGS_HC65_FABRIC)
#define PHY_EEE_CAPABLE(unit, port)   PHY_FLAGS_TST(unit, port, \
                                                        PHY_FLAGS_EEE_CAPABLE)
#define PHY_BR_MODE(unit, port)       (PHY_FLAGS_TST(unit, port, PHY_FLAGS_COPPER) && \
                                        PHY_FLAGS_TST(unit, port, PHY_FLAGS_BR))
#define PHY_HS_CAPABLE(unit, port)   PHY_FLAGS_TST(unit, port, \
                                                        PHY_FLAGS_HS_CAPABLE)
#define PHY_IS_CHAINED(unit, port)   PHY_FLAGS_TST(unit, port, \
                                                        PHY_FLAGS_CHAINED)
#define PHY_REPEATER(unit, port)   PHY_FLAGS_TST(unit, port, \
													   PHY_FLAGS_REPEATER)
#define PHY_IS_SUPPORT_DUAL_RATE(unit, port)   PHY_FLAGS_TST(unit, port, \
                                                        PHY_FLAGS_SUPPORT_DUAL_RATE)


/* PHY 100FX support
  * - Currently, the driver supports phy5482s only. Early chip like phy5461,
  *     phy5464 or other should be very different on 100FX specification.
  * - PHY5482s 100FX in bcm95324_a1 board :
  *     a. 100FX(SFP)-to-fiber wire, means wired at SGOUT+/- and SGIN+/-.
  *     b. This driver is designed for the 100FX/1000X fiber auto-detect mode.
  *     c. both 100FX/1000X use the same signal detecting for awaring fiber
  *         link.
  * - Extern definition for explain the 100FX property, PHY_100FX_PROPERTY.
  *     a. Fiber 100FX          0x1
  *     b. Copper 100FX     0x2
  *     c. 100FX only       0x10
  *     d. 100FX/1000X auto-detect      0x20
  */
#define PHY_100FX_SUPPORT   1
#if PHY_100FX_SUPPORT
    #define PROP_100FX_FIBER        0x1
    #define PROP_100FX_COPPER       0x2
    #define PROP_100FX_ONLY         0x10
    #define PROP_100FX_1000X_BOTH   0x20

    /* above property-bit mask */
    #define PHY_100FX_PROPERTY      (PROP_100FX_FIBER |PROP_100FX_1000X_BOTH)
#else
    #undef PHY_100FX_SUPPORT
#endif

#ifdef BCM_ROBO_SUPPORT
/* ROBO internal SerDes flag
 *  - Indicating this phy_addr is for internal SerDes miim_read/write
 *
 * Note :
 *  1. SW usage only on this bit flag.
 *  2. this flag must not be applied to real phy_addr miim_read/write
 */
#define PHY_ADDR_ROBO_INT_SERDES        0x80
#define PHY_ADDR_ROBO_INT_FLAG_CLR(_phy_addr)   \
                (_phy_addr) &= ~PHY_ADDR_ROBO_INT_SERDES
#define PHY_ADDR_ROBO_INT_FLAG_CHK(_phy_addr)   \
                ((_phy_addr) & PHY_ADDR_ROBO_INT_SERDES)


/* IS_ROBO_SPECIFIC_INT_SERDES ; check robo specific internal SerDes
 * - This definition must indicating on the specific chip and port.
 *
 * Some Robo chip might designed with the built-in GE port been consisted of
 *  different port type. Like bcm53115, the ge0-ge4 is 65nm GPHY but the ge5
 *  is 65nm SerDes.
 *
 */
#define IS_ROBO_SPECIFIC_INT_SERDES(_unit, _port)   \
        ((SOC_IS_POLAR((_unit)) && ((_port) == 5)) || \
        (SOC_IS_VULCAN((_unit)) && ((_port) == 5)) || \
        (SOC_IS_NORTHSTARPLUS((_unit)) && (((_port) == 5) || ((_port) == 4))) || \
        (SOC_IS_DINO8((_unit)) && (IS_GE_PORT((_unit), (_port)))) || \
        (SOC_IS_ROBO53262((_unit)) && (IS_GE_PORT((_unit), (_port)))) || \
        (SOC_IS_TBX((_unit)) && ((IS_GE_PORT((_unit), (_port))) && \
        (!(IS_GMII_PORT((_unit), (_port)))))))

/* External PHY via CPU MDIO interface flag
 *  - Indicating this phy_addr is for CPU MDIO interface
 *
 */
#define PHY_ADDR_ROBO_CPU_MDIOBUS        0x100
#define PHY_ADDR_ROBO_CPU_MDIOBUS_CLR(_phy_addr)   \
                (_phy_addr) &= ~PHY_ADDR_ROBO_CPU_MDIOBUS
#define PHY_ADDR_ROBO_CPU_MDIOBUS_CHK(_phy_addr)   \
                ((_phy_addr) & PHY_ADDR_ROBO_CPU_MDIOBUS)


#define IS_ROBO_CPU_MDIOBUS(_unit, _port)   \
        (SOC_IS_NORTHSTAR((_unit)) && ((_port) == 5))
#endif

#define PHY_DIAG_FULL_SNR_SUPPORT 0x1

typedef struct {
    int    flags;
    uint32 serr;
    uint32 cerr;
    uint16 block_lock;
    uint16 block_point_id;
    uint16 digital_temp;
    uint16 analog_temp;
    uint8  snr_block[48];
} XGPHY_DIAG_DATA_t;

extern int
soc_phyctrl_software_init(int unit);

extern int
soc_phyctrl_software_port_init(int unit, soc_port_t port);

extern int
soc_phyctrl_software_deinit(int unit);

extern int
soc_phyctrl_init(int unit, soc_port_t port);

extern int
soc_phyctrl_probe(int unit, soc_port_t port);

extern int
soc_phyctrl_drv_name_get(int unit, soc_port_t port, char *name, int len);

extern char *
soc_phyctrl_drv_name(int unit, soc_port_t port);

extern int
soc_phyctrl_reset(int unit, soc_port_t port, void *user_arg);

extern int
soc_phyctrl_link_get(int unit, soc_port_t port, int *link);

extern int
soc_phyctrl_enable_set(int unit, soc_port_t port, int enable);

extern int
soc_phyctrl_enable_get(int unit, soc_port_t port, int *enable);

extern int
soc_phyctrl_duplex_set(int unit, soc_port_t port, int duplex);

extern int
soc_phyctrl_duplex_get(int unit, soc_port_t port, int *duplex);

extern int
soc_phyctrl_speed_set(int unit, soc_port_t port, int speed);

extern int
soc_phyctrl_speed_get(int unit, soc_port_t port, int *speed);

extern int
soc_phyctrl_master_set(int unit, soc_port_t port, int master);

extern int
soc_phyctrl_master_get(int unit, soc_port_t port, int *master);

extern int
soc_phyctrl_auto_negotiate_set(int unit, soc_port_t port, int an);

extern int
soc_phyctrl_auto_negotiate_get(int unit, soc_port_t port, int *an,
                               int *an_done);

extern int
soc_phyctrl_adv_local_set(int unit, soc_port_t port, soc_port_mode_t mode);

extern int
soc_phyctrl_adv_local_get(int unit, soc_port_t port, soc_port_mode_t *mode);

extern int
soc_phyctrl_adv_remote_get(int unit, soc_port_t port, soc_port_mode_t *mode);

extern int
soc_phyctrl_loopback_set(int unit, soc_port_t port, int enable, int serdes_linkup_wait);

extern int
soc_phyctrl_loopback_get(int unit, soc_port_t port, int *enable);

extern int
soc_phyctrl_interface_set(int unit, soc_port_t port, soc_port_if_t pif);

extern int
soc_phyctrl_interface_get(int unit, soc_port_t port, soc_port_if_t *pif);

extern int
soc_phyctrl_ability_get(int unit, soc_port_t port, soc_port_mode_t *mode);

extern int
soc_phyctrl_linkup_evt(int unit, soc_port_t port);

extern int
soc_phyctrl_linkdn_evt(int unit, soc_port_t port);

extern int
soc_phyctrl_mdix_set(int unit, soc_port_t port, soc_port_mdix_t mdix);

extern int
soc_phyctrl_mdix_get(int unit, soc_port_t port, soc_port_mdix_t *mdix);

extern int
soc_phyctrl_mdix_status_get(int unit, soc_port_t port,
                            soc_port_mdix_status_t *status);

extern int
soc_phyctrl_medium_config_set(int unit, soc_port_t port,
                              soc_port_medium_t medium,
                              soc_phy_config_t *cfg);

extern int
soc_phyctrl_medium_config_get(int unit, soc_port_t port,
                              soc_port_medium_t medium,
                              soc_phy_config_t *cfg);

extern int
soc_phyctrl_medium_get(int unit, soc_port_t port, soc_port_medium_t *medium);

extern int
soc_phyctrl_cable_diag(int unit, soc_port_t port,
                       soc_port_cable_diag_t *status);

extern int
soc_phyctrl_link_change(int unit, soc_port_t port, int *link);

extern int
soc_phyctrl_control_set(int unit, soc_port_t port,
                        soc_phy_control_t ctrl_type, uint32 value);

extern int
soc_phyctrl_control_get(int unit, soc_port_t port,
                        soc_phy_control_t ctrl_type, uint32 *value);

extern int
soc_phyctrl_redirect_control_set(int unit, soc_port_t port,
                                 int phyn, int phy_lane, int sys_side,
                                 soc_phy_control_t ctrl_type, uint32 value);

extern int
soc_phyctrl_redirect_control_get(int unit, soc_port_t port,
                                 int phyn, int phy_lane, int sys_side,
                                 soc_phy_control_t ctrl_type, uint32 *value);

extern int
soc_phyctrl_reg_read(int unit, soc_port_t port, uint32 flags,
                     uint32 addr, uint32 *data);

extern int
soc_phyctrl_reg_write(int unit, soc_port_t port, uint32 flags,
                      uint32 addr, uint32 data);

extern int
soc_phyctrl_lane_control_set(int unit, soc_port_t port, int lane,
                             soc_phy_control_t ctrl_type, uint32 value);

extern int
soc_phyctrl_lane_control_get(int unit, soc_port_t port, int lane,
                             soc_phy_control_t ctrl_type, uint32 *value);

extern int
soc_phyctrl_lane_reg_read(int unit, soc_port_t port, int lane, uint32 flags,
                          uint32 addr, uint32 *data);

extern int
soc_phyctrl_lane_reg_write(int unit, soc_port_t port, int lane, uint32 flags,
                           uint32 addr, uint32 data);

extern int
soc_phyctrl_reg_modify(int unit, soc_port_t port, uint32 flags,
                       uint32 addr, uint32 data, uint32 mask);

extern int
soc_phyctrl_ability_advert_get(int unit, soc_port_t port,
                            soc_port_ability_t * ability);

extern int
soc_phyctrl_ability_advert_set(int unit, soc_port_t port,
                            soc_port_ability_t * ability);

extern int
soc_phyctrl_ability_remote_get(int unit, soc_port_t port,
                                   soc_port_ability_t * ability);

extern int
soc_phyctrl_ability_local_get(int unit, soc_port_t port,
                               soc_port_ability_t * ability);

extern int
soc_phyctrl_firmware_set(int unit, soc_port_t port, uint32 flags,
                   int offset, uint8 *array, int len);

extern int
soc_phyctrl_primary_set(int unit, soc_port_t port, soc_port_t primary);

extern int
soc_phyctrl_primary_get(int unit, soc_port_t port, soc_port_t *primary);

extern int
soc_phyctrl_offset_set(int unit, soc_port_t port, int offset);

extern int
soc_phyctrl_offset_get(int unit, soc_port_t port, soc_port_t *offset);

extern int
soc_phy_primary_and_offset_get(int unit, soc_port_t port, soc_port_t *primary_port, int *offset);

extern int
soc_phyctrl_toplvl_reg_read(int unit, soc_port_t port, soc_port_t primary_port,
                          uint8 reg_offset, uint16 *data);

extern int
soc_phyctrl_toplvl_reg_write(int unit, soc_port_t port, soc_port_t primary_port,
                           uint8 reg_offset, uint16 data);

extern int
soc_phyctrl_port_phy_multi_get(int unit, soc_port_t port, uint32 flags,
                 uint32 dev_addr, uint32 offset, int max_size, uint8 *data, int *actual_size);

extern int
soc_phyctrl_detach(int unit, soc_port_t port);

extern int
soc_phyctrl_notify(int unit, soc_port_t port,
                   soc_phy_event_t event, uint32 data);

extern int
soc_phy_init(int unit);

extern int
soc_phy_port_init(int unit, soc_port_t port);

extern int
soc_phy_deinit(int unit);

extern int
soc_phy_info_get(int unit, soc_port_t port, soc_phy_info_t *pi);

extern uint16
soc_phy_addr_of_port(int unit, soc_port_t port);

extern uint16
soc_phy_addr_int_of_port(int unit, soc_port_t port);
#define PORT_TO_PHY_ADDR_INT(_u, _p) PHY_ADDR_INT((_u), (_p))

extern soc_port_t
soc_phy_addr_to_port(int unit, uint16 phy_id);
#define PORT_TO_PHY_ADDR(_u, _p) PHY_ADDR((_u), (_p))

extern uint16
soc_phy_id0reg_get(int unit, soc_port_t port);

extern uint16
soc_phy_id1reg_get(int unit, soc_port_t port);

extern int
soc_phy_is_c45_miim(int unit, soc_port_t port);

extern int
soc_phy_port_offset_get(int unit, soc_port_t port);

extern char*
soc_phy_name_get(int unit, soc_port_t port);

extern sal_usecs_t
soc_phy_an_timeout_get(int unit, soc_port_t port);

extern int
soc_phy_cfg_addr_get(int unit, soc_port_t port, int flags,uint16 *addr_ptr);

extern int
soc_phy_cfg_addr_set(int unit, soc_port_t port, int flags, uint16 addr);

extern int
soc_phyctrl_pbm_probe_init(int unit, pbmp_t pbmp, pbmp_t *okay_pbmp);

/*
 * Phy reset method overloading support
 */
typedef _shr_port_phy_reset_cb_t soc_port_phy_reset_cb_t;

extern int
soc_phy_reset_register(int                      unit,
                       soc_port_t               port,
                       soc_port_phy_reset_cb_t  callback,
                       void                    *user_data,
                       int                      reg_default);

extern int
soc_phy_reset_unregister(int                      unit,
                         soc_port_t               port,
                         soc_port_phy_reset_cb_t  callback,
                         void                    *user_data);

extern int
soc_phy_reset(int unit, soc_port_t port);

/*
 * Medium configuration and control
 */
typedef _shr_port_medium_status_cb_t soc_port_medium_status_cb_t;


extern int
soc_phy_medium_status_register(int unit,
                               soc_port_t port,
                               soc_port_medium_status_cb_t cb,
                               void  *user_data);

extern int
soc_phy_medium_status_unregister(int unit,
                                 soc_port_t port,
                                 soc_port_medium_status_cb_t cb,
                                 void  *user_data);

extern void
soc_phy_medium_status_notify(int unit, soc_port_t port,
                             soc_port_medium_t medium);

extern int
soc_phyctrl_diag_ctrl(int, soc_port_t, uint32, int, int, void *);

extern int
soc_cmic_rate_param_get(int unit, int *dividend, int *divisor);

extern int
soc_cmic_rate_param_set(int unit, int dividend, int divisor);

/*
 * Initialization of the features above
 */
extern int
soc_phy_common_init(int unit);
extern int
soc_phy_common_detach(int unit);

#endif /* _PHYCTRL_H_ */

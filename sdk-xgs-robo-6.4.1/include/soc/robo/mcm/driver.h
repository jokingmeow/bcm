/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated from the registers file.
 * Edits to this file will be lost when it is regenerated.
 *
 * $Id: f2ce674e0f0e8b776ec6f29fa142f856815d914b $
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
 * File:	driver.h
 * Purpose:	Chip driver declarations
 * Supports:	bcm53242_a0
 *		bcm53262_a0
 *		bcm53115_a0
 *		bcm53118_a0
 *		bcm53280_a0
 *		bcm53280_b0
 *		bcm53101_a0
 *		bcm53125_a0
 *		bcm53128_a0
 *		bcm53600_a0
 *		bcm89500_a0
 *		bcm53010_a0
 *		bcm5389_a0
 *		bcm53020_a0
 *		bcm5396_a0
 */

#ifndef _SOC_ROBO_DRIVER_H
#define _SOC_ROBO_DRIVER_H


#include <soc/drv.h>

/****************************************************************
 *
 *    Chip driver declarations
 *
 ****************************************************************/

EXTERN soc_driver_t soc_driver_bcm53242_a0;
EXTERN soc_driver_t soc_driver_bcm53262_a0;
EXTERN soc_driver_t soc_driver_bcm53115_a0;
EXTERN soc_driver_t soc_driver_bcm53118_a0;
EXTERN soc_driver_t soc_driver_bcm53280_a0;
EXTERN soc_driver_t soc_driver_bcm53280_b0;
EXTERN soc_driver_t soc_driver_bcm53101_a0;
EXTERN soc_driver_t soc_driver_bcm53125_a0;
EXTERN soc_driver_t soc_driver_bcm53128_a0;
EXTERN soc_driver_t soc_driver_bcm53600_a0;
EXTERN soc_driver_t soc_driver_bcm89500_a0;
EXTERN soc_driver_t soc_driver_bcm53010_a0;
EXTERN soc_driver_t soc_driver_bcm5389_a0;
EXTERN soc_driver_t soc_driver_bcm53020_a0;
EXTERN soc_driver_t soc_driver_bcm5396_a0;
#ifdef ETH_MII_DEBUG
EXTERN soc_driver_t soc_driver_bcm4713_a0;
#endif
/* The table of all known drivers */
/* Indexed by supported chips */
EXTERN soc_driver_t *soc_robo_base_driver_table[SOC_ROBO_NUM_SUPPORTED_CHIPS];

EXTERN int soc_robo_chip_type_to_index(soc_chip_types chip);
EXTERN soc_chip_types soc_robo_index_to_chip_type(int chip);


#endif	/* !_SOC_ROBO_DRIVER_H */

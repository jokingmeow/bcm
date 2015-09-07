/* 
 * $Id: bcm956504r48.c,v 1.2 Broadcom SDK $
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
 * File:        bcm956504r48.c
 * Purpose:     BCM956504R48 and similar Dual Firebolt and similar
 *
 */

#include <soc/devids.h>
#include <board/xgs.h>

#if defined (INCLUDE_BOARD_BCM956504R48)

/* Devices */
#define MAX_UNIT 2

/* Macro for each set of devices on a board */
#define BCM956504R48 BCM56504_DEVICE_ID, BCM56504_DEVICE_ID
#define BCM956514R48 BCM56514_DEVICE_ID, BCM56514_DEVICE_ID
#define BCM956102R48 BCM56102_DEVICE_ID, BCM56102_DEVICE_ID
#define BCM956112R48 BCM56112_DEVICE_ID, BCM56112_DEVICE_ID
 
STATIC uint32 _bcm956504r48_supported_devices[] = {
    BCM956504R48, /* device set 1 */
    BCM956514R48, /* device set 2 */
    BCM956102R48, /* device set 3 */
    BCM956112R48  /* device set 4 */
};

/* LED code poe48p56504.hex */
STATIC uint8 _bcm956504r48_led[] = {
    0xE0, 0x28, 0x60, 0xE3, 0x67, 0x85, 0x67, 0x49,
    0x06, 0xE3, 0x80, 0xD2, 0x18, 0x74, 0x01, 0x28,
    0x60, 0xE3, 0x67, 0xAD, 0x75, 0x1A, 0x67, 0xC2,
    0x77, 0x20, 0x32, 0x0E, 0x87, 0x32, 0x08, 0x87,
    0x67, 0x49, 0x06, 0xE3, 0x80, 0xD2, 0x1A, 0x74,
    0x0F, 0x12, 0xE2, 0x85, 0x05, 0xD2, 0x0F, 0x71,
    0x33, 0x52, 0x00, 0x12, 0xE1, 0x85, 0x05, 0xD2,
    0x1F, 0x71, 0x3D, 0x52, 0x00, 0x12, 0xE0, 0x85,
    0x05, 0xD2, 0x05, 0x71, 0x47, 0x52, 0x00, 0x3A,
    0x68, 0x32, 0x00, 0x97, 0x75, 0x55, 0x12, 0xA0,
    0xFE, 0xE3, 0x02, 0x0A, 0x50, 0x32, 0x01, 0x97,
    0x75, 0x61, 0x12, 0xBA, 0xFE, 0xE3, 0x02, 0x0A,
    0x50, 0x12, 0xBA, 0xFE, 0xE3, 0x95, 0x75, 0x73,
    0x85, 0x12, 0xA0, 0xFE, 0xE3, 0x95, 0x75, 0xC2,
    0x85, 0x77, 0xB4, 0x12, 0xA0, 0xFE, 0xE3, 0x95,
    0x75, 0x7D, 0x85, 0x77, 0xBB, 0x16, 0xE0, 0xDA,
    0x02, 0x71, 0xBB, 0x77, 0xC2, 0x32, 0x05, 0x97,
    0x71, 0x95, 0x32, 0x02, 0x97, 0x71, 0xB4, 0x06,
    0xE1, 0xD2, 0x01, 0x71, 0xB4, 0x06, 0xE3, 0x67,
    0xAD, 0x75, 0xB4, 0x32, 0x03, 0x97, 0x71, 0xC2,
    0x32, 0x04, 0x97, 0x75, 0xBB, 0x06, 0xE2, 0xD2,
    0x07, 0x71, 0xBB, 0x77, 0xC2, 0x12, 0x80, 0xF8,
    0x15, 0x1A, 0x00, 0x57, 0x32, 0x0E, 0x87, 0x32,
    0x0E, 0x87, 0x57, 0x32, 0x0E, 0x87, 0x32, 0x0F,
    0x87, 0x57, 0x32, 0x0F, 0x87, 0x32, 0x0E, 0x87,
    0x57
};

/* Internal connections */

STATIC board_connection_t _bcm956504r48_internal_connection[] = {
    { BCM_GPORT_DEVPORT(0, 26), BCM_GPORT_DEVPORT(1, 26) },
    { BCM_GPORT_DEVPORT(0, 27), BCM_GPORT_DEVPORT(1, 27) }
};

/* Board private data */
STATIC board_xgs_data_t _bcm956504r48_private_data = {
    MAX_UNIT,                                   /* Devices per board */
    ARRAY(_bcm956504r48_supported_devices),     /* Supported devices */
    ARRAY(_bcm956504r48_led),                   /* LED program */
    0,                                          /* LED program port offset */
    ARRAY(_bcm956504r48_internal_connection)    /* Internal connections */
};

BOARD_XGS_DRIVER(bcm956504r48);

#endif

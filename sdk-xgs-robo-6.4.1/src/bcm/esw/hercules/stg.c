/*
 * $Id: stg.c,v 1.4 Broadcom SDK $
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
 */

#include <soc/drv.h>
#include <soc/mem.h>

#include <bcm/error.h>
#include <bcm/vlan.h>
#include <bcm/port.h>
#include <bcm/stg.h>

#include <bcm_int/esw/mbcm.h>
#include <bcm_int/esw/stg.h>
#include <bcm_int/esw/hercules.h>

/*
 * Function:
 *	bcm_hercules_stg_stp_init
 * Purpose:
 *	Write an entry with the spanning tree state DISABLE for all ports.
 */

int
bcm_hercules_stg_stp_init(int unit, bcm_stg_t stg)
{
    return BCM_E_NONE;
}

/*
 * Function:
 *	bcm_hercules_stg_stp_set
 * Purpose:
 *	Set the spanning tree state for a port in specified STG.
 * Parameters:
 *	unit - StrataSwitch unit number.
 *      stg - STG ID.
 *	port - StrataSwitch port number.
 *	stp_state - State to place port in.
 */

int
bcm_hercules_stg_stp_set(int unit, bcm_stg_t stg, bcm_port_t port,
			 int stp_state)
{    
    return (BCM_E_NONE);
}

/*
 * Function:
 *	bcm_hercules_stg_stp_get
 * Purpose:
 *	Retrieve the spanning tree state for a port in specified STG.
 * Parameters:
 *	unit - StrataSwitch unit number.
 *      stg - STG ID.
 *	port - StrataSwitch port number.
 *	stp_state - Pointer where state stored.
 */

int
bcm_hercules_stg_stp_get(int unit, bcm_stg_t stg, bcm_port_t port,
			 int *stp_state)
{
    /* Hercules ports are always in forwarding, really. */
    *stp_state = BCM_STG_STP_FORWARD;
    return (BCM_E_NONE);
}

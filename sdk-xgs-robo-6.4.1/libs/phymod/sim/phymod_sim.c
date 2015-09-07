/*
 * $Id: c2fe904907d40bc676031d1bd60c3056a3cec328 $
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

#include <phymod/phymod_sim.h>

int
phymod_sim_init(phymod_sim_t *pms, int num_ent, phymod_sim_entry_t *ent)
{
    if (pms == NULL || pms->drv == NULL || pms->drv->init == NULL) {
        return PHYMOD_E_INIT;
    }
    return pms->drv->init(&pms->data, num_ent, ent);
}

int
phymod_sim_reset(phymod_sim_t *pms)
{
    if (pms == NULL || pms->drv == NULL || pms->drv->reset == NULL) {
        return PHYMOD_E_INIT;
    }
    return pms->drv->reset(&pms->data);
}

int
phymod_sim_read(phymod_sim_t *pms, uint32_t addr, uint32_t *data)
{
    if (pms == NULL || pms->drv == NULL || pms->drv->read == NULL) {
        return PHYMOD_E_INIT;
    }
    return pms->drv->read(&pms->data, addr, data);
}

int
phymod_sim_write(phymod_sim_t *pms, uint32_t addr, uint32_t data)
{
    if (pms == NULL || pms->drv == NULL || pms->drv->write == NULL) {
        return PHYMOD_E_INIT;
    }
    return pms->drv->write(&pms->data, addr, data);
}

int
phymod_sim_event(phymod_sim_t *pms, phymod_sim_event_t event)
{
    if (pms == NULL || pms->drv == NULL || pms->drv->event == NULL) {
        return PHYMOD_E_INIT;
    }
    return pms->drv->event(&pms->data, event);
}

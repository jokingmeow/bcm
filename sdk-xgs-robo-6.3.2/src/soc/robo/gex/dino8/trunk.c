/*
 * $Id: trunk.c 1.3 Broadcom SDK $
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
 */
#include <soc/drv.h>
#include <soc/debug.h>

#define DINO8_TRUNK_HASH_FIELD_MACDA_VALUE  1
#define DINO8_TRUNK_HASH_FIELD_MACSA_VALUE  2
#define DINO8_TRUNK_HASH_FIELD_MACDASA_VALUE  0

/* trunk seed in dino8 is named as trunk hash */
static uint32  dino8_default_trunk_seed = DINO8_TRUNK_HASH_FIELD_MACDASA_VALUE;

/*
 *  Function : _drv_dino8_trunk_enable_set
 *
 *  Purpose :
 *      Enable trunk function (global).
 *
 *  Parameters :
 *      unit    :  RoboSwitch unit number.
 *      enable  :  status of the trunk id (global).
 *
 *  Return :
 *      SOC_E_NONE
 *
 *  Note :
 */
static int 
_drv_dino8_trunk_enable_set(int unit, uint32 enable)
{
    uint32  reg_value, temp;

    /* Enable LOCAL TRUNK */ /* should move to somewhere to initialize it */
    SOC_IF_ERROR_RETURN(REG_READ_GLOBAL_TRUNK_CTLr
        (unit, &reg_value));

    if (enable) {
        temp = 1;
    } else {
        temp = 0;
    }
    soc_GLOBAL_TRUNK_CTLr_field_set(unit, &reg_value, 
        EN_TRUNK_LOCALf, &temp);
    SOC_IF_ERROR_RETURN(REG_WRITE_GLOBAL_TRUNK_CTLr
        (unit, &reg_value));

    return SOC_E_NONE;
}

/*
 *  Function : _drv_dino8_trunk_enable_get
 *
 *  Purpose :
 *      Get the status of the selected GE trunk.
 *
 *  Parameters :
 *      unit    :  RoboSwitch unit number.
 *      tid     :   trunk id.
 *      enable  :  status of the trunk id.
 *
 *  Return :
 *      SOC_E_NONE
 *
 *  Note :
 */
static int 
_drv_dino8_trunk_enable_get(int unit, int tid, uint32 *enable)
{
    uint32  reg_value, temp, bmp;

    SOC_IF_ERROR_RETURN(REG_READ_GLOBAL_TRUNK_CTLr
        (unit, &reg_value));

    temp = 0;
    soc_GLOBAL_TRUNK_CTLr_field_get(unit, &reg_value, 
        EN_TRUNK_LOCALf, &temp);

    if (temp) {
        SOC_IF_ERROR_RETURN(REG_READ_TRUNK_GRP_CTLr
            (unit, 0, &reg_value));

        bmp = 0;
        soc_TRUNK_GRP_CTLr_field_get(unit, &reg_value, 
            EN_TRUNK_GRP0f, &bmp);

        if(bmp) {
            *enable = 1;
        } else {
            *enable = 0;
        }
    } else {
        *enable = 0;
    }

    return SOC_E_NONE;
}


/*
 *  Function : drv_dino8_trunk_set
 *
 *  Purpose :
 *      Set the member ports to a trunk group.
 *
 *  Parameters :
 *      unit    :  RoboSwitch unit number.
 *      tid     :  trunk id.
 *      bmp     :  trunk member port bitmap.
 *      flag    :  trunk flag.
 *      hash_op :  trunk hash seed.
 *
 *  Return :
 *      SOC_E_NONE
 *
 *  Note :
 */
int 
drv_dino8_trunk_set(int unit, int tid, soc_pbmp_t bmp, 
    uint32 flag, uint32 hash_op)
{
    uint32  reg_value, temp, c_temp, temp_value = 0;
    uint32  bmp_value = 0, trunk_prop;

    bmp_value = SOC_PBMP_WORD_GET(bmp, 0);
    soc_cm_debug(DK_PORT, "drv_dino8_trunk_set: \
        unit = %d, trunk id = %d, bmp = %x, flag = 0x%x, hash_op = 0x%x\n",
        unit, tid, bmp_value, flag, hash_op);

    /* handle default trunk hash seed */
    if (flag & DRV_TRUNK_FLAG_HASH_DEFAULT) {
        if (hash_op & DRV_TRUNK_HASH_FIELD_MACDA) {
            if (hash_op & DRV_TRUNK_HASH_FIELD_MACSA) {
                dino8_default_trunk_seed = DINO8_TRUNK_HASH_FIELD_MACDASA_VALUE;
            } else {
                dino8_default_trunk_seed = DINO8_TRUNK_HASH_FIELD_MACDA_VALUE;
            }
        } else if (hash_op & DRV_TRUNK_HASH_FIELD_MACSA) {
            dino8_default_trunk_seed = DINO8_TRUNK_HASH_FIELD_MACSA_VALUE;
        }
        return SOC_E_NONE;
    }

    /* Check TRUNK MAX ID */
    SOC_IF_ERROR_RETURN(DRV_DEV_PROP_GET
        (unit, DRV_DEV_PROP_TRUNK_NUM, &trunk_prop));
    if (tid > (trunk_prop - 1)) {
        return SOC_E_PARAM;
    }        

    if (flag & DRV_TRUNK_FLAG_ENABLE) {
        SOC_IF_ERROR_RETURN(
            _drv_dino8_trunk_enable_set(unit, TRUE));
    } else if (flag & DRV_TRUNK_FLAG_DISABLE) {
        SOC_IF_ERROR_RETURN(
            _drv_dino8_trunk_enable_set(unit, FALSE));
    }

    if (flag & DRV_TRUNK_FLAG_BITMAP) {   
        /* Check per trunk member port number */
        SOC_IF_ERROR_RETURN(DRV_DEV_PROP_GET
            (unit, DRV_DEV_PROP_TRUNK_MAX_PORT_NUM, &trunk_prop));

        /* check pbmp parameter (port count = 0 is allowed) */
        SOC_PBMP_COUNT(bmp, c_temp); 
        if (c_temp) {
            if (c_temp != trunk_prop) {
                return SOC_E_PARAM;
            }
        }

        switch (tid) {
            case 0: /* port 0-1*/
                if (bmp_value & 0xfc) {
                    return SOC_E_PARAM;
                }
                temp = 0x1;
                break;
            case 1: /* port 2-3*/
                if (bmp_value & 0xf3) {
                    return SOC_E_PARAM;
                }
                temp = 0x2;
                break;
            case 2: /* port 4-5*/
                if (bmp_value & 0xcf) {
                    return SOC_E_PARAM;
                }
                temp = 0x4;
                break;
            case 3: /* port 6-7*/
                if (bmp_value & 0x3f) {
                    return SOC_E_PARAM;
                }                    
                temp = 0x8;
                break;
            default:
                return SOC_E_PARAM;                                
        }

        SOC_IF_ERROR_RETURN(REG_READ_TRUNK_GRP_CTLr
            (unit, 0, &reg_value));
        soc_TRUNK_GRP_CTLr_field_get(unit, &reg_value, 
            EN_TRUNK_GRP0f, &temp_value);

        if (c_temp) {
            temp_value |= temp;
        } else {
            temp_value &= (~temp);
        }

        soc_TRUNK_GRP_CTLr_field_set(unit, &reg_value, 
            EN_TRUNK_GRP0f, &temp_value);
        SOC_IF_ERROR_RETURN(REG_WRITE_TRUNK_GRP_CTLr
            (unit, 0, &reg_value));
    }

    return SOC_E_NONE;
}

/*
 *  Function : drv_dino8_trunk_get
 *
 *  Purpose :
 *      Get the member ports to a trunk group.
 *
 *  Parameters :
 *      unit    :  RoboSwitch unit number.
 *      tid     :  trunk id.
 *      bmp     :  trunk member port bitmap.
 *      flag    :  trunk flag.
 *      hash_op :  trunk hash seed.
 *
 *  Return :
 *      SOC_E_NONE
 *
 *  Note :
 */
int 
drv_dino8_trunk_get(int unit, int tid, soc_pbmp_t *bmp, 
    uint32 flag, uint32 *hash_op)
{
    uint32  reg_value, temp = 0, enable;
    uint32  trunk_prop;

    /* handle default trunk hash seed */
    if (flag & DRV_TRUNK_FLAG_HASH_DEFAULT) {
        switch (dino8_default_trunk_seed) {
            case DINO8_TRUNK_HASH_FIELD_MACDASA_VALUE:
                *hash_op = DRV_TRUNK_HASH_FIELD_MACDA | 
                    DRV_TRUNK_HASH_FIELD_MACSA;
                break;
            case DINO8_TRUNK_HASH_FIELD_MACDA_VALUE:
                *hash_op = DRV_TRUNK_HASH_FIELD_MACDA;
                break;
            case DINO8_TRUNK_HASH_FIELD_MACSA_VALUE:
                *hash_op = DRV_TRUNK_HASH_FIELD_MACSA;
                break;
            default:
                return SOC_E_INTERNAL;
        }
        soc_cm_debug(DK_PORT, "drv_dino8_trunk_get: \
            unit = %d, trunk id = %d, flag = 0x%x, *hash_op = 0x%x\n",
            unit, tid, flag, *hash_op);

        return SOC_E_NONE;
    }

    /* Check TRUNK MAX ID */
    SOC_IF_ERROR_RETURN(DRV_DEV_PROP_GET
        (unit, DRV_DEV_PROP_TRUNK_NUM, &trunk_prop));
    if (tid > (trunk_prop - 1)) {
        return SOC_E_PARAM;
    }

    if (flag & DRV_TRUNK_FLAG_ENABLE) {
        SOC_IF_ERROR_RETURN(
            _drv_dino8_trunk_enable_get(unit, tid, &enable));
        if (!enable) {
            SOC_PBMP_CLEAR(*bmp);
            return SOC_E_NONE;
        }
    }
    
    /* Get group member port bitmap */
    if (flag & DRV_TRUNK_FLAG_BITMAP) {
        SOC_IF_ERROR_RETURN(REG_READ_TRUNK_GRP_CTLr
            (unit, 0, &reg_value));
        soc_TRUNK_GRP_CTLr_field_get
            (unit, &reg_value, EN_TRUNK_GRP0f, &temp);

        switch(tid) {
            case 0: /* port 0-1*/
                if (temp & 0x1) {
                    SOC_PBMP_WORD_SET(*bmp, 0, 0x3);
                } else {
                    SOC_PBMP_WORD_SET(*bmp, 0, 0);
                }
                break;
            case 1: /* port 2-3*/
                if (temp & 0x2) {
                    SOC_PBMP_WORD_SET(*bmp, 0, 0xc);
                } else {
                    SOC_PBMP_WORD_SET(*bmp, 0, 0);
                }
                break;
            case 2: /* port 4-5*/
                if (temp & 0x4) {
                    SOC_PBMP_WORD_SET(*bmp, 0, 0x30);
                } else {
                    SOC_PBMP_WORD_SET(*bmp, 0, 0);
                }
                break;
            case 3: /* port 6-7*/
                if (temp & 0x8) {
                    SOC_PBMP_WORD_SET(*bmp, 0, 0xc0);
                } else {
                    SOC_PBMP_WORD_SET(*bmp, 0, 0);
                }
                break;
            default:
                return SOC_E_PARAM;                                
        }
    }
	
    soc_cm_debug(DK_PORT, "drv_dino8_trunk_get: \
        unit = %d, trunk id = %d, flag = 0x%x, *bmp = 0x%x\n",
        unit, tid, flag, SOC_PBMP_WORD_GET(*bmp, 0));

    return SOC_E_NONE;
}

/*
 *  Function : drv_dino8_trunk_hash_field_add
 *
 *  Purpose :
 *      Add trunk hash field type.
 *
 *  Parameters :
 *      unit      :  RoboSwitch unit number.
 *      field_type:  trunk hash field type to be add.
 *
 *  Return :
 *      SOC_E_NONE
 *
 *  Note :
 *      1. For the hash type field in dino8 family allowed 3 hash types only.
 *          (ie. MAC_DASA=0; MAC_DA=1; MAC_SA=2), here the final type value 
 *          to set to register will be :
 *          - no change : when add new hash is the same with current hash.
 *          - MAC_SADA : add to DASA.
 *          - MAC_DA : add DA. (no matter what current type is)
 *          - MAC_SA : add SA. (no matter what current type is)
 */
int 
drv_dino8_trunk_hash_field_add(int unit, uint32 field_type)
{
    uint32  reg_value, temp = 0;

    soc_cm_debug(DK_VERBOSE, 
        "drv_dino8_trunk_hash_field_add: unit = %d, field type = 0x%x\n",
        unit, field_type);

    SOC_IF_ERROR_RETURN(REG_READ_GLOBAL_TRUNK_CTLr
        (unit, &reg_value));
    soc_GLOBAL_TRUNK_CTLr_field_get(unit, &reg_value, 
        TRUNK_SEEDf, &temp);

    if ((field_type & DRV_TRUNK_HASH_FIELD_MACDA) && 
        (field_type & DRV_TRUNK_HASH_FIELD_MACSA)) {
        if (temp == DINO8_TRUNK_HASH_FIELD_MACDASA_VALUE) {
            return SOC_E_NONE;
        } else {
            temp = DINO8_TRUNK_HASH_FIELD_MACDASA_VALUE;
        }
    } else if (field_type & DRV_TRUNK_HASH_FIELD_MACDA) {
        if (temp == DINO8_TRUNK_HASH_FIELD_MACDA_VALUE) {
            return SOC_E_NONE;
        } else {
            temp = DINO8_TRUNK_HASH_FIELD_MACDA_VALUE;
        }
    } else if (field_type & DRV_TRUNK_HASH_FIELD_MACSA) {
        if (temp == DINO8_TRUNK_HASH_FIELD_MACSA_VALUE) {
            return SOC_E_NONE;
        } else {
            temp = DINO8_TRUNK_HASH_FIELD_MACSA_VALUE;
        }
    } else {
        soc_cm_debug(DK_WARN, 
            "drv_dino8_trunk_hash_field_add: hash type = 0x%x, is invalid!\n",
            field_type);
        return SOC_E_UNAVAIL;
    }

    soc_GLOBAL_TRUNK_CTLr_field_set(unit, &reg_value, 
        TRUNK_SEEDf, &temp);
    SOC_IF_ERROR_RETURN(REG_WRITE_GLOBAL_TRUNK_CTLr
        (unit, &reg_value));

    return SOC_E_NONE;
}

/*
 *  Function : drv_dino8_trunk_hash_field_remove
 *
 *  Purpose :
 *      Remove trunk hash field type.
 *
 *  Parameters :
 *      unit      :  RoboSwitch unit number.
 *      field_type:  trunk hash field type to be removed.
 *
 *  Return :
 *      SOC_E_NONE
 *
 *  Note :
 *      1. For the hash type field in dino8 family allowed 3 hash types only.
 *          (ie. MAC_DASA=0; MAC_DA=1; MAC_SA=2), here the final type value 
 *          to set to register will be :
 *          - MAC_DA : when remove DA+SA
 *          - MAC_SADA : when current is SA only and remove SA.
 *          - MAC_SADA : when current is DA only and remove DA.
 *          - MAC_SADA : when other hask key applying but no SA or DA.
 */
int 
drv_dino8_trunk_hash_field_remove(int unit, uint32 field_type)
{
    uint32  reg_value, temp = 0, current_hash;

    soc_cm_debug(DK_VERBOSE, 
        "drv_dino8_trunk_hash_field_remove: unit = %d, field type = 0x%x\n",
        unit, field_type);

    SOC_IF_ERROR_RETURN(REG_READ_GLOBAL_TRUNK_CTLr
        (unit, &reg_value));
    soc_GLOBAL_TRUNK_CTLr_field_get(unit, &reg_value, 
        TRUNK_SEEDf, &temp);

    /* hash key with 2 bits length but "3" is not a valid value : 
     *  - in such case, the hash key is treat as DASA.
     */
    current_hash = (temp == 3) ? DINO8_TRUNK_HASH_FIELD_MACDASA_VALUE : temp;
    
    if ((field_type & DRV_TRUNK_HASH_FIELD_MACDA) && 
        (field_type & DRV_TRUNK_HASH_FIELD_MACSA)) {
        temp = DINO8_TRUNK_HASH_FIELD_MACDA_VALUE;
    } else if (field_type & DRV_TRUNK_HASH_FIELD_MACDA) {
        if (current_hash == DINO8_TRUNK_HASH_FIELD_MACDA_VALUE) {
            temp = DINO8_TRUNK_HASH_FIELD_MACDASA_VALUE;
        }
    } else if (field_type & DRV_TRUNK_HASH_FIELD_MACSA) {
        if (current_hash == DINO8_TRUNK_HASH_FIELD_MACSA_VALUE) {
            temp = DINO8_TRUNK_HASH_FIELD_MACDASA_VALUE;
        }
    }

    soc_GLOBAL_TRUNK_CTLr_field_set(unit, &reg_value, 
        TRUNK_SEEDf, &temp);
    SOC_IF_ERROR_RETURN(REG_WRITE_GLOBAL_TRUNK_CTLr
        (unit, &reg_value));

    return SOC_E_NONE;
}


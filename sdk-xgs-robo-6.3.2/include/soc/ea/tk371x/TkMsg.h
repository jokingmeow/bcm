/*
 * $Id: TkMsg.h 1.1 Broadcom SDK $
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
 * File:     TkMsg.h
 * Purpose: 
 *
 */

#ifndef _SOC_EA_TkMsg_H
#define _SOC_EA_TkMsg_H

#if defined(__cplusplus)
extern "C"  {
#endif

#include <soc/ea/tk371x/TkTypes.h>
#include <soc/ea/tk371x/TkOsSync.h>
#include <soc/ea/tk371x/TkOsAlloc.h>


#define WAIT_FOREVER        (-1)
#define NO_WAIT             0
#define WAIT_MAX_CYCLES     1024

#define MAX_MSGS            3
#define MAX_MSG_LEN         1518
#define MIN_MSG_LEN         60

#define SAL_MSG_CNT         5
#define SAL_MSG_LEN         2048

#define TK_MAX_RX_TX_DATA_LENGTH    1600


typedef struct sal_msg_buffer_s {
    unsigned int        len;
    char                buff[SAL_MSG_LEN];
} sal_msg_buffer_t;

typedef struct sal_msg_desc_s {
    sal_sem_t           sem;    /*multiple valued semphore*/
    int                 id;
    unsigned int        max_cnt;
    unsigned int        msg_cnt;
    sal_msg_buffer_t  * msg;
} sal_msg_desc_t;


typedef struct {
    long    mtype;
    uint8   buff[TK_MAX_RX_TX_DATA_LENGTH];
} TkMsgBuff;



sal_msg_desc_t * sal_msg_create (char *name, unsigned int count);

void    sal_msg_destory (sal_msg_desc_t * msg);
int     sal_msg_snd (sal_msg_desc_t * msg, char *buff, int len, int ms);
int     sal_msg_rcv (sal_msg_desc_t * msg, char *buff, int len, int ms);
int     sal_msg_clear (sal_msg_desc_t * msg);

#if defined(__cplusplus)
}
#endif

#endif /* _SOC_EA_TkMsg_H */

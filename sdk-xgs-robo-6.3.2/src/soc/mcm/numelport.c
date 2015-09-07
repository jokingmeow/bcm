/*
 * DO NOT EDIT THIS FILE!
 * This file is auto-generated from the registers file.
 * Edits to this file will be lost when it is regenerated.
 *
 * $Id: numelport.c 1.11 Broadcom SDK $
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
 * File:	numelport.c
 * Purpose:	Common numel & portlists for all chips.
 */

#include <soc/chip.h>

uint32 soc_ports_list[][6] = {
    { 0xffffffff, 0x3fffff, 0x0, 0x0, 0x0, 0x0 }, /* 0 */
    { 0xfc00c00d, 0x801, 0x0, 0x0, 0x0, 0x0 }, /* 1 */
    { 0x1, 0x0, 0x0, 0x0, 0x0, 0x0 }, /* 2 */
    { 0xfffffffe, 0x3fffff, 0x0, 0x0, 0x0, 0x0 }, /* 3 */
    { 0xfc00c00c, 0x801, 0x0, 0x0, 0x0, 0x0 }, /* 4 */
    { 0xfc004004, 0x0, 0x0, 0x0, 0x0, 0x0 }, /* 5 */
    { 0xfc004005, 0x0, 0x0, 0x0, 0x0, 0x0 }, /* 6 */
    { 0x1fffffff, 0x0, 0x0, 0x0, 0x0, 0x0 }, /* 7 */
    { 0x1ffffffe, 0x0, 0x0, 0x0, 0x0, 0x0 }, /* 8 */
    { 0x1fffffe, 0x0, 0x0, 0x0, 0x0, 0x0 }, /* 9 */
    { 0xffffffff, 0x7fffff, 0x0, 0x0, 0x0, 0x0 }, /* 10 */
    { 0xfc000001, 0xc4cc4, 0x0, 0x0, 0x0, 0x0 }, /* 11 */
    { 0xfc000000, 0xc4cc4, 0x0, 0x0, 0x0, 0x0 }, /* 12 */
    { 0x0, 0x400000, 0x0, 0x0, 0x0, 0x0 }, /* 13 */
    { 0x7c000000, 0x444444, 0x0, 0x0, 0x0, 0x0 }, /* 14 */
    { 0xffffffff, 0x1ffffff, 0x0, 0x0, 0x0, 0x0 }, /* 15 */
    { 0xffffffff, 0xffffff, 0x0, 0x0, 0x0, 0x0 }, /* 16 */
    { 0xfc000000, 0x4c4cc4, 0x0, 0x0, 0x0, 0x0 }, /* 17 */
    { 0xfc000001, 0x4c4cc4, 0x0, 0x0, 0x0, 0x0 }, /* 18 */
    { 0x83ffffff, 0x1bbbbbb, 0x0, 0x0, 0x0, 0x0 }, /* 19 */
    { 0xfffffffe, 0x7fffff, 0x0, 0x0, 0x0, 0x0 }, /* 20 */
    { 0x3fffffff, 0x0, 0x0, 0x0, 0x0, 0x0 }, /* 21 */
    { 0x3c000001, 0x0, 0x0, 0x0, 0x0, 0x0 }, /* 22 */
    { 0x3ffffffe, 0x0, 0x0, 0x0, 0x0, 0x0 }, /* 23 */
    { 0x3c000000, 0x0, 0x0, 0x0, 0x0, 0x0 }, /* 24 */
    { 0x1e, 0x3c, 0x0, 0x0, 0x0, 0x0 }, /* 25 */
    { 0xfffffffe, 0xfffffffd, 0x3, 0x0, 0x0, 0x0 }, /* 26 */
    { 0xffffffff, 0xffffffff, 0x3, 0x0, 0x0, 0x0 }, /* 27 */
    { 0xfffffffe, 0xffffffff, 0x3, 0x0, 0x0, 0x0 }, /* 28 */
    { 0xffffffff, 0xfffffffd, 0x3, 0x0, 0x0, 0x0 }, /* 29 */
    { 0x1f, 0x3c, 0x0, 0x0, 0x0, 0x0 }, /* 30 */
    { 0x1ffff, 0x0, 0x0, 0x0, 0x0, 0x0 }, /* 31 */
    { 0x1fffe, 0x0, 0x0, 0x0, 0x0, 0x0 }, /* 32 */
    { 0xffffffff, 0x7f, 0x0, 0x0, 0x0, 0x0 }, /* 33 */
    { 0xffffffff, 0xf, 0x0, 0x0, 0x0, 0x0 }, /* 34 */
    { 0x1e000000, 0x0, 0x0, 0x0, 0x0, 0x0 }, /* 35 */
    { 0xfe000001, 0x0, 0x0, 0x0, 0x0, 0x0 }, /* 36 */
    { 0xfffffffe, 0xf, 0x0, 0x0, 0x0, 0x0 }, /* 37 */
    { 0xffffffff, 0x7dffffff, 0x0, 0x0, 0x0, 0x0 }, /* 38 */
    { 0x0, 0x110000, 0x0, 0x0, 0x0, 0x0 }, /* 39 */
    { 0xffffffff, 0x77ffffff, 0x0, 0x0, 0x0, 0x0 }, /* 40 */
    { 0x0, 0xf, 0x0, 0x0, 0x0, 0x0 }, /* 41 */
    { 0xffffffff, 0x1dffffff, 0x0, 0x0, 0x0, 0x0 }, /* 42 */
    { 0x0, 0x8ffff00, 0x0, 0x0, 0x0, 0x0 }, /* 43 */
    { 0x0, 0x8000000, 0x0, 0x0, 0x0, 0x0 }, /* 44 */
    { 0x0, 0xff0000, 0x0, 0x0, 0x0, 0x0 }, /* 45 */
    { 0xffffffff, 0x3dffffff, 0x0, 0x0, 0x0, 0x0 }, /* 46 */
    { 0x0, 0x4000000, 0x0, 0x0, 0x0, 0x0 }, /* 47 */
    { 0x0, 0xff00, 0x0, 0x0, 0x0, 0x0 }, /* 48 */
    { 0xffffffff, 0x35ffffff, 0x0, 0x0, 0x0, 0x0 }, /* 49 */
    { 0x0, 0x1000000, 0x0, 0x0, 0x0, 0x0 }, /* 50 */
    { 0x0, 0xf0, 0x0, 0x0, 0x0, 0x0 }, /* 51 */
    { 0xffffffff, 0x1fffff, 0xffffffff, 0x1fffff, 0x0, 0x0 }, /* 52 */
    { 0xffff, 0x0, 0xffff, 0x0, 0x0, 0x0 }, /* 53 */
    { 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x3ff }, /* 54 */
    { 0xfe000001, 0x3ff, 0x0, 0x0, 0x0, 0x0 }, /* 55 */
    { 0xffffffff, 0x3ff, 0x0, 0x0, 0x0, 0x0 }, /* 56 */
    { 0xfffffffe, 0x3ff, 0x0, 0x0, 0x0, 0x0 }, /* 57 */
    { 0xffffffff, 0x1ff, 0x0, 0x0, 0x0, 0x0 }, /* 58 */
    { 0x3ffffffd, 0x0, 0x0, 0x0, 0x0, 0x0 }, /* 59 */
    { 0x3ffffffc, 0x0, 0x0, 0x0, 0x0, 0x0 }, /* 60 */
};

soc_numelport_set_t soc_numelports_list[][5] = {
    { {0,7, 0}, {8,23, 1}, {24,47, 2}, {-1,-1,-1} }, /* 0 */
    { {0,7, 3}, {8,23, 4}, {-1,-1,-1} }, /* 1 */
    { {0,0, 0}, {1,7, 5}, {-1,-1,-1} }, /* 2 */
    { {0,0, 6}, {-1,-1,-1} }, /* 3 */
    { {0,0, 3}, {-1,-1,-1} }, /* 4 */
    { {0,0, 4}, {-1,-1,-1} }, /* 5 */
    { {0,7, 3}, {8,9, 4}, {-1,-1,-1} }, /* 6 */
    { {0,0, 5}, {-1,-1,-1} }, /* 7 */
    { {0,7, 3}, {8,25, 4}, {-1,-1,-1} }, /* 8 */
    { {0,9, 7}, {10,47, 2}, {-1,-1,-1} }, /* 9 */
    { {0,0, 8}, {-1,-1,-1} }, /* 10 */
    { {0,0, 9}, {-1,-1,-1} }, /* 11 */
    { {0,7, 10}, {8,23, 11}, {24,47, 2}, {-1,-1,-1} }, /* 12 */
    { {0,7, 3}, {8,23, 12}, {-1,-1,-1} }, /* 13 */
    { {0,7, 13}, {-1,-1,-1} }, /* 14 */
    { {0,1, 10}, {2,7, 14}, {-1,-1,-1} }, /* 15 */
    { {0,0, 0}, {-1,-1,-1} }, /* 16 */
    { {0,1, 15}, {2,7, 14}, {-1,-1,-1} }, /* 17 */
    { {0,0, 15}, {-1,-1,-1} }, /* 18 */
    { {0,0, 16}, {-1,-1,-1} }, /* 19 */
    { {0,0, 13}, {-1,-1,-1} }, /* 20 */
    { {0,0, 17}, {-1,-1,-1} }, /* 21 */
    { {0,7, 10}, {8,9, 18}, {10,47, 2}, {-1,-1,-1} }, /* 22 */
    { {0,0, 14}, {-1,-1,-1} }, /* 23 */
    { {0,7, 10}, {8,25, 18}, {26,47, 2}, {-1,-1,-1} }, /* 24 */
    { {0,1, 16}, {2,7, 14}, {-1,-1,-1} }, /* 25 */
    { {0,0, 19}, {-1,-1,-1} }, /* 26 */
    { {0,0, 20}, {-1,-1,-1} }, /* 27 */
    { {0,7, 21}, {8,23, 22}, {24,47, 2}, {-1,-1,-1} }, /* 28 */
    { {0,7, 23}, {8,23, 24}, {-1,-1,-1} }, /* 29 */
    { {0,0, 21}, {1,7, 24}, {-1,-1,-1} }, /* 30 */
    { {0,0, 22}, {-1,-1,-1} }, /* 31 */
    { {0,0, 23}, {-1,-1,-1} }, /* 32 */
    { {0,0, 24}, {-1,-1,-1} }, /* 33 */
    { {0,7, 21}, {8,9, 22}, {10,47, 2}, {-1,-1,-1} }, /* 34 */
    { {0,7, 23}, {8,25, 24}, {26,47, 2}, {-1,-1,-1} }, /* 35 */
    { {0,0, 25}, {-1,-1,-1} }, /* 36 */
    { {0,0, 26}, {-1,-1,-1} }, /* 37 */
    { {0,4, 27}, {5,47, 2}, {-1,-1,-1} }, /* 38 */
    { {0,0, 28}, {-1,-1,-1} }, /* 39 */
    { {0,3, 28}, {-1,-1,-1} }, /* 40 */
    { {0,7, 26}, {8,23, 24}, {-1,-1,-1} }, /* 41 */
    { {0,4, 27}, {5,14, 29}, {15,47, 30}, {48,78, 25}, {-1,-1,-1} }, /* 42 */
    { {0,73, 25}, {-1,-1,-1} }, /* 43 */
    { {0,9, 26}, {-1,-1,-1} }, /* 44 */
    { {0,71, 25}, {-1,-1,-1} }, /* 45 */
    { {0,6, 27}, {7,47, 2}, {-1,-1,-1} }, /* 46 */
    { {0,7, 28}, {8,71, 25}, {-1,-1,-1} }, /* 47 */
    { {0,4, 28}, {-1,-1,-1} }, /* 48 */
    { {0,9, 31}, {10,47, 2}, {-1,-1,-1} }, /* 49 */
    { {0,0, 32}, {-1,-1,-1} }, /* 50 */
    { {0,0, 33}, {-1,-1,-1} }, /* 51 */
    { {0,0, 34}, {1,7, 35}, {-1,-1,-1} }, /* 52 */
    { {0,0, 35}, {-1,-1,-1} }, /* 53 */
    { {0,0, 36}, {-1,-1,-1} }, /* 54 */
    { {0,0, 34}, {-1,-1,-1} }, /* 55 */
    { {0,0, 37}, {-1,-1,-1} }, /* 56 */
    { {0,0, 38}, {-1,-1,-1} }, /* 57 */
    { {0,0, 39}, {-1,-1,-1} }, /* 58 */
    { {0,0, 40}, {-1,-1,-1} }, /* 59 */
    { {0,9, 39}, {10,47, 2}, {-1,-1,-1} }, /* 60 */
    { {0,0, 41}, {-1,-1,-1} }, /* 61 */
    { {0,0, 38}, {1,7, 42}, {8,9, 43}, {10,47, 44}, {-1,-1,-1} }, /* 62 */
    { {0,0, 45}, {-1,-1,-1} }, /* 63 */
    { {0,0, 46}, {1,7, 42}, {8,9, 43}, {10,47, 44}, {-1,-1,-1} }, /* 64 */
    { {0,0, 47}, {-1,-1,-1} }, /* 65 */
    { {0,47, 44}, {-1,-1,-1} }, /* 66 */
    { {0,0, 48}, {-1,-1,-1} }, /* 67 */
    { {0,0, 44}, {-1,-1,-1} }, /* 68 */
    { {0,0, 49}, {-1,-1,-1} }, /* 69 */
    { {0,0, 50}, {-1,-1,-1} }, /* 70 */
    { {0,0, 51}, {-1,-1,-1} }, /* 71 */
    { {0,0, 52}, {-1,-1,-1} }, /* 72 */
    { {0,0, 53}, {-1,-1,-1} }, /* 73 */
    { {0,0, 54}, {-1,-1,-1} }, /* 74 */
    { {0,0, 55}, {-1,-1,-1} }, /* 75 */
    { {0,0, 56}, {-1,-1,-1} }, /* 76 */
    { {0,0, 57}, {-1,-1,-1} }, /* 77 */
    { {0,0, 58}, {-1,-1,-1} }, /* 78 */
    { {0,0, 59}, {-1,-1,-1} }, /* 79 */
    { {0,0, 60}, {-1,-1,-1} }, /* 80 */
};


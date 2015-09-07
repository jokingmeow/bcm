/* $Id: nd_ucode.c 1.5 Broadcom SDK $
 * Copyright 2011 BATM
 */


#if 1
/* created by Software_vob\Source\tools\ucode_load\create_ucode_c_file.exe */

#include "ag_common.h"

#define CES16_BCM_VERSION

/*///////////////////////////////////////////////////////////////////////////// */
/* 	ucode version information */
/* */
const AG_U32 nNdUcodeMajorVersionNumber =
0x0003
;

const AG_U32 nNdUcodeMinorVersionNumber =
0x0000
;

/*///////////////////////////////////////////////////////////////////////////// */
/*	nNdUcodeSize - number of ucode instructions */
/*	multiply by 4 to get the number of 16-bit words */
/* */
const AG_U32 nNdUcodeSize =
0x0078
;

/*///////////////////////////////////////////////////////////////////////////// */
/* destination MAC address offsets */
/*  */
const AG_U32 nNdUcodeDestMacInstr[] = {
0x0000,
0x0001,
0x0002
};


/*///////////////////////////////////////////////////////////////////////////// */
/* destination VLAN offset */
/*  */
const AG_U32 nNdUcodeVlanInstr[] = {
#ifndef CES16_BCM_VERSION
0x0014
#else
0x0013
#endif
};


/*///////////////////////////////////////////////////////////////////////////// */
/* destination IPv4 address offsets */
/*  */
const AG_U32 nNdUcodeDestIpv4Instr[] = {
#ifndef CES16_BCM_VERSION
0x0024,
0x0025
#else
0x0024,
0x0025
#endif
};

/*///////////////////////////////////////////////////////////////////////////// */
/* destination IPv6 address offsets */
/*  */
const AG_U32 nNdUcodeDestIpv6Instr[] = {
#ifndef CES16_BCM_VERSION
0x0038,
0x0039,
0x003a,
0x003b,
0x003c,
0x003d,
0x003e,
0x003f
#else
0x003c,
0x003d,
0x003e,
0x003f,
0x0040,
0x0041,
0x0042,
0x0043
#endif
};

/*///////////////////////////////////////////////////////////////////////////// */
/* UDP command offset */
/*  */
const AG_U32 nNdUcodeUdpCmdInstr[] = {
#ifndef CES16_BCM_VERSION
0x004B
#else
0x004f
#endif
};

/*///////////////////////////////////////////////////////////////////////////// */
/* MPLS command offset */
/*  */
const AG_U32 nNdUcodeMplsCmdInstr[] = {
#ifndef CES16_BCM_VERSION
0x0060
#else
0x0064
#endif
};

/*///////////////////////////////////////////////////////////////////////////// */
/* ECID command offset */
/*  */
const AG_U32 nNdUcodeEcidCmdInstr[] = {
#ifndef CES16_BCM_VERSION
0x0054
#else
0x0058
#endif
};


#ifdef CES16_BCM_VERSION
/*///////////////////////////////////////////////////////////////////////////// */
/* L2Tp command offset */
/*  */
const AG_U32 nNdUcodeL2TpCmdInstr[] = {
0x006e
};
#endif



/*///////////////////////////////////////////////////////////////////////////// */
/* ucode */
/* */
const AG_U16 nNdUcodeInstructions[] = {
0x1a03, 0x0000, 0x187b, 0xffff,
0x1000, 0x8600, 0x3a7e, 0xffff,
0x1307, 0x8600, 0x31eb, 0xffff,
0x1c00, 0x4500, 0x0100, 0x0100,
0x1000, 0x8600, 0x0100, 0x0100,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x00cd, 0x0000, 0x0000,
0x1000, 0x00cd, 0x0000, 0x0000,
0x1000, 0x00cd, 0x0000, 0x0000,
0x1913, 0x4200, 0x8100, 0xffff,
0x1964, 0x4000, 0x8847, 0xffff,
0x1964, 0x4000, 0x8848, 0xffff,
0x1914, 0x4100, 0x0800, 0xffff,
0x192a, 0x4100, 0x86dd, 0xffff,
0x1958, 0x4300, 0x88d8, 0xffff,
0x1977, 0x4d00, 0x0806, 0xffff,
0x1177, 0x4d00, 0x814c, 0xffff,
0x1377, 0xc700, 0x0000, 0x0000,
0x130a, 0x00cf, 0x0000, 0x0fff,
0x1c00, 0x8941, 0x4500, 0xff00,
0x1000, 0x0000, 0x0000, 0x00ff,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x8900, 0x0000, 0xbfff,
0x1c00, 0x4900, 0x0000, 0xff00,
0x191f, 0x4443, 0x0011, 0x00ff,
0x191f, 0x0000, 0x0073, 0x00ff,
0x1977, 0x4d00, 0x0001, 0x00ff,
0x1177, 0x4d00, 0x0006, 0x00ff,
0x1377, 0xca00, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x00cd, 0x0000, 0x0000,
0x1000, 0x00cd, 0x0000, 0x0000,
0x1928, 0x4800, 0xe000, 0xf000,
0x1928, 0x4800, 0xffff, 0xffff,
0x1000, 0x8b00, 0x506b, 0xffff,
0x1000, 0x8b00, 0x8341, 0xffff,
0x3e6e, 0x0000, 0x0010, 0x0010,
0x3d4d, 0x0000, 0x0010, 0x0010,
0x326e, 0x0000, 0x0010, 0x0010,
0x3d4d, 0x0000, 0x0010, 0x0010,
0x1000, 0x8942, 0x6000, 0xf000,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0x0000,
0x1d32, 0x4443, 0x1100, 0xff00,
0x1d32, 0x0000, 0x7300, 0xff00,
0x1977, 0x4d00, 0x0100, 0xff00,
0x1177, 0x4d00, 0x0600, 0xff00,
0x1377, 0xca00, 0x0000, 0x0000,
0x1000, 0x4900, 0x0000, 0x00ff,
0x1000, 0x00cd, 0x0000, 0x0000,
0x1000, 0x00cd, 0x0000, 0x0000,
0x1000, 0x00cd, 0x0000, 0x0000,
0x1000, 0x00cd, 0x0000, 0x0000,
0x1000, 0x00cd, 0x0000, 0x0000,
0x1000, 0x00cd, 0x0000, 0x0000,
0x1000, 0x00cd, 0x0000, 0x0000,
0x1000, 0x00cd, 0x0000, 0x0000,
0x1946, 0x4800, 0xff00, 0xff00,
0x1000, 0x8b00, 0x1b6c, 0x0000,
0x1000, 0x8b00, 0x322b, 0x0000,
0x1000, 0x8b00, 0xde3d, 0x0000,
0x1000, 0x8b00, 0x4edd, 0x0000,
0x1000, 0x8b00, 0xb1fc, 0x0000,
0x1000, 0x8b00, 0xc856, 0x0000,
0x1000, 0x8b00, 0x8dff, 0x0000,
0x1000, 0x8b00, 0x3856, 0x0000,
0x3e6e, 0x0000, 0x0010, 0x0010,
0x3d4d, 0x0000, 0x0010, 0x0010,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0x0000,
0x326e, 0x0000, 0x0800, 0x0800,
0x1000, 0x0000, 0x0000, 0x1fff,
0x196a, 0x0000, 0x06a5, 0xffff,
0x1000, 0x00c5, 0x0000, 0x0000,
0x1000, 0x00d0, 0x0000, 0x1fff,
0x1368, 0x0000, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0x007f,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x00ca, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0x0000,
0x135a, 0x0000, 0x0000, 0x0000,
0x1000, 0x00c6, 0x0000, 0x0000,
0x0368, 0x00d0, 0x0000, 0xffff,
0x1000, 0x00cc, 0x0000, 0x0000,
0x5e5b, 0x00cb, 0x8000, 0x8000,
0x5a77, 0x0000, 0x2000, 0x2000,
0x1c00, 0x0000, 0x0000, 0x007f,
0x1000, 0x8e00, 0x8000, 0xf000,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x00ca, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0x0000,
0x1f77, 0x0000, 0x0000, 0x0000,
0x1000, 0x00c4, 0x0000, 0x0000,
0x1964, 0x0000, 0x0000, 0x0100,
0x1c00, 0x4c00, 0x0000, 0x00ff,
0x1000, 0x00d0, 0x0000, 0x1fff,
0x1d52, 0x0000, 0x8000, 0xf000,
0x1f5a, 0x0000, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0x0000,
0x1000, 0x00c7, 0x0000, 0x0000,
0x1000, 0x0000, 0x0000, 0xffff,
0x5e70, 0x0000, 0x8000, 0x8000,
0x5d76, 0x0000, 0x0000, 0x0600,
0x5000, 0x00cd, 0x0000, 0x0000,
0x5176, 0x00cd, 0x0200, 0x0600,
0x5000, 0x00cd, 0x0000, 0x0000,
0x5176, 0x00cd, 0x0400, 0x0600,
0x1f5a, 0x00d0, 0x0000, 0x1fff,
0x9000, 0x00d1, 0x0000, 0x0000
};

#endif

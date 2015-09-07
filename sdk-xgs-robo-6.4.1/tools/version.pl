#!/usr/bin/perl
#
# Build a version.c
#
# $Id: version.pl,v 1.2 Broadcom SDK $
#
# $Copyright: Copyright 2012 Broadcom Corporation.
# This program is the proprietary software of Broadcom Corporation
# and/or its licensors, and may only be used, duplicated, modified
# or distributed pursuant to the terms and conditions of a separate,
# written license agreement executed between you and Broadcom
# (an "Authorized License").  Except as set forth in an Authorized
# License, Broadcom grants no license (express or implied), right
# to use, or waiver of any kind with respect to the Software, and
# Broadcom expressly reserves all rights in and to the Software
# and all intellectual property rights therein.  IF YOU HAVE
# NO AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS SOFTWARE
# IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY BROADCOM AND DISCONTINUE
# ALL USE OF THE SOFTWARE.  
#  
# Except as expressly set forth in the Authorized License,
#  
# 1.     This program, including its structure, sequence and organization,
# constitutes the valuable trade secrets of Broadcom, and you shall use
# all reasonable efforts to protect the confidentiality thereof,
# and to use this information only in connection with your use of
# Broadcom integrated circuit products.
#  
# 2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS
# PROVIDED "AS IS" AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES,
# REPRESENTATIONS OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY,
# OR OTHERWISE, WITH RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY
# DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY,
# NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES,
# ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
# CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING
# OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
# 
# 3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL
# BROADCOM OR ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL,
# INCIDENTAL, SPECIAL, INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER
# ARISING OUT OF OR IN ANY WAY RELATING TO YOUR USE OF OR INABILITY
# TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF
# THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR USD 1.00,
# WHICHEVER IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING
# ANY FAILURE OF ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.$
# 

($prog = $0) =~ s/.*\///;

use Config;
use Sys::Hostname;
use Time::localtime;
use Cwd;

# if $SDK env var is set, read release file directly
# if not set, search back from current working directory
if ($ENV{'SDK'}) {
	$TREE = $ENV{'SDK'};
	if (open(F, "$TREE/RELEASE")) {
		chop($RELEASE = <F>);
		close F;
	} else {
		$RELEASE = "unknown_release";
	}
} else {
	$dir = cwd();
	do {
		if (open(F, "$dir/RELEASE")) {
			chop($RELEASE = <F>);
			close F;
			($TREE = $dir) =~ s@/[^/]*$@@;
		} else {
			$dir =~ s@/[^/]*$@@;
		}
	} while (!defined $RELEASE && $dir ne "");
	$RELEASE = "unknown_release" unless defined $RELEASE;
	$TREE = "unknown_tree" unless defined $TREE;
}

$USER = getlogin() || getpwuid($<) || "unknown_user";
$HOST = hostname() || "unknown_host";
$OS = $Config{'osname'} || "unknown_os";
$ARCH = $Config{'archname'} || "unknown_arch";
$ARCH =~ s/-.*$//;
$DATE = ctime() || "unknown_date";
$DATESTAMP = sprintf "%04d%02d%02d",
	localtime->year()+1900,
	localtime->mon+1,
	localtime->mday;

if ($ARGV[0] eq "-release") {
	print $RELEASE, "\n";
} elsif ($ARGV[0] eq "-tree") {
	print $TREE, "\n";
} elsif ($ARGV[0] eq "-user") {
	print $USER, "\n";
} elsif ($ARGV[0] eq "-host") {
	print $HOST, "\n";
} elsif ($ARGV[0] eq "-date") {
	print $DATE, "\n";
} elsif ($ARGV[0] eq "-datestamp") {
	print $DATESTAMP, "\n";
} elsif ($ARGV[0] eq "-arch") {
	print $ARCH, "\n";
} elsif ($ARGV[0] eq "-os") {
	print $OS, "\n";
} elsif ($ARGV[0] eq "-(help" || $ARGV[0] eq "-?") {
	print "$prog [-release|-tree|-user|-host|-date|-datestamp|-arch|-os|-help]\n";
	exit 1;
} else {

print <<"EOT";
/*
 * This file is automatically generated by $prog. DO NOT EDIT!
 */

char	*_build_release =	"$RELEASE";
char	*_build_tree =		"$TREE";
char	*_build_user =		"$USER";
char	*_build_host =		"$HOST";
char	*_build_date =		"$DATE";
char	*_build_datestamp =	"$DATESTAMP";
char	*_build_arch =		"$ARCH";
char	*_build_os =		"$OS";
EOT

}

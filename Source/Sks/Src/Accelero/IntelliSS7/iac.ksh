#
# Copyright (C) 1999-2000 IntelliNet Technologies, Inc.  All rights reserved.
#


#
# $Id: iac.ksh,v 1.1.1.1 2007-10-08 11:11:10 bsccs2 Exp $
#
# $Log: not supported by cvs2svn $
# Revision 1.1.1.1  2007/10/04 13:23:38  bsccs2
# init tree
#
# Revision 1.1.1.1  2007/08/03 06:48:37  cvsadmin
# BscCs2
#
# Revision 1.1.1.1  2007/03/08 15:12:51  cvsadmin
# BSC project
#
# Revision 9.1  2005/03/23 12:51:01  cvsadmin
# Begin PR6.5
#
# Revision 8.2  2005/03/21 13:49:06  cvsadmin
# PR6.4.2 Source Propagated to Current
#
# Revision 7.1  2002/08/26 22:08:32  mmiers
# Begin PR6.2
#
# Revision 6.1  2002/02/28 16:13:16  mmiers
# Begin PR7.
#
# Revision 5.1  2001/08/16 20:45:05  mmiers
# Start PR6.
#
# Revision 4.1  2001/05/01 00:52:59  mmiers
# Begin PR5
#
# Revision 3.1  2000/08/15 23:55:37  mmiers
#
# Begin round 4.
#
# Revision 1.1  2000/03/31 19:18:24  npopov
# A startup Korn shell script for regression testing ASN.1/C compiler
#
#



perl -S -P $ITS_ROOT/iac.pl $*


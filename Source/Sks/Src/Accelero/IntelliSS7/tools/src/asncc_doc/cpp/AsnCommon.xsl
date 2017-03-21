<?xml version='1.0'?>

<!-- /////////////////////////////////////////////////////////////////////// -->
<!--                                                                         -->
<!--      (C) 2001 - 2002 IntelliNet Technologies Inc. All Rights Reserved.  -->
<!--             Manufactured in the United States of America.               -->
<!--     1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        -->
<!--                                                                         -->
<!--  This product and related documentation is protected by copyright and   -->
<!--  distributed under licenses restricting its use, copying, distribution  -->
<!--  and decompilation.  No part of this product or related documentation   -->
<!--  may be reproduced in any form by any means without prior written       -->
<!--  authorization of IntelliNet Technologies and its licensors, if any.    -->
<!--                                                                         -->
<!--  RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the      -->
<!--  government is subject to restrictions as set forth in subparagraph     -->
<!--  (c)(1)(ii) of the Rights in Technical Data and Computer Software       -->
<!--                                                                         -->
<!-- /////////////////////////////////////////////////////////////////////// -->
<!--                                                                         -->
<!-- CONTRACT: INTERNAL                                                      -->
<!--                                                                         -->
<!-- /////////////////////////////////////////////////////////////////////// -->
<!--                                                                         -->
<!-- ID: $Id: AsnCommon.xsl,v 1.1.1.1 2007-10-08 11:12:05 bsccs2 Exp $ -->
<!--                                                                         -->
<!-- /////////////////////////////////////////////////////////////////////// -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
  <xsl:template match="/">
    <html>

    <head>
    <title>Class <xsl:value-of select="./asnType/asnCommon/className"/>
    </title>
    </head>

    <body bgcolor="#FFFFFF" text="#000000">


    <!-- Header /////////////////////////////////////////////////////////////////////////////////////////////////// -->

    <p>
      <i>
        <img border="0" src="AsnModuleLogo.jpg" width="240" height="47" align="right"></img>
      </i>
    </p>

    <p style="margin-bottom: 0">
      <i>
        <font size="3">
          - IntelliSS7 Application Development Environment - <xsl:value-of select=
          "./asnType/asnCommon/asnModuleName"/> C++ API -
        </font>
      </i>
    </p>

    <hr size="4" style="margin-top: 0"></hr>

    <!-- Equivalence to common type /////////////////////////////////////////////////////////////////////////////// -->

    <p align="left">
      <u>
        <font size="6">Class <xsl:value-of select="./asnType/asnCommon/className"/></font>
      </u>
    </p>

    <p>The ASN.1 type <xsl:value-of select="./asnType/asnCommon/asnTypeName"/> is a common ASN.1 type accross the
	different ASN.1 modules of <xsl:value-of select="./asnType/asnCommon/asnModuleName"/>. The class 
	<xsl:value-of select="./asnType/asnCommon/className"/> is equivalent (C++ typedef) to the class 
	<xsl:value-of select="./asnType/asnCommon/asnCommonClassName"/>. See <b><xsl:element name="a">
	<xsl:attribute name="href"><xsl:value-of select="./asnType/asnCommon/asnCommonTypeFileName"/>.html</xsl:attribute>
	<xsl:value-of select="./asnType/asnCommon/asnCommonClassName"/></xsl:element></b> for more information.</p>


    <!-- Footer (copyright notice) //////////////////////////////////////////////////////////////////////////////// -->

    <br></br>
    <hr size="4"></hr>

    <p style="line-height: 100%; margin-left: 0; margin-top: 1; margin-bottom: 0" align="center">
      <font size="2">
        (C) 2001 - 2002 IntelliNet Technologies, Inc. All rights reserved.
      </font>
    </p>

    <br></br>

    </body>

    </html>
  </xsl:template>
</xsl:stylesheet>
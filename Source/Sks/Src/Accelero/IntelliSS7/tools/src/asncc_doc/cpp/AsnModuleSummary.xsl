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
<!-- ID: $Id: AsnModuleSummary.xsl,v 1.1.1.1 2007-10-08 11:12:06 bsccs2 Exp $ -->
<!--                                                                         -->
<!-- /////////////////////////////////////////////////////////////////////// -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
  <xsl:template match="/">
    <html>

    <head>
    <title>
      ASN.1 Module Summary
    </title>
    </head>

    <body bgcolor="#FFFFFF" text="#000000">


    <!-- Introduction ///////////////////////////////////////////////////////////////////////////////////////////// -->

    <br></br>
    <br></br>

    <p align="center">
      <img border="0" src="AsnModuleLogo.jpg" width="474" height="91"></img>
    </p>

    <br></br>
    <br></br>

    <p align="center">
      <font size="6">
        IntelliSS7 Application Development Environment
      </font>
    </p>
    <p align="center">
      <font size="6">
        <xsl:value-of select="asnModuleSummary/moduleName"/> API Reference Documentation
      </font>
    </p>

    <br></br>

    <hr size="4"></hr>

    <br></br>

    <ul type="square">
      <li><font size="4">List of all classes</font></li>
    </ul>

    <!-- Class list /////////////////////////////////////////////////////////////////////////////////////////////// -->

    <p>
    <xsl:for-each select="asnModuleSummary/asnType">
      <xsl:element name="a">
        <xsl:attribute name="href"><xsl:value-of select="asnTypeFileName"/>.html</xsl:attribute>
        <xsl:value-of select="className"/>
      </xsl:element>
      -
    </xsl:for-each>
    </p>

    <br></br>
    <br></br>


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
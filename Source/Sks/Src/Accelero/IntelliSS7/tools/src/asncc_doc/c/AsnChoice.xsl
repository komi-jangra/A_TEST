<?xml version='1.0'?>

<!-- /////////////////////////////////////////////////////////////////////// -->
<!--                                                                         -->
<!--      (C) 2000 IntelliNet Technologies Inc. All Rights Reserved.         -->
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
<!-- ID: $Id: AsnChoice.xsl,v 1.1.1.1 2007-10-08 11:12:05 bsccs2 Exp $ -->
<!--                                                                         -->
<!-- /////////////////////////////////////////////////////////////////////// -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
  <xsl:template match="/">
    <html>

    <head>
    <title>Class Interface <xsl:value-of select="./asnType/asnChoice/className"/>
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
          "./asnType/asnChoice/asnModuleName"/> C API -
        </font>
      </i>
    </p>

    <hr size="4" style="margin-top: 0"></hr>

    <!-- Inheritance from base type /////////////////////////////////////////////////////////////////////////////// -->

    <p align="left">
      <u>
        <font size="6">Class Interface <xsl:value-of select="./asnType/asnChoice/className"/></font>
      </u>
    </p>

    <p>The ASN.1 type <xsl:value-of select="./asnType/asnChoice/asnTypeName"/> is based on the ASN.1 CHOICE built-in 
    type, therefore the class interface <xsl:value-of select="./asnType/asnChoice/className"/> inherits (conceptually)
    from the class interface <b><a href="AsnChoice.html">ASN_Choice</a></b>.</p>

    <!-- Class summary //////////////////////////////////////////////////////////////////////////////////////////// -->

    <br></br>

    <ul type="square">
      <li>
        <font size="4">
          Class interface functions summary
        </font>
      </li>
    </ul>

    <p>
      <xsl:element name="a">
        <xsl:attribute name="href">#ConstructDefault</xsl:attribute>
        <xsl:value-of select="./asnType/asnChoice/className"/>_ConstructDefault
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#Destruct</xsl:attribute>
        <xsl:value-of select="./asnType/asnChoice/className"/>_Destruct
      </xsl:element>
      -
      <xsl:for-each select="asnType/asnChoice/memberFunctions/memberFunctionSetChoice">
        <xsl:element name="a">
          <xsl:attribute name="href">#<xsl:value-of select="name"/></xsl:attribute>
          <xsl:value-of select="name"/>
        </xsl:element>
        -
      </xsl:for-each>
      <xsl:for-each select="asnType/asnChoice/memberFunctions/memberFunctionGetChoice">
        <xsl:element name="a">
          <xsl:attribute name="href">#<xsl:value-of select="name"/></xsl:attribute>
          <xsl:value-of select="name"/>
        </xsl:element>
        -
      </xsl:for-each>
      <xsl:for-each select="asnType/asnChoice/memberFunctions/memberFunctionChoice">
        <xsl:element name="a">
          <xsl:attribute name="href">#<xsl:value-of select="name"/></xsl:attribute>
          <xsl:value-of select="name"/>
        </xsl:element>
        -
      </xsl:for-each>
      <xsl:element name="a">
        <xsl:attribute name="href">#Encode</xsl:attribute>
        <xsl:value-of select="./asnType/asnChoice/className"/>_Encode
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#Decode</xsl:attribute>
        <xsl:value-of select="./asnType/asnChoice/className"/>_Decode
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#Clone</xsl:attribute>
        <xsl:value-of select="./asnType/asnChoice/className"/>_Clone
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#Equals</xsl:attribute>
        <xsl:value-of select="./asnType/asnChoice/className"/>_Equals
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#GetName</xsl:attribute>
        <xsl:value-of select="./asnType/asnChoice/className"/>_GetName
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#GetBaseName</xsl:attribute>
        <xsl:value-of select="./asnType/asnChoice/className"/>_GetBaseName
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#Print</xsl:attribute>
        <xsl:value-of select="./asnType/asnChoice/className"/>_Print
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#ToString</xsl:attribute>
        <xsl:value-of select="./asnType/asnChoice/className"/>_ToString
      </xsl:element>
    </p>

    <!-- Constructors/Destructor ////////////////////////////////////////////////////////////////////////////////// -->

    <br></br>

    <ul type="square">
      <li>
        <font size="4">
          Constructor/Destructor functions
        </font>
      </li>
    </ul>

    <div align="left">
      <table border="1" width="100%">
        <tr>
          <td valign="middle" align="center" bgcolor="#CCCCFF" width="33%">
            <b>Constructor/Destructor function signature</b>
          </td>
          <td valign="middle" align="center" bgcolor="#CCCCFF">
            <b>Constructor/Destructor function summary</b>
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">ConstructDefault</xsl:attribute>
              <b><xsl:value-of select="./asnType/asnChoice/className"/> 
              <xsl:value-of select="./asnType/asnChoice/className"/>_ConstructDefault()</b>
            </xsl:element>
          </td>
          <td valign="middle" align="left">
            The <b><xsl:value-of select="./asnType/asnChoice/className"/>_ConstructDefault</b> constructor function
            allows creating a <xsl:value-of select="./asnType/asnChoice/className"/> object with an empty (i.e. no 
            choice) contents (default constructor function). A call to one of the <b><xsl:value-of select=
            "/asnType/asnChoice/className"/>_SetChoice__</b> function is mandatory before the object is encoded (call
            to the <b><xsl:value-of select="./asnType/asnChoice/className"/>_Encode</b> function) or an <a href=
            "AsnEncodeError.html"><b>ASN_EncodeError</b></a> object is returned by the <b><xsl:value-of select=
            "./asnType/asnChoice/className"/>_Encode</b> function. The constructor function returns <b>NULL</b> if
            there is insufficient memory available.
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">Destruct</xsl:attribute>
              <b>void <xsl:value-of select="./asnType/asnChoice/className"/>_Destruct(<xsl:value-of select=
              "./asnType/asnChoice/className"/> object)</b>
            </xsl:element>
          </td>
          <td valign="middle" align="left">
            The <b><xsl:value-of select="./asnType/asnChoice/className"/>_Destruct</b> destructor function allows
            destroying a <xsl:value-of select="./asnType/asnChoice/className"/> object.
          </td>
        </tr>
      </table>
    </div>

    <!-- Functions //////////////////////////////////////////////////////////////////////////////////////////////// -->

    <br></br>

    <ul type="square">
      <li>
        <font size="4">
          Public functions
        </font>
      </li>
    </ul>

    <div align="left">
      <table border="1" width="100%">
        <tr>
          <td valign="middle" align="center" bgcolor="#CCCCFF" width="33%">
            <b>Function signature</b>
          </td>
          <td valign="middle" align="center" bgcolor="#CCCCFF">
            <b>Function summary</b>
          </td>
        </tr>
        <xsl:for-each select="asnType/asnChoice/memberFunctions/memberFunctionSetChoice">
          <tr>
            <td valign="middle" align="left" width="33%">
              <xsl:element name="a">
                <xsl:attribute name="name"><xsl:value-of select="name"/></xsl:attribute>
                <b><xsl:value-of select="signature"/></b>
              </xsl:element>
            </td>
            <td valign="middle" align="left">
              The <b><xsl:value-of select="name"/></b> function allows specifying the "<xsl:value-of select=
              "asnChoiceName"/>" choice for a <xsl:value-of select="//asnType/asnChoice/className"/> object. The 
              <xsl:value-of select="choiceTypeName"/> object passed as parameter of the <xsl:value-of select="name"/>
              function is destroyed when the <xsl:value-of select="//asnType/asnChoice/className"/> object is
              destroyed, therefore the end-user must not explicitly destroy the <xsl:value-of select=
              "choiceTypeName"/> object (i.e. no explicit call to the associated destructor function).
            </td>
          </tr>
        </xsl:for-each>

        <xsl:for-each select="asnType/asnChoice/memberFunctions/memberFunctionGetChoice">
          <tr>
            <td valign="middle" align="left" width="33%">
              <xsl:element name="a">
                <xsl:attribute name="name"><xsl:value-of select="name"/></xsl:attribute>              
                <b><xsl:value-of select="signature"/></b>
              </xsl:element>
            </td>
            <td valign="middle" align="left">
              The <b><xsl:value-of select="name"/></b> function returns the "<xsl:value-of select="asnChoiceName"/>"
              choice of a <xsl:value-of select="//asnType/asnChoice/className"/> object. If the 
              "<xsl:value-of select="asnChoiceName"/>" choice is not the choice (i.e. the choice is not 
              "<xsl:value-of select="asnChoiceName"/>") or no choice is present (i.e. no previous call to the
              associated <b><xsl:value-of select="//asnType/asnChoice/className"/>_SetChoice__</b> function or <b>
              <xsl:value-of select="//asnType/asnChoice/className"/>_Decode</b> function) an <b> <a href=
              "ITS_Precondition.html">ASN C Runtime precondition</a></b> is triggered and the function returns 
              <b>NULL</b>. After a call to the <b><xsl:value-of select="//asnType/asnChoice/className"/>_Decode</b> 
              function, the end-user must use the associated <b><xsl:value-of select=
              "//asnType/asnChoice/className"/>_Choice__</b> function to check if the choice is "<xsl:value-of 
              select="asnChoiceName"/>".
            </td>
          </tr>
        </xsl:for-each>

        <xsl:for-each select="asnType/asnChoice/memberFunctions/memberFunctionChoice">
          <tr>
            <td valign="middle" align="left" width="33%">
              <xsl:element name="a">
                <xsl:attribute name="name"><xsl:value-of select="name"/></xsl:attribute>              
                <b><xsl:value-of select="signature"/></b>
              </xsl:element>
            </td>
            <td valign="middle" align="left">
              The <b><xsl:value-of select="name"/></b> function allows checking if the choice of a <xsl:value-of 
              select="//asnType/asnChoice/className"/> object is "<xsl:value-of select="asnChoiceName"/>". 
            </td>
          </tr>
        </xsl:for-each>

      </table>
    </div>

    <!-- Inherited functions (encoding and decoding) ////////////////////////////////////////////////////////////// -->

    <br></br>

    <ul type="square">
      <li>
        <font size="4">
          Public functions inherited (conceptually) from <a href="AsnChoice.html">ASN_Choice</a> and 
          <a href="AsnObject.html">ASN_Object</a>
        </font>
      </li>
    </ul>

    <div align="left">
      <table border="1" width="100%">
        <tr>
          <td valign="middle" align="center" bgcolor="#CCCCFF" width="33%">
            <b>Function signature</b>
          </td>
          <td valign="middle" align="center" bgcolor="#CCCCFF">
            <b>Function summary</b>
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">Encode</xsl:attribute>
              <b>int <xsl:value-of select="./asnType/asnChoice/className"/>_Encode(<xsl:value-of select=
              "./asnType/asnChoice/className"/> object, ASN_Octets* octets, ASN_EncodeError* encodeError)</b>
            </xsl:element>
          </td>
          <td valign="middle" align="left">
            The <b><xsl:value-of select="./asnType/asnChoice/className"/>_Encode</b> function allows encoding a 
            <xsl:value-of select="./asnType/asnChoice/className"/> object to an ASN.1 encoded value. If the 
            encoding is successful the function returns <b>ITS_SUCCESS</b> and the ASN.1 encoded value is returned 
            through an object of class <b><a href="Octets.html">ASN_Octets</a></b> (<i>octets</i> parameter of C type
            ASN_Octets*). The end-user is responsible for destroying the returned <b><a href="Octets.html">ASN_Octets
            </a></b> object. If the encoding is not successful the function returns <b>ITS_E_ASN_ENCODE_ERROR</b> and
            an encode error is returned through an object of class <b><a href="AsnEncodeError.html">ASN_EncodeError</a>
            </b> (<i>encodeError</i> parameter of C type ASN_EncodeError*). The end-user is responsible for destroying 
            the returned <b><a href="AsnEncodeError.html">ASN_EncodeError</a></b> object. The function returns <b>
            ITS_ENOMEM</b> if there is insufficient memory available.
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">Decode</xsl:attribute>
              <b>int <xsl:value-of select="./asnType/asnChoice/className"/>_Decode(<xsl:value-of select=
              "./asnType/asnChoice/className"/> object, ASN_Octets octets, ASN_DecodeError* decodeError)</b>
            </xsl:element>
          </td>
          <td valign="middle" align="left">
            The <b><xsl:value-of select="./asnType/asnChoice/className"/>_Decode</b> function allows decoding an
            ASN.1 encoded value (of type <xsl:value-of select="./asnType/asnChoice/className"/>). The ASN.1 encoded
            value is passed through an object of class <b><a href="Octets.html">ASN_Octets</a></b> (<i>octets</i> 
            parameter of C type ASN_Octets). If the decoding is successful the function returns <b>ITS_SUCCESS</b>. If
            the decoding is not successful the function returns <b>ITS_E_ASN_DECODE_ERROR</b> and a decode error is 
            returned through an object of class <b><a href="AsnDecodeError.html">ASN_DecodeError</a></b> 
            (<i>decodeError</i> parameter of C type ASN_DecodeError*). The end-user is responsible for destroying the 
            returned <b><a href="AsnDecodeError.html">ASN_DecodeError</a></b> object. The function returns <b>
            ITS_ENOMEM</b> if there is insufficient memory available.
          </td>
        </tr>
      </table>
    </div>

    <!-- Inherited functions ////////////////////////////////////////////////////////////////////////////////////// -->

    <br></br>

    <ul type="square">
      <li>
        <font size="4">
          Public functions inherited (conceptually) from <a href="AsnChoice.html">ASN_Choice</a> and 
          <a href="AsnObject.html">ASN_Object</a> (continued)
        </font>
      </li>
    </ul>

    <div align="left">
      <table border="1" width="100%">
        <tr>
          <td valign="middle" align="center" bgcolor="#CCCCFF" width="33%">
            <b>Function signature</b>
          </td>
          <td valign="middle" align="center" bgcolor="#CCCCFF">
            <b>Function summary</b>
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">Clone</xsl:attribute>
              <b><xsl:value-of select="./asnType/asnChoice/className"/> <xsl:value-of select=
              "./asnType/asnChoice/className"/>_Clone(const <xsl:value-of select=
              "./asnType/asnChoice/className"/> object)</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b><xsl:value-of select="./asnType/asnChoice/className"/>_Clone</b> function allows cloning a 
            <xsl:value-of select="./asnType/asnChoice/className"/> object. The end-user is responsible for 
            destroying the clone object. The function returns <b>NULL</b> if there is insufficient memory available.
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
            <xsl:attribute name="name">Equals</xsl:attribute>
              <b>ITS_BOOLEAN <xsl:value-of select="./asnType/asnChoice/className"/>_Equals(const 
              <xsl:value-of select="./asnType/asnChoice/className"/> object, const <xsl:value-of select=
              "./asnType/asnChoice/className"/> other)</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b><xsl:value-of select="./asnType/asnChoice/className"/>_Equals</b> function allows checking the
            equality of two <xsl:value-of select="./asnType/asnChoice/className"/> objects. The function returns
            <b>ITS_TRUE</b> if the two objects are equal and <b>ITS_FALSE</b> otherwise.
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">GetName</xsl:attribute>
              <b>const char* <xsl:value-of select="./asnType/asnChoice/className"/>_GetName(const 
              <xsl:value-of select="./asnType/asnChoice/className"/> object)</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b><xsl:value-of select="./asnType/asnChoice/className"/>_GetName</b> function returns the 
            character string <font color="#000080">&quot;<xsl:value-of select="./asnType/asnChoice/className"/>
            &quot;</font>.
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">GetBaseName</xsl:attribute>
              <b>const char* <xsl:value-of select="./asnType/asnChoice/className"/>_GetBaseName(const 
              <xsl:value-of select="./asnType/asnChoice/className"/> object)</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b><xsl:value-of select="./asnType/asnChoice/className"/>_GetBaseName</b> function returns the
            character string <font color="#000080">&quot;CHOICE&quot;</font>.
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">Print</xsl:attribute>
              <b>void <xsl:value-of select="./asnType/asnChoice/className"/>_Print(const <xsl:value-of select=
              "./asnType/asnChoice/className"/> object)</b>
            </xsl:element>
          </td>
          <td valign="middle" align="left">
            The <b><xsl:value-of select="./asnType/asnChoice/className"/>_Print</b> function allows printing the
            contents of a <xsl:value-of select="./asnType/asnChoice/className"/> object to the standard output at
            any time.
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">ToString</xsl:attribute>
              <b>char* <xsl:value-of select="./asnType/asnChoice/className"/>_ToString(const <xsl:value-of select=
              "./asnType/asnChoice/className"/> object)</b>
            </xsl:element>
          </td>
          <td valign="middle" align="left">
            The <b><xsl:value-of select="./asnType/asnChoice/className"/>_ToString</b> function allows printing the
            contents of a <xsl:value-of select="./asnType/asnChoice/className"/> object to a character string at
            any time and returns the character string. The end-user is responsible for freeing the returned character
            string. The function returns <b>NULL</b> if there is insufficient memory available.
          </td>
        </tr>
      </table>
    </div>

    <!-- ASN.1 type definition //////////////////////////////////////////////////////////////////////////////////// -->

    <br></br>

    <ul type="square">
      <li>
        <font size="4">
          ASN.1 type <xsl:value-of select="./asnType/asnChoice/asnTypeName"/> definition
        </font>
      </li>
    </ul>

    <div align="left">
      <table border="1" width="100%">
        <tr>
          <td valign="middle" align="center" bgcolor="#CCCCFF" width="100%">
            <b>ASN.1 type definition</b>
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="100%">
            <xsl:for-each select="asnType/asnChoice/asnDefinition/line">
              <p style="line-height: 100%; margin-left: 0; margin-top: 0; margin-bottom: 0">
              <xsl:for-each select="shift">
                <font color="#FFFFFF">......</font>
              </xsl:for-each>
              <xsl:value-of select="text"/>
              </p>
            </xsl:for-each>
          </td>
        </tr>
      </table>
    </div>

    <!-- Footer (copyright notice) //////////////////////////////////////////////////////////////////////////////// -->

    <br></br>
    <hr size="4"></hr>

    <p style="line-height: 100%; margin-left: 0; margin-top: 1; margin-bottom: 0" align="center">
      <font size="2">
        © 2000 IntelliNet Technologies, Inc. All rights reserved.
      </font>
    </p>

    <br></br>

    </body>

    </html>
  </xsl:template>
</xsl:stylesheet>
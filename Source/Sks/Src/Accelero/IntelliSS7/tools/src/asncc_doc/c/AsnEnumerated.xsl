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
<!-- ID: $Id: AsnEnumerated.xsl,v 1.1.1.1 2007-10-08 11:12:05 bsccs2 Exp $ -->
<!--                                                                         -->
<!-- /////////////////////////////////////////////////////////////////////// -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
  <xsl:template match="/">
    <html>

    <head>
    <title>Class Interface <xsl:value-of select="./asnType/asnEnumerated/className"/>
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
          "./asnType/asnEnumerated/asnModuleName"/> C API -
        </font>
      </i>
    </p>

    <hr size="4" style="margin-top: 0"></hr>

    <!-- Inheritance from base type /////////////////////////////////////////////////////////////////////////////// -->

    <p align="left">
      <u>
        <font size="6">Class Interface <xsl:value-of select="./asnType/asnEnumerated/className"/></font>
      </u>
    </p>

    <p>The ASN.1 type <xsl:value-of select="./asnType/asnEnumerated/asnTypeName"/> is based on the ASN.1 ENUMERATED
    built-in type, therefore the class interface <xsl:value-of select="./asnType/asnEnumerated/className"/> inherits 
    (conceptually) from the class interface <b><a href="AsnEnumerated.html">ASN_Enumerated</a></b>.</p>

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
        <xsl:value-of select="./asnType/asnEnumerated/className"/>_ConstructDefault
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#ConstructWithValue</xsl:attribute>
        <xsl:value-of select="./asnType/asnEnumerated/className"/>_ConstructWithValue
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#Destruct</xsl:attribute>
        <xsl:value-of select="./asnType/asnEnumerated/className"/>_Destruct
      </xsl:element>
      -
      <xsl:for-each select="asnType/asnEnumerated/memberFunctions/memberFunctionSet">
        <xsl:element name="a">
          <xsl:attribute name="href">#<xsl:value-of select="name"/></xsl:attribute>
          <xsl:value-of select="name"/>
        </xsl:element>
        -
      </xsl:for-each>
      <xsl:for-each select="asnType/asnEnumerated/memberFunctions/memberFunctionIs">
        <xsl:element name="a">
          <xsl:attribute name="href">#<xsl:value-of select="name"/></xsl:attribute>
          <xsl:value-of select="name"/>
        </xsl:element>
        -
      </xsl:for-each>
      <xsl:element name="a">
        <xsl:attribute name="href">#Encode</xsl:attribute>
        <xsl:value-of select="./asnType/asnEnumerated/className"/>_Encode
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#Decode</xsl:attribute>
        <xsl:value-of select="./asnType/asnEnumerated/className"/>_Decode
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#GetValue</xsl:attribute>
        <xsl:value-of select="./asnType/asnEnumerated/className"/>_GetValue
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#SetValue</xsl:attribute>
        <xsl:value-of select="./asnType/asnEnumerated/className"/>_SetValue
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#Clone</xsl:attribute>
        <xsl:value-of select="./asnType/asnEnumerated/className"/>_Clone
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#Equals</xsl:attribute>
        <xsl:value-of select="./asnType/asnEnumerated/className"/>_Equals
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#GetName</xsl:attribute>
        <xsl:value-of select="./asnType/asnEnumerated/className"/>_GetName
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#GetBaseName</xsl:attribute>
        <xsl:value-of select="./asnType/asnEnumerated/className"/>_GetBaseName
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#Print</xsl:attribute>
        <xsl:value-of select="./asnType/asnEnumerated/className"/>_Print
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#ToString</xsl:attribute>
        <xsl:value-of select="./asnType/asnEnumerated/className"/>_ToString
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
              <b><xsl:value-of select="./asnType/asnEnumerated/className"/> 
              <xsl:value-of select="./asnType/asnEnumerated/className"/>_ConstructDefault()</b>
            </xsl:element>
          </td>
          <td valign="middle" align="left">
            The <b><xsl:value-of select="./asnType/asnEnumerated/className"/>_ConstructDefault</b> constructor 
            function allows creating a <xsl:value-of select="./asnType/asnEnumerated/className"/> object with a default
            value of 0 (default constructor function). If 0 is not one of the enumerated predefined values then a call
            to one of the <b><xsl:value-of select="./asnType/asnEnumerated/className"/>_Set__</b> functions is 
            mandatory before the object is encoded (call to the <b><xsl:value-of select=
            "./asnType/asnEnumerated/className"/>_Encode</b> function) or an <a href="AsnEncodeError.html"><b>
            ASN_EncodeError</b></a> object is returned by the <b><xsl:value-of select=
            "./asnType/asnEnumerated/className"/>_Encode</b> function. The constructor function returns <b>NULL</b> if
            there is insufficient memory available. 
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">ConstructWithValue</xsl:attribute>
              <b><xsl:value-of select="./asnType/asnEnumerated/className"/> 
              <xsl:value-of select="./asnType/asnEnumerated/className"/>_ConstructWithValue(ITS_LONG value)</b>
            </xsl:element>
          </td>
          <td valign="middle" align="left">
            The <b><xsl:value-of select="./asnType/asnEnumerated/className"/>_ConstructWithValue</b> constructor 
            function allows creating a <xsl:value-of select="./asnType/asnEnumerated/className"/> object with a 
            specified value (<i>value</i> parameter of C type ITS_LONG). The specified value must be one of the 
            enumerated predefined values or an <b><a href="AsnEncodeError.html">ASN_EncodeError</a></b> object is 
            returned when the <xsl:value-of select="./asnType/asnEnumerated/className"/> object is encoded (call to the
            <b><xsl:value-of select="./asnType/asnEnumerated/className"/>_Encode</b> function). The constructor 
            function returns <b>NULL</b> if there is insufficient memory available.
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">Destruct</xsl:attribute>
              <b>void <xsl:value-of select="./asnType/asnEnumerated/className"/>_Destruct(<xsl:value-of select=
              "./asnType/asnEnumerated/className"/> object)</b>
            </xsl:element>
          </td>
          <td valign="middle" align="left">
            The <b><xsl:value-of select="./asnType/asnEnumerated/className"/>_Destruct</b> destructor function allows
            destroying a <xsl:value-of select="./asnType/asnEnumerated/className"/> object.
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
        <xsl:for-each select="asnType/asnEnumerated/memberFunctions/memberFunctionSet">
          <tr>
            <td valign="middle" align="left" width="33%">
              <xsl:element name="a">
                <xsl:attribute name="name"><xsl:value-of select="name"/></xsl:attribute>
                <b><xsl:value-of select="signature"/></b>
              </xsl:element>
            </td>
            <td valign="middle" align="left">
              The <b><xsl:value-of select="name"/></b> function allows setting the value of a <xsl:value-of select=
              "//asnType/asnEnumerated/className"/> object to the value <font color="#000080">&quot;
              <xsl:value-of select="enumItemName"/>&quot;</font>.
            </td>
          </tr>
        </xsl:for-each>
        <xsl:for-each select="asnType/asnEnumerated/memberFunctions/memberFunctionIs">
          <tr>
            <td valign="middle" align="left" width="33%">
              <xsl:element name="a">
                <xsl:attribute name="name"><xsl:value-of select="name"/></xsl:attribute>              
                <b><xsl:value-of select="signature"/></b>
              </xsl:element>
            </td>
            <td valign="middle" align="left">
              The <b><xsl:value-of select="name"/></b> function allows checking if the value of a <xsl:value-of select=
              "//asnType/asnEnumerated/className"/> object is <font color="#000080">&quot;<xsl:value-of select=
              "enumItemName"/>&quot;</font> (the function returns <b>ITS_TRUE</b> in this case and <b>ITS_FALSE</b>
              otherwise).
            </td>
          </tr>
        </xsl:for-each>
      </table>
    </div>

    <!-- Inherited functions (encoding and decoding) /////////////////////////////////////////////////////// -->

    <br></br>

    <ul type="square">
      <li>
        <font size="4">
          Public functions inherited (conceptually) from <a href="AsnEnumerated.html">ASN_Enumerated</a> and 
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
              <b>int <xsl:value-of select="./asnType/asnEnumerated/className"/>_Encode(<xsl:value-of select=
              "./asnType/asnEnumerated/className"/> object, ASN_Octets* octets, ASN_EncodeError* encodeError)</b>
            </xsl:element>
          </td>
          <td valign="middle" align="left">
            The <b><xsl:value-of select="./asnType/asnEnumerated/className"/>_Encode</b> function allows encoding a 
            <xsl:value-of select="./asnType/asnEnumerated/className"/> object to an ASN.1 encoded value. If the 
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
              <b>int <xsl:value-of select="./asnType/asnEnumerated/className"/>_Decode(<xsl:value-of select=
              "./asnType/asnEnumerated/className"/> object, ASN_Octets octets, ASN_DecodeError* decodeError)</b>
            </xsl:element>
          </td>
          <td valign="middle" align="left">
            The <b><xsl:value-of select="./asnType/asnEnumerated/className"/>_Decode</b> function allows decoding an
            ASN.1 encoded value (of type <xsl:value-of select="./asnType/asnEnumerated/className"/>). The ASN.1 encoded
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
          Public functions inherited (conceptually) from <a href="AsnEnumerated.html">ASN_Enumerated</a> and 
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
              <xsl:attribute name="name">GetValue</xsl:attribute>
              <b>ITS_LONG <xsl:value-of select="./asnType/asnEnumerated/className"/>_GetValue(const 
              <xsl:value-of select="./asnType/asnEnumerated/className"/> object)</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b><xsl:value-of select="./asnType/asnEnumerated/className"/>_GetValue</b> function returns the value
            (C type ITS_LONG) of a <xsl:value-of select="./asnType/asnEnumerated/className"/> object.
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">SetValue</xsl:attribute>
              <b>void <xsl:value-of select="./asnType/asnEnumerated/className"/>_SetValue(<xsl:value-of select=
              "./asnType/asnEnumerated/className"/> object, ITS_LONG value)</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b><xsl:value-of select="./asnType/asnEnumerated/className"/>_SetValue</b> function allows setting the
            value (<i>value</i> parameter of C type ITS_LONG) of a <xsl:value-of select=
            "./asnType/asnEnumerated/className"/> object. The specified value must be one of the enumerated predefined
            values or an <b><a href="AsnEncodeError.html">ASN_EncodeError</a></b> object is returned when the 
            <xsl:value-of select="./asnType/asnEnumerated/className"/> object is encoded (call to the 
            <b><xsl:value-of select="./asnType/asnEnumerated/className"/>_Encode</b> function).
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">Clone</xsl:attribute>
              <b><xsl:value-of select="./asnType/asnEnumerated/className"/> <xsl:value-of select=
              "./asnType/asnEnumerated/className"/>_Clone(const <xsl:value-of select=
              "./asnType/asnEnumerated/className"/> object)</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b><xsl:value-of select="./asnType/asnEnumerated/className"/>_Clone</b> function allows cloning a 
            <xsl:value-of select="./asnType/asnEnumerated/className"/> object. The end-user is responsible for 
            destroying the clone object. The function returns <b>NULL</b> if there is insufficient memory available.
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
            <xsl:attribute name="name">Equals</xsl:attribute>
              <b>ITS_BOOLEAN <xsl:value-of select="./asnType/asnEnumerated/className"/>_Equals(const 
              <xsl:value-of select="./asnType/asnEnumerated/className"/> object, const <xsl:value-of select=
              "./asnType/asnEnumerated/className"/> other)</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b><xsl:value-of select="./asnType/asnEnumerated/className"/>_Equals</b> function allows checking the
            equality of two <xsl:value-of select="./asnType/asnEnumerated/className"/> objects. The function returns
            <b>ITS_TRUE</b> if the two objects are equal and <b>ITS_FALSE</b> otherwise.
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">GetName</xsl:attribute>
              <b>const char* <xsl:value-of select="./asnType/asnEnumerated/className"/>_GetName(const 
              <xsl:value-of select="./asnType/asnEnumerated/className"/> object)</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b><xsl:value-of select="./asnType/asnEnumerated/className"/>_GetName</b> function returns the 
            character string <font color="#000080">&quot;<xsl:value-of select="./asnType/asnEnumerated/className"/>
            &quot;</font>.
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">GetBaseName</xsl:attribute>
              <b>const char* <xsl:value-of select="./asnType/asnEnumerated/className"/>_GetBaseName(const 
              <xsl:value-of select="./asnType/asnEnumerated/className"/> object)</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b><xsl:value-of select="./asnType/asnEnumerated/className"/>_GetBaseName</b> function returns the
            character string <font color="#000080">&quot;ENUMERATED&quot;</font>.
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">Print</xsl:attribute>
              <b>void <xsl:value-of select="./asnType/asnEnumerated/className"/>_Print(const <xsl:value-of select=
              "./asnType/asnEnumerated/className"/> object)</b>
            </xsl:element>
          </td>
          <td valign="middle" align="left">
            The <b><xsl:value-of select="./asnType/asnEnumerated/className"/>_Print</b> function allows printing the
            contents of a <xsl:value-of select="./asnType/asnEnumerated/className"/> object to the standard output at
            any time.
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">ToString</xsl:attribute>
              <b>char* <xsl:value-of select="./asnType/asnEnumerated/className"/>_ToString(const <xsl:value-of select=
              "./asnType/asnEnumerated/className"/> object)</b>
            </xsl:element>
          </td>
          <td valign="middle" align="left">
            The <b><xsl:value-of select="./asnType/asnEnumerated/className"/>_ToString</b> function allows printing the
            contents of a <xsl:value-of select="./asnType/asnEnumerated/className"/> object to a character string at
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
          ASN.1 type <xsl:value-of select="./asnType/asnEnumerated/asnTypeName"/> definition
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
            <xsl:for-each select="asnType/asnEnumerated/asnDefinition/line">
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
        � 2000 IntelliNet Technologies, Inc. All rights reserved.
      </font>
    </p>

    <br></br>

    </body>

    </html>
  </xsl:template>
</xsl:stylesheet>
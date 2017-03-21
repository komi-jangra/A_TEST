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
<!-- ID: $Id: AsnAny.xsl,v 1.1.1.1 2007-10-08 11:12:05 bsccs2 Exp $ -->
<!--                                                                         -->
<!-- /////////////////////////////////////////////////////////////////////// -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
  <xsl:template match="/">
    <html>

    <head>
    <title>Class <xsl:value-of select="./asnType/asnAny/className"/>
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
          "./asnType/asnAny/asnModuleName"/> C++ API -
        </font>
      </i>
    </p>

    <hr size="4" style="margin-top: 0"></hr>

    <!-- Inheritance from base type /////////////////////////////////////////////////////////////////////////////// -->

    <p align="left">
      <u>
        <font size="6">Class <xsl:value-of select="./asnType/asnAny/className"/></font>
      </u>
    </p>

    <p>The ASN.1 type <xsl:value-of select="./asnType/asnAny/asnTypeName"/> is based on the ASN.1 ANY built-in 
    type, therefore the class <xsl:value-of select="./asnType/asnAny/className"/> inherits from the class 
    <b><a href="AsnAny.html">AsnAny</a></b>.</p>

    <!-- Class summary //////////////////////////////////////////////////////////////////////////////////////////// -->

    <br></br>

    <ul type="square">
      <li>
        <font size="4">
          Class interface summary
        </font>
      </li>
    </ul>

    <p>
      <xsl:element name="a">
        <xsl:attribute name="href">#<xsl:value-of select="./asnType/asnAny/className"/></xsl:attribute>
        <xsl:value-of select="./asnType/asnAny/className"/>
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#Encode</xsl:attribute>
        Encode
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#Decode</xsl:attribute>
        Decode
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#GetAny</xsl:attribute>
        GetAny
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#SetAny1</xsl:attribute>
        SetAny
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#SetAny2</xsl:attribute>
        SetAny
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">ContainsAny</xsl:attribute>
        ContainsAny
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">IsDecoded</xsl:attribute>
        IsDecoded
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">GetDecodedOctets</xsl:attribute>
        GetDecodedOctets
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#Clone</xsl:attribute>
        Clone
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#Equals</xsl:attribute>
        Equals
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#GetName</xsl:attribute>
        GetName
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#GetBaseName</xsl:attribute>
        GetBaseName
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#operator=</xsl:attribute>
        operator=
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#operator==</xsl:attribute>
        operator==
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#Print</xsl:attribute>
        Print
      </xsl:element>
      -
      <xsl:element name="a">
        <xsl:attribute name="href">#operator&lt;&lt;</xsl:attribute>
        operator&lt;&lt;
      </xsl:element>
    </p>

    <!-- Constructors ///////////////////////////////////////////////////////////////////////////////////////////// -->

    <br></br>

    <ul type="square">
      <li>
        <font size="4">
          Constructors
        </font>
      </li>
    </ul>

    <div align="left">
      <table border="1" width="100%">
        <tr>
          <td valign="middle" align="center" bgcolor="#CCCCFF" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name"><xsl:value-of select="./asnType/asnAny/className"/></xsl:attribute>
              <b>Constructor signature</b>
            </xsl:element>
          </td>
          <td valign="middle" align="center" bgcolor="#CCCCFF">
            <b>Constructor summary</b>
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <b><xsl:value-of select="./asnType/asnAny/className"/>()</b>
          </td>
          <td valign="middle" align="left">
            The first <b><xsl:value-of select="./asnType/asnAny/className"/></b> constructor allows creating a
            <xsl:value-of select="./asnType/asnAny/className"/> object with an empty (i.e. no any object) contents
            (default constructor). A call to one of the the <b>SetAny__</b> member functions is mandatory before
            the object is encoded (call to the <b>Encode</b> member function) or an <a href="AsnEncodeError.html">
            <b>AsnEncodeError</b></a> exception is thrown.
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <b><xsl:value-of select="./asnType/asnAny/className"/>(AsnObject* anyParam)
            </b>
          </td>
          <td valign="middle" align="left">
            The second <b><xsl:value-of select="./asnType/asnAny/className"/></b> constructor allows creating a
            <xsl:value-of select="./asnType/asnAny/className"/> object with a specified any object (<i>anyParam</i>
            parameter of C++ type AsnObject*). The AsnObject passed as parameter is deleted when the 
            <xsl:value-of select="./asnType/asnAny/className"/> object is deleted, therefore the end-user must not
            explicitly or implicitly delele the AsnObject (i.e. no explicit call to operator delete and no allocation
            on the stack).
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <b><xsl:value-of select=
            "./asnType/asnAny/className"/>(Octets&amp; octets)</b>
          </td>
          <td valign="middle" align="left">
            The third <b><xsl:value-of select="./asnType/asnAny/className"/></b> constructor allows creating a
            <xsl:value-of select="./asnType/asnAny/className"/> object from an ASN.1 encoded value (the <b>
            Decode</b> member function is called). The ASN.1 encoded value is passed through an object of class <b>
            <a href="Octets.html">Octets</a></b>. Can throw an <b><a href="AsnDecodeError.html">AsnDecodeError</a></b>
			exception.
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <b><xsl:value-of select="./asnType/asnAny/className"/>(const 
            <xsl:value-of select="./asnType/asnAny/className"/>&amp; rhs)</b>
          </td>
          <td valign="middle" align="left">
            The fourth <b><xsl:value-of select="./asnType/asnAny/className"/></b> constructor is the standard 
            C++ copy constructor.
          </td>
        </tr>
      </table>
    </div>

    <!-- Inherited member functions (encoding and decoding) /////////////////////////////////////////////////////// -->

    <br></br>

    <ul type="square">
      <li>
        <font size="4">
          Public member functions inherited from <a href="AsnAny.html">AsnAny</a> and 
          <a href="AsnObject.html">AsnObject</a>
        </font>
      </li>
    </ul>

    <div align="left">
      <table border="1" width="100%">
        <tr>
          <td valign="middle" align="center" bgcolor="#CCCCFF" width="33%">
            <b>Member function signature</b>
          </td>
          <td valign="middle" align="center" bgcolor="#CCCCFF">
            <b>Member function summary</b>
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">Encode</xsl:attribute>
              <b>Octets* Encode()</b>
            </xsl:element>
          </td>
          <td valign="middle" align="left">
            The <b>Encode</b> member function allows encoding a <xsl:value-of select=
            "./asnType/asnAny/className"/> object to an ASN.1 encoded value. The ASN.1 encoded value is returned 
            through an object of class <b><a href="Octets.html">Octets</a></b>. The end-user is responsible for 
            deleting the object of class<b><a href="Octets.html">Octets</a></b>. Can throw an <a href=
            "AsnEncodeError.html"><b> AsnEncodeError</b></a> exception.
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">Decode</xsl:attribute>
              <b>void Decode(Octets&amp; octets)</b>
            </xsl:element>
          </td>
          <td valign="middle" align="left">
            The <b>Decode</b> member function allows decoding an ASN.1 encoded value (of type <xsl:value-of select=
            "./asnType/asnAny/className"/>). The ASN.1 encoded value is passed through an object of class 
            <b><a href="Octets.html">Octets</a></b>. Can throw an <b><a href="AsnDecodeError.html">AsnDecodeError</a>
            </b> exception.
          </td>
        </tr>
      </table>
    </div>

    <!-- Inherited member functions /////////////////////////////////////////////////////////////////////////////// -->

    <br></br>

    <ul type="square">
      <li>
        <font size="4">
          Public member functions inherited from <a href="AsnAny.html">AsnAny</a> and 
          <a href="AsnObject.html">AsnObject</a> (continued)
        </font>
      </li>
    </ul>

    <div align="left">
      <table border="1" width="100%">
        <tr>
          <td valign="middle" align="center" bgcolor="#CCCCFF" width="33%">
            <b>Member function signature</b>
          </td>
          <td valign="middle" align="center" bgcolor="#CCCCFF">
            <b>Member function summary</b>
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">GetAny</xsl:attribute>
              <b>const AsnObject&amp; GetAny() const</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b>GetAny</b> member function returns the previously specified any object of a <xsl:value-of select=
            "./asnType/asnAny/className"/> object. If no any object has been previously specified (i.e. no previous 
            call to one of the two associated <b>SetAny__</b> member functions or use of the second constructor) an <b>
            <a href="ITS_Precondition.html">ITS_Precondition</a></b> exception is thrown. The end-user can use the 
            <b>ContainsAny</b> member function to check if an any object has been previously specified.
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">SetAny1</xsl:attribute>
              <b>void SetAny(AsnObject* anyParam)</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b>SetAny</b> member function allows specifying an any object for a <xsl:value-of select=
            "./asnType/asnAny/className"/> object. The AsnObject object passed as paremeter of the <b>SetAny</b>
            member function is deleted when the <xsl:value-of select="./asnType/asnAny/className"/> object is deleted,
            therefore the end-user must not explictly or implicitly delete the AsnObject (i.e. no explicit call to
            operator delete and no allocation on the stack).
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">SetAny2</xsl:attribute>
              <b>void SetAny(const AsnObject&amp; anyParam)</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b>SetAny</b> member function allows specifying an any object for a <xsl:value-of select=
            "./asnType/asnAny/className"/> object. The AsnObject object passed as paremeter of the <b>SetAny</b>
            member function is cloned, therefore the end-user must explicitly delete the AsnObject object. In term
            of performance the alternative SetAny member function is better (no cloning).
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">ContainsAny</xsl:attribute>
              <b>bool ContainsAny() const</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b>ContainsAny</b> member function allows checking if an any object has been specified for a 
            <xsl:value-of select="./asnType/asnAny/className"/> object.
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">IsDecoded</xsl:attribute>
              <b>bool IsDecoded() const</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b>IsDecoded</b> member function allows checking if a <xsl:value-of select=
            "./asnType/asnAny/className"/> object has been decoded.
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">GetDecodedOctets</xsl:attribute>
              <b>const Octets&amp; GetDecodedOctets() const</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b>GetDecodedOctets</b> member function  returns the ASN.1 encoded value of an any object of a 
            previously decoded <xsl:value-of select="./asnType/asnAny/className"/> object. The ASN.1 encoded value is
            returned through an object of class Octets. If the <xsl:value-of select="./asnType/asnAny/className"/> has
            not been previously decoded an <b><a href="ITS_Precondition.html">ITS_Precondition</a></b> exception is
            thrown. The end-user is responsible to write the code required to identify the ASN.1 type of the ASN.1 
            encoded value of the any object and then call the appropriate ASN.1 decoder.
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">Clone</xsl:attribute>
              <b>AsnObject* Clone() const</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b>Clone</b> member function allows cloning a <xsl:value-of select=
            "./asnType/asnAny/className"/> object. The end-user is responsible for deleting the clone object.
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
            <xsl:attribute name="name">Equals</xsl:attribute>
              <b>bool Equals(const AsnObject&amp; rhs) const</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b>Equals</b> member function allows checking the equality of two 
            <xsl:value-of select="./asnType/asnAny/className"/> objects. It is used to implement the comparison
            operator (i.e. operator==).
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">GetName</xsl:attribute>
              <b>std::string GetName() const</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b>GetName</b> member function returns the string <font color="#000080">&quot;<xsl:value-of select=
            "./asnType/asnAny/className"/>&quot;</font>.
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">GetBaseName</xsl:attribute>
              <b>std::string GetBaseName() const</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b>GetBaseName</b> member function returns the string <font color="#000080">&quot;ANY&quot;
            </font>.
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">operator=</xsl:attribute>
              <b>AsnAny&amp; operator=(const AsnAny&amp; rhs)</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b>operator=</b> is the standard C++ assignment operator.
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">operator==</xsl:attribute>
              <b>bool operator==(const AsnAny&amp; rhs) const</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b>operator==</b> is the standard C++ comparison operator.
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">Print</xsl:attribute>
              <b>void Print(std::ostream&amp; os) const</b>
            </xsl:element>
          </td>
          <td valign="middle" align="left">
            The <b>Print</b> member function allows printing the contents of a <xsl:value-of select=
            "./asnType/asnAny/className"/> object to an output stream at any time.
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">operator&lt;&lt;</xsl:attribute>
              <b>std::ostream&amp; operator&lt;&lt; (std::ostream&amp; os, const AsnObject&amp; asnObject)</b>
            </xsl:element>
          </td>
          <td align="left">
            The stream output operator (i.e. operator&lt;&lt;) allows printing the contents of a <xsl:value-of select=
            "./asnType/asnAny/className"/> object to an output stream at any time.
          </td>
        </tr>
      </table>
    </div>

    <!-- ASN.1 type definition //////////////////////////////////////////////////////////////////////////////////// -->

    <br></br>

    <ul type="square">
      <li>
        <font size="4">
          ASN.1 type <xsl:value-of select="./asnType/asnAny/asnTypeName"/> definition
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
            <xsl:for-each select="asnType/asnAny/asnDefinition/line">
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
        (C) 2001 - 2002 IntelliNet Technologies, Inc. All rights reserved.
      </font>
    </p>

    <br></br>

    </body>

    </html>
  </xsl:template>
</xsl:stylesheet>
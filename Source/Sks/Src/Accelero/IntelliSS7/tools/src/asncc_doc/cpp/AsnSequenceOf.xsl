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
<!-- ID: $Id: AsnSequenceOf.xsl,v 1.1.1.1 2007-10-08 11:12:06 bsccs2 Exp $ -->
<!--                                                                         -->
<!-- /////////////////////////////////////////////////////////////////////// -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
  <xsl:template match="/">
    <html>

    <head>
    <title>Class <xsl:value-of select="./asnType/asnSequenceOf/className"/>
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
          "./asnType/asnSequenceOf/asnModuleName"/> C++ API -
        </font>
      </i>
    </p>

    <hr size="4" style="margin-top: 0"></hr>

    <!-- Inheritance from base type /////////////////////////////////////////////////////////////////////////////// -->

    <p align="left">
      <u>
        <font size="6">Class <xsl:value-of select="./asnType/asnSequenceOf/className"/></font>
      </u>
    </p>

    <p>The ASN.1 type <xsl:value-of select="./asnType/asnSequenceOf/asnTypeName"/> is based on the ASN.1 SEQUENCE OF
    built-in type, therefore the class <xsl:value-of select="./asnType/asnSequenceOf/className"/> inherits from the 
    class <b><a href="AsnSequenceOf.html">AsnSequenceOf</a></b>.</p>

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
        <xsl:attribute name="href">#<xsl:value-of select="./asnType/asnSequenceOf/className"/></xsl:attribute>
        <xsl:value-of select="./asnType/asnSequenceOf/className"/>
      </xsl:element>
      -
      <xsl:for-each select="asnType/asnSequenceOf/memberFunctions/memberFunctionAdd">
        <xsl:element name="a">
          <xsl:attribute name="href">#<xsl:value-of select="name"/>1</xsl:attribute>
          <xsl:value-of select="name"/>
        </xsl:element>
        -
      </xsl:for-each>
      <xsl:for-each select="asnType/asnSequenceOf/memberFunctions/memberFunctionAddWithRef">
        <xsl:element name="a">
          <xsl:attribute name="href">#<xsl:value-of select="name"/>2</xsl:attribute>
          <xsl:value-of select="name"/>
        </xsl:element>
        -
      </xsl:for-each>
      <xsl:for-each select="asnType/asnSequenceOf/memberFunctions/memberFunctionAt">
        <xsl:element name="a">
          <xsl:attribute name="href">#<xsl:value-of select="name"/></xsl:attribute>
          <xsl:value-of select="name"/>
        </xsl:element>
        -
      </xsl:for-each>
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
        <xsl:attribute name="href">#GetSize</xsl:attribute>
        GetSize
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
              <xsl:attribute name="name"><xsl:value-of select="./asnType/asnSequenceOf/className"/></xsl:attribute>
              <b>Constructor signature</b>
            </xsl:element>
          </td>
          <td valign="middle" align="center" bgcolor="#CCCCFF">
            <b>Constructor summary</b>
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <b><xsl:value-of select="./asnType/asnSequenceOf/className"/>()</b>
          </td>
          <td valign="middle" align="left">
            The first <b><xsl:value-of select="./asnType/asnSequenceOf/className"/></b> constructor allows creating a
            <xsl:value-of select="./asnType/asnSequenceOf/className"/> object with an empty contents (default 
            constructor).
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <b><xsl:value-of select=
            "./asnType/asnSequenceOf/className"/>(Octets&amp; octets)</b>
          </td>
          <td valign="middle" align="left">
            The second <b><xsl:value-of select="./asnType/asnSequenceOf/className"/></b> constructor allows creating a
            <xsl:value-of select="./asnType/asnSequenceOf/className"/> object from an ASN.1 encoded value (the <b>
            Decode</b> member function is called). The ASN.1 encoded value is passed through an object of class <b>
            <a href="Octets.html">Octets</a></b>. Can throw an <b><a href="AsnDecodeError.html">AsnDecodeError</a></b>
			exception.
          </td>
        </tr>
        <tr>
          <td valign="middle" align="left" width="33%">
            <b><xsl:value-of select="./asnType/asnSequenceOf/className"/>(const 
            <xsl:value-of select="./asnType/asnSequenceOf/className"/>&amp; rhs)</b>
          </td>
          <td valign="middle" align="left">
            The third <b><xsl:value-of select="./asnType/asnSequenceOf/className"/></b> constructor is the standard 
            C++ copy constructor.
          </td>
        </tr>
      </table>
    </div>

    <!-- Member functions ///////////////////////////////////////////////////////////////////////////////////////// -->

    <br></br>

    <ul type="square">
      <li>
        <font size="4">
          Public member functions
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
        <xsl:for-each select="asnType/asnSequenceOf/memberFunctions/memberFunctionAdd">
          <tr>
            <td valign="middle" align="left" width="33%">
              <xsl:element name="a">
                <xsl:attribute name="name"><xsl:value-of select="name"/>1</xsl:attribute>
                <b><xsl:value-of select="signature"/></b>
              </xsl:element>
            </td>
            <td valign="middle" align="left">
              The <b><xsl:value-of select="name"/></b> member function allows to add an element (object of type
              <xsl:value-of select="elementTypeName"/>) at the end of a <xsl:value-of select=
              "//asnType/asnSequenceOf/className"/> object. The <xsl:value-of select="elementTypeName"/> object passed
              as parameter of the <xsl:value-of select="name"/> member function is deleted when the 
              <xsl:value-of select="//asnType/asnSequenceOf/className"/> object is deleted, therefore the end-user must
              not explicitly or implicitly delete the <xsl:value-of select="elementTypeName"/> object (i.e. no explicit
              call to operator delete and no allocation on the stack).
            </td>
          </tr>
        </xsl:for-each>

        <xsl:for-each select="asnType/asnSequenceOf/memberFunctions/memberFunctionAddWithRef">
          <tr>
            <td valign="middle" align="left" width="33%">
              <xsl:element name="a">
                <xsl:attribute name="name"><xsl:value-of select="name"/>2</xsl:attribute>
                <b><xsl:value-of select="signature"/></b>
              </xsl:element>
            </td>
            <td valign="middle" align="left">
              The <b><xsl:value-of select="name"/></b> member function allows to add an element (object of type
              <xsl:value-of select="elementTypeName"/>) at the end of a <xsl:value-of select=
              "//asnType/asnSequenceof/className"/> object. The <xsl:value-of select="elementTypeName"/> object passed
              as parameter of the <xsl:value-of select="name"/> member function is cloned, therefore the end-user must
              explicitly delete the <xsl:value-of select="elementTypeName"/> object. In term of performance the
              alternative <xsl:value-of select="name"/> member function is better (no cloning).
            </td>
          </tr>
        </xsl:for-each>

        <xsl:for-each select="asnType/asnSequenceOf/memberFunctions/memberFunctionAt">
          <tr>
            <td valign="middle" align="left" width="33%">
              <xsl:element name="a">
                <xsl:attribute name="name"><xsl:value-of select="name"/></xsl:attribute>              
                <b><xsl:value-of select="signature"/></b>
              </xsl:element>
            </td>
            <td valign="middle" align="left">
              The <b><xsl:value-of select="name"/></b> member function returns an element (object of type
              <xsl:value-of select="elementTypeName"/>) at the specified index (<i>index</i> parameter). If the index
              is out of range an <b><a href="ITS_Precondition.html"> ITS_Precondition</a></b> exception is thrown. 
              After a call to the <b>Decode</b> member function, the end-user must use the <b>GetSize</b> member 
			  function to retrieve the range of valid indexes (from zero to the - not included - value returned by
			  GetSize).
            </td>
          </tr>
        </xsl:for-each>

      </table>
    </div>

    <!-- Inherited member functions (encoding and decoding) /////////////////////////////////////////////////////// -->

    <br></br>

    <ul type="square">
      <li>
        <font size="4">
          Public member functions inherited from <a href="AsnSequenceOf.html">AsnSequenceOf</a> and 
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
            "./asnType/asnSequenceOf/className"/> object to an ASN.1 encoded value. The ASN.1 encoded value is 
            returned through an object of class <b><a href="Octets.html">Octets</a></b>. The end-user is responsible
            for deleting the object of class <b><a href="Octets.html">Octets</a></b>. Can throw an <a href=
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
            "./asnType/asnSequenceOf/className"/>). The ASN.1 encoded value is passed through an object of class 
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
          Public member functions inherited from <a href="AsnSequenceOf.html">AsnSequenceOf</a> and 
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
              <xsl:attribute name="name">GetSize</xsl:attribute>
              <b>size_t GetSize() const</b>
            </xsl:element>
          </td>
          <td align="left">
            The <b>GetSize</b> member function returns the number of elements of a <xsl:value-of select=
            "./asnType/asnSequenceOf/className"/> object.
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
            "./asnType/asnSequenceOf/className"/> object. The end-user is responsible for deleting the clone object.
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
            <xsl:value-of select="./asnType/asnSequenceOf/className"/> objects. It is used to implement the comparison
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
            "./asnType/asnSequenceOf/className"/>&quot;</font>.
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
            The <b>GetBaseName</b> member function returns the string <font color="#000080">&quot;SEQUENCE OF&quot;
            </font>.
          </td>
        </tr>
        <tr>
          <td align="left" width="33%">
            <xsl:element name="a">
              <xsl:attribute name="name">operator=</xsl:attribute>
              <b>AsnSequenceOf&amp; operator=(const AsnSequenceOf&amp; rhs)</b>
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
              <b>bool operator==(const AsnSequenceOf&amp; rhs) const</b>
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
            "./asnType/asnSequenceOf/className"/> object to an output stream at any time.
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
            "./asnType/asnSequenceOf/className"/> object to an output stream at any time.
          </td>
        </tr>
      </table>
    </div>

    <!-- ASN.1 type definition //////////////////////////////////////////////////////////////////////////////////// -->

    <br></br>

    <ul type="square">
      <li>
        <font size="4">
          ASN.1 type <xsl:value-of select="./asnType/asnSequenceOf/asnTypeName"/> definition
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
            <xsl:for-each select="asnType/asnSequenceOf/asnDefinition/line">
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
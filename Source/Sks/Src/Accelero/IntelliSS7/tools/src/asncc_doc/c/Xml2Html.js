////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 2000 IntelliNet Technologies, Inc. All Rights Reserved.     //
//              Manufactured in the United States of America.                 //
//        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        //
//                                                                            //
//    This product and related documentation is protected by copyright and    //
//    distributed under licenses restricting its use, copying, distribution   //
//    and decompilation.  No part of this product or related documentation    //
//    may be reproduced in any form by any means without prior written        //
//    authorization of IntelliNet Technologies and its licensors, if any.     //
//                                                                            //
//    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       //
//    government is subject to restrictions as set forth in subparagraph      //
//    (c)(1)(ii) of the Rights in Technical Data and Computer Software        //
//    clause at DFARS 252.227-7013 and FAR 52.227-19.                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
// CONTRACT: INTERNAL                                                         //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//
//  ID: $Id: Xml2Html.js,v 1.1.1.1 2007-10-08 11:12:05 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//  Java Script to convert XML + XSL to HTML using Microsoft XSL processor.
//

//
//  More info about scripting under Windows: 
//  http://msdn.microsoft.com/scripting.
//

//
//  Args: input-file style-file output-file.
//

var xml = WScript.CreateObject("Microsoft.XMLDOM"); // Input.

xml.validateOnParse = false;

xml.load(WScript.Arguments(0));

var xsl = WScript.CreateObject("Microsoft.XMLDOM"); // Style.

xsl.validateOnParse = false;

xsl.load(WScript.Arguments(1));

var out = WScript.CreateObject("Scripting.FileSystemObject"); // Output.

var replace = true; var unicode = false; // Output file properties.

var hdl = out.CreateTextFile(WScript.Arguments(2), replace, unicode);

hdl.write(xml.transformNode(xsl.documentElement));

// eof.




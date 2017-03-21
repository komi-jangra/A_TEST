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
//  ID: $Id: AsnccXml2Html.js,v 1.1.1.1 2007-10-08 11:12:05 bsccs2 Exp $
//
////////////////////////////////////////////////////////////////////////////////

//
//  Java Script to convert Asncc XML output file to HTML using Microsoft XSL
//  processor.
//

//
//  More info about scripting under Windows: 
//  http://msdn.microsoft.com/scripting.
//

//
//  Arg: xml-input-file
//


var WSHShell = WScript.CreateObject("WScript.Shell");

var debug = false;

if (debug)
{
    WSHShell.popup("Debugging mode...");
}


var xmlFileName = WScript.Arguments(0);

var xslFileName = FindAsnPattern(xmlFileName);

if (xslFileName != "AsnNotFound")
{
    xslFileName += ".xsl";

    var htmlFileName = xmlFileName.replace(".xml", ".html");

    if (debug)
    {
        WSHShell.popup(xmlFileName + " " + xslFileName + " " + htmlFileName);
    }
   
    Convert2Html(xmlFileName, xslFileName, htmlFileName);
    
}
else
{
    // Nothing to do.

    if (debug)
    {
        WSHShell.popup("AsnNotFound!");
    }
}



////////////////////////////////////////////////////////////////////////////////
//
// Find asn pattern in file: return asn pattern (i.e. "Asn..." string).
//

function FindAsnPattern(fileName)
{
    var patternArray = 
            new Array(
                    "asnAny",
                    "asnBitString",
                    "asnBoolean",
                    "asnChoice",
                    "asnEnumerated",
                    "asnInteger",
                    "asnNull",
                    "asnObjectIdentifier",
                    "asnOctetString",
                    "asnReal",
                    "asnSequenceOf",        // Must be before "asnSequence".
                    "asnSequence",
                    "asnSetOf",             // Must be before "asnSet".
                    "asnSet",
                    "asnModuleClassList",
                    "asnModuleSummary");


    var fso = new ActiveXObject("Scripting.FileSystemObject");

    var forReading = 1;

    var textFile = fso.OpenTextFile(fileName, forReading, false);

    // Process text file line by line.

    while (!textFile.AtEndOfStream)
    {
        var str = textFile.ReadLine();

        for (index in patternArray)
        {
            var rgexp = patternArray[index];

            var searchResult = str.search(rgexp);

            if (searchResult != -1)
            {
                textFile.Close();

                return patternArray[index];
            }
        }
    }

    textFile.Close();

    return "AsnNotFound";
}


////////////////////////////////////////////////////////////////////////////////
//
//  Convert XML file to HTML file according to XSL file.
//
//

function Convert2Html(xmlFileName, xslFileName, htmlFileName)
{
    var xml = WScript.CreateObject("Microsoft.XMLDOM");
    
    xml.validateOnParse = false;
    
    xml.load(xmlFileName);
    
    
    var xsl = WScript.CreateObject("Microsoft.XMLDOM");
    
    xsl.validateOnParse = false;
    
    xsl.load(xslFileName);    


    var out = WScript.CreateObject("Scripting.FileSystemObject");

    var replace = true;  // Output file property.
    var unicode = false; // Output file property.

    var html = out.CreateTextFile(htmlFileName, replace, unicode);

    html.write(xml.transformNode(xsl.documentElement));
}


// eof.





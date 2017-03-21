////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//      Copyright 1998 IntelliNet Technologies, Inc. All Rights Reserved.     //
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
//  ID: $Id: exc_main.cpp,v 1.1.1.1 2007-10-08 11:12:08 bsccs2 Exp $
//
// LOG: $Log: not supported by cvs2svn $
// LOG: Revision 1.1.1.1  2007/10/04 13:24:43  bsccs2
// LOG: init tree
// LOG:
// LOG: Revision 1.1.1.1  2007/08/03 06:49:21  cvsadmin
// LOG: BscCs2
// LOG:
// LOG: Revision 1.1.1.1  2007/03/08 15:14:56  cvsadmin
// LOG: BSC project
// LOG:
// LOG: Revision 9.1  2005/03/23 12:54:17  cvsadmin
// LOG: Begin PR6.5
// LOG:
// LOG: Revision 8.2  2005/03/21 13:53:08  cvsadmin
// LOG: PR6.4.2 Source Propagated to Current
// LOG:
// LOG: Revision 7.1  2002/08/26 22:10:19  mmiers
// LOG: Begin PR6.2
// LOG:
// LOG: Revision 6.1  2002/02/28 16:14:37  mmiers
// LOG: Begin PR7.
// LOG:
// LOG: Revision 5.2  2001/11/21 21:16:07  hdivoux
// LOG: Updated compiler version and copyright dates.
// LOG:
// LOG: Revision 5.1  2001/08/16 20:46:24  mmiers
// LOG: Start PR6.
// LOG:
// LOG: Revision 4.1  2001/05/01 00:53:25  mmiers
// LOG: Begin PR5
// LOG:
// LOG: Revision 3.1  2000/08/16 00:08:38  mmiers
// LOG:
// LOG: Begin round 4.
// LOG:
// LOG: Revision 2.0  1999/12/03 23:30:30  mmiers
// LOG:
// LOG: Begin third iteration.
// LOG:
// LOG: Revision 1.3  1999/06/28 19:13:59  skarmakar
// LOG:
// LOG:
// LOG: Update with awareness of throw specifier, behavior control defines
// LOG: in its++.h.
// LOG:
// LOG: Revision 1.2  1998/09/22 23:56:35  jrao
// LOG: Changes made to accomodate HPUX code
// LOG:
// LOG: Revision 1.1  1998/05/19 22:39:56  hdivoux
// LOG: Creation.
// LOG:
//
////////////////////////////////////////////////////////////////////////////////


// exc_main.cpp
// Exception compiler main source file.


#include <stdio.h>
#include <string>
#if defined(_WIN32)
#pragma warning(disable : 4786)
#endif
#include <list>
#include <exc_assert.h>
#include <exc_parse_types.h>
#include <exc_generate.h>

#if defined(HAVE_STD_NAMESPACE)
using namespace std;
#endif

extern bool smallError;
extern int  yydebug;

Subsystem* ParseExcFile(const string& fileName);
void InitExcParser(Subsystem* subsystem, const string& fileName, FILE* fDesc);
int yyparse();

string compilerVersion = "1.1";

#define PrintErrorOrigin(fileName, lineNumber) \
    fprintf(stderr,"File \"%s\", line %d : ", fileName.c_str(), lineNumber)


void Usage(const string& prgName)
{
    fprintf(stderr, "\nUsage: %s ", prgName.c_str());
    fprintf(stderr, "[Options] Exc files...\n");  
    fprintf(stderr, "\n");

    fprintf(stderr, "Options:\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "    [-h]                  Display this help and exit.\n");
    fprintf(stderr, "    [-debugP]             Debug parser mode (print parser information).\n");
    fprintf(stderr, "    [-debugT]             Debug type mode (print Exc type information).\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "\n");

    fprintf(stderr, "IntelliExc Exception compiler (Exc -> C++) version %s.\n", compilerVersion.c_str());
    fprintf(stderr, "All rights reserved. (C) 1998 - 2001 IntelliNet Technologies.\n");
    fprintf(stderr, "\n");
}
    


int main(int argc, char* argv[])
{

#ifdef YYDEBUG

    yydebug = 1;    // Prints yacc (or bison) debugging information to stdout.

#endif


    if (argc <= 1)
    {
        Usage(argv[0]);
        exit(1);
    }


    list<string> excFileNameList;

    bool bDebugParser  = false;
    bool bDebugTypes   = false;

    // Parse command line argument(s).

    for (int currArg = 1; currArg < argc;)
    { 
        if ((argv[currArg][0] == '-' || argv[currArg][0] == '/') &&
             argv[currArg][1] != '\0')
        {
            if (strcmp(argv[currArg], "-h") == 0)
            {
                Usage(argv[0]);
                exit(EXIT_SUCCESS);
            }
            else if (strcmp(argv[currArg], "-debugP") == 0)
            {
                bDebugParser = true;
                currArg++;
            }
            else if (strcmp(argv[currArg], "-debugT") == 0)
            {
                bDebugTypes = true;
                currArg++;
            }
            else 
            {
                Usage(argv[0]);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            excFileNameList.push_back(argv[currArg++]);
        }
    }


    // Genaral message before compilation.

    fprintf(stderr, "\n");
    fprintf(stderr, "IntelliExc Exception compiler (Exc -> C++) version %s.\n", compilerVersion.c_str());
    fprintf(stderr, "All rights reserved. (C) 1998 IntelliNet Technologies.\n");
    fprintf(stderr, "\n");

    fprintf(stderr, "Compiling...\n");



    if (excFileNameList.size() == 0)
    {
        fprintf(stderr,
                "Command line: ERROR - no Exc files were specified.\n");

        Usage(argv[0]);
        exit(EXIT_FAILURE);
    }


    // Debug parser option.

    //if (bDebugParser)
    //{
    //    yydebug = 1;
    //}


    // ------
    // STEP 1
    // ------

    // Parse each Exc source file.

    SubsystemList allSubsystems;

    Subsystem* currentSubsystem = NULL;

    for (list<string>::iterator iter = excFileNameList.begin();
         iter != excFileNameList.end();
         ++iter)
    {
        currentSubsystem = ParseExcFile((*iter));

        if (currentSubsystem == NULL)
        {
            exit(EXIT_FAILURE);
        }

        allSubsystems.push_back(currentSubsystem);
    }



    // ------
    // STEP 2
    // ------

    // Check for sematic errors in each subsystem.




    // ------
    // STEP 3
    // ------

    // Exit if parsing errors.

    if (smallError)
    {
        exit(EXIT_FAILURE);
    }



    // ------
    // STEP 4
    // ------

    // Generate code for each subsystem.

    for (SubsystemList::iterator iterSbs = allSubsystems.begin();
         iterSbs != allSubsystems.end();
         ++iterSbs)
    {
        currentSubsystem = *iterSbs;

        if (currentSubsystem->status == Subsystem::OK)
        {
            GenerateSubsystemCode(currentSubsystem);
        }
        else
        {
            fprintf(stderr,
                    "General: ERROR - Subsystem \"%s\""
                    "cannot be processed.\n",
                    currentSubsystem->name.c_str()); 
        }
    }

    fprintf(stderr, "Done.\n");

    return(0);
}



//
// Calls the yacc/lex (or flex/bison) parser given an Exc source file name.
//
// Returns a Subsystem* for the given Exc file. If the filename is "-" stdin
// is used.
//

Subsystem* ParseExcFile(const string& fileName)
{
    FILE* fDesc       = NULL;
    Subsystem* retVal = NULL;    
    int parseResult   = 0;

    // Open input file for lexical analyzer/parser.
    // Use stdin if the filename is "-".

    if (fileName == "-")
    {
        fDesc = stdin;
    }
    else
    {
        fDesc = fopen(fileName.c_str(), "r");

        if (fDesc == NULL)
        {
            fprintf(stderr,
                    "General: ERROR - Exc file \"%s\""
                    "cannot be opened for reading.\n",
                    fileName.c_str()); 
        }
    }
    
    retVal = new Subsystem();

    // Init parser by giving it a ptr to the Module to 
    // initialize/use, and the file name associated with
    // the given FILE*, fDesc (for error reporting).
    
    InitExcParser(retVal, fileName, fDesc);
    

    // Parse the current ASN.1 source file into the module
    // data struct.

    parseResult = yyparse();
    
    if ((parseResult != 0) || (retVal->status == Subsystem::PARSE_ERRORS))
    {
        // Parser has print exact error message previously.

        fprintf(stderr,"General: ERROR - Parsing errors, cannot proceed.\n");
        return(NULL);
    }

    if (fDesc != stdin)
    {
        fclose(fDesc);
    }

    return retVal;
    
}



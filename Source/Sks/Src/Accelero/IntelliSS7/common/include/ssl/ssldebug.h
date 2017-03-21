/*  *********************************************************************
    File: ssldebug.h

    SSLRef 3.0 Final -- 11/19/96

    Copyright (c)1996 by Netscape Communications Corp.

    By retrieving this software you are bound by the licensing terms
    disclosed in the file "LICENSE.txt". Please read it, and if you don't
    accept the terms, delete this software.

    SSLRef 3.0 was developed by Netscape Communications Corp. of Mountain
    View, California <http://home.netscape.com/> and Consensus Development
    Corporation of Berkeley, California <http://www.consensus.com/>.

    *********************************************************************

    File: ssldebug.h   Debug utilities

    This header supports debugging data dumps, depending on the value of
    the DEBUG preprocessor symbol (from 0 to 5, with 5 being the most
    data).

    ****************************************************************** */

#ifndef _SSLDEBUG_H_
#define _SSLDEBUG_H_ 1

#ifndef DEBUG
    #define DEBUG   3
#endif /* DEBUG */

#ifndef DEBUGASSERT
    #if DEBUG >= 1
        #define DEBUGASSERT 1
    #endif /* DEBUG >= 1 */
#endif /* DEBUGASSERT */

#ifndef DEBUGERR
    #if DEBUG >= 2
        #define DEBUGERR 1
    #endif /* DEBUG >= 2 */
#endif /* DEBUGERR */

#ifndef DEBUGMESSAGE
    #if DEBUG >= 3
        #define DEBUGMESSAGE 1
    #endif /* DEBUG >= 3 */
#endif /* DEBUGMESSAGE */

#ifndef DEBUGDATA
    #if DEBUG >= 4
        #define DEBUGDATA 1
    #endif /* DEBUG >= 4 */
#endif /* DEBUGDATA */

#if DEBUGASSERT
    #define ASSERT(val)     do {if (!(val)) AssertMessage("Assert failed: '" ## #val ##"'", __FILE__, __LINE__);} while (0)
    #define ASSERTPTR(val)  do {if ((val) == 0) AssertMessage("Pointer assert failed: '" ## #val ##"'", __FILE__, __LINE__);} while (0)
    #define ASSERTMSG(msg)  AssertMessage("Assert: " ## msg, __FILE__, __LINE__)
#else
    #define ASSERT(val)     ((void)0)
    #define ASSERTPTR(val)  ((void)0)
    #define ASSERTMSG(msg)  ((void)0)
#endif

#if DEBUGERR
    #define ERR(err)    DebugError(err, __FILE__, __LINE__)
#else
    #define ERR(err)    (err)
#endif

#if DEBUGMESSAGE
    #define DEBUGMSG(msg)                   DebugMessage(msg, __FILE__, __LINE__)
    #define DEBUGVAL1(msg, v1)              DebugValMessage((msg), __FILE__, __LINE__, (uint32)(v1), 0, 0, 0)
    #define DEBUGVAL2(msg, v1, v2)          DebugValMessage((msg), __FILE__, __LINE__, (uint32)(v1), (uint32)(v2), 0, 0)
    #define DEBUGVAL3(msg, v1, v2, v3)      DebugValMessage((msg), __FILE__, __LINE__, (uint32)(v1), (uint32)(v2), (uint32)(v3), 0)
    #define DEBUGVAL4(msg, v1, v2, v3, v4)  DebugValMessage((msg), __FILE__, __LINE__, (uint32)(v1), (uint32)(v2), (uint32)(v3), (uint32)(v4))
#else
    #define DEBUGMSG(msg)                   ((void)0)
    #define DEBUGVAL1(msg, v1)              ((void)0)
    #define DEBUGVAL2(msg, v1, v2)          ((void)0)
    #define DEBUGVAL3(msg, v1, v2, v3)      ((void)0)
    #define DEBUGVAL4(msg, v1, v2, v3, v4)  ((void)0)
#endif

#if DEBUGDATA
    #define DUMP_BUFFER_PTR(marker, value, buffer) DebugDumpDataValue((marker), (uint32)(value), (buffer) .data, (buffer) .length)
    #define DUMP_BUFFER_NAME(name, buffer) DebugDumpDataName((name), (buffer) .data, (buffer) .length)
    #define DUMP_DATA_PTR(marker, value, data, length) DebugDumpDataValue((marker), (uint32)(value), (data), (length))
    #define DUMP_DATA_NAME(name, data, length) DebugDumpDataName((name), (data), (length))
#else
    #define DUMP_BUFFER_PTR(marker, value, buffer) ((void)0)
    #define DUMP_BUFFER_NAME(name, buffer) ((void)0)
    #define DUMP_DATA_PTR(marker, value, data, length) ((void)0)
    #define DUMP_DATA_NAME(name, data, length) ((void)0)
#endif

void AssertMessage(char *message, char *file, int line);
SSLErr DebugError(SSLErr err, char *file, int line);
void DebugMessage(char *message, char *file, int line);
void DebugValMessage(char *message, char *file, int line, uint32 v1, uint32 v2, uint32 v3, uint32 v4);
void DebugDumpDataValue(char *message, uint32 value, void *data, uint32 length);
void DebugDumpDataName(char *name, void *data, uint32 length);

#endif /* _SSLDEBUG_H_ */

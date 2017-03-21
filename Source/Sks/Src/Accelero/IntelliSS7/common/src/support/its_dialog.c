/******************************************************************************
 *                                                                            *
 *      Copyright 1998 IntelliNet Technologies, Inc. All Rights Reserved.     *
 *              Manufactured in the United States of America.                 *
 *        1990 W. New Haven Ste. 312, Melbourne, Florida, 32904 U.S.A.        *
 *                                                                            *
 *    This product and related documentation is protected by copyright and    *
 *    distributed under licenses restricting its use, copying, distribution   *
 *    and decompilation.  No part of this product or related documentation    *
 *    may be reproduced in any form by any means without prior written        *
 *    authorization of IntelliNet Technologies and its licensors, if any.     *
 *                                                                            *
 *    RESTRICTED RIGHTS LEGEND:  Use, duplication, or disclosure by the       *
 *    government is subject to restrictions as set forth in subparagraph      *
 *    (c)(1)(ii) of the Rights in Technical Data and Computer Software        *
 *    clause at DFARS 252.227-7013 and FAR 52.227-19.                         *
 *                                                                            *
 ******************************************************************************
 *                                                                            *
 * CONTRACT: INTERNAL                                                         *
 *                                                                            *
 ******************************************************************************
 *
 * LOG: $Log: not supported by cvs2svn $
 * LOG: Revision 1.1.1.1  2007/10/04 13:24:28  bsccs2
 * LOG: init tree
 * LOG:
 * LOG: Revision 1.1.1.1  2007/08/03 06:49:12  cvsadmin
 * LOG: BscCs2
 * LOG:
 * LOG: Revision 1.2  2007/03/30 04:58:51  cvsadmin
 * LOG: *** empty log message ***
 * LOG:
 * LOG: Revision 1.1.1.1  2006/12/22 13:34:45  cvsadmin
 * LOG: Initialising sources in CVS
 * LOG:
 * LOG: Revision 9.1  2005/03/23 12:53:37  cvsadmin
 * LOG: Begin PR6.5
 * LOG:
 * LOG: Revision 8.2  2005/03/21 13:51:57  cvsadmin
 * LOG: PR6.4.2 Source Propagated to Current
 * LOG:
 * LOG: Revision 7.1  2002/08/26 22:09:56  mmiers
 * LOG: Begin PR6.2
 * LOG:
 * LOG: Revision 6.1  2002/02/28 16:14:23  mmiers
 * LOG: Begin PR7.
 * LOG:
 * LOG: Revision 5.1  2001/08/16 20:46:10  mmiers
 * LOG: Start PR6.
 * LOG:
 * LOG: Revision 4.1  2001/05/01 00:53:16  mmiers
 * LOG: Begin PR5
 * LOG:
 * LOG: Revision 3.5  2001/02/07 22:12:55  mmiers
 * LOG: Convert RCSID to ident.
 * LOG:
 * LOG: Revision 3.4  2001/01/31 00:55:49  mmiers
 * LOG: A few typos.
 * LOG:
 * LOG: Revision 3.3  2001/01/31 00:51:27  mmiers
 * LOG: Get rcsid to really work
 * LOG:
 * LOG: Revision 3.2  2001/01/31 00:32:57  mmiers
 * LOG: RCSID addition.
 * LOG:
 * LOG: Revision 3.1  2000/08/16 00:05:22  mmiers
 * LOG:
 * LOG: Begin round 4.
 * LOG:
 * LOG: Revision 2.0  1999/12/03 23:27:27  mmiers
 * LOG:
 * LOG: Begin third iteration.
 * LOG:
 * LOG: Revision 1.4  1999/08/19 02:02:20  mmiers
 * LOG:
 * LOG:
 * LOG: Make that const char...
 * LOG:
 * LOG: Revision 1.3  1999/08/19 01:47:29  mmiers
 * LOG:
 * LOG:
 * LOG: Finalize the assertion string.
 * LOG:
 * LOG: Revision 1.2  1999/08/19 01:37:28  mmiers
 * LOG:
 * LOG:
 * LOG: Whooptydoo debugger startup on assertions.
 * LOG:
 * LOG: Revision 1.1  1999/08/19 00:15:12  mmiers
 * LOG:
 * LOG:
 * LOG: Fancy shmancy for UNIX.  What a useless feature.
 * LOG:
 *
 ******************************************************************************/

#include <stdarg.h>
#include <Xm/MessageB.h>
#include <unistd.h>
#include <signal.h>

#include <its.h>

#ident "$Id: its_dialog.c,v 1.1.1.1 2007-10-08 11:11:56 bsccs2 Exp $"

static int goAway = 1, finish = 0;

extern char *SERVICE_ARGV0;

#define ITS_DEBUGGER_COMMAND_STRING     "ITS_DEBUGGER_COMMAND"
#define ITS_DEBUGGER_DELAY_STRING       "ITS_DEBUGGER_DELAY"

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      To determine if the user wants to debug the application.
 *
 *  Input Parameters:
 *      Normal Xt pushbutton callback stuff.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
yesNo(Widget w, XtPointer data, XtPointer cbs)
{
    XmAnyCallbackStruct *any = (XmAnyCallbackStruct *)cbs;

    finish = 1;
    if (any->reason == XmCR_OK)
    {
        goAway = 1;
    }
    else
    {
        goAway = 0;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      Start the debugger running against this process.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
static void
StartDebugger()
{
    char *env, message[1024], *argv[256], *tmp;
    int i, j, pid;

    if ((env = getenv(ITS_DEBUGGER_COMMAND_STRING)) == NULL)
    {
        goAway = 1;
    }
    else
    {
        message[0] = 0;
        for (i = 0, j = 0; i < strlen(env);)
        {
            if (env[i] == '%')
            {
                switch (env[i+1])
                {
                case 'p':
                    sprintf(&message[strlen(message)], "%d", getpid());
                    i += 2;
                    j = strlen(message);
                    break;

                case 'f':
                    sprintf(&message[strlen(message)], "%s", SERVICE_ARGV0);
                    i += 2;
                    j = strlen(message);
                    break;

                default:
                    message[j] = env[i];
                    message[j+1] = 0;
                    i++; j++;
                    break;
                }
            }
            else
            {
                message[j] = env[i];
                message[j+1] = 0;
                i++; j++;
            }
        }

        tmp = message;
        for (i = 0; i < 256; i++)
        {
            env = strtok(tmp, " ");
            tmp = NULL;
            if (env == NULL)
            {
                argv[i] = NULL;
                break;
            }
            else
            {
                argv[i] = env;
            }
        }

        if ((pid = vfork()) == 0)
        {
            setsid();
 
            /*
             * ditch stdxx
             */
            close(0);
            close(1);
            close(2);

            execvp(argv[0], argv);
            exit(0);
        }
    }
}

/*.implementation:public
 ****************************************************************************
 *  Purpose:
 *      Popup a dialog and present a message.  Options are to debug,
 *      terminate, or ignore.
 *
 *  Input Parameters:
 *      Varargs of message.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 *
 *  Notes:
 *
 *  See Also:
 ****************************************************************************/
void
ITS_ReportErrorUI(const char *format, ...)
{
    Widget topLevel, mb;
    int argc = 0; 
    Dimension width, height;
    char *argv[1] = { NULL };
    Arg args[5];
    XtAppContext appContext;
    XmString str, ok, cancel, help;
    char message[1024];
    va_list al;

    va_start(al, format);
    vsprintf(message, format, al);
    va_end(al);
    strcat(message, "\n\n(Press Retry to debug the application)");

    XtSetLanguageProc(NULL, NULL, NULL);
 
    /* headless? */
    if ((topLevel = XtAppInitialize(&appContext, "Unix Rules",
                                    NULL, 0, &argc, argv,
                                    NULL, NULL, 0)) == NULL)
    {
        abort();
    }
    XtVaSetValues(topLevel, XmNmappedWhenManaged, False, NULL);
 
    str = XmStringCreateLtoR(message, XmFONTLIST_DEFAULT_TAG);
    ok = XmStringCreateLtoR("Abort", XmFONTLIST_DEFAULT_TAG);
    cancel = XmStringCreateLtoR("Retry", XmFONTLIST_DEFAULT_TAG);
    help = XmStringCreateLtoR("Ignore", XmFONTLIST_DEFAULT_TAG);
    XtSetArg(args[0], XmNmessageString, str);
    XtSetArg(args[1], XmNokLabelString, ok);
    XtSetArg(args[2], XmNcancelLabelString, cancel);
    XtSetArg(args[3], XmNhelpLabelString, help);
    XtSetArg(args[4], XtNtitle, "Terminate?");
    if ((mb = XmCreateErrorDialog(topLevel, "Terminate?", args, 5)) == NULL)
    {
        abort();
    }
    XmStringFree(str);
    XmStringFree(ok);
    XmStringFree(cancel);
    XmStringFree(help);
    XtAddCallback(mb, XmNcancelCallback, yesNo);
    XtAddCallback(mb, XmNokCallback, yesNo);

    XtManageChild(mb);
    XtVaGetValues(mb, XmNwidth, &width, XmNheight, &height, NULL);
    XtVaSetValues(mb,
                  XmNx, (DisplayWidth(XtDisplay(mb), 0) - width) / 2,
                  XmNy, (DisplayHeight(XtDisplay(mb), 0) - height) / 2,
                  NULL);
    XtRealizeWidget(topLevel);

    while (!finish)
    {
        XEvent event;

        XtAppNextEvent(appContext, &event);
        XtDispatchEvent(&event);
    }

    XtDestroyApplicationContext(appContext);

    if (!goAway)
    {
        StartDebugger();

        if (!goAway)
        {
            char *env;

            if ((env = getenv(ITS_DEBUGGER_DELAY_STRING)) != NULL)
            {
                sleep(atoi(env));

                kill(getpid(), SIGINT);
            }
        }
    }

    if (goAway)
    {
        exit(goAway);
    }
}

#if defined(DTEST)

char *SERVICE_ARGV0 = NULL;

#define ITS_ASSERT(cond) \
 if (!(cond)) \
 { \
     ITS_ReportErrorUI("Assertion <%s> failed!\nIn file '%s' at line: %d\n", \
                       #cond, __FILE__, __LINE__); \
 }

int
main(int argc, char **argv)
{
    SERVICE_ARGV0 = argv[0];
    
    ITS_ASSERT(ITS_FALSE);
}
#endif

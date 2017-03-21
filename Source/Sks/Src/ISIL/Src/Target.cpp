#include <its++.h>
#include <engine++.h>
#include <mtp3_sn.h>
#include <mtp2_cmn.h>
#include <mtp3_intern.h>
#include<trace.h>
#if defined(ITS_STD_NAMESPACE)
using namespace std;
using namespace its;
using namespace engine;
#endif

#include<stdio.h>
//#include<WorkItem.h>
#include<its_worker.h>
#include<its_transports.h>

#if defined(ANSI)
#define ITS_MTP2_SRC   ITS_MTP2_ANSI_SRC
#elif defined(CCITT)
#define ITS_MTP2_SRC   ITS_MTP2_CCITT_SRC
#endif
#if defined(ANSI)
#define ITS_MTP3_SRC   ITS_MTP3_ANSI_SRC
#elif defined(CCITT)
#define ITS_MTP3_SRC   ITS_MTP3_CCITT_SRC
#endif

#if defined(ANSI)
#define ITS_SCCP_SRC   ITS_SCCP_ANSI_SRC
#elif defined(CCITT)
#define ITS_SCCP_SRC   ITS_SCCP_CCITT_SRC
#endif
#define NATIONAL_SCCP 03
#define INTERNATIONAL_SCCP 83
#define NATIONAL_ISUP 05
#define INTERNATIONAL_ISUP 85

extern "C" int role (ITS_EVENT *);

extern "C"
{
  int Node2 (ThreadPoolThread * thr, Event * event)
  {
    ITS_EVENT & evt = event->GetEvent ();

    role (&evt);
    return (!ITS_SUCCESS);
  }

  int role (ITS_EVENT * ev)
  {
    ITS_EVENT e;
    char ret = 0;
    ITS_OCTET *buff = NULL;
    ITS_OCTET TempBuffer[10];
    ITS_OCTET count = 0;
    SS7_LinkPtr ln = NULL;


    switch (ev->src)
      {
      case ITS_MTP3_SRC:
#if defined(ANSI)
	ITS_EVENT_INIT (&e, ITS_MTP3_SRC, (ev->len) * sizeof (ITS_OCTET));
	memcpy (&e.data[0], &ev->data[0], e.len);
	ISIL_DEBUG_TRACE (("\n  ANSI: MSG Recevied From MTP3 PEER at ISIL\n"));
	if ((ev->data[0] == 0x80))
	  {
	    ISIL_DEBUG_TRACE (("\n ANSI:   MTP3 START RECEIVED FROM PEER MTP3 at ISIL\n"));
	  }
	else if ((ev->data[0] == 0x81))
	  {
	    ISIL_DEBUG_TRACE (("\n ANSI:   MTP3 STOP RECEIVED FROM PEER MTP3 at ISIL\n"));
	  }
	else if ((ev->data[0] == 0x87))
	  {
	    ISIL_DEBUG_TRACE (("\n ANSI:   MTP3 DATA RECEIVED FROM PEER MTP3 at ISIL\n"));
	  }
	else if ((ev->data[0] == 0x88))
	  {
	    ISIL_DEBUG_TRACE (("\n ANSI:   MTP3 RETRIEVE BSNT RECEIVED FROM PEER MTP3 at ISIL\n"));
	  }
	else if ((ev->data[0] == 0x89))
	  {
	    ISIL_DEBUG_TRACE (("\n ANSI:   MTP3 RETRIEVE MSG RECEIVED FROM PEER MTP3 at ISIL\n"));
	  }
	else if ((ev->data[0] == 0x94))
	  {
	    ISIL_DEBUG_TRACE (("\n ANSI:   MTP3 CONNECT RECEIVED FROM PEER MTP3 at ISIL\n"));
	  }
	else if ((ev->data[0] == 0x95))
	  {
	    ISIL_DEBUG_TRACE (("\n ANSI:   MTP3 DISC-CONNECT RECEIVED FROM PEER MTP3 at ISIL\n"));
	  }
	if ((ev->data[0] == 0x80) || (ev->data[0] == 0x94) || (ev->data[0] == 0x81) || (ev->data[0] == 0x95))
	  {
	    ISIL_DEBUG_TRACE (("\n ANSI:   Discarding message for peer\n"));
	    break;
	  }
	ret = TRANSPORT_PutEvent (ITS_MTP2_SRC, &e);
	if (ret != ITS_SUCCESS)
	  {
	    ITS_EVENT_TERM (&e);
	  }
	ITS_EVENT_TERM (&e);
	break;
#elif defined(CCITT)

	ITS_EVENT_INIT (&e, ITS_MTP3_SRC, (ev->len) * sizeof (ITS_OCTET));
	memcpy (&e.data[0], &ev->data[0], e.len);
	ISIL_DEBUG_TRACE (("\n  MSG Recevied From MTP3 PEER\n"));
	if ((ev->data[0] == 0x80))
	  {

	    ISIL_DEBUG_TRACE (("\n   MTP3 START RECEIVED FROM PEER :DISCARDING\n"));
	  }
	else if ((ev->data[0] == 0x81))
	  {
	    ISIL_DEBUG_TRACE (("\n   MTP3 STOP RECEIVED FROM PEER :DISCARDING\n"));
	  }
	else if ((ev->data[0] == 0x87))
	  {
	    ISIL_DEBUG_TRACE (("\n   MTP3 DATA RECEIVED FROM PEER\n"));
	  }
	else if ((ev->data[0] == 0x88))
	  {
	    ISIL_DEBUG_TRACE (("\n   MTP3 RETRIEVE BSNT RECEIVED FROM PEER\n"));
	  }
	else if ((ev->data[0] == 0x89))
	  {
	    ISIL_DEBUG_TRACE (("\n   MTP3 RETRIEVE MSG RECEIVED FROM PEER\n"));
	  }
	else if ((ev->data[0] == 0x94))
	  {
	    ISIL_DEBUG_TRACE (("\n   MTP3 CONNECT RECEIVED FROM PEER :DISCARDING \n"));
	  }
	else if ((ev->data[0] == 0x95))
	  {
	    ISIL_DEBUG_TRACE (("\n   MTP3 DISC-CONNECT RECEIVED FROM PEER :DISCARDING \n"));
	  }
	if ((ev->data[0] == 0x80) || (ev->data[0] == 0x94) || (ev->data[0] == 0x81) || (ev->data[0] == 0x95))
	  {
	    ISIL_DEBUG_TRACE (("\n   Discarding message for peer\n"));
	    break;
	  }
	ret = TRANSPORT_PutEvent (ITS_MTP2_SRC, &e);
	if (ret != ITS_SUCCESS)
	  {
	    ITS_EVENT_TERM (&e);
	  }
	ITS_EVENT_TERM (&e);
#endif
	break;
      case ITS_MTP2_SRC:
	ISIL_DEBUG_TRACE (("\nSpecial PEER MTP2 Msg Received  \n"));

	if ((ev->data[0] == L2_L3_BSNT_NOT_RETRIEVABLE))
	  {
	    ISIL_DEBUG_TRACE (("\n   Special PEER MTP2 L2_L3_BSNT_NOT_RETRIEVABLE\n"));
	  }
	else if ((ev->data[0] == L2_L3_RETRIEVAL_NOT_POSSIBLE))
	  {
	    ISIL_DEBUG_TRACE (("\n   Special PEER MTP2 L2_L3_RETRIEVAL_NOT_POSSIBLE\n"));
	  }
	ITS_EVENT_INIT (&e, ITS_MTP2_SRC, (ev->len) * sizeof (ITS_OCTET));
	memcpy (&e.data[0], &ev->data[0], e.len);
	ret = TRANSPORT_PutEvent (ITS_MTP3_SRC, &e);
	if (ret != ITS_SUCCESS)
	  {
	    ITS_EVENT_TERM (&e);
	  }
	ITS_EVENT_TERM (&e);
	break;

      case ITS_SCCP_SRC:

	ITS_EVENT_INIT (&e, ITS_SCCP_SRC, (ev->len) * sizeof (ITS_OCTET));
	memcpy (&e.data[0], &ev->data[0], e.len);
	ISIL_DEBUG_TRACE ((" MSG Recevied From SCCP  PEER\n"));
	ret = TRANSPORT_PutEvent (ITS_MTP3_SRC, &e);
	if (ret != ITS_SUCCESS)
	  {
	    ITS_EVENT_TERM (&e);
	  }
	break;

      case INTERNATIONAL_SCCP:
      case NATIONAL_SCCP:

	ITS_EVENT_INIT (&e, ITS_MTP3_SRC, (ev->len) * sizeof (ITS_OCTET));
	memcpy (&e.data[0], ev->data, e.len);

	ISIL_DEBUG_TRACE (("\nMSG Recevied For SCCP  PEER\n"));
	ret = TRANSPORT_PutEvent (ITS_SCCP_SRC, &e);
	if (ret != ITS_SUCCESS)
	  {
	    ITS_EVENT_TERM (ev);
	  }
	break;

      case INTERNATIONAL_ISUP:
      case NATIONAL_ISUP:
	ITS_EVENT_INIT (&e, ITS_MTP3_SRC, (ev->len) * sizeof (ITS_OCTET));
	memcpy (&e.data[0], ev->data, e.len);

	ISIL_DEBUG_TRACE (("\n MSG Recevied For  ISUP  PEER\n"));

      }
    buff = (ITS_OCTET *) calloc (ev->len * 6 + 1, sizeof (ITS_OCTET));

    for (count = 0; count < ev->len; count++)
      {
	sprintf ((char *) TempBuffer, "%02x ", ev->data[count]);
	strcat ((char *) buff, (const char *) TempBuffer);

	if (!(count % 15) && (count != 0))
	  {
	    strcat ((char *) buff, "\n");
	  }
      }

    ISIL_DEBUG_TRACE ((":-\n%02s\n", buff));
    free (buff);

    ITS_EVENT_TERM (ev);
  }

}

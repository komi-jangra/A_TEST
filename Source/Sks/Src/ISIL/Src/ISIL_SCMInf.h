
#include <stdio.h>
#include <bssap_cicdb.h>
#include <bssap_call.h>
#include <bssap_cfgdb.h>
#include <bssap_timer.h>
#include <bssap_pegs.h>
#include <bssap_dbc.h>


#define ln_add_cmd  0x1a;
#define ln_del_cmd  0x1b;
#define ITS_SCM_SRC 0x00
#define tshift      0x05
#define NWSTK_SCM_HEADER 0x05
ITS_OCTET pegtrid=0;
extern ITS_OCTET ENTRYDONE;
extern ITS_OCTET ENTRYDELETE;
extern ITS_OCTET TIMERCONFIG;
extern ITS_OCTET PEGCONFIG;
extern "C" {

int  ISILPro_SCMMsg(ITS_EVENT *ev);
int
IMR_GTT_Implemt();
}

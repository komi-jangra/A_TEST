
#ifndef __ADAP_HEADER_H__
#define __ADAP_HEADER_H__

#include<tester.h>
#include<check.h>
//#define MSG_ORD_PRIO 3

void AdapMsgSend(void *, int);
void AdapMsgRecv(void **, int *, int);

void RegisterEntity(int ,char* );
void RegisterWithDB();
int  RunTestSuite(Suite *s);
void ExecuteTestSuite(void);

#endif

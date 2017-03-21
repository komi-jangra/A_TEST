#include<stdio.h>
#include "adap_header.h"

#define EXIT_FAILURE 0

void RegisterEntity(int entityId, char *entityName)
{

printf("\nUT ENV TESTING.. Trying to Register to IPC Framework with entity Id [%d] and entity name [%s]", entityId, entityName);

if (RegisterWithIpcFrmwrk(entityId, entityName) < ZERO)
  {
     printf(" Unable to Register itself with IPC FrameWork. Exiting...");
     exit(EXIT_FAILURE);
  }


}

void RegisterWithDB()
{
  printf("\nUT ENV TESTING.. Trying to Register to DB Framework...");
  
if(dbConnect() != DBLIB_SUCCESS)
  {
    printf(" Unable to connect with DB. Exiting...");
    exit(EXIT_FAILURE);
  }

}

void AdapMsgSend(void *buffer, int msgSize)
{
   
   I_PVoid *sendBuffer = NULL;

   sendBuffer = AlocMsgBuf(msgSize);
   if(sendBuffer)
   {
      memset(sendBuffer, ZERO, msgSize);
      memcpy(sendBuffer, buffer, msgSize);
      SendMsg(sendBuffer, MSG_ORD_PRIO, msgSize);
      printf("\nUT ENV TESTING. SENT %d BYTES ", msgSize);
   }
   else
   {
      printf("\nUT ENV TESTING. MSG ALLOCATION FAILED...");
   }

}

void AdapMsgRecv(void **rcvBuffer, int *msgSize, int entityID)
{ 
   printf("\nUT ENV TESTING..Waiting in AdapMsgRecv function\n");
 
  while(!(*rcvBuffer = RecvMsg(entityID, msgSize)));
  
   printf("\nUT ENV TESTING.. MESSAGE RECEIVED");
}

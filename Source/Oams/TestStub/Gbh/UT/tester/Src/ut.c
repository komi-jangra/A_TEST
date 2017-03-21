#include"check.h"
#include"../Inc/adap_header.h"
#include"../Inc/tester.h"
int main(void)
{ 
 
  /* connecting to framework */
   RegisterEntity(ENT_TESTER, SELF_ENTITY_NAME);

   /* connecting to database */
   RegisterWithDB();

  /* execute test suite */
   ExecuteTestSuite();
   return 0;
} 


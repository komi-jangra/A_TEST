#include <stdio.h>
#include "CSSINC.CEXT"      nolist
#include "p2system.p2apdfh" nolist
#include <stdlib.h>
#include <string.h>

#define USER_COMMAND (0x0002U)
#define CMDLINE_LEN 100

int main (short argc, char* argv[], char* env[])
{
    char ev[100];
    P2_MTS_STD_ADDR_DEF mts_address;
    short ret, len;
    short mmp = 'A';

    ev[0] = (unsigned char)(USER_COMMAND >> 8 & 0XFF);
    ev[1] = (unsigned char) (USER_COMMAND & 0XFF);

    L_CINITIALIZE(42, 21, , , , ,mmp);

    L_INITIALIZE_END();

    printf("**** IntelliNet Command Line Tool *****\n");
    printf("Enter commands on prompt. type exit to quit.\n");

    while (1)
    {
        printf ("\n>> ");

        if (fgets(&ev[4], CMDLINE_LEN, (FILE *)stdin) != NULL);
        {
             len = strlen(&ev[4]);
             printf ("read len is %d, %s", len, &ev[4]);
        }

        if (len <= 1)
        {
            continue;
        }
        else if (strncmp((const char *)&ev[4], "exit", 4) == 0)
        {
            printf ("Exiting Command Line Tool...\n");
            break;
        }

        /* Send Command to User Application */
        memset((char*)&mts_address, 0, sizeof(P2_MTS_STD_ADDR_DEF));
        mts_address.flags.generic_id = '#';

        /*
         * Populating the destination address.
         */
        mts_address.to.cpu_req = 0;
        mts_address.to.task_id = 40;
        mts_address.to.server_class = 21;

        /* now send the message out to the Stack application */
        ret = MTS_SEND((void*)&mts_address, (void*)&ev,
                       len + 4);
        if (ret != 0)
        {
            printf("Command could not be sent to Server: MTS_SEND failed\n");
        }
        else
        {
            printf("Command sent Successfully to Server Application\n");
        }
    }
    return 0;
}




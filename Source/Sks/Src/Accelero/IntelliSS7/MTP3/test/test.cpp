
#include <mtp3++.h>

/*
 * this test is not meant to be runnable
 */
int
main(int argc, char **argv)
{
    its::MTP3_Message msg(MTP3_MSG_USER_DATA);
    its::Event event;

    msg.Encode(event);

    return 0;
}

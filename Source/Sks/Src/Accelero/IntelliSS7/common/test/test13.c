/*
 * performance testing.
 */
#include <stdio.h>
#include <stdlib.h>

#include <its.h>
#include <its_emlist.h>

int
main(int argc, char **argv)
{
    EMLIST_Manager *emList;
    ITS_EVENT ev;
    void *data;
    int i, len;

    ITS_GlobalStart(0);

    ITS_Initialize(1, 0);

    ITS_EVENT_INIT(&ev, 0, 0);

    emList = EMLIST_Create();

    EMLIST_PutEvent(emList, &ev, sizeof(ITS_EVENT));
    EMLIST_PutEvent(emList, &ev, sizeof(ITS_EVENT));
    EMLIST_PutEvent(emList, &ev, sizeof(ITS_EVENT));

    for (i = 0; i < 250000; i++)
    {
        EMLIST_GetNextEvent(emList, &data, &len);

        if (data)
        {
            ITS_Free(data);
        }

        EMLIST_PutEvent(emList, &ev, sizeof(ITS_EVENT));
    }

    EMLIST_Delete(emList);

    ITS_GlobalStop();

    return 0;
}

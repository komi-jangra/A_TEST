
#include <its.h>
#include <its_timers.h>
#include <its_work_item_pool.h>

void
delegate(void *instance)
{
    WORKITEM_Instance *wi = (WORKITEM_Instance *)instance;

    printf("I am a delegate: %p\n", wi);
}

int
main(int argc, char **argv)
{
    WORKITEMPOOL *wp;
    int i;

    ITS_GlobalStart(0);

    wp = WORKITEMPOOL_InitPool(NULL, 1, 0, 0, WORKITEMPOOL_Dispatch);

    if (wp == NULL)
    {
        ITS_GlobalStop();

        return (-1);
    }

    for (i = 0; i < 5; i++)
    {
        WORKITEM_Instance *wi;

        wi = WORKITEM_Create(sizeof(WORKITEM_Instance), ITS_TRUE, delegate);

        if (wi == NULL)
        {
            WORKITEMPOOL_DestroyPool(wp);

            ITS_GlobalStop();

            return (-1);
        }

        WORKITEM_PutWorkItem(1, wi);
    }

    TIMERS_Sleep(5);

    WORKITEMPOOL_DestroyPool(wp);

    ITS_GlobalStop();

    return (0);
}

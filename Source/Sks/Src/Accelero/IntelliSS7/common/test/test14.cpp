
#include <deque>

#include <its++.h>
#include <its_emlist.h>
#include <its_statics.cpp>

using namespace std;
using namespace its;

int
main(int argc, char **argv)
{
    ITS_STL_EMList<ITS_EVENT *> emList;
    ITS_EVENT *ev;
    int i;

    ITS_GlobalStart(0);

    ITS_Initialize(1, 0);

    ev = new ITS_EVENT;
    emList.PutEvent(ev);
    ev = new ITS_EVENT;
    emList.PutEvent(ev);
    ev = new ITS_EVENT;
    emList.PutEvent(ev);

    for (i = 0; i < 250000; i++)
    {
        emList.GetNextEvent(ev);

        delete ev;

        ev = new ITS_EVENT;

        emList.PutEvent(ev);
    }

    ITS_GlobalStop();

    return 0;
}

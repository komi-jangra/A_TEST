#include <stdio.h>
#include <string.h>

#include <its_ring_buf.h>

char *strings[] =
{
    "This is a test.  This is only a test.  Please do not adjust your set.\n",
    "When in the course of human events, it has become necessary for one ",
    "nation to dissolve the political bands which have connected it with ",
    "another,\nand to assume among the powers of the earth the separate and ",
    "equal station to which the laws of Nature and Nature's God have ",
    "entitled it.\n",
    NULL
};

static int
Write(RINGBUF_Manager *rb, char *text, ITS_UINT len)
{
    printf("%*.*s", len, len, text);

    return (len);
}

int
main(int argc, char **argv)
{
    RINGBUF_Manager *rb;
    int i = 0;

    rb = RINGBUF_InitManager(128, 90, Write);

    while (strings[i] != NULL)
    {
        RINGBUF_Append(rb, strings[i], strlen(strings[i]));

        i++;
    }

    RINGBUF_FreeManager(rb);

    return (0);
}

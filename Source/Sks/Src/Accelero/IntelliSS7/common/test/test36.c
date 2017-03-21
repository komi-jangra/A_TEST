#include <stdio.h>
#include <string.h>

#include <its_splay.h>

int
StringCompare(void *k1, ITS_UINT k1len, void *k2, ITS_UINT k2len)
{
    if (k1 == NULL || k2 == NULL)
    {
        abort();
    }

    return strcmp(k1, k2);
}

int
Iterate(SPLAY_Node *n, void *in, void *out)
{
    printf("%s", n->key);

    return (ITS_SUCCESS);
}

int
main(int argc, char **argv)
{
    SPLAY_Tree *b;
    char buf[80];
    int i = 0;

    b = SPLAY_InitSplay();
    
    while (i < 5 && fgets(buf, 80, stdin) != NULL)
    {
        i++;

        SPLAY_InsertNode(b, buf, strlen(buf) + 1, NULL, 0,
                         StringCompare);
    }

    SPLAY_Iterate(b, NULL, NULL, Iterate);

    SPLAY_FreeSplay(b);

    return (0);
}


#include <stdio.h>
#include <string.h>

#include <its_rb.h>

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
Iterate(REDBLACK_Node *n, void *in, void *out)
{
    printf("%s", n->key);

    return (ITS_SUCCESS);
}

int
main(int argc, char **argv)
{
    REDBLACK_Tree *b;
    char buf[80];
    int i = 0;

    b = RB_InitTree();
    
    while (i < 5 && fgets(buf, 80, stdin) != NULL)
    {
        i++;

        RB_InsertNode(b, buf, strlen(buf) + 1, NULL, 0,
                      StringCompare);
    }
    
    RB_Iterate(b, NULL, NULL, Iterate);

    RB_FreeTree(b);

    return (0);
}


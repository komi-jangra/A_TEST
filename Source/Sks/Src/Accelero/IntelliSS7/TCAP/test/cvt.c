
#include <AsnC.h>
#include <ITU-TCAP-APDU-types.h>

int
main(int argc, char **argv)
{
    PE test;
    char *enc, buf[32];
    int len;

    int2strb(1 << bit_ITU__TCAP__APDU_protocol__version_version1,
             1, buf, 32);
    test = strb2bitstr(buf, 1,
                       PE_CLASS_UNIV, PE_FORM_PRIM);

    test = bit2prim(test);

    if (pe2ssdu(test, &enc, &len) != OK)
    {
        return (-1);
    }

    return (0);
}

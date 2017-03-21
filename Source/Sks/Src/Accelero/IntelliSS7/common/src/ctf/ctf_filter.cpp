#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <its++.h>
#include <vector>

#undef CCITT
#undef ANSI
#define CCITT

#include <itu/sccp.h>

#undef CCITT
#undef ANSI
#define ANSI

#include <ansi/sccp.h>

#undef CCITT
#undef ANSI

typedef struct
{
    ITS_UINT MTP3FilterBits;
    ITS_INT opc;
    ITS_INT dpc;
    ITS_INT sio;
}MTP3Filter;

std::vector<MTP3Filter> MTP3FilterList;

typedef struct
{
    ITS_UINT SCCPFilterBits;
    ITS_UINT CGPNFilterBits;
    ITS_INT  ssn1;
    ITS_CHAR gtt1[25];
    ITS_CHAR pc1[25];
    ITS_INT  ni1;
    ITS_UINT CDPNFilterBits;
    ITS_INT  ssn2;
    ITS_CHAR gtt2[25];
    ITS_CHAR pc2[25];
    ITS_INT  ni2;
}SCCPFilter;

std::vector<SCCPFilter> SCCPFilterList;

typedef struct
{
    ITS_UINT TCAPFilterBits;
    ITS_OCTET nat;
    ITS_INT opfam;
    ITS_INT op;
}TCAPFilter;

std::vector<TCAPFilter> TCAPFilterList;

static ITS_INT
ParseFilterInfo(char* fileBuf, ITS_UINT bufSize)
{
    ITS_INT ret = 0;
    char tempBuf[1024];
    char charCount = 0;
    ITS_BOOLEAN mtp3section = ITS_FALSE;
    ITS_BOOLEAN sccpsection = ITS_FALSE;
    ITS_BOOLEAN tcapsection = ITS_FALSE;

    for (ITS_UINT i = 0; i < bufSize; i++)
    {
        if (ret != 0)
        {
            break;
        }
 
        switch (fileBuf[i])
        {
            case ' ':
            case '\n':
            case '\r':
            case ',':
                break;
            case ';':
            {
                tempBuf[charCount] = '\0';
                char priBuf[1024];
                ITS_UINT priCount = 0; 

                int ruleCount = strlen(tempBuf);

                if (mtp3section)
                {
                    int element = 0;
                    MTP3Filter filt;
                    memset (&filt, 0, sizeof(MTP3Filter));
             
                    for (int j = 0; j < ruleCount; )
                    {
                        if (ret != 0)
                            break;
                        switch (tempBuf[j])
                        {
                            case '=':
                                priBuf[priCount] = '\0';
                                if (strcmp(priBuf, "opc") == 0)
                                {
                                    element = 1;
                                    filt.MTP3FilterBits |= 1;
                                }
                                else if (strcmp(priBuf, "dpc") == 0)
                                {
                                    element = 2;
                                    filt.MTP3FilterBits |= 2;
                                }
                                else if (strcmp(priBuf, "sio") == 0)
                                {
                                    element = 3;
                                    filt.MTP3FilterBits |= 4;
                                }
                                else
                                {
                                    ret = i;
                                }
                                priCount = 0;
                                priBuf[priCount] = '\0';
                                j++;
                                break;
                            case '\"':
                                j++;
                                while ((j < ruleCount) && (tempBuf[j] != '\"')) 
                                {
                                    priBuf[priCount] = tempBuf[j];
                                    priCount++;
                                    j++;
                                }
                                j++;
                                priBuf[priCount] = '\0';
                                if ((strlen(priBuf) > 2) && 
                                   (priBuf[0] == '0' && (priBuf[1] == 'x' || priBuf[1] == 'X')))
                                {
                                    if (element == 1)
                                        sscanf(priBuf,"%x",&(filt.opc));
                                    else if (element == 2)
                                        sscanf(priBuf,"%x",&(filt.dpc));
                                    else if (element == 3)
                                        sscanf(priBuf,"%x",&(filt.sio));
                                }
                                else
                                {
                                    if (element == 1)
                                    {
                                        sscanf(priBuf,"%d",&(filt.opc));
                                    }
                                    else if (element == 2)
                                    {
                                        sscanf(priBuf,"%d",&(filt.dpc));
                                    }
                                    else if (element == 3)
                                    {
                                        sscanf(priBuf,"%d",&(filt.sio));
                                    }
                                }
                                priCount = 0;
                                priBuf[priCount] = '\0';
                                break;
                            case '&':
                                j++; 
                                priCount = 0;
                                priBuf[priCount] = '\0'; 
                                break;
                            default:
                                priBuf[priCount] = tempBuf[j]; 
                                priCount++;
                                j++;
                                break;
                        }
                    }
                    if (priCount == 0)
                    {
                        MTP3FilterList.push_back(filt);
                    } 
                }
                else if (sccpsection)
                {
                    memset(priBuf, 0, 1024);
                    priCount = 0;
                    int element = 0;
                    int sccpelement = 0;
                    SCCPFilter filt;
                    memset (&filt, 0, sizeof(SCCPFilter));

                    if (tempBuf[0] == 'c' && tempBuf[1] == 'g' && 
                        tempBuf[2] == 'p' && tempBuf[3] == 'n')
                    {
                        filt.SCCPFilterBits |= 1; 
                        sccpelement = 1;
                    }
                    else if (tempBuf[0] == 'c' && tempBuf[1] == 'd' &&
                        tempBuf[2] == 'p' && tempBuf[3] == 'n')
                    {
                        filt.SCCPFilterBits |= 2; 
                        sccpelement = 2;
                    }

                    for (int j = 4; j < ruleCount; )
                    {
                        if (ret != 0)
                            break;
                        switch (tempBuf[j])
                        {
                            case '=':
                                priBuf[priCount] = '\0';
                                if (strcmp(priBuf, "ssn") == 0)
                                {
                                    element = 1;
                                    if (sccpelement == 1)
                                        filt.CGPNFilterBits |= 1;
                                    else if (sccpelement == 2)
                                        filt.CDPNFilterBits |= 1;
                                }
                                else if (strcmp(priBuf, "gtt") == 0)
                                {
                                    element = 2;
                                    if (sccpelement == 1)
                                        filt.CGPNFilterBits |= 2;
                                    else if (sccpelement == 2)
                                        filt.CDPNFilterBits |= 2;
                                }
                                else if (strcmp(priBuf, "pc") == 0)
                                {
                                    element = 3;
                                    if (sccpelement == 1)
                                        filt.CGPNFilterBits |= 4;
                                    else if (sccpelement == 2)
                                        filt.CDPNFilterBits |= 4;
                                }
                                else if (strcmp(priBuf, "ni") == 0)
                                {
                                    element = 4;
                                    if (sccpelement == 1)
                                        filt.CGPNFilterBits |= 8;
                                    else if (sccpelement == 2)
                                        filt.CDPNFilterBits |= 8; 
                                }
                                else
                                {
                                    ret = i;
                                }
                                priCount = 0;
                                priBuf[priCount] = '\0';
                                j++;
                                break;
                            case '\"':
                                j++;
                                while ((j < ruleCount) && (tempBuf[j] != '\"'))
                                {
                                    priBuf[priCount] = tempBuf[j];
                                    priCount++;
                                    j++;
                                }
                                j++;
                                priBuf[priCount] = '\0';
                                if (element == 1)
                                {
                                    if ((priBuf[0] == '0') && 
                                        (priBuf[1] == 'x' || priBuf[1] == 'X'))
                                    {
                                        if (sccpelement == 1)
                                            sscanf(priBuf,"%x",&(filt.ssn1));
                                        else if (sccpelement == 2)
                                            sscanf(priBuf,"%x",&(filt.ssn2));
                                    }
                                    else
                                    {
                                        if (sccpelement == 1)
                                            sscanf(priBuf,"%d",&(filt.ssn1));
                                        else if (sccpelement == 2)
                                            sscanf(priBuf,"%d",&(filt.ssn2));
                                    }
                                }
                                else if (element == 4)
                                {
                                    if ((priBuf[0] == '0') &&
                                        (priBuf[1] == 'x' || priBuf[1] == 'X'))
                                    {
                                        if (sccpelement == 1)
                                            sscanf(priBuf,"%x",&(filt.ni1));
                                        else if (sccpelement == 2)
                                            sscanf(priBuf,"%x",&(filt.ni2));
                                    }
                                    else
                                    {
                                        if (sccpelement == 1)
                                            sscanf(priBuf,"%d",&(filt.ni1));
                                        else if (sccpelement == 2)
                                            sscanf(priBuf,"%d",&(filt.ni2));
                                    }
                                }
                                else if (element == 3)
                                {
                                    if (sccpelement == 1)
                                        strcpy (filt.pc1, priBuf);
                                    else if (sccpelement == 2)
                                        strcpy (filt.pc2, priBuf);
                                }
                                else if (element == 2)
                                {
                                    if (sccpelement == 1)
                                        strcpy (filt.gtt1, priBuf);
                                    else if (sccpelement == 2)
                                        strcpy (filt.gtt2, priBuf);
                                }

                                priCount = 0;
                                priBuf[priCount] = '\0';
                                break;
                           case '&':
                                j++;
                                if (tempBuf[j] == 'c' && tempBuf[j+1] == 'g' &&
                                    tempBuf[j+2] == 'p' && tempBuf[j+3] == 'n')
                                {
                                    filt.SCCPFilterBits |= 1;
                                    sccpelement = 1; 
                                }
                                else if (tempBuf[j] == 'c' && tempBuf[j+1] == 'd' &&
                                    tempBuf[j+2] == 'p' && tempBuf[j+3] == 'n')
                                {
                                    filt.SCCPFilterBits |= 2;
                                    sccpelement = 2;
                                }
                                j += 4;

                                priCount = 0;
                                priBuf[priCount] = '\0';
                                break;
                            default:
                                priBuf[priCount] = tempBuf[j];
                                priCount++;
                                j++;
                                break;
                        }
                    }
                    if (priCount == 0)
                    {
                        SCCPFilterList.push_back(filt);
                    }
                }
                else if (tcapsection)
                {
                    int element = 0;
                    TCAPFilter filt;
                    memset (&filt, 0, sizeof(TCAPFilter));
                    memset(priBuf, 0, 1024);
                    priCount = 0;

                    for (int j = 0; j < ruleCount; )
                    {
                        if (ret != 0)
                            break;
                        switch (tempBuf[j])
                        {
                            case '=':
                                priBuf[priCount] = '\0';
                                if (strcmp(priBuf, "nat") == 0)
                                {
                                    element = 1;
                                    filt.TCAPFilterBits |= 1;
                                }
                                else if (strcmp(priBuf, "opfam") == 0)
                                {
                                    element = 2;
                                    filt.TCAPFilterBits |= 2;
                                }
                                else if (strcmp(priBuf, "op") == 0)
                                {
                                    element = 3;
                                    filt.TCAPFilterBits |= 4;
                                }
                                else
                                {
                                    ret = i;
                                }
                                priCount = 0;
                                priBuf[priCount] = '\0';
                                j++;
                                break;
                            case '&':
                                j++; 
                                priCount = 0;
                                priBuf[priCount] = '\0'; 
                                break;
                            case '\"':
                                j++;
                                while ((j < ruleCount) && (tempBuf[j] != '\"'))
                                {
                                    priBuf[priCount] = tempBuf[j];
                                    priCount++;
                                    j++;
                                }
                                j++;
                                priBuf[priCount] = '\0';

                                switch (element)
                                {
                                case 1:
                                    if (strcmp(priBuf,"TRUE") == 0)
                                    {
                                        filt.nat = 1;
                                    }
                                    break;
                                case 2:
                                    
                                    if ((strlen(priBuf) > 2) && 
                                        (priBuf[0] == '0' && (priBuf[1] == 'x' || priBuf[1] == 'X')))
                                    {
                                        sscanf(priBuf,"%x",&(filt.opfam));
                                    }
                                    else
                                    {
                                        sscanf(priBuf,"%d",&(filt.opfam));
                                    }
                                    
                                    break;

                                case 3:
                                    
                                    if ((strlen(priBuf) > 2) && 
                                        (priBuf[0] == '0' && (priBuf[1] == 'x' || priBuf[1] == 'X')))
                                    {
                                        sscanf(priBuf,"%x",&(filt.op));
                                    }
                                    else
                                    {
                                        sscanf(priBuf,"%d",&(filt.op));
                                    }
                                    break;
                                }
                                

                                priCount = 0;
                                priBuf[priCount] = '\0';
                                break;
                                
                            default:
                                priBuf[priCount] = tempBuf[j];
                                priCount++;
                                j++;
                                break;
                        }
                    }
                    if (priCount == 0)
                    {
                        TCAPFilterList.push_back(filt);
                    }
                }

                if (priCount != 0)
                {
                    ret = i;
                }
                memset(tempBuf, 0, 1024);
                charCount = 0;
               
                break;
            }
            case ']':
                tempBuf[charCount] = fileBuf[i]; charCount++;
                tempBuf[charCount] = '\0';

                if (strcmp(tempBuf,"[MTP3]") == 0)
                {
                    mtp3section = ITS_TRUE;
                    sccpsection = ITS_FALSE;
                    tcapsection = ITS_FALSE;
                }
                else if (strcmp(tempBuf,"[SCCP]") == 0)
                {
                    mtp3section = ITS_FALSE;
                    sccpsection = ITS_TRUE;
                    tcapsection = ITS_FALSE;
                }
                else if (strcmp(tempBuf,"[TCAP]") == 0)
                {
                    mtp3section = ITS_FALSE;
                    sccpsection = ITS_FALSE;
                    tcapsection = ITS_TRUE;
                }
                else
                {
                    ret = i + 1;
                }  
                
                charCount = 0;
                tempBuf[charCount] = '\0';

                break;
            default:
                tempBuf[charCount] = fileBuf[i];
                charCount++;
                break;
        }
    }

    return ret;
}

void
PrintFilterList()
{
    printf("\n\n[MTP3]\n");
    printf ("Size : %d\n",MTP3FilterList.size());
    for (ITS_UINT i = 0; i < MTP3FilterList.size(); i++)
    {
        if ((MTP3FilterList[i].MTP3FilterBits & 0x01) == 0x01)
        {
            printf("OPC = %d ",MTP3FilterList[i].opc);
        }
        if ((MTP3FilterList[i].MTP3FilterBits & 0x02) == 0x02)
        {
            printf("DPC = %d",MTP3FilterList[i].dpc);
        }
        printf("\n");
    }
    printf("\n\n[SCCP]\n");
    printf ("Size : %d\n",SCCPFilterList.size());
    for (ITS_UINT j = 0; j < SCCPFilterList.size(); j++)
    {
        printf("\n");
        if ((SCCPFilterList[j].SCCPFilterBits & 0x01) == 1)
        {
            printf ("CGPN : ");
        }

        if ((SCCPFilterList[j].CGPNFilterBits & 0x01) == 0x01)
        {
            printf("SSN = %d ",SCCPFilterList[j].ssn1);
        }
        if ((SCCPFilterList[j].CGPNFilterBits & 0x02) == 0x02)
        {
            printf("GTT = %s ",SCCPFilterList[j].gtt1);
        }
        if ((SCCPFilterList[j].CGPNFilterBits & 0x04) == 0x04)
        {
            printf("PC = %s ",SCCPFilterList[j].pc1);
        } 
        if ((SCCPFilterList[j].CGPNFilterBits & 0x08) == 0x08)
        {
            printf("NI = %d ",SCCPFilterList[j].ni1);
        }

        if ((SCCPFilterList[j].SCCPFilterBits & 0x02) == 2)
        {
            printf ("CDPN : ");
        }
    
        if ((SCCPFilterList[j].CDPNFilterBits & 0x01) == 0x01)
        {
            printf("SSN = %d ",SCCPFilterList[j].ssn2);
        }
        if ((SCCPFilterList[j].CDPNFilterBits & 0x02) == 0x02)
        {
            printf("GTT = %s ",SCCPFilterList[j].gtt2);
        }
        if ((SCCPFilterList[j].CDPNFilterBits & 0x04) == 0x04)
        {
            printf("PC = %s ",SCCPFilterList[j].pc2);
        }
        if ((SCCPFilterList[j].CDPNFilterBits & 0x08) == 0x08)
        {
            printf("NI = %d ",SCCPFilterList[j].ni2);
        }

        printf("\n");
    }
    printf("\n\n[TCAP]\n");    
    printf ("Size : %d\n",TCAPFilterList.size());
    for (ITS_UINT k = 0; k < TCAPFilterList.size(); k++)
    {
        printf("OP = %d",TCAPFilterList[k].op);
        printf("\n");
    }
        
}

void
ClearFilterList()
{
    MTP3FilterList.clear();
    SCCPFilterList.clear();
    TCAPFilterList.clear();
}

ITS_INT
ParseFilterFile (char* filtFile)
{
    struct stat buff;
    ITS_CHAR* fileBuf = NULL;
    ITS_INT ret = 0;
    FILE* fp = fopen(filtFile,"r");

    if (fp == NULL)
        return -1;

    if (!stat(filtFile, &buff))
    {
        fileBuf = (ITS_CHAR*)calloc(buff.st_size, sizeof(ITS_CHAR));
        fread(fileBuf, buff.st_size, 1, fp);
#if defined (DEBUG_CTF)
        for (int i = 0; i < buff.st_size; i++)
            printf ("%c",fileBuf[i]);
#endif
        ret = ParseFilterInfo(fileBuf, buff.st_size);
        if (ret != ITS_SUCCESS)
        {
            printf ("Check the Line number : %d in the filter file", ret);
            MTP3FilterList.clear();
            SCCPFilterList.clear();
            TCAPFilterList.clear();
        }
    }
    else
    {
        return -2;
    }

#if defined (DEBUG_CTF)
    PrintFilterList();     
#endif
    fclose (fp);

    return ITS_SUCCESS;
}
     
ITS_BOOLEAN
IsMTP3EventTobeFiltered (ITS_UINT opc, ITS_UINT dpc, ITS_UINT sio)
{
    ITS_BOOLEAN ret = ITS_TRUE;
    
    for (ITS_UINT i = 0; i < MTP3FilterList.size(); i++)
    {
        if ((MTP3FilterList[i].MTP3FilterBits & 0x01) == 0x01)
        {
            if (MTP3FilterList[i].opc != (ITS_INT)opc)
            {
                ret = ITS_FALSE;
                break;
            }
        }

        if (!ret) { 
            if ((i + 1) != MTP3FilterList.size())
                ret = ITS_TRUE; 
            continue; 
        }

        if ((MTP3FilterList[i].MTP3FilterBits & 0x02) == 0x02)
        {
            if (MTP3FilterList[i].dpc != (ITS_INT)dpc)
            {
                ret = ITS_FALSE;
                break;
            }
        }

        if (!ret) { 
            if ((i + 1) != MTP3FilterList.size())
                ret = ITS_TRUE; 
            continue; 
        }

        if ((MTP3FilterList[i].MTP3FilterBits & 0x04) == 0x04)
        {
            if (MTP3FilterList[i].sio != (ITS_INT)sio)
            {
                ret = ITS_FALSE;
                break;
            }
        }

        if (!ret) { 
            if ((i + 1) != MTP3FilterList.size())
                ret = ITS_TRUE; 
            continue; 
        }

        if (ret) break;
    }

    if ((MTP3FilterList.size() > 0) && ret) 
    {
        ret = ITS_TRUE;
    }
    else
        ret = ITS_FALSE;

    return ret;
}

ITS_BOOLEAN
IsSCCPEventTobeFiltered (ITS_OCTET family, SCCP_ADDR* clp, SCCP_ADDR* cdp)
{
    ITS_BOOLEAN ret = ITS_TRUE;
    
    ITS_OCTET ssn1 = 0, ssn2 = 0, addrInd1 = 0, addrInd2 = 0, gttInfo1[32], gttInfo2[32];
    ITS_UINT pc1 = 0, pc2 = 0;
    ITS_USHORT gttLen1 = 0, gttLen2 = 0;

    if (!clp && !cdp) return ITS_FALSE;

    if (clp)
    {
        if (family == 1)
        {
            SCCP_DecodeAddr_CCITT(clp, &addrInd1, &pc1, &ssn1,
                        gttInfo1, &gttLen1);
        }
        else if (family == 2)
        {
            SCCP_DecodeAddr_ANSI(clp, &addrInd1, &pc1, &ssn1,
                        gttInfo1, &gttLen1);
        } 
    }

    if (cdp)
    {
        if (family == 1)
        {
            SCCP_DecodeAddr_CCITT(cdp, &addrInd2, &pc2, &ssn2,
                        gttInfo2, &gttLen2);
        }
        else if (family == 2)
        {
            SCCP_DecodeAddr_ANSI(cdp, &addrInd2, &pc2, &ssn2,
                        gttInfo2, &gttLen2);
        }
    }

    for (ITS_UINT i = 0; i < SCCPFilterList.size(); i++)
    {
        if (clp)
        {
            if ((SCCPFilterList[i].SCCPFilterBits & 0x01) == 0x01)
            {
                if ((SCCPFilterList[i].CGPNFilterBits & 0x01) == 0x01)
                {
                    if (ssn1 != SCCPFilterList[i].ssn1)
                    {
                        ret = ITS_FALSE;
                    } 
                }

                if (!ret) { 
                    if ((i + 1) != SCCPFilterList.size())
                        ret = ITS_TRUE; 
                    continue; 
                }

                if ((SCCPFilterList[i].CGPNFilterBits & 0x02) == 0x02)
                {
                    if (memcmp(gttInfo1, SCCPFilterList[i].gtt1, gttLen1) != 0)
                    {
                        ret = ITS_FALSE;
                    }
                }

                if (!ret) { 
                    if ((i + 1) != SCCPFilterList.size())
                        ret = ITS_TRUE; 
                    continue; 
                }

                if ((SCCPFilterList[i].CGPNFilterBits & 0x04) == 0x04)     
                {
                    ITS_UINT pc = atoi(SCCPFilterList[i].pc1);
                    if (pc != pc1)
                    {
                        ret = ITS_FALSE;
                    }
                }

                if (!ret) { 
                    if ((i + 1) != SCCPFilterList.size())
                        ret = ITS_TRUE; 
                    continue; 
                }

                if ((SCCPFilterList[i].CGPNFilterBits & 0x08) == 0x08)
                {
                    if ((addrInd1 & 0x80) != SCCPFilterList[i].ni1)
                    {
                        ret = ITS_FALSE;
                    }
                }

                if (!ret) { 
                    if ((i + 1) != SCCPFilterList.size())
                        ret = ITS_TRUE; 
                    continue; 
                }
            }
        }

        if (cdp)
        {
            if ((SCCPFilterList[i].SCCPFilterBits & 0x02) == 0x02)
            {
                if ((SCCPFilterList[i].CDPNFilterBits & 0x01) == 0x01)
                {
                    if (ssn2 != SCCPFilterList[i].ssn2)
                    {
                        ret = ITS_FALSE;
                    }
                }

                if (!ret) { 
                    if ((i + 1) != SCCPFilterList.size())
                        ret = ITS_TRUE; 
                    continue; 
                }

                if ((SCCPFilterList[i].CDPNFilterBits & 0x02) == 0x02)
                {
                    if (memcmp(gttInfo2, SCCPFilterList[i].gtt2, gttLen2) != 0)
                    {
                        ret = ITS_FALSE;
                    }
                }

                if (!ret) { 
                    if ((i + 1) != SCCPFilterList.size())
                        ret = ITS_TRUE; 
                    continue; 
                }

                if ((SCCPFilterList[i].CDPNFilterBits & 0x04) == 0x04)
                {
                    ITS_UINT pc = atoi(SCCPFilterList[i].pc2);
                    if (pc != pc2)
                    {
                        ret = ITS_FALSE;
                    }
                }

                if (!ret) { 
                    if ((i + 1) != SCCPFilterList.size())
                        ret = ITS_TRUE; 
                    continue; 
                }

                if ((SCCPFilterList[i].CDPNFilterBits & 0x08) == 0x08)
                {
                    if ((addrInd2 & 0x80) != SCCPFilterList[i].ni2)
                    {
                        ret = ITS_FALSE;
                    }
                }

                if (!ret) { 
                    if ((i + 1) != SCCPFilterList.size())
                        ret = ITS_TRUE; 
                    continue; 
                }
            }
        }

        if (ret) break;
    }

    if ((SCCPFilterList.size() > 0) && ret) 
    {
        ret = ITS_TRUE;
    }
    else
        ret = ITS_FALSE;

    return ret;
}

ITS_BOOLEAN
IsTCAPEventTobeFiltered (ITS_OCTET nat, ITS_OCTET opfam, ITS_USHORT op)
{
    ITS_BOOLEAN ret = ITS_TRUE;
    
    for (ITS_UINT i = 0; i < TCAPFilterList.size(); i++)
    {
        if ((TCAPFilterList[i].TCAPFilterBits & 0x01) == 0x01)
        {
            if (TCAPFilterList[i].nat != nat)
            {
                ret = ITS_FALSE;
                break;
            }
        }

        if (!ret) { 
            if ((i + 1) != TCAPFilterList.size())
                ret = ITS_TRUE; 
            continue; 
        }

        if ((TCAPFilterList[i].TCAPFilterBits & 0x02) == 0x02)
        {
            if (TCAPFilterList[i].opfam != opfam)
            {
                ret = ITS_FALSE;
                break;
            }
        }

        if (!ret) { 
            if ((i + 1) != TCAPFilterList.size())
                ret = ITS_TRUE; 
            continue; 
        }

        if ((TCAPFilterList[i].TCAPFilterBits & 0x04) == 0x04)
        {
            if (TCAPFilterList[i].op != op)
            {
                ret = ITS_FALSE;
                break;
            }
        }

        if (!ret) { 
            if ((i + 1) != TCAPFilterList.size())
                ret = ITS_TRUE; 
            continue; 
        }

        if (ret) break;
    }

    if ((TCAPFilterList.size() > 0) && ret) 
    {
        ret = ITS_TRUE;
    }
    else
        ret = ITS_FALSE;

    return ret;
}

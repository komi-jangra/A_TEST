
#define EXT_LEN_FLAG    0x80U
#define OTID_IDENT      0x48U
#define DTID_IDENT      0x49U
#define PABT_IDENT      0x6AU
#define DIALOG_IDENT    0x6BU
#define CSEQ_IDENT      0x6CU

#define IS_CONSTRUCTED(x) \
    ((x) & 0x20)

#define TAG_MASK        0x1FU

/*
 * simple parser returns
 */
enum ParseCode
{
    PC_NO_TIDS,
    PC_OOD_1,
    PC_OOD_2,
    PC_OOD_3,
    PC_OVERFLOW,
    PC_PARSE_OK
};

/*
 * parser forwards.
 */
static int GetSub(ITS_OCTET *data, ITS_OCTET *stop);
static int GetTag(ITS_OCTET *data, ITS_UINT *retTag,
                  ITS_OCTET *stop);
static int GetLength(ITS_OCTET *data, ITS_UINT *retLen,
                     ITS_OCTET *stop, ITS_BOOLEAN isConstructed);

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static ITS_BOOLEAN
GetTID(ITS_OCTET** buf, ITS_UINT *tid, ITS_UINT *tidLen)
{
    ITS_BOOLEAN firstTime = ITS_TRUE;
    ITS_OCTET *data = *buf;
    ITS_UINT len = *data;

    *tid = 0;
    data += GetLength(data, &len, data + 7, ITS_FALSE);

    if (data == *buf || data == (data + 7))
    {
        TCAP_ERROR(("GetTID: Error parsing length\n"));

        return (ITS_NO);
    }

    *tidLen = len;

    if (len > 4)
    {
        TCAP_ERROR(("GetTID: TID too large.\n"));

        return (ITS_NO);
    }
    if (len == 0)
    {
        TCAP_ERROR(("GetTID: TID too small.\n"));

        return (ITS_NO);
    }

    /* backup for the ++ that happens in the while loop */
    data--;

    /* get TID2 */
    while (len > 0)
    {
        *tid <<= 8;
        data++;
        if (firstTime)
        {
            /* sign extend first byte */
            *tid |= (char)*data;
            firstTime = ITS_FALSE;
        }
        else
        {
            *tid |= *data;
        }
        len--;
    }

    *buf = data + 1;

    return (ITS_YES);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static int
GetTag(ITS_OCTET *data, ITS_UINT *retTag,
       ITS_OCTET *stop)
{
    int len = 1;

    *retTag = 0;
    if ((*data & TAG_MASK) == TAG_MASK) /* long form */
    {
        do
        {
            data++;
            len++;

            *retTag <<= 7;
            *retTag |= *data & 0x7F;
        }
        while ((*data & 0x80) && data < stop);
    }
    else
    {
        /*
         * Note that I don't mask off the context or constructed bits.
         * We want to know them in this code (for equality checks),
         * and if long form tags appear, we don't care about their value.
         */
        *retTag = *data;
    }

    return len;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static int
GetLength(ITS_OCTET *data, ITS_UINT *retLen,
          ITS_OCTET *stop, ITS_BOOLEAN isConstructed)
{
    int len;
    int rlen = 1;

    len = *data;
    if (len > EXT_LEN_FLAG) /* long form */
    {
        int tlen = len & ~EXT_LEN_FLAG;

        rlen += tlen;
        len = 0;
        if (tlen > 4)
        {
            return 0;
        }
        data++;
        while (tlen > 0)
        {
            len <<= 8;
            len = *data;
            tlen--;
            data++;
        }

        *retLen = len;
    }
    else if (len < EXT_LEN_FLAG) /* short form */
    {
        *retLen = len;
    }
    else /* indeterminate */
    {
        ITS_OCTET *start = data;

        data++;

        if (isConstructed)
        {
            while (data[0] != 0 && data[1] != 0 && data < stop)
            {
                data += GetSub(data, stop);
            }
        }
        else
        {
            while (data[0] != 0 && data[1] != 0 && data < stop)
            {
                data++;
            }
        }

        if (data[0] == 0 && data[1] == 0)
        {
            data += 2;
        }
        else
        {
            data = stop;
        }

        *retLen = data - start;
    }

    return rlen;
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 *      None.
 ****************************************************************************/
static int
GetSub(ITS_OCTET *data, ITS_OCTET *stop)
{
    ITS_UINT tag;
    ITS_UINT len;
    ITS_BOOLEAN isConstructed = ITS_FALSE;
    ITS_OCTET* start;

    start = data;

    if (IS_CONSTRUCTED(*data))
    {
        isConstructed = ITS_TRUE;
    }

    data += GetTag(data, &tag, stop);
    if (data >= stop)
    {
        return (stop - start);
    }

    data += GetLength(data, &len, stop, isConstructed);
    if (data >= stop)
    {
        return (stop - start);
    }

    return (data - start);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 ****************************************************************************/
static enum ParseCode
FindParts(ITS_OCTET *pdup, int wlen,
          ITS_OCTET **tp, ITS_OCTET **dp, ITS_OCTET **cp)
{
    ITS_UINT tid, tidLen;
    ITS_UINT tag, clen;
    ITS_OCTET *pdu = pdup;

    *tp = pdup;
    *dp = NULL;
    *cp = NULL;

    /* skip tag */
    pdu += GetTag(pdu, &tag, pdup + wlen);

    /* get total len */
    pdu += GetLength(pdu, &clen, pdup + wlen, ITS_TRUE);

    /*
     * skip 1st tids
     */
    if (*pdu == OTID_IDENT)
    {
        pdu++;

        GetTID(&pdu, &tid, &tidLen);
    }
    else if (*pdu == DTID_IDENT)
    {
        pdu++;

        GetTID(&pdu, &tid, &tidLen);
    }
    else
    {
        if (*pdup != TCAP_PT_TC_UNI_CCITT)
        {
            return PC_NO_TIDS;
        }
    }

    /*
     * skip second tid, if present
     */
    /* have we run out of data */
    if ((pdu - pdup) >= wlen)
    {
        return PC_OOD_1;
    }

    if (*pdu == OTID_IDENT)
    {
        pdu++;

        GetTID(&pdu, &tid, &tidLen);
    }
    else if (*pdu == DTID_IDENT)
    {
        pdu++;

        GetTID(&pdu, &tid, &tidLen);
    }

    /*
     * Dialogue portion present?
     */
    /* have we run out of data */
    if ((pdu - pdup) >= wlen)
    {
        if (*pdup != TCAP_PT_TC_UNI_CCITT)
        {
            return PC_OOD_2;
        }
        else
        {
            return PC_PARSE_OK;
        }
    }

    if (*pdu == DIALOG_IDENT)
    {
        *dp = pdu;

        pdu++;
        pdu += GetLength(pdu, &clen, pdup + wlen, ITS_TRUE);
        pdu += clen;
    }
    else if (*pdu == PABT_IDENT)
    {
        pdu++;
        pdu += GetLength(pdu, &clen, pdup + wlen, ITS_TRUE);
        pdu += clen;
    }

    /*
     * component portion ?
     */
    /* have we run out of data */
    if ((pdu - pdup) >= wlen)
    {
        if (*pdup == TCAP_PT_TC_UNI_CCITT)
        {
            return PC_OOD_3;
        }
        else
        {
            return PC_PARSE_OK;
        }
    }

    if (*pdu == CSEQ_IDENT)
    {
        *cp = pdu;

        pdu++;
        pdu += GetLength(pdu, &clen, pdup + wlen, ITS_TRUE);
        pdu += clen;
    }

    if ((pdu - pdup) >= wlen)
    {
        return PC_PARSE_OK;
    }
    else
    {
        return PC_OVERFLOW;
    }
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 ****************************************************************************/
static int
ParseTRP(struct type_ITU__TCAP_MessageType **pdu, ITS_OCTET *tp, int wlen)
{
    ITS_OCTET *data;
    ITS_UINT tag, len;
    struct type_ITU__TCAP_MessageType *ret = NULL;

    *pdu = NULL;

    if (!tp)
    {
        return (ITS_EPROTERR);
    }

    /* get the PType */
    data = tp;
    data += GetTag(data, &tag, data + wlen);
    if (data == tp)
    {
        return (ITS_EPROTERR);
    }

    /* get the len */
    tp = data;
    data += GetLength(data, &len, data + wlen, ITS_TRUE);
    if (data == tp)
    {
        return (ITS_EPROTERR);
    }

    /* allocate PDU */
    ret = (struct type_ITU__TCAP_MessageType *)
            calloc(1, sizeof(struct type_ITU__TCAP_MessageType));

    if (!ret)
    {
        return (ITS_EPROTERR);
    }

    switch (tag)
    {
    case TCAP_PT_TC_UNI_CCITT:
        ret->offset = type_ITU__TCAP_MessageType_unidirectional;

        /* allocate TRP */
        ret->un.unidirectional = (struct type_ITU__TCAP_Unidirectional *)
                                    calloc(1, sizeof(struct type_ITU__TCAP_Unidirectional));

        if (!ret->un.unidirectional)
        {
            free(ret);

            return (ITS_EPROTERR);
        }

        break;

    case TCPPT_TC_BEGIN:
        ret->offset = type_ITU__TCAP_MessageType_begin;

        /* Allocate TRP */
        ret->un.begin = (struct type_ITU__TCAP_Begin *)
                            calloc(1, sizeof(struct type_ITU__TCAP_Begin));

        if (!ret->un.begin)
        {
            free(ret);

            return (ITS_EPROTERR);
        }

        /* check TID */
        if (*data != OTID_IDENT)
        {
            free(ret->un.begin);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* Allocate TID */
        data += GetTag(data, &tag, data + wlen);
        data += GetLength(data, &len, data + wlen, ITS_FALSE);

        ret->un.begin->otid = (struct type_ITU__TCAP_OrigTransactionID *)
                                calloc(1, sizeof(struct type_ITU__TCAP_OrigTransactionID) + wlen);

        if (!ret->un.begin->otid)
        {
            free(ret->un.begin);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* link it up and copy TID */
        ret->un.begin->otid->qb_forw = ret->un.begin->otid;
        ret->un.begin->otid->qb_back = ret->un.begin->otid;
        ret->un.begin->otid->qb_data = ret->un.begin->otid->qb_base;
        ret->un.begin->otid->qb_len = len;
        memcpy(ret->un.begin->otid->qb_data, data, len);
        break;

    case TCPPT_TC_CONTINUE:
        ret->offset = type_ITU__TCAP_MessageType_contin;

        /* allocate TRP */
        ret->un.contin = (struct type_ITU__TCAP_Continue *)
                            calloc(1, sizeof(struct type_ITU__TCAP_Continue));

        if (!ret->un.contin)
        {
            free(ret);

            return (ITS_EPROTERR);
        }

        /* check TID */
        if (*data != OTID_IDENT)
        {
            free(ret->un.contin);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* Allocate TID */
        data += GetTag(data, &tag, data + wlen);
        data += GetLength(data, &len, data + wlen, ITS_FALSE);

        ret->un.contin->otid = (struct type_ITU__TCAP_OrigTransactionID *)
                                calloc(1, sizeof(struct type_ITU__TCAP_OrigTransactionID) + wlen);

        if (!ret->un.contin->otid)
        {
            free(ret->un.contin);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* link it up and copy TID */
        ret->un.contin->otid->qb_forw = ret->un.contin->otid;
        ret->un.contin->otid->qb_back = ret->un.contin->otid;
        ret->un.contin->otid->qb_data = ret->un.contin->otid->qb_base;
        ret->un.contin->otid->qb_len = len;
        memcpy(ret->un.contin->otid->qb_data, data, len);

        /* check TID */
        data += len;
        if (*data != DTID_IDENT)
        {
            free(ret->un.contin->otid);
            free(ret->un.contin);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* Allocate TID */
        data += GetTag(data, &tag, data + wlen);
        data += GetLength(data, &len, data + wlen, ITS_FALSE);

        ret->un.contin->dtid = (struct type_ITU__TCAP_DestTransactionID *)
                                calloc(1, sizeof(struct type_ITU__TCAP_DestTransactionID) + wlen);

        if (!ret->un.contin->dtid)
        {
            free(ret->un.contin->otid);
            free(ret->un.contin);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* link it up and copy TID */
        ret->un.contin->dtid->qb_forw = ret->un.contin->dtid;
        ret->un.contin->dtid->qb_back = ret->un.contin->dtid;
        ret->un.contin->dtid->qb_data = ret->un.contin->dtid->qb_base;
        ret->un.contin->dtid->qb_len = len;
        memcpy(ret->un.contin->dtid->qb_data, data, len);
        break;

    case TCPPT_TC_END:
        ret->offset = type_ITU__TCAP_MessageType_end;

        /* Allocate TRP */
        ret->un.end = (struct type_ITU__TCAP_End *)
                        calloc(1, sizeof(struct type_ITU__TCAP_End));

        if (!ret->un.end)
        {
            free(ret);

            return (ITS_EPROTERR);
        }

        /* check TID */
        if (*data != DTID_IDENT)
        {
            free(ret->un.end);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* Allocate TID */
        data += GetTag(data, &tag, data + wlen);
        data += GetLength(data, &len, data + wlen, ITS_FALSE);

        ret->un.end->dtid = (struct type_ITU__TCAP_DestTransactionID *)
                                calloc(1, sizeof(struct type_ITU__TCAP_DestTransactionID) + wlen);

        if (!ret->un.end->dtid)
        {
            free(ret->un.end);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* link it up and copy TID */
        ret->un.end->dtid->qb_forw = ret->un.end->dtid;
        ret->un.end->dtid->qb_back = ret->un.end->dtid;
        ret->un.end->dtid->qb_data = ret->un.end->dtid->qb_base;
        ret->un.end->dtid->qb_len = len;
        memcpy(ret->un.end->dtid->qb_data, data, len);
        break;

    case TCPPT_TC_P_ABORT:
        ret->offset = type_ITU__TCAP_MessageType_abort;

        ret->un.abort = (struct type_ITU__TCAP_Abort *)
                           calloc(1, sizeof(struct type_ITU__TCAP_Abort));

        if (!ret->un.abort)
        {
            free(ret);

            return (ITS_EPROTERR);
        }

        /* check TID */
        if (*data != DTID_IDENT)
        {
            free(ret->un.abort);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* Allocate TID */
        data += GetTag(data, &tag, data + wlen);
        data += GetLength(data, &len, data + wlen, ITS_FALSE);

        ret->un.abort->dtid = (struct type_ITU__TCAP_DestTransactionID *)
                                calloc(1, sizeof(struct type_ITU__TCAP_DestTransactionID) + wlen);

        if (!ret->un.abort->dtid)
        {
            free(ret->un.abort);
            free(ret);

            return (ITS_EPROTERR);
        }

        /* link it up and copy TID */
        ret->un.abort->dtid->qb_forw = ret->un.abort->dtid;
        ret->un.abort->dtid->qb_back = ret->un.abort->dtid;
        ret->un.abort->dtid->qb_data = ret->un.abort->dtid->qb_base;
        ret->un.abort->dtid->qb_len = len;
        memcpy(ret->un.abort->dtid->qb_data, data, len);
        break;

    default:
        free(ret);
        return (ITS_EPROTERR);
    }

    *pdu = ret;

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 ****************************************************************************/
static int
ParseDLG(struct type_ITU__TCAP_MessageType *pdu,
         ITS_OCTET *dp, ITS_OCTET *stop)
{
    ITS_OCTET *data = dp, *tmp;
    ITS_UINT tag, len;
    int err = PS_ERR_NONE;
    PE pe;

    if (!dp)
    {
        return (ITS_SUCCESS);
    }

    if (CCITT_TCAP_Variant != CCITT_TCAP_WHITE_BOOK)
    {
        if (pdu->offset != type_ITU__TCAP_MessageType_abort)
        {
            return (ITS_EPROTERR);
        }
    }

    /* compute length and check tag */
    data += GetTag(data, &tag, stop);
    if (data == dp)
    {
        return (ITS_EPROTERR);
    }

    tmp = data;
    data += GetLength(data, &len, stop, ITS_TRUE);
    if (data == tmp)
    {
        return (ITS_EPROTERR);
    }

    pe = ssdu2pe((char *)dp, len + (data - dp), NULL, &err);
    if (err != PS_ERR_NONE)
    {
        return (ITS_EPROTERR);
    }

    switch (pdu->offset)
    {
    case type_ITU__TCAP_MessageType_unidirectional:
        pdu->un.unidirectional->dialoguePortion = pe;
        break;

    case type_ITU__TCAP_MessageType_begin:
        pdu->un.begin->dialoguePortion = pe;
        break;

    case type_ITU__TCAP_MessageType_contin:
        pdu->un.contin->dialoguePortion = pe;
        break;

    case type_ITU__TCAP_MessageType_end:
        pdu->un.end->dialoguePortion = pe;
        break;

    case type_ITU__TCAP_MessageType_abort:
        pdu->un.abort->reason = (struct choice_ITU__TCAP_2 *)
                                    calloc(1, sizeof(struct choice_ITU__TCAP_2));

        if (!pdu->un.abort->reason)
        {
            return (ITS_EPROTERR);
        }

        if (tag == DIALOG_IDENT)
        {
            pdu->un.abort->reason->offset = choice_ITU__TCAP_2_dialoguePortion;
            pdu->un.abort->reason->un.dialoguePortion = pe;
        }
        else if (tag == PABT_IDENT)
        {
            pdu->un.abort->reason->offset = choice_ITU__TCAP_2_p__abort__cause;
            if (decode_ITU__TCAP_P__AbortCause(pe, 1, NULL, NULL, 
                                               (char **)&pdu->un.abort->reason->un.p__abort__cause)
                != OK)
            {
                free(pdu->un.abort->reason);
                pdu->un.abort->reason = NULL;

                return (ITS_EPROTERR);
            }
        }
        else
        {
            free(pdu->un.abort->reason);
            pdu->un.abort->reason = NULL;

            return (ITS_EPROTERR);
        }

        break;

    default:
        pe_free(pe);
        return (ITS_EPROTERR);
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 ****************************************************************************/
static int
ParseCMP(struct type_ITU__TCAP_MessageType *pdu,
         ITS_OCTET *cp, ITS_OCTET *stop)
{
    ITS_OCTET *data = cp;
    ITS_UINT tag, len;
    struct type_ITU__TCAP_ComponentPortion *cseq = NULL;

    if (!cp)
    {
        return (ITS_SUCCESS);
    }

    data += GetTag(data, &tag, stop);
    if (data == cp)
    {
        return (ITS_EPROTERR);
    }

    cp = data;
    data += GetLength(data, &len, stop, ITS_TRUE);
    if (data == cp)
    {
        return (ITS_EPROTERR);
    }

    if (len == 0 || (data[0] == 0 && data[1] == 0))
    {
        if (pdu->offset == type_ITU__TCAP_MessageType_unidirectional)
        {
            return (ITS_EPROTERR);
        }
        else
        {
            return (ITS_SUCCESS);
        }
    }

    while (data < cp + len && data[0] != 0 && data[1] != 0)
    {
        ITS_OCTET *limit = data, *comp, *tmp;
        PE pe;
        int err;
        struct type_ITU__TCAP_ComponentPortion *c, **list;

        limit = data + GetSub(data, stop);

        if (limit == data)
        {
            if (cseq)
            {
                free_ITU__TCAP_ComponentPortion(cseq);
            }

            return (ITS_EPROTERR);
        }

        comp = data;

        /* compute length and check tag */
        comp += GetTag(comp, &tag, stop);
        if (comp == data)
        {
            if (cseq)
            {
                free_ITU__TCAP_ComponentPortion(cseq);
            }

            return (ITS_EPROTERR);
        }

        tmp = comp;
/* old code was
        comp += ParseCMP(comp, &len, stop);
*/
        comp += GetLength(comp, &len, stop, ITS_TRUE);
        if (comp == tmp)
        {
            if (cseq)
            {
                free_ITU__TCAP_ComponentPortion(cseq);
            }

            return (ITS_EPROTERR);
        }

        pe = ssdu2pe((char *)data, len + (comp - data), NULL, &err);
        if (err != PS_ERR_NONE)
        {
            if (cseq)
            {
                free_ITU__TCAP_ComponentPortion(cseq);
            }

            return (ITS_EPROTERR);
        }

        c = (struct type_ITU__TCAP_ComponentPortion *)
                calloc(1, sizeof(struct type_ITU__TCAP_ComponentPortion));

        if (!c)
        {
            if (cseq)
            {
                free_ITU__TCAP_ComponentPortion(cseq);
            }

            return (ITS_EPROTERR);
        }

        if (decode_ITU__TCAP_ComponentPDU(pe, 1, NULL, NULL,
                                          (char **)&c->ComponentPDU) != OK)
        {

            switch (tag)
            {
            case TCPPT_TC_INVOKE:
            case TCPPT_TC_RESULT_L:
            case TCPPT_TC_RESULT_NL:
            case TCPPT_TC_U_ERROR:
                if (*comp == TCAP_PN_INVOKE_TAG_CCITT &&
                    (*(comp+1) > 0 && *(comp+1) <= 4))
                {
                    c->ComponentPDU = GenerateReject(ITS_TRUE,
                                                     comp, stop);
                }
                else
                {
                    c->ComponentPDU = GenerateReject(ITS_FALSE,
                                                     NULL, NULL);
                }

                if (!c->ComponentPDU)
                {
                    if (cseq)
                    {
                        free_ITU__TCAP_ComponentPortion(cseq);
                    }

                    return (ITS_EPROTERR);
                }
                break;

            case TCPPT_TC_R_REJECT:
                break;

            default:
                if (cseq)
                {
                    free_ITU__TCAP_ComponentPortion(cseq);
                }

                return (ITS_EPROTERR);
            }
        }

        for (list = &cseq; *list != NULL; list = &(*list)->next)
        {
        }

        *list = c;

        data = comp + len;
    }

    switch (pdu->offset)
    {
    case type_ITU__TCAP_MessageType_unidirectional:
        pdu->un.unidirectional->components = cseq;
        break;

    case type_ITU__TCAP_MessageType_begin:
        pdu->un.begin->components = cseq;
        break;

    case type_ITU__TCAP_MessageType_contin:
        pdu->un.contin->components = cseq;
        break;

    case type_ITU__TCAP_MessageType_end:
        pdu->un.end->components = cseq;
        break;

    default:
        if (cseq)
        {
            free_ITU__TCAP_ComponentPortion(cseq);
        }
        break;
    }

    return (ITS_SUCCESS);
}

/*.implementation:static
 ****************************************************************************
 *  Purpose:
 *      None.
 *
 *  Input Parameters:
 *      None.
 *
 *  Input/Output Parameters:
 *      None.
 *
 *  Output Parameters:
 *      None.
 *
 *  Return Value:
 ****************************************************************************/
struct type_ITU__TCAP_MessageType *
CCITT_DecodeTCAPData(ITS_OCTET *data, ITS_USHORT len)
{
    PE pe = NULL;
    struct type_ITU__TCAP_MessageType *pdu = NULL;
    int err = PS_ERR_NONE;
    enum ParseCode pc = PC_PARSE_OK;

    pe = ssdu2pe((char *)data, len, NULL, &err);
    if (err != PS_ERR_NONE)
    {
        TCAP_ERROR(("CCITT_DecodeTCAPData: decode failed.\n"));

        return (NULL);
    }

    if (decode_ITU__TCAP_MessageType(pe, 1, NULL, NULL, (char **)&pdu) == OK)
    {
        TCAP_DEBUG(("CCITT_DecodeTCAPData: Package decode successful.\n"));
    }
    else
    {
        ITS_OCTET *tp = NULL, *dp = NULL, *cp = NULL;

        pe_free(pe);

        TCAP_DEBUG(("CCITT_DecodeTCAPData: PE decode failed.  "
                    "Trying partial decode.\n"));

        pc = FindParts(data, len, &tp, &dp, &cp);

        if (pc != PC_PARSE_OK)
        {
            TCAP_ERROR(("CCITT_DecodeTCAPData: parser failure.\n"));

            return (NULL);
        }

        if (ParseTRP(&pdu, tp, len) != ITS_SUCCESS)
        {
            TCAP_ERROR(("CCITT_DecodeTCAPData: TRP parser failure.\n"));

            return (NULL);
        }

        if (ParseDLG(pdu, dp, tp + len) != ITS_SUCCESS)
        {
            TCAP_ERROR(("CCITT_DecodeTCAPData: DLG parser failure.\n"));

            free_ITU__TCAP_MessageType(pdu);

            return (NULL);
        }

        if (ParseCMP(pdu, cp, tp + len) != ITS_SUCCESS)
        {
            TCAP_ERROR(("CCITT_DecodeTCAPData: DLG parser failure.\n"));

            free_ITU__TCAP_MessageType(pdu);

            return (NULL);
        }

        return (pdu);
    }

    pe_free(pe);

    return (pdu);
}


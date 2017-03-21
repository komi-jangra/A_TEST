/****************************************************************************/
/*                                                                          */
/*      Copyright (C) 1992-2003 by TeleSoft International, Inc.             */
/*                                                                          */
/*      These computer program listings and specifications,                 */
/*      herein, are the property of TeleSoft International, Inc.            */
/*      and shall not be reproduced or copied or used in whole or in        */
/*      part without written permission from TeleSoft International, Inc.   */
/*                                                                          */
/****************************************************************************/
#if !defined(__L3_L2_H_)
#define __L3_L2_H_

/* Layer 2 to Layer 3 (L2 to L3) Mailbox Codes          */

#define DL_EST_IN     20     /* DL_ESTABLISH_INDICATION */
#define DL_REL_IN     21     /* DL_RELEASE_INDICATION   */
#define DL_U_DA_IN    22     /* DL_UNIT_DATA_INDICATION */
#define DL_DA_IN      23     /* DL_DATA_INDICATION      */
#define DL_EST_CF     24     /* DL_ESTABLISH_CONFIRM    */
#define DL_REL_CF     25     /* DL_RELEASE_CONFIRM      */
#define DL_SWITCHOVER_IN   26     /* DL_SWITCHOVER_INDICATION */

/* Layer 3 to Layer 2 (L3 to L2) Mailbox Codes                      */

#define DL_DA_RQ        13  /*
                             *  To pass layer 3 messages to and from the
                             *  data link data link layer which are to be
                             *  transmitted, or have been received, using
                             *  unacknowledged operation.
                             */
#define DL_EST_RQ       14  /*
                             *  To request the outcome of the procedures
                             *  for establishing multiple frame operation.
                             */
#define DL_REL_RQ       15  /*
                             *  To request the  terminating a previously
                             *  established multiple frame operation session.
                             *  In the case of a data link layer malfunction,
                             *  layer 3 will be notified by a RELEASE
                             *  indication.
                             */
#define DL_U_DA_RQ      16  /*
                             *  To pass L3 messages to the data link layer
                             *  which are to be transmitted using
                             *  unacknowledged operation.
                             */
#define DL_ST_RQ        17  /* FLOW ON/OFF */

#define BACKUP_D_STATE_CHANGE 0x14 /* PRI BACKUP D-Ch State Change */

union l2l3_prms
{
    /*
     *  Note that these structures are not quite identical in format to
     *  that of the L2_L3 mbox format.  Specifically, a receipt code member
     *  is missing.  This is not important, because all information
     *  necessary to create a mbox message to/from L2 IS present.
     */
    struct
    {
        unsigned char primcode;
        unsigned char parms[13];
    } generic;
    /* Note that the first three members of each union struct are
     * primcode, sapi, and ces -- this order must be preserved due to
     * the way that the code uses this union. For example, the dl_da_in
     * template is used to access the ces member in some situations for
     * other union structs such as dl_est_in
     */
    struct
    {
        unsigned char primcode;
        unsigned char sapi;
        unsigned char ces;
        unsigned char temp1; /* to preserve alignment */
    } dl_est_rq;
    struct
    {
        unsigned char primcode;
        unsigned char sapi;
        unsigned char ces;
        unsigned char temp1; /* to preserve alignment */
    } dl_rel_rq;
    struct
    {
        unsigned char primcode;
        unsigned char sapi;
        unsigned char ces;
        unsigned char temp1; /* to preserve alignment */
        unsigned char *address;
        unsigned short length;
        unsigned short refnum;
    } dl_da_rq;
    struct
    {
        unsigned char primcode;
        unsigned char sapi;
        unsigned char ces;
        unsigned char temp1; /* to preserve alignment */
        unsigned char *address;
        unsigned short length;
        unsigned short refnum;
    } dl_u_da_rq;
    struct
    {
        unsigned char primcode;
        unsigned char sapi;
        unsigned char ces;
        unsigned char rq_type;
        unsigned char state;
    } dl_st_rq;
    struct
    {
        unsigned char primcode;
        unsigned char sapi;
        unsigned char ces;
        unsigned char temp1; /* to preserve alignment */
    } dl_est_in;
    struct
    {
        unsigned char primcode;
        unsigned char sapi;
        unsigned char ces;
        unsigned char temp1; /* to preserve alignment */
    } dl_rel_in;
    struct
    {
        unsigned char primcode;
        unsigned char sapi;
        unsigned char ces;
        unsigned char temp1; /* to preserve alignment */
        unsigned char *address;
        unsigned short length;
        unsigned short refnum;
    } dl_u_da_in;
    struct
    {
        unsigned char primcode;
        unsigned char sapi;
        unsigned char ces;
        unsigned char temp1; /* to preserve alignment */
        unsigned char *address;
        unsigned short length;
        unsigned short refnum;
    } dl_da_in;
    struct
    {
        unsigned char primcode;
        unsigned char sapi;
        unsigned char ces;
        unsigned char temp1; /* to preserve alignment */
    } dl_est_cf;
    struct
    {
        unsigned char primcode;
        unsigned char sapi;
        unsigned char ces;
        unsigned char temp1; /* to preserve alignment */
    } dl_rel_cf;
    struct
    {
        unsigned char primcode;
        unsigned char sapi;
        unsigned char ces;
        unsigned char temp1; /* to preserve alignment */
    } dl_switchover_in;
};

struct l2_l3
{
    long reserved1;  /* PSOS "header" to message.                    */
    long reserved2;
    unsigned short pchan;
    union l2l3_prms l2l3_parms;
}; /* Currently 24 bytes long */

#endif  /* end of if !defined(__L3_L2_H_) */

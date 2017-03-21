/*
 * Message buffer definitions
 *
 * Copyright 2000, Hughes Software Systems, Ltd.
 */

#ifndef _SL_MSG_H_
#define _SL_MSG_H_

struct sl_msg {
    unsigned char   type;
    unsigned char   ref;

    unsigned short  size;

    struct sl_msg   *next;

    unsigned char   *data;
    unsigned char   *edata;

    unsigned char   base[32];
};
typedef struct sl_msg sl_msg_t;

sl_msg_t *sl_msg_alloc (unsigned int size);
void sl_msg_free (sl_msg_t *msg);

#endif /* ifndef _SL_MSG_H_ */

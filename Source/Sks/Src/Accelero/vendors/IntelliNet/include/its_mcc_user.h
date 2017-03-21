#ifndef _ITS_MCC_USER_H
#define _ITS_MCC_USER_H

#ifdef linux

#include <linux/ioctl.h>

#define MCC_IOC_MAGIC 252  /* Same as device number as of now */

#define MCC_IOCRESET      _IO(MCC_IOC_MAGIC, 0)

#define MCC_IOCSCONFIG    _IOW(MCC_IOC_MAGIC, 1, int)

#define MCC_IOCENABLE     _IO(MCC_IOC_MAGIC, 2)
#define MCC_IOCDISABLE    _IO(MCC_IOC_MAGIC, 3)
#define MCC_IOCTSEND      _IO(MCC_IOC_MAGIC, 4)
#define MCC_IOCTDUMP      _IO(MCC_IOC_MAGIC, 5)

/* LAPD Specific configurations */
#define LAPD_IOCSCUPPARMS _IOW(MCC_IOC_MAGIC, 6, int) 
#define LAPD_IOCGIFCNUM   _IOWR(MCC_IOC_MAGIC, 7, int)

/*
 * struct for configuration
 */
struct mcc_cfg
{
    unsigned int num_chan;
    struct mcc_channel
    {
        unsigned char  chan;  /* Which channel index.             */
        unsigned char  mode; /* For superchannel.  Not used here */
        unsigned char  type; /* Channel type.  Here always SS7   */
        unsigned char  loop;  /* Loopback or not (simple boolean) */
    }
    channels[1];   /* At least 1.  Up to 32            */
};

/*
 * Things we need to know.
 */
#define MCC_MAJOR        252  /* Device major.  MAX_LINKS minors   */
#define MCC_CTL_MINOR    252  /* Misc major, this is the minor     */

#define MTP2_MAX_LINKS    32   /* Maximum number of links per board */

/* Temporarily keep them here */
#define MCC_TYPE_SS7     0
#define MCC_TYPE_HDLC    1
#define MCC_TYPE_TRANS   2
#define MCC_TYPE_LAPD    3

#endif

#endif


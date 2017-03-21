
#ifdef TMCC

#include <fcntl.h>
#include <tslink3.h>
#include <its_mcc_user.h>

int MCC_Get_Interface(int fd, int *mcc)
{
    return ioctl(fd, LAPD_IOCGIFCNUM, mcc);
}

int MCC_Load_Cup_Param(int fd, struct req_data_xfer *reqdataxfer)
{
    return ioctl(fd, LAPD_IOCSCUPPARMS, reqdataxfer);
}

void MCC_Close(int fd)
{
    close(fd);
}


#endif // TMCC

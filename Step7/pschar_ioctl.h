#include <asm/ioctl.h>

struct pschar_stat
{
    int len;
    int avail;
};

#define IOC_MAGIC                   'p'
#define PSCHAR_IOCTL_LEN            _IO(IOC_MAGIC, 1)
#define PSCHAR_IOCTL_AVAIL          _IO(IOC_MAGIC, 2)
#define PSCHAR_IOCTL_RESET          _IO(IOC_MAGIC, 3)
#define PSCHAR_IOCTL_PSTAT          _IOR(IOC_MAGIC, 4, struct pschar_stat)

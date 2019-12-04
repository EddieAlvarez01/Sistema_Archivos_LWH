#ifndef MBR_H
#define MBR_H

#include <string.h>
#include "partition.h"


class Mbr
{
public:
    Mbr();
    int mbr_size;
    char dateTime [50];
    int mbr_disk_aignature;
    char disk_fit [10];
    Partition particions[4];
    char id [8];
};

#endif // MBR_H

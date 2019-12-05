#ifndef PARTITION_H
#define PARTITION_H

#include <string.h>

class Partition
{
public:
    Partition();
    char part_status;
    char part_type;
    char part_fit [3];
    int part_start;
    int part_size;
    char part_name [16];
    char id [8];
};

#endif // PARTITION_H

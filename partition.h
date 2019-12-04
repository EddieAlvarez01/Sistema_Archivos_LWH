#ifndef PARTITION_H
#define PARTITION_H

#include <string.h>

class Partition
{
public:
    Partition();
    int part_status;
    char part_type [5];
    char part_fit [5];
    int part_start;
    int part_size;
    char part_name [30];
    char id [8];
};

#endif // PARTITION_H

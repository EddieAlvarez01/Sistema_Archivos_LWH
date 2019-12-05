#include "partition.h"

Partition::Partition()
{

    part_status = 48;
    strcpy(part_fit, "");
    part_start = -1;
    part_size = 0;
    strcpy(part_name, "");
    strcpy(id, "");

}

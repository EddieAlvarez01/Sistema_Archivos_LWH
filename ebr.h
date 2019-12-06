#ifndef EBR_H
#define EBR_H

#include <string.h>

class Ebr
{
public:
    Ebr();
    char part_status;
    char part_fit [5];
    int part_start;
    int part_size;
    int part_next;
    char part_name [30];
    char isLogic;
};

#endif // EBR_H

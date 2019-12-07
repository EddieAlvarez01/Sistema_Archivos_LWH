#include "ebr.h"

Ebr::Ebr()
{

    part_status = 48;
    strcpy(part_fit, "");
    part_start = -1;
    part_size = -1;
    part_next = 0;
    strcpy(part_name, "");
    isLogic = 48;
    strcpy(id, "");

}

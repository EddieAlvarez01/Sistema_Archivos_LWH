#ifndef INODE_H
#define INODE_H

#include "datablock.h"

class Inode
{
public:
    Inode();
    int i_count_inodo;
    int i_size_archivo;
    int i_count_bloques_asignados;
    int i_array_bloques [4];
    int i_ap_indirecto;
    int i_id_proper;
    int i_perm;
};

#endif // INODE_H

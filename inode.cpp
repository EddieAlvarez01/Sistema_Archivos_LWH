#include "inode.h"

Inode::Inode()
{
    i_count_inodo = -1;
    i_size_archivo = -1;
    i_count_bloques_asignados = -1;
    i_ap_indirecto = -1;
    i_id_proper = -1;
}

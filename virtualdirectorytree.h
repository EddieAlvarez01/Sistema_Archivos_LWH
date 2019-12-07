#ifndef VIRTUALDIRECTORYTREE_H
#define VIRTUALDIRECTORYTREE_H

#include <string.h>

class VirtualDirectoryTree
{
public:
    VirtualDirectoryTree();
    char avd_fecha_creacion [20];
    char avd_nombre_directorio [20];
    int avd_ap_array_subdirectorios [6];
    int avd_ap_detalle_directorio;
    int avd_ap_arbol_virtual_directorio;
    int avd_proper;
    int i_perm;
};

#endif // VIRTUALDIRECTORYTREE_H

#include "virtualdirectorytree.h"

VirtualDirectoryTree::VirtualDirectoryTree()
{
    strcpy(avd_fecha_creacion, "");
    strcpy(avd_nombre_directorio, "");
    for(int i=0; i<6; i++){
        avd_ap_array_subdirectorios[i] = -1;
    }
    avd_ap_detalle_directorio = -1;
    avd_ap_arbol_virtual_directorio = -1;
    avd_proper = -1;
}

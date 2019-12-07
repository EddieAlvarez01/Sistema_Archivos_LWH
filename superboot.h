#ifndef SUPERBOOT_H
#define SUPERBOOT_H


class SuperBoot
{
public:
    SuperBoot();
    char sd_nombre_hd [12];
    int sb_arbol_virtual_count;
    int sb_detalle_directorio_count;
    int sb_inodos_count;
    int sb_bloques_count;
    int sb_arbol_virtual_free;
    int sb_detalle_directorio_free;
    int sb_inodos_free;
    int sb_bloques_free;
    char sb_date_creacion [20];
    char sb_date_ultimo_montaje [20];
    int sb_montajes_count;
    int sb_ap_bitmap_arbol_directorio;
    int sb_ap_arbol_directorio;
    int sb_ap_bitmap_detalle_directorio;
    int sb_ap_detalle_directorio;
    int sb_ap_bitmap_tabla_inodo;
    int sb_ap_tabla_inodo;
    int sb_ap_bitmap_bloques;
    int sb_ap_bloques;
    int sb_ap_log;
    int sb_size_struct_arbol_directorio;
    int sb_size_struct_detalle_directorio;
    int sb_size_struct_inodo;
    int sb_size_struct_bloque;
    int sb_first_free_bit_arbol_directorio;
    int sb_first_free_bit_detalle_directorio;
    int sb_first_free_bit_tabla_inodo;
    int sb_first_free_bit_bloques;
    int sb_magic_num;
};

#endif // SUPERBOOT_H

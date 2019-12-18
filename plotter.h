#ifndef PLOTTER_H
#define PLOTTER_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <queue>
#include "mbr.h"
#include "ebr.h"
#include "log.h"
#include "superboot.h"
#include "virtualdirectorytree.h"
#include "directorydetail.h"
#include "inode.h"
#include "contentdetail.h"
#include "datablock.h"

class Plotter
{
public:
    Plotter();
    void Plot_Mbr(FILE *file, Mbr mbr, std::string nameDisk, std::string path);
    void Plot_Disk(FILE *file, Mbr mbr, std::string path, int space);
    std::string Ebr_Recursive(FILE *file, Ebr logic, std::string textBody, char nodeName, int countEbr);  //Metodo para escribir cada tabla de Ebr (partciones logicas)
    std::string Ebr_REcursive_Disk(FILE *file, Ebr logic, std::string txtBody, int totalSize, int freeExtended); //METODO para escribir las logicas en el reporte disk
    void Plot_BmAvd(FILE *file, int startBm, int endBm, std::string path);
    void Plot_Log(FILE *file, int startLog, int endLog, std::string path);
    void Plot_Directory(FILE *file, SuperBoot sb, std::string path);
    std::string Directory_Tour(FILE *file, SuperBoot sb, VirtualDirectoryTree root, std::string, int posAvd);
    std::string Pointer_Travel(FILE *file, SuperBoot sb, VirtualDirectoryTree root, std::string, int posAvd);
    void Plot_Tree_File(FILE *file, SuperBoot sb, std::string folder, std::queue<std::string> route, std::string path);    //Graficador de Inodo de archivo con sus bloques
    VirtualDirectoryTree SearchAvd(FILE *file, SuperBoot sb, VirtualDirectoryTree root, std::string folder, std::queue<std::string> route, VirtualDirectoryTree searchNode);
    ContentDetail searchContent(FILE *file, SuperBoot sb, DirectoryDetail dd, int count, int selection, ContentDetail cD); // Regresa datos para la graficacion del inodo
    void Print_Files(FILE *file, SuperBoot sb, DirectoryDetail dd, int count); //Imprime los archivos de &ruta (solo los exteriores no subdirectorios)
    std::string Txt_Inode(FILE *file, SuperBoot sb, Inode in, std::string txt, int posInodo); //Crea los nodos en graphviz para los 'n' inodos
    std::string Txt_Block(FILE *file, SuperBoot sb, Inode in, std::string txt); //Crea los nodos de los bloques
    std::string Node_Relationsip_Inodes(FILE *file, SuperBoot sb, Inode in, int posInodo, std::string txt); //Crea los enlaces de los bloques con inodos e inodos indirectos
    std::string RetirveTextBlock(DataBlock db); //Devuelve el texto de un bloque sin el char '\0'
    void Plot_Sb(SuperBoot sb, FILE *file, std::string path); //Genera la tabla de superboot de la particion
    int FreeBitmap(FILE *file, int startBm, int endBm); //Devuelve el bit del primer bit libre en el bitmap
};

#endif // PLOTTER_H

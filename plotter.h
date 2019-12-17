#ifndef PLOTTER_H
#define PLOTTER_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "mbr.h"
#include "ebr.h"
#include "log.h"
#include "superboot.h"
#include "virtualdirectorytree.h"

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
};

#endif // PLOTTER_H

#ifndef PLOTTER_H
#define PLOTTER_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "mbr.h"
#include "ebr.h"

class Plotter
{
public:
    Plotter();
    void Plot_Mbr(FILE *file, Mbr mbr, std::string nameDisk, std::string path);
    void Plot_Disk(Mbr mbr, std::string path, int space);
    std::string Ebr_Recursive(FILE *file, Ebr logic, std::string textBody, char nodeName, int countEbr);  //Metodo para escribir cada tabla de Ebr (partciones logicas)
};

#endif // PLOTTER_H

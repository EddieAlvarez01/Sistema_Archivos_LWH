#ifndef PLOTTER_H
#define PLOTTER_H

#include <string>
#include <fstream>
#include <iostream>
#include "mbr.h"

class Plotter
{
public:
    Plotter();
    void Plot_Mbr(Mbr mbr, std::string nameDisk, std::string path);
    void Plot_Disk(Mbr mbr, std::string path, int space);
};

#endif // PLOTTER_H

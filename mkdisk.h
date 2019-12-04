#ifndef MKDISK_H
#define MKDISK_H

#include <string>
#include "command.h"

class Mkdisk: public Command
{
public:
    int size;
    std::string fit;
    std::string unit;
    std::string path;
    Mkdisk();
};

#endif // MKDISK_H

#ifndef FDISK_H
#define FDISK_H

#include <string>
#include "command.h"

class Fdisk: public Command
{
public:
    int size;
    std::string unit;
    std::string path;
    std::string type;
    std::string fit;
    std::string toDelete;
    std::string name;
    std::string allocation;
    bool isAdd;
    int add;
    Fdisk();
};

#endif // FDISK_H

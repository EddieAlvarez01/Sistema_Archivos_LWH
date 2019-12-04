#ifndef RMDISK_H
#define RMDISK_H

#include <string>
#include "command.h"

class Rmdisk: public Command
{
public:
    std::string path;
    Rmdisk();
};

#endif // RMDISK_H

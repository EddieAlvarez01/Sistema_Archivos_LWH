#ifndef MKFS_H
#define MKFS_H

#include "command.h"
#include <string>

class Mkfs : public Command
{
public:
    Mkfs();
    std::string id;
    std::string type;
    int add;
    bool isAdd;
    std::string unit;
};

#endif // MKFS_H

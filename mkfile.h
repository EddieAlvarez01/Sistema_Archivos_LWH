#ifndef MKFILE_H
#define MKFILE_H

#include "string"
#include "command.h"

class Mkfile : public Command
{
public:
    Mkfile();
    std::string path;
    bool isP;
    int size;
    std::string cont;
};

#endif // MKFILE_H

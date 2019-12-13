#ifndef MKDIR_H
#define MKDIR_H

#include <string>
#include "command.h"

class Mkdir : public Command
{
public:
    Mkdir();
    std::string path;
    std::string id;
    bool isP;
};

#endif // MKDIR_H

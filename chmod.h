#ifndef CHMOD_H
#define CHMOD_H

#include "command.h"
#include <string>

class Chmod : public Command
{
public:
    Chmod();
    std::string path;
    int ugo;
    bool isRecursive;
};

#endif // CHMOD_H

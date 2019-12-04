#ifndef MKUSR_H
#define MKUSR_H

#include "command.h"
#include <string>

class Mkusr : public Command
{
public:
    Mkusr();
    std::string usr;
    std::string pwd;
    std::string grp;
};

#endif // MKUSR_H

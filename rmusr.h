#ifndef RMUSR_H
#define RMUSR_H

#include "command.h"
#include <string>

class Rmusr : public Command
{
public:
    Rmusr();
    std::string usr;
};

#endif // RMUSR_H

#ifndef RECOVERY_H
#define RECOVERY_H

#include <string>
#include "command.h"

class Recovery : public Command
{
public:
    Recovery();
    std::string id;
};

#endif // RECOVERY_H

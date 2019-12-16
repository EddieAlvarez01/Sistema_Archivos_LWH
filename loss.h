#ifndef LOSS_H
#define LOSS_H

#include <string>
#include "command.h"

class Loss : public Command
{
public:
    Loss();
    std::string id;
};

#endif // LOSS_H

#ifndef RMGRP_H
#define RMGRP_H

#include "command.h"
#include <string>

class Rmgrp : public Command
{
public:
    Rmgrp();
    std::string name;
};

#endif // RMGRP_H

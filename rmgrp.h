#ifndef RMGRP_H
#define RMGRP_H

#include "command.h"
#include <string>

class Rmgrp : public Command
{
public:
    Rmgrp();
    std::string name;
    std::string id;
};

#endif // RMGRP_H

#ifndef MKGRP_H
#define MKGRP_H

#include "command.h"
#include <string>

class Mkgrp : public Command
{
public:
    Mkgrp();
    std::string id;
    std::string name;
};

#endif // MKGRP_H

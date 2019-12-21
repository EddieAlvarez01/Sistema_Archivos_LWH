#ifndef REN_H
#define REN_H

#include<string>
#include "command.h"

class Ren : public Command
{
public:
    Ren();
    std::string id;
    std::string path;
    std::string name;
};

#endif // REN_H

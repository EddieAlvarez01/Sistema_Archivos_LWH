#ifndef REP_H
#define REP_H

#include <string>
#include "command.h"

class Rep: public Command
{
public:
    std::string name;
    std::string path;
    std::string id;
    std::string route;
    Rep();
};

#endif // REP_H

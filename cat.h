#ifndef CAT_H
#define CAT_H

#include <string>
#include <list>
#include "command.h"

class Cat : public Command
{
public:
    Cat();
    std::string id;
    std::list <std::string> file;
};

#endif // CAT_H

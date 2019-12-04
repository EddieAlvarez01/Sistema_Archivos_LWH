#ifndef UNMOUNT_H
#define UNMOUNT_H

#include <string>
#include "command.h"

class Unmount: public Command
{
public:
    std::string id;
    Unmount();
};

#endif // UNMOUNT_H

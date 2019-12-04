#ifndef MOUNT_H
#define MOUNT_H


#include <string>
#include "command.h"

class Mount: public Command
{
public:
    std::string path;
    std::string name;
    Mount();
};

#endif // MOUNT_H

#ifndef EXEC_H
#define EXEC_H

#include <string>
#include "command.h"

class Exec : public Command
{
public:
    std::string path;
    Exec();
};

#endif // EXEC_H

#ifndef LOGIN_H
#define LOGIN_H

#include <string>
#include "command.h"

class Login : public Command
{
public:
    Login();
    std::string usr;
    std::string pwd;
    std::string id;
};

#endif // LOGIN_H

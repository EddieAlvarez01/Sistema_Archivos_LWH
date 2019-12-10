#ifndef USER_H
#define USER_H

#include <string>
#include "nodelist.h"

class User
{
public:
    User();
    std::string user;
    std::string id;
    std::string group;
    std::string idGroup;
    bool isSession;
    NodeList *partition;
    std::string idPartition;
};

#endif // USER_H

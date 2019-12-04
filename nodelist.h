#ifndef NODELIST_H
#define NODELIST_H

#include "partition.h"
#include <string>


class NodeList
{
public:
    NodeList(Partition _data);
    Partition data;
    int format;
    std::string disk;
    std::string date;
    NodeList *next;
};

#endif // NODELIST_H

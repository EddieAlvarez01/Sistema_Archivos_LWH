#ifndef NODELIST_H
#define NODELIST_H

#include "partition.h"
#include "ebr.h"
#include <string>


class NodeList
{
public:
    NodeList(Partition _data);
    NodeList(Ebr _data);
    Partition data;
    Ebr data2;
    int format;
    std::string disk;
    std::string date;
    NodeList *next;
    int type;
};

#endif // NODELIST_H

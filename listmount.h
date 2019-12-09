#ifndef LISTMOUNT_H
#define LISTMOUNT_H

#include "nodelist.h"
#include <iostream>

class ListMount
{
public:
    ListMount();
    NodeList *first;
    void insert(NodeList *);
    void unMount(std::string idDisk);
    std::string To_Report(std::string idDisk);
    bool isMount(std::string id);
    bool isMountByName(std::string name);
    void FormatPartition(std::string id);
    void List_Mount();
    NodeList *SearchNode(std::string id);
};

#endif // LISTMOUNT_H

#include "nodelist.h"

NodeList::NodeList(Partition _data)
{

    data = _data;
    next = nullptr;
    disk = "";
    format = 0;
    type = 0;

}

NodeList::NodeList(Ebr _data){

    data2 = _data;
    next = nullptr;
    disk = "";
    format = 0;
    type = 1;

}

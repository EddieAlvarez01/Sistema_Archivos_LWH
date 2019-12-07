#ifndef CONTENTDETAIL_H
#define CONTENTDETAIL_H

#include <string.h>

class ContentDetail
{
public:
    ContentDetail();
    char dd_file_nombre [20];
    int dd_file_app_inodo;
    char dd_file_date_creacion [20];
    char dd_file_date_modificacion [20];
};

#endif // CONTENTDETAIL_H

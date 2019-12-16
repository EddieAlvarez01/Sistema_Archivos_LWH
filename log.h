#ifndef LOG_H
#define LOG_H

#include <string.h>

class Log
{
public:
    Log();
    int log_tipo_operacion;  /*  1. creacion de carpeta,  2. creacion de archivo */
    char log_tipo;
    char op[80];
    bool isP = false;
    char log_nombre [20];
    char log_contenido [150];
    char log_fecha [20];
};

#endif // LOG_H

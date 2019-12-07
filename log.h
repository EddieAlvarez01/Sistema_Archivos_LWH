#ifndef LOG_H
#define LOG_H


class Log
{
public:
    Log();
    int log_tipo_operacion;
    char log_tipo;
    char log_nombre [20];
    char log_contenido [100];
    char log_fecha [20];
};

#endif // LOG_H

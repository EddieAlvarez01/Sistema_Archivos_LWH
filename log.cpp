#include "log.h"

Log::Log()
{
    log_tipo_operacion = 0;
    log_tipo = 48;
    strcpy(log_nombre, "");
    strcpy(log_contenido, "");
    strcpy(log_fecha, "");
    strcpy(op, "");
}

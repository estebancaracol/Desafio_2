#ifndef SIMULACIONVENTAS_H
#define SIMULACIONVENTAS_H

#include "funcionesapoyo.h"


class gestionRed;

class simulacionVentas
{
public:
    simulacionVentas();
    int simularVenta(funcionesApoyo &fa, gestionRed &gr);
    void verificarFugas(funcionesApoyo &fa);
};

#endif // SIMULACIONVENTAS_H

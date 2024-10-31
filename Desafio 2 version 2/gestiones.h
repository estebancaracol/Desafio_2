#ifndef GESTIONES_H
#define GESTIONES_H

#include "funcionesapoyo.h"


class GestionES
{
public:
    GestionES();
    void agregarSurtidor(funcionesApoyo &fa);
    void eliminarSurtidor(funcionesApoyo &fa);
    void cambiarEstado(funcionesApoyo &fa);
    void consultarHistoricoTransacciones(funcionesApoyo &fa);
    void ReporteCombustibleVendido(funcionesApoyo &fa);
    int ventaCombustible(funcionesApoyo &fa);
};

#endif // GESTIONES_H

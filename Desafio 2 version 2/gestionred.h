#ifndef GESTIONRED_H
#define GESTIONRED_H

#include "funcionesapoyo.h" // Para usar las estructuras de estaciones, islas y transacciones
#include "simulacionventas.h"
#include <iostream>
#include <string>

using namespace std;

class gestionRed {
public:
    gestionRed();
    void agregarEstacion(funcionesApoyo &fa);
    void eliminarEstacion(funcionesApoyo &fa);
    void fijarPreciosCombustible(double precioNorte[3], double precioSur[3], double precioCentro[3]);
    void calcularVentasPorEstacion(funcionesApoyo &fa);
    void fijarPreciosCombustible(funcionesApoyo &fa);

    friend class simulacionVentas;
};

#endif // GESTIONRED_H


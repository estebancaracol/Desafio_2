#ifndef GESTIONRED_H
#define GESTIONRED_H

#include "funcionesapoyo.h" // Para usar las estructuras de estaciones, islas y transacciones
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
private:
    funcionesApoyo datos; // Usamos la clase que tiene los datos leídos del archivo
    double precioCombustibleNorte[3];
    double precioCombustibleSur[3];
    double precioCombustibleCentro[3];

    double sumarMontosPorCategoria(const string &idEstacion, const string &categoria);
};

#endif // GESTIONRED_H

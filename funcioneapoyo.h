#ifndef FUNCIONESAPOYO_H
#define FUNCIONESAPOYO_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class funcionesApoyo {
public:
    funcionesApoyo();
    void leerArchivo(const std::string &archivo);
    void mostrarDatos();
    bool ingresarComoAdmin();
    void mostrarMenu();

    friend class gestionRed;

private:
    string estaciones[100][8];     // Para almacenar estaciones
    string islas[100][6];          // Para almacenar islas
    string transacciones[100][8];  // Para almacenar transacciones
    int totalEstaciones, totalIslas, totalTransacciones;

    void procesarEstaciones(const string &linea);
    void procesarIslas(const string &linea);
    void procesarTransacciones(const string &linea);
};

#endif // FUNCIONESAPOYO_H

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
    void leerArchivo(const string &archivo);
    void mostrarDatos();
    bool ingresarComoAdmin();
    void mostrarMenu();
    string generarCodigoEstacion();
    string seleccionarRegion();
    string generarCoordenadasGPS();
    int generarCantidadCombustible();
    void agregarEstacion(const string &codigo, const string &nombre, const string &gerente, const string &codigoGerente, const string &region, const string &coordenadasGPS, int regular, int premium, int ecoextra);
    void guardarDatos(const string &nombreArchivo);
    void transferirNuevaEstacion();
    int contarGerentes(const string& nombreArchivo);
    int leerGerentes(const string& nombreArchivo, string*& codigos, string*& nombres, int totalGerentes);
    int seleccionarGerente(string* codigos, string* nombres, int totalGerentes);
    bool identificarEstacion(string &idEstacion);
    bool VersiEstacionesEliminable(string &idEstacion);
    void guardarRespaldo(const string &idEstacion, string estaciones[][9], int totalEstaciones, string islas[][7], int totalIslas, string transacciones[][10], int totalTransacciones);
    double calcularMontoVenta(double litrosVendidos, double precioCombustible);

    static string trim(const string &str);

    friend class gestionRed;

private:
    // Definición de los tamaños máximos de los arreglos
    const static int MAX_ESTACIONES = 100;
    const static int MAX_ISLAS = 100;
    const static int MAX_TRANSACCIONES = 100;
    const static int MAX_COLUMNAS_E = 9; // Máximo número de columnas que tiene el archivo
    const static int MAX_COLUMNAS_I = 7;
    const static int MAX_COLUMNAS_T = 10;

    // Arreglos fijos para agregar los datos que se ingresan
    string newEstacion[MAX_ESTACIONES][MAX_COLUMNAS_E];
    string newIsla[MAX_ISLAS][MAX_COLUMNAS_I];
    string newTransaccion[MAX_TRANSACCIONES][MAX_COLUMNAS_T];

    // Arreglos fijos para almacenar los datos
    string estaciones[MAX_ESTACIONES][MAX_COLUMNAS_E];
    string islas[MAX_ISLAS][MAX_COLUMNAS_I];
    string transacciones[MAX_TRANSACCIONES][MAX_COLUMNAS_T];

    // Contadores para los datos
    int totalEstaciones = 0;
    int totalIslas = 0;
    int totalTransacciones = 0;
    int totalnewEstacion = 0;

    // Métodos de procesamiento
    void procesarEstaciones(const string &linea);
    void procesarIslas(const string &linea);
    void procesarTransacciones(const string &linea);
};

#endif // FUNCIONESAPOYO_H

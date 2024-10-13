#include "funcionesapoyo.h"
#include <iostream>
#include <string>

using namespace std;

funcionesApoyo::funcionesApoyo() : totalEstaciones(0), totalIslas(0), totalTransacciones(0) {}

void funcionesApoyo::leerArchivo(const string &archivo) {
    ifstream archivoEntrada(archivo);
    string linea;
    bool enEstaciones = false, enIslas = false, enTransacciones = false;

    if (archivoEntrada.is_open()) {
        while (getline(archivoEntrada, linea)) {
            if (linea.find('%') != string::npos) {
                enEstaciones = true;
                enIslas = false;
                enTransacciones = false;
            } else if (linea.find('$') != string::npos) {
                enEstaciones = false;
                enIslas = true;
                enTransacciones = false;
            } else if (linea.find('&') != string::npos) {
                enEstaciones = false;
                enIslas = false;
                enTransacciones = true;
            } else if (enEstaciones) {
                procesarEstaciones(linea);
            } else if (enIslas) {
                procesarIslas(linea);
            } else if (enTransacciones) {
                procesarTransacciones(linea);
            }
        }
        archivoEntrada.close();
    } else {
        cerr << "No se pudo abrir el archivo." << endl;
    }
}

void funcionesApoyo::procesarEstaciones(const string &linea) {
    if (linea[0] == '#' || linea.empty()) return;

    stringstream ss(linea);
    string token;
    int columna = 0;

    while (getline(ss, token, '|')) {
        estaciones[totalEstaciones][columna++] = token;
    }
    totalEstaciones++;
}

void funcionesApoyo::procesarIslas(const string &linea) {
    if (linea[0] == '#' || linea.empty()) return;

    stringstream ss(linea);
    string token;
    int columna = 0;

    while (getline(ss, token, '|')) {
        islas[totalIslas][columna++] = token;
    }
    totalIslas++;
}

void funcionesApoyo::procesarTransacciones(const string &linea) {
    if (linea[0] == '#' || linea.empty()) return;

    stringstream ss(linea);
    string token;
    int columna = 0;

    while (getline(ss, token, '|')) {
        transacciones[totalTransacciones][columna++] = token;
    }
    totalTransacciones++;
}

void funcionesApoyo::mostrarDatos() {
    cout << "Estaciones:\n";
    for (int i = 0; i < totalEstaciones; ++i) {
        for (int j = 0; j < 8; ++j) {
            cout << estaciones[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\nIslas:\n";
    for (int i = 0; i < totalIslas; ++i) {
        for (int j = 0; j < 6; ++j) {
            cout << islas[i][j] << " ";
        }
        cout << "\n";
    }

    cout << "\nTransacciones:\n";
    for (int i = 0; i < totalTransacciones; ++i) {
        for (int j = 0; j < 8; ++j) {
            cout << transacciones[i][j] << " ";
        }
        cout << "\n";
    }
}

bool funcionesApoyo::ingresarComoAdmin() {
    string usuario, contrasena;
    cout << "Ingrese su usuario: ";
    cin >> usuario;
    cout << "Ingrese su clave: ";
    cin >> contrasena;

    // Simulación de autenticación
    if (usuario == "admin" && contrasena == "1234") {
        return true;
    } else {
        cout << "Usuario o clave incorrectos." << endl;
        return false;
    }
}

void funcionesApoyo::mostrarMenu() {
    cout << "\nOpciones de gestion de la red:\n";
    cout << "1. Agregar estacion de servicio.\n";
    cout << "2. Eliminar estacion de servicio (si no tiene surtidores activos).\n";
    cout << "3. Calcular monto total de ventas.\n";
    cout << "4. Fijar precios del combustible por region.\n";
    cout << "0. Salir.\n";
    cout << "Seleccione una opcion: ";
}

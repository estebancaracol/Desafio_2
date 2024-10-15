#include "funcionesapoyo.h"
#include "gestionred.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

funcionesApoyo::funcionesApoyo() : totalEstaciones(0), totalIslas(0), totalTransacciones(0), totalnewEstacion(0) {
    totalnewEstacion = 0;
    srand(time(0));
}

string funcionesApoyo::generarCodigoEstacion(){
    stringstream ss;
    ss << setfill('0') << setw(3) << totalEstaciones + 1;
    return ss.str();
}

string funcionesApoyo::seleccionarRegion(){
    int opcion;
    cout << "Seleccione la region:\n";
    cout << "1. Norte\n2. Centro\n3. Sur\n4. Otra\n";
    cin >> opcion;

    switch (opcion) {
    case 1: return "Norte";
    case 2: return "Centro";
    case 3: return "Sur";
    case 4: {
        string regionManual;
        cout << "Ingrese el nombre de la región: ";
        cin.ignore(); // Limpiar buffer
        getline(cin, regionManual);
        return regionManual;
    }
    default:
        cout << "Opcion no valida, se asigna 'Norte' por defecto.\n";
        return "Norte";
    }
}

string funcionesApoyo::generarCoordenadasGPS(){
    double latitud = 4.0 + static_cast<double>(rand()) / RAND_MAX * (5.0 - 4.0);  // Latitud entre 4 y 5
    double longitud = -75.0 + static_cast<double>(rand()) / RAND_MAX * (-74.0 + 75.0); // Longitud entre -75 y -74
    stringstream ss;
    ss << "(" << latitud << "," << longitud << ")";
    return ss.str();
}

int funcionesApoyo::generarCantidadCombustible(){
    return rand() % 101 + 100;
}

double funcionesApoyo::calcularMontoVenta(double litrosVendidos, double precioCombustible){
    return litrosVendidos * precioCombustible;
}

// Función para eliminar espacios en blanco al inicio y al final
string funcionesApoyo::trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return ""; // Cadena vacía si solo hay espacios

    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

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

    while (getline(ss, token, '|') && columna < MAX_COLUMNAS_E) {
        estaciones[totalEstaciones][columna++] = token;
    }
    totalEstaciones++;
}

void funcionesApoyo::procesarIslas(const string &linea) {
    if (linea[0] == '#' || linea.empty()) return;

    stringstream ss(linea);
    string token;
    int columna = 0;

    while (getline(ss, token, '|') && columna < MAX_COLUMNAS_I) {
        islas[totalIslas][columna++] = token;
    }
    totalIslas++;
}

void funcionesApoyo::procesarTransacciones(const string &linea) {
    if (linea[0] == '#' || linea.empty()) return;

    stringstream ss(linea);
    string token;
    int columna = 0;

    while (getline(ss, token, '|') && columna < MAX_COLUMNAS_T) {
        transacciones[totalTransacciones][columna++] = token;
    }
    totalTransacciones++;
}

void funcionesApoyo::mostrarDatos() {
    cout << "Estaciones:\n";
    for (int i = 0; i < totalEstaciones; ++i) {
        for (int j = 0; j < MAX_COLUMNAS_E && !estaciones[i][j].empty(); ++j) {
            cout << estaciones[i][j] << " | ";
        }
        cout << "\n";
    }

    cout << "\nIslas:\n";
    for (int i = 0; i < totalIslas; i++) {
        for (int j = 0; j < MAX_COLUMNAS_I && !islas[i][j].empty(); j++) {
            cout << islas[i][j] << " | ";
        }
        cout << "\n";
    }

    cout << "\nTransacciones:\n";
    for (int i = 0; i < totalTransacciones; i++) {
        for (int j = 0; j < MAX_COLUMNAS_T && !transacciones[i][j].empty(); j++) {
            cout << transacciones[i][j] << " | ";
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

void funcionesApoyo::agregarEstacion(const string &codigo, const string &nombre, const string &codigoGerente, const string &gerente, const string &region, const string &coordenadasGPS, int regular, int premium, int ecoextra){
    // Asignar los valores al arreglo de estaciones
    if (totalnewEstacion < 100){
        newEstacion[totalnewEstacion][0] = codigo;
        newEstacion[totalnewEstacion][1] = nombre;
        newEstacion[totalnewEstacion][2] = codigoGerente;
        newEstacion[totalnewEstacion][3] = gerente;
        newEstacion[totalnewEstacion][4] = region;
        newEstacion[totalnewEstacion][5] = coordenadasGPS;

        // Convertimos las cantidades de combustible a string antes de almacenarlas
        newEstacion[totalnewEstacion][6] = to_string(regular);
        newEstacion[totalnewEstacion][7] = to_string(premium);
        newEstacion[totalnewEstacion][8] = to_string(ecoextra);

        // Incrementar el total de nuevas estaciones
        totalnewEstacion++;
    } else {
        cout << "Error: No se pueden agregar mas estaciones, limite alcanzado.";
    }

    // Después de agregar una estación, transferirla al arreglo estaciones
    transferirNuevaEstacion();
}

// Función para contar cuántos gerentes hay en el archivo
int funcionesApoyo::contarGerentes(const string& nombreArchivo) {
    ifstream archivoEntrada(nombreArchivo);
    string linea;
    int contador = 0;

    if (!archivoEntrada.is_open()) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return 0;
    }

    // Contar el número de líneas en el archivo
    while (getline(archivoEntrada, linea)) {
        if (!linea.empty()) {
            contador++;
        }
    }

    archivoEntrada.close();
    return contador;
}

// Función para leer los gerentes desde un archivo en arreglos dinámicos
int funcionesApoyo::leerGerentes(const string& nombreArchivo, string*& codigos, string*& nombres, int totalGerentes) {
    ifstream archivoEntrada(nombreArchivo);
    string linea;
    int contador = 0;

    if (!archivoEntrada.is_open()) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        return 0;
    }

    // Asignar memoria para los arreglos según el número de gerentes
    codigos = new string[totalGerentes];
    nombres = new string[totalGerentes];

    // Leer línea por línea y separar el código del nombre del gerente
    while (getline(archivoEntrada, linea) && contador < totalGerentes) {
        size_t delimitador = linea.find('|');
        if (delimitador != string::npos) {
            codigos[contador] = linea.substr(0, delimitador);
            nombres[contador] = linea.substr(delimitador + 1);

            // Eliminar espacios en blanco al inicio y al final
            codigos[contador].erase(codigos[contador].find_last_not_of(" ") + 1);
            nombres[contador].erase(0, nombres[contador].find_first_not_of(" "));

            contador++;
        }
    }

    archivoEntrada.close();
    return contador;
}

// Función para permitir que el usuario seleccione un gerente
int funcionesApoyo::seleccionarGerente(string* codigos, string* nombres, int totalGerentes) {
    if (totalGerentes == 0) {
        cerr << "No hay gerentes disponibles para seleccionar.\n";
        return -1;
    }

    // Mostrar la lista de gerentes
    cout << "Seleccione un gerente:\n";
    for (int i = 0; i < totalGerentes; ++i) {
        cout << i + 1 << ". " << nombres[i] << " (" << codigos[i] << ")\n";
    }

    // Obtener la selección del usuario
    int opcion;
    cout << "Ingrese el numero del gerente: ";
    cin >> opcion;

    // Validar la opción seleccionada
    if (opcion < 1 || opcion > totalGerentes) {
        cerr << "Seleccion invalida.\n";
        return -1;
    }

    // Retornar el índice del gerente seleccionado
    return opcion - 1;
}

void funcionesApoyo::transferirNuevaEstacion(){
    // Copiar los datos de newEstacion al arreglo estaciones
    for (int i = 0; i < totalnewEstacion; i++) {
        for (int j = 0; j < 8; j++) {
            estaciones[totalEstaciones][j] = newEstacion[i][j];
        }
        totalEstaciones++; // Incrementar el contador de estaciones
    }

    // Limpiar el arreglo newEstacion y restablecer totalnewEstacion a 0
    for (int i = 0; i < totalnewEstacion; i++) {
        for (int j = 0; j < 8; j++) {
            newEstacion[i][j].clear(); // Limpiar cada campo de newEstacion
        }
    }
    totalnewEstacion = 0; // Reiniciar el contador de nuevas estaciones
}

bool funcionesApoyo::identificarEstacion(string &idEstacion){
    for (int i = 0; i < totalEstaciones; i++){
        if(trim(estaciones[i][0]) == idEstacion){
            for (int j = 0; j < MAX_COLUMNAS_E; j++){
                newEstacion[0][j] = estaciones[i][j];
            }
            totalnewEstacion = 1;

            cout << "Datos de la estacion encontrada: " << endl;
            for (int j = 0; j < MAX_COLUMNAS_E; j++){
                cout << newEstacion[0][j] << "|";
            }
            cout << endl;

            for (int j = 0; j < MAX_COLUMNAS_E; j++) {
                newEstacion[0][j].clear();
            }
            totalnewEstacion = 0;

            return true;
        }
    }
    return false;
}

bool funcionesApoyo::VersiEstacionesEliminable(string &idEstacion){
    for (int i = 0; i < totalIslas; i++){
        if(trim(islas[i][0]) == idEstacion){
            if (islas[i][3] == "1"){
                return false;
            }
        }
    }
    return true;
}

void funcionesApoyo::guardarRespaldo(const string &idEstacion, string estaciones[][MAX_COLUMNAS_E], int totalEstaciones, string islas[][MAX_COLUMNAS_I], int totalIslas, string transacciones[][MAX_COLUMNAS_T], int totalTransacciones) {
    ofstream papelera("papelera.txt", ios::app);
    if (!papelera) {
        cout << "Error al abrir el archivo papelera.txt" << endl;
        return;
    }

    // Guardar la estación
    papelera << "Estacion eliminada:\n";
    for (int i = 0; i < totalEstaciones; i++) {
        if (trim(estaciones[i][0]) == idEstacion) {
            for (int j = 0; j < MAX_COLUMNAS_E; j++) {
                papelera << estaciones[i][j] << "|";
            }
            papelera << endl;
            break;
        }
    }

    // Guardar las islas asociadas
    papelera << "Islas eliminadas para la estacion " << idEstacion << ":\n";
    for (int i = 0; i < totalIslas; i++) {
        if (trim(islas[i][0]) == idEstacion) {
            for (int j = 0; j < MAX_COLUMNAS_I; j++) {
                papelera << islas[i][j] << "|";
            }
            papelera << endl;
        }
    }

    // Guardar las transacciones asociadas
    papelera << "Transacciones eliminadas para la estacion " << idEstacion << ":\n";
    for (int i = 0; i < totalTransacciones; i++) {
        if (trim(transacciones[i][0]) == idEstacion) {
            for (int j = 0; j < MAX_COLUMNAS_T; j++) {
                papelera << transacciones[i][j] << "|";
            }
            papelera << endl;
        }
    }

    papelera.close();
    cout << "Respaldo guardado en papelera.txt para la estacion " << idEstacion << endl;
}

void funcionesApoyo::guardarDatos(const string &nombreArchivo){
    ofstream archivoSalida(nombreArchivo);

    if (!archivoSalida.is_open()){
        cerr << "Error al abrir el archivo para guardar los datos.\n";
        return;
    }

    // Guardar estaciones
    archivoSalida << "%\n";
    for (int i = 0; i < totalEstaciones; ++i) {
        for (int j = 0; j < 9; ++j) {
            archivoSalida << estaciones[i][j];
            if (j < 8) archivoSalida << " | "; // Separador entre columnas
        }
        archivoSalida << "\n";
    }
    archivoSalida << "%\n";

    // Guardar islas
    archivoSalida << "$\n";
    for (int i = 0; i < totalIslas; ++i) {
        for (int j = 0; j < 7; ++j) {
            archivoSalida << islas[i][j];
            if (j < 6) archivoSalida << " | "; // Separador entre columnas
        }
        archivoSalida << "\n";
    }
    archivoSalida << "$\n";

    // Guardar transacciones
    archivoSalida << "&\n";
    for (int i = 0; i < totalTransacciones; ++i) {
        for (int j = 0; j < 10; ++j) {
            archivoSalida << transacciones[i][j];
            if (j < 9) archivoSalida << " | "; // Separador entre columnas
        }
        archivoSalida << "\n";
    }
    archivoSalida << "&\n";

    archivoSalida.close();
    cout << "Datos guardados correctamente en " << nombreArchivo << endl;
}


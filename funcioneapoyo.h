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
    void leerArchivoPrecios(const string &archivoPrecios);
    void mostrarDatos();
    void mostrarPrecios();
    bool loginUsuario();
    bool esGerente() const;
    void mostrarMenuAdministrador();
    void mostrarMenuEmpleado();
    void mostrarSubMenuGestionRed();
    void mostrarSubMenuGestionEstaciones();
    void mostrarSubMenuVerificacionFugas();
    void mostrarSubMenuSimulacionVentas();
    string seleccionarTipoGasolina();
    string generarCodigoEstacion();
    string seleccionarRegion();
    string generarCoordenadasGPS();
    int generarCantidadCombustible();
    void agregarEstacion(const string &codigo, const string &nombre, const string &gerente, const string &codigoGerente, const string &region, const string &coordenadasGPS, int regular, int premium, int ecoextra);
    void armarNuevaTransaccion(const string &codigoEstacion, const string &codigoIsla, const string &fecha, const string &hora, const string tipoGasolina, int litrosVendidos, const string &metodoPago, const string &idUsuario, double montoPagado);
    void guardarDatos(const string &nombreArchivo);
    void guardarPrecios(const string &archivoPrecios);
    void transferirNuevaEstacion();
    void transferirNuevaTransaccion();
    int contarGerentes(const string& nombreArchivo);
    int leerGerentes(const string& nombreArchivo, string*& codigos, string*& nombres, int totalGerentes);
    int seleccionarGerente(string* codigos, string* nombres, int totalGerentes);
    bool identificarEstacion(string &idEstacion);
    bool VersiEstacionesEliminable(string &idEstacion);
    string seleccionarEstacion();
    bool validarIdUsuario(const string &idUsuario);
    string seleccionarMetodoPago();
    string seleccionarIslaAleatoria(int codigoEstacion);
    void verificarTanque(double capacidadTanque, double nivelActual, double totalVentas, const string& tipoGasolina);
    void agregarsEstacion(const string &codigo, const string &nombre);
    void agregarTransaccion(const string &codigoEstacion, const string &codigoIsla, const string &fecha, const string &hora, const string tipoGasolina, int litrosVendidos, const string &metodoPago, const string &idUsuario, int precioPorLitro, int montoPagado);
    void guardarRespaldo(const string &idEstacion, string estaciones[][9], int totalEstaciones, string islas[][10], int totalIslas, string transacciones[][10], int totalTransacciones);
    double calcularMontoVenta(double litrosVendidos, double precioCombustible);
    double solicitarPrecio(string tipoCombustible);
    void actualizarVentasPorIsla(const string &codigoIsla, int litrosVendidos, const string &tipoGasolina);
    int generarVentaAleatoria(int codigoEstacion, const string &tipoGasolina, const string &codigoIsla);
    void realizarVenta(int indiceEstacion, const string &codigoIsla, int litrosSolicitados, const string &tipoGasolina);
    int verificarCantidadDisponible(int indiceEstacion, const string &tipoGasolina);

    static string trim(const string &str);
    string addPadding(const string &str);

    friend class gestionRed;
    friend class simulacionVentas;

private:
    // Definición de los tamaños máximos de los arreglos
    const static int MAX_ESTACIONES = 100;
    const static int MAX_ISLAS = 100;
    const static int MAX_TRANSACCIONES = 1000;
    const static int MAX_PRECIOS = 3;
    const static int MAX_COLUMNAS_E = 9; // Máximo número de columnas que tiene el archivo
    const static int MAX_COLUMNAS_I = 10;
    const static int MAX_COLUMNAS_T = 10;
    const static int MAX_COLUMNAS_P = 4;

    string sEstacion[MAX_ESTACIONES][2];
    string islasActivas[MAX_ISLAS];

    // Arreglos fijos para agregar los datos que se ingresan
    string newEstacion[MAX_ESTACIONES][MAX_COLUMNAS_E];
    string newIsla[MAX_ISLAS][MAX_COLUMNAS_I];
    string newTransaccion[MAX_TRANSACCIONES][MAX_COLUMNAS_T];

    // Arreglos fijos para almacenar los datos
    string estaciones[MAX_ESTACIONES][MAX_COLUMNAS_E];
    string islas[MAX_ISLAS][MAX_COLUMNAS_I];
    string transacciones[MAX_TRANSACCIONES][MAX_COLUMNAS_T];
    string precios[MAX_PRECIOS][MAX_COLUMNAS_P];

    // Contadores para los datos
    int totalEstaciones = 0;
    int totalIslas = 0;
    int totalTransacciones = 0;
    int totalnewEstacion = 0;
    int totalnewTransacciones = 0;

    // Métodos de procesamiento
    void procesarEstaciones(const string &linea);
    void procesarIslas(const string &linea);
    void procesarTransacciones(const string &linea);
    void procesarPrecios(const string &linea);

    bool gerente;
};

#endif // FUNCIONESAPOYO_H

#include "simulacionventas.h"
#include "funcionesapoyo.h"
#include "gestionred.h"
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>

using namespace std;

simulacionVentas::simulacionVentas() {}

int simulacionVentas::simularVenta(funcionesApoyo &fa){

    string codigoEstacionSeleccionada = fa.seleccionarEstacion();

    if (codigoEstacionSeleccionada.empty()) {
        cout << "No se pudo seleccionar la estacion." << endl;
        return 0;
    }

    string nombreEstacionSeleccionada;
    string regionEstacion;
    int litrosVendidos = 0;
    for (int i = 0; i < fa.totalEstaciones; ++i) {
        if (fa.trim(fa.estaciones[i][0]) == codigoEstacionSeleccionada) {
            nombreEstacionSeleccionada = fa.trim(fa.estaciones[i][1]);
            regionEstacion = fa.trim(fa.estaciones[i][4]);
            break;
        }
    }
    fa.agregarsEstacion(codigoEstacionSeleccionada, nombreEstacionSeleccionada);
    string tipoGasolina = fa.seleccionarTipoGasolina();
    string codigoIsla = fa.seleccionarIslaAleatoria(stoi(codigoEstacionSeleccionada));
    if (codigoIsla == ""){
        return 0;
    } else {
        litrosVendidos = fa.generarVentaAleatoria(codigoEstacionSeleccionada, tipoGasolina, codigoIsla);
    }

    // Determinar el precio por litro según la región y el tipo de gasolina
    double precioPorLitro = fa.obtenerPrecioGasolina(regionEstacion, tipoGasolina);

    //Calcular el monto total
    double montoPagado = fa.calcularMontoVenta(litrosVendidos, precioPorLitro);

    // Obtener la fecha y la hora actual
    time_t ahora = time(0);
    tm *tiempoLocal = localtime(&ahora);
    char fecha[11], hora[6];
    strftime(fecha, sizeof(fecha), "%Y-%m-%d", tiempoLocal);
    strftime(hora, sizeof(hora), "%H:%M", tiempoLocal);

    string metodoPago = fa.seleccionarMetodoPago();
    string idUsuario;
    while (true) {
        try {
            cout << "Ingrese el ID del usuario: ";
            cin >> idUsuario;

            if (fa.validarIdUsuario(idUsuario)) {
                break;
            } else {
                throw invalid_argument("ID de usuario no valido. Intente de nuevo.");
            }
        } catch (const invalid_argument &e) {
            cout << e.what() << endl;
        }
    }

    // Agregar la transacción
    fa.agregarTransaccion(codigoEstacionSeleccionada, codigoIsla, fecha, hora, tipoGasolina, litrosVendidos, metodoPago, idUsuario, precioPorLitro, montoPagado);

    // Mostrar mensaje de confirmación
    cout << "Venta realizada en la estacion " << nombreEstacionSeleccionada << " con exito." << endl;
    cout << "Monto total a pagar: $" << montoPagado << " pesos." << endl;

    return 0;
}

void simulacionVentas::verificarFugas(funcionesApoyo &fa) {

    string codigoEstacion = fa.seleccionarEstacion();

    // Encontrar la estación seleccionada por el código
    int indiceEstacion = -1;
    for (int i = 0; i < fa.totalEstaciones; ++i) {
        if (fa.trim(fa.estaciones[i][0]) == codigoEstacion) {
            indiceEstacion = i;
            break;
        }
    }

    if (indiceEstacion == -1) {
        cout << "Estacion no encontrada." << endl;
        return;
    }

    // Obtener las capacidades de los tanques de la estación
    double capacidadTanqueRegular = stod(fa.estaciones[indiceEstacion][6]); // Capacidad del tanque de Regular
    double capacidadTanquePremium = stod(fa.estaciones[indiceEstacion][7]); // Capacidad del tanque de Premium
    double capacidadTanqueEcoExtra = stod(fa.estaciones[indiceEstacion][8]); // Capacidad del tanque de EcoExtra

    cout << "Capacidades de los tanques: " << endl;
    cout << "Regular: " << capacidadTanqueRegular << " litros" << endl;
    cout << "Premium: " << capacidadTanquePremium << " litros" << endl;
    cout << "EcoExtra: " << capacidadTanqueEcoExtra << " litros" << endl;

    // Variables para almacenar las ventas totales por tipo de combustible
    double totalVentasRegular = 0.0, totalVentasPremium = 0.0, totalVentasEcoExtra = 0.0;

    // Sumar las ventas de transacciones para esta estación
    for (int i = 0; i < fa.totalTransacciones; ++i) {
        if (fa.trim(fa.transacciones[i][0]) == codigoEstacion) {
            string tipoGasolina = fa.trim(fa.transacciones[i][4]);
            int litrosVendidos = stoi(fa.trim(fa.transacciones[i][5]));

            if (tipoGasolina == "Regular") {
                totalVentasRegular += litrosVendidos;
            } else if (tipoGasolina == "Premium") {
                totalVentasPremium += litrosVendidos;
            } else if (tipoGasolina == "EcoExtra") {
                totalVentasEcoExtra += litrosVendidos;
            }
        }
    }

    // Obtener el nivel actual de los tanques
    double nivelActualRegular = stod(fa.islas[indiceEstacion][7]);
    double nivelActualPremium = stod(fa.islas[indiceEstacion][8]);
    double nivelActualEcoExtra = stod(fa.islas[indiceEstacion][9]);

    cout << "\nNiveles actuales de los tanques: " << endl;
    cout << "Regular: " << nivelActualRegular << " litros" << endl;
    cout << "Premium: " << nivelActualPremium << " litros" << endl;
    cout << "EcoExtra: " << nivelActualEcoExtra << " litros" << endl;

    // Verificar fugas para cada tipo de gasolina
    fa.verificarTanque(capacidadTanqueRegular, nivelActualRegular, totalVentasRegular, "Regular");
    fa.verificarTanque(capacidadTanquePremium, nivelActualPremium, totalVentasPremium, "Premium");
    fa.verificarTanque(capacidadTanqueEcoExtra, nivelActualEcoExtra, totalVentasEcoExtra, "EcoExtra");
}



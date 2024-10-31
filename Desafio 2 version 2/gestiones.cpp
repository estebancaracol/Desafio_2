#include "gestiones.h"
#include "funcionesapoyo.h"

using namespace std;

GestionES::GestionES() {}

void GestionES::agregarSurtidor(funcionesApoyo& fa) {
    string codigoEstacion, codigoIsla, modelo;
    int estado, vendidoRegular, vendidoPremium, vendidoEcoExtra;

    // Seleccionar la estacion
    cout << "Seleccionar estacion para agregar surtidor.\n";
    codigoEstacion = fa.seleccionarEstacion();

    // Verificar si la estacion seleccionada es valida
    if (codigoEstacion.empty()) {
        cerr << "No se selecciono una estacion valida.\n";
        return;
    }

    // Generar el codigo de la isla para la estacion seleccionada
    codigoIsla = fa.generarCodigoIsla(codigoEstacion);

    // Seleccionar el modelo de la isla
    modelo = fa.seleccionarModeloIsla();

    // Establecer el estado en 1 (Activo) automaticamente
    estado = 1;
    cout << "El estado del surtidor se ha establecido en Activo (1).\n";

    // Asignar valores predeterminados de 0 litros vendidos para cada tipo de combustible
    vendidoRegular = 0;
    vendidoPremium = 0;
    vendidoEcoExtra = 0;

    // Mostrar los litros vendidos
    cout << "Litros vendidos de Regular: " << vendidoRegular << endl;
    cout << "Litros vendidos de Premium: " << vendidoPremium << endl;
    cout << "Litros vendidos de EcoExtra: " << vendidoEcoExtra << endl;

    // Mostrar la confirmacion de la nueva isla agregada
    cout << "Nueva isla agregada:\n";
    cout << "Estacion: " << codigoEstacion << " | Surtidor: " << codigoIsla << " | Modelo: " << modelo << " | Estado: " << estado << endl;
    cout << "Vendido Regular: " << vendidoRegular << " | Vendido Premium: " << vendidoPremium << " | Vendido EcoExtra: " << vendidoEcoExtra << endl;

    // Insertar la nueva isla en el arreglo de islas
    fa.agregarIsla(codigoEstacion, codigoIsla, modelo, estado, vendidoRegular, vendidoPremium, vendidoEcoExtra);
}

void GestionES::eliminarSurtidor(funcionesApoyo &fa) {
    string idIsla, codigoEstacion;

    // Solicitar el código de la estación
    cout << "Ingrese el codigo de la estacion donde se encuentra la isla a eliminar: " << endl;
    codigoEstacion = fa.seleccionarEstacion();

    // Solicitar el código de la isla a eliminar
    cout << "Seleccione el codigo de la isla a eliminar: ";
    idIsla = fa.seleccionarIsla(codigoEstacion);

    // Llamar directamente a la función eliminarIslaPorCodigo
    if (fa.eliminarIslaPorCodigo(codigoEstacion, idIsla)) {
        cout << "Isla " << idIsla << " eliminada correctamente." << endl;
    } else {
        cout << "Error: No se encontro una isla con el codigo proporcionado." << endl;
    }
}

//Función para cambiar el estado de las islas
void GestionES::cambiarEstado(funcionesApoyo &fa){
    string codigoEstacion, codigoIsla;
    int nuevoEstado;

    cout << "Seleccione el codigo de la estacion: " << endl;
    codigoEstacion = fa.seleccionarEstacion();

    cout << "Seleccione el codigo de la isla: " << endl;
    codigoIsla = fa.seleccionarIsla(codigoEstacion);

    cout << "Seleccione el nuevo estado (1 para Activa, 0 para Inactiva): ";
    cin >> nuevoEstado;

    // Validar el estado ingresado
    if (nuevoEstado != 1 && nuevoEstado != 0) {
        cout << "Error: Estado invalido. Debe ser 1 (Activa) o 0 (Inactiva)." << endl;
        return;
    }

    // Llamada a la función para cambiar el estado en funcionesApoyo
    fa.cambiarEstadoEstacion(codigoEstacion, codigoIsla, nuevoEstado);
}

void GestionES::consultarHistoricoTransacciones(funcionesApoyo &fa){

    int opcionEstacion, opcionIsla;
    string codigoEstacion, codigoIsla;

    cout << "Desea ver transacciones de todas las estaciones o una en especifico?" << endl;
    cout << "1. Todas las estaciones" << endl;
    cout << "2. Una estacion especifica" << endl;
    cout << "Opcion: ";
    cin >> opcionEstacion;

    if (opcionEstacion == 2) {
        cout << "Seleccione el codigo de la estacion: " << endl;
        codigoEstacion = fa.seleccionarEstacion();
    }

    cout << "\nDesea ver transacciones de todas las islas o una en especifico?" << endl;
    cout << "1. Todas las islas" << endl;
    cout << "2. Una isla especifica" << endl;
    cout << "Opcion: ";
    cin >> opcionIsla;

    if (opcionIsla == 2) {
        cout << "Seleccione el codigo de la isla: " << endl;
        codigoIsla = fa.seleccionarIsla(codigoEstacion);
    }

    //Llamar la función para mostrar Historico de transacciones
    fa.mostrarHistoricoTransacciones(codigoEstacion, codigoIsla, opcionEstacion, opcionIsla);
}

//función para el reporte de ventas de combustible
void GestionES::ReporteCombustibleVendido(funcionesApoyo &fa){
    int opcionCombustible;

    cout << "Seleccione el tipo de combustible para el reporte:" << endl;
    cout << "1. Regular" << endl;
    cout << "2. Premium" << endl;
    cout << "3. EcoExtra" << endl;
    cout << "4. Todos" << endl;
    cout << "Opcion: " << endl;
    cin >> opcionCombustible;

    fa.mostrarReporteCVendido(opcionCombustible);
}

//Funcion para la venta de combustible
int GestionES::ventaCombustible(funcionesApoyo &fa){
    string codigoEstacionSeleccionada = fa.seleccionarEstacion();

    if (codigoEstacionSeleccionada.empty()) {
        cout << "No se pudo seleccionar la estacion." << endl;
        return 0;
    }

    string nombreEstacionSeleccionada;
    string regionEstacion;
    double litrosVendidos = 0.0;


    // Obtener detalles de la estación seleccionada
    if (fa.obtenerDetallesEstacion(codigoEstacionSeleccionada, nombreEstacionSeleccionada, regionEstacion)) {
        fa.agregarsEstacion(codigoEstacionSeleccionada, nombreEstacionSeleccionada);
    } else {
        cout << "No se pudieron obtener los detalles de la estacion seleccionada." << endl;
        return 0; // Salir de la función si no se encuentran los detalles
    }
    fa.agregarsEstacion(codigoEstacionSeleccionada, nombreEstacionSeleccionada);

    // Selección del tipo de gasolina
    string tipoGasolina = fa.seleccionarTipoGasolina();

    //Seleccionar Isla
    string codigoIsla = fa.seleccionarIsla(codigoEstacionSeleccionada);
    if (codigoIsla == ""){
        return 0;
    } else {
        // Solicitar la cantidad de litros a vender (entre 3 y 20 litros)
        while (true) {
            cout << "Ingrese la cantidad de litros a vender (entre 3 y 20): ";
            cin >> litrosVendidos;

            if (litrosVendidos >= 3 && litrosVendidos <= 20) {
                break;  // Valor válido, salir del bucle
            } else {
                cout << "Cantidad de litros no valida. Intente nuevamente." << endl;
            }
        }
    }

    fa.realizarVenta(codigoEstacionSeleccionada, codigoIsla, litrosVendidos, tipoGasolina);

    // Determinar el precio por litro según la región y el tipo de gasolina
    double precioPorLitro = fa.obtenerPrecioGasolina(regionEstacion, tipoGasolina);


    if (precioPorLitro == 0) {
        return 0; // Salimos de la función si la región o el tipo de gasolina no son válidos
    }

    cout << "El precio por litro de gasolina es: $" << precioPorLitro
         << " en la region " << regionEstacion << endl;

    // Calcular el monto total
    double montoPagado = fa.calcularMontoVenta(litrosVendidos, precioPorLitro);

    // Obtener la fecha y la hora actual
    time_t ahora = time(0);
    tm *tiempoLocal = localtime(&ahora);
    char fecha[11], hora[6];
    strftime(fecha, sizeof(fecha), "%Y-%m-%d", tiempoLocal);
    strftime(hora, sizeof(hora), "%H:%M", tiempoLocal);

    // Seleccionar método de pago
    string metodoPago = fa.seleccionarMetodoPago();

    // Solicitar ID del usuario
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



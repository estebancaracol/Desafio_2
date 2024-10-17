#include "gestionred.h"
#include "funcionesapoyo.h"
#include <iostream>

using namespace std;

gestionRed::gestionRed() {

}

void gestionRed::agregarEstacion(funcionesApoyo& fa) {
    string* codigos = nullptr;
    string* nombres = nullptr;
    string codigo = fa.generarCodigoEstacion();
    string nombre, gerente, codigoGerente, region, coordenadasGPS;
    int regular, premium, ecoextra;

    // Contar el número de gerentes en el archivo
    int totalGerentes = fa.contarGerentes("gerentes.txt");
    if (totalGerentes == 0) {
        cerr << "No se puede continuar sin gerentes disponibles.\n";
        return;
    }

    // Leer gerentes desde el archivo
    fa.leerGerentes("gerentes.txt", codigos, nombres, totalGerentes);

    // Solicitar datos al usuario
    cout << "Ingrese el nombre de la estacion: ";
    cin.ignore(); // Limpiar buffer
    getline(cin, nombre);

    // Seleccionar un gerente
    int indiceGerente = fa.seleccionarGerente(codigos, nombres, totalGerentes);
    if (indiceGerente == -1) {
        cerr << "No se selecciono ningun gerente valido.\n";
        return;
    }
    codigoGerente = codigos[indiceGerente];
    gerente = nombres[indiceGerente];

    // Llamar a la función que selecciona la región
    region = fa.seleccionarRegion();

    // Generar automáticamente las coordenadas GPS
    coordenadasGPS = fa.generarCoordenadasGPS();

    // Generar cantidades aleatorias de combustible
    regular = fa.generarCantidadCombustible();
    premium = fa.generarCantidadCombustible();
    ecoextra = fa.generarCantidadCombustible();

    // Mostrar la confirmación de la estación agregada
    cout << "Nueva estacion agregada:\n";
    cout << codigo << " | " << nombre << " | " << codigoGerente << " | " << gerente << " | " << region << " | "
         << coordenadasGPS << " | " << regular << " | " << premium << " | " << ecoextra << endl;

    // Insertar la nueva estación en el arreglo de estaciones
    fa.agregarEstacion(codigo, nombre, codigoGerente, gerente, region, coordenadasGPS, regular, premium, ecoextra);

    // Liberar la memoria dinámica
    delete[] codigos;
    delete[] nombres;
}

void gestionRed::eliminarEstacion(funcionesApoyo &fa){
    string idEstacion;
    cout << "Ingrese el ID de la estacion a eliminar: ";
    cin >> idEstacion;

    idEstacion = fa.trim(idEstacion);

    if (!fa.identificarEstacion(idEstacion)) {
        cout << "Error: No se encontro una estacion con el ID proporcionado" << endl;
        return;
    }

    if (!fa.VersiEstacionesEliminable(idEstacion)){
        cout << "Error: La estacion tiene islas activas y no puede ser eliminada" << endl;
        return;
    }

    fa.guardarRespaldo(idEstacion, fa.estaciones, fa.totalEstaciones, fa.islas, fa.totalIslas, fa.transacciones, fa.totalTransacciones);

    // Eliminar la estación del arreglo
    int posicion = -1;
    for (int i = 0; i < fa.totalEstaciones; i++) {
        if (fa.trim(fa.estaciones[i][0]) == idEstacion) {
            posicion = i;
            break;
        }
    }

    // Si no se encontró la posición, retornar
    if (posicion == -1) {
        cout << "Error: La estacion no fue encontrada en el arreglo." << endl;
        return;
    }

    // Eliminar las islas asociadas del arreglo
    int nuevaTotalIslas = 0;
    for (int i = 0; i < fa.totalIslas; i++) {
        if (fa.trim(fa.islas[i][0]) != idEstacion) {
            for (int j = 0; j < fa.MAX_COLUMNAS_I; j++) {
                fa.islas[nuevaTotalIslas][j] = fa.islas[i][j];
            }
            nuevaTotalIslas++;
        }
    }
    fa.totalIslas = nuevaTotalIslas;

    // Eliminar las transacciones asociadas del arreglo
    int nuevaTotalTransacciones = 0;
    for (int i = 0; i < fa.totalTransacciones; i++) {
        if (fa.trim(fa.transacciones[i][0]) != idEstacion) {
            for (int j = 0; j < fa.MAX_COLUMNAS_T; j++) {
                fa.transacciones[nuevaTotalTransacciones][j] = fa.transacciones[i][j];
            }
            nuevaTotalTransacciones++;
        }
    }
    fa.totalTransacciones = nuevaTotalTransacciones;

    // Mover todas las estaciones siguientes una posición hacia atrás
    for (int i = posicion; i < fa.totalEstaciones - 1; i++) {
        for (int j = 0; j < fa.MAX_COLUMNAS_E; j++) {
            fa.estaciones[i][j] = fa.estaciones[i + 1][j];
        }
    }

    // Decrementar el total de estaciones
    fa.totalEstaciones--;

    cout << "Estacion con ID " << idEstacion << " eliminada correctamente." << endl;
}

void gestionRed::calcularVentasPorEstacion(funcionesApoyo &fa){

    for (int i = 0; i < fa.totalEstaciones; i++){
        string codigoEstacion = fa.trim(fa.estaciones[i][0]);
        string region = fa.trim(fa.estaciones[i][4]);
        double preciosRegion[3];

        // Asignar los precios de acuerdo a la región
        if (region == "Norte") {
            preciosRegion[0] = stod(fa.trim(fa.precios[0][1])); // Precio Regular
            preciosRegion[1] = stod(fa.trim(fa.precios[0][2])); // Precio Premium
            preciosRegion[2] = stod(fa.trim(fa.precios[0][3])); // Precio EcoExtra
        } else if (region == "Sur") {
            preciosRegion[0] = stod(fa.trim(fa.precios[1][1])); // Precio Regular
            preciosRegion[1] = stod(fa.trim(fa.precios[1][2])); // Precio Premium
            preciosRegion[2] = stod(fa.trim(fa.precios[1][3])); // Precio EcoExtra
        } else if (region == "Centro") {
            preciosRegion[0] = stod(fa.trim(fa.precios[2][1])); // Precio Regular
            preciosRegion[1] = stod(fa.trim(fa.precios[2][2])); // Precio Premium
            preciosRegion[2] = stod(fa.trim(fa.precios[2][3])); // Precio EcoExtra
        }

        double litrosRegular = 0, litrosPremium = 0, litrosEcoExtra = 0;

        // Buscar las islas pertenecientes a la estación
        for (int j = 0; j < fa.totalIslas; j++) {
            if (fa.trim(fa.islas[j][0]) == codigoEstacion) {  // La isla pertenece a esta estación
                cout << "++++++++++++++++++++++++++++++++++++++++++" << endl;
                cout << "Isla encontrada: " << fa.trim(fa.islas[j][1]) << " de la estacion: " << fa.trim(fa.islas[j][0]) << endl;
                cout << "Litros Regular en isla: " << fa.islas[j][4] << endl;
                cout << "Litros Premium en isla: " << fa.islas[j][5] << endl;
                cout << "Litros EcoExtra en isla: " << fa.islas[j][6] << endl;
                cout << "++++++++++++++++++++++++++++++++++++++++++" << endl;

                litrosRegular += stod(fa.islas[j][4]);    // Litros vendidos de Regular
                litrosPremium += stod(fa.islas[j][5]);    // Litros vendidos de Premium
                litrosEcoExtra += stod(fa.islas[j][6]);   // Litros vendidos de EcoExtra
            }
        }

        cout << "++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "Region: " << region << endl;
        cout << "Precio Regular: " << preciosRegion[0] << endl;
        cout << "Precio Premium: " << preciosRegion[1] << endl;
        cout << "Precio EcoExtra: " << preciosRegion[2] << endl;
        cout << "++++++++++++++++++++++++++++++++++++++++++" << endl;

        // Calcular el monto de las ventas por categoría usando la clase funcionesApoyo
        double ventasRegular = fa.calcularMontoVenta(litrosRegular, preciosRegion[0]);
        double ventasPremium = fa.calcularMontoVenta(litrosPremium, preciosRegion[1]);
        double ventasEcoExtra = fa.calcularMontoVenta(litrosEcoExtra, preciosRegion[2]);

        // Imprimir o guardar los resultados de esta estación
        cout << "--------------------------" << endl;
        cout << "Estacion: " << fa.trim(fa.estaciones[i][1]) << endl;
        cout << "Ventas Regular: " << ventasRegular << endl;
        cout << "Ventas Premium: " << ventasPremium << endl;
        cout << "Ventas EcoExtra: " << ventasEcoExtra << endl;
        cout << "--------------------------" << endl;
    }
}

void gestionRed::fijarPreciosCombustible(funcionesApoyo &fa){
    try{
        fa.leerArchivoPrecios("precios.txt");
        fa.mostrarPrecios();

        double precioNorte[3];
        double precioSur[3];
        double precioCentro[3];

        // Solicitar nuevos precios para la región Norte
        cout << "Ingrese los nuevos precios para la region Norte (Regular, Premium, EcoExtra): " << endl;
        precioNorte[0] = fa.solicitarPrecio("Regular");
        precioNorte[1] = fa.solicitarPrecio("Premium");
        precioNorte[2] = fa.solicitarPrecio("EcoExtra");

        // Solicitar nuevos precios para la región Sur
        cout << "Ingrese los nuevos precios para la region Sur (Regular, Premium, EcoExtra): " << endl;
        precioSur[0] = fa.solicitarPrecio("Regular");
        precioSur[1] = fa.solicitarPrecio("Premium");
        precioSur[2] = fa.solicitarPrecio("EcoExtra");

        // Solicitar nuevos precios para la región Centro
        cout << "Ingrese los nuevos precios para la region Centro (Regular, Premium, EcoExtra): " << endl;
        precioCentro[0] = fa.solicitarPrecio("Regular");
        precioCentro[1] = fa.solicitarPrecio("Premium");
        precioCentro[2] = fa.solicitarPrecio("EcoExtra");

        // Actualizar los precios en cada región en el arreglo 'precios'
        for (int i = 0; i < 3; ++i) {
            fa.precios[0][i+1] = to_string(precioNorte[i]);  // Norte
            fa.precios[1][i+1] = to_string(precioSur[i]);    // Sur
            fa.precios[2][i+1] = to_string(precioCentro[i]); // Centro
        }

        fa.guardarPrecios("precios.txt");

        cout << "Los precios de combustible han sido actualizados." << endl;
    }catch (const std::exception &e) {
        cerr << "Error en fijar precios: " << e.what() << endl;
    }
}



#include <iostream>
#include "funcionesapoyo.h"
#include "gestionred.h"

using namespace std;


int main() {
    funcionesApoyo fa;
    gestionRed gr;

    fa.leerArchivo("estaciones.txt"); // Suponiendo que "archivo.txt" tiene el formato solicitado
    fa.mostrarDatos();             // Mostrar todos los datos

    int opcion;
    do {
        fa.mostrarMenu();
        cin >> opcion;

        switch (opcion) {
        case 1:
            // Lógica para agregar estación de servicio
            // Utilizar funcionesApoyo para agregar la nueva estación
            cout << "Funcionalidad de agregar estacion aun no implementada.\n";
            break;
        case 2:
            // Lógica para eliminar estación de servicio
            // Verificar estaciones sin surtidores activos
            cout << "Funcionalidad de eliminar estacion aun no implementada.\n";
            break;
        case 3:
            // Calcular monto total de ventas
            // Se trabajará sobre los arreglos cargados en funcionesApoyo
            cout << "Funcionalidad de calcular ventas aun no implementada.\n";
            break;
        case 4:
            // Fijar precios del combustible por región
            double nuevosPrecios[3];
            cout << "Ingrese los nuevos precios para Regular, Premium y EcoExtra: ";
            cin >> nuevosPrecios[0] >> nuevosPrecios[1] >> nuevosPrecios[2];
            gr.cambiarPrecioCombustiblePorRegion("Norte", nuevosPrecios);
            cout << "Precios actualizados.\n";
            break;
        case 0:
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion no valida.\n";
        }
    } while (opcion != 0);


    return 0;
}

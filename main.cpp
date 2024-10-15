#include <iostream>
#include "funcionesapoyo.h"
#include "gestionred.h"

using namespace std;

int main() {
    funcionesApoyo fa;
    gestionRed gr;

    fa.leerArchivo("estaciones.txt"); // Suponiendo que ".txt" tiene el formato solicitado
    fa.mostrarDatos();             // Mostrar todos los datos

    int opcion = 0;
    do {
        fa.mostrarMenu();
        cin >> opcion;

        switch (opcion) {
        case 1:
            gr.agregarEstacion(fa);
        case 2:
            gr.eliminarEstacion(fa);
        case 3:
            gr.calcularVentasPorEstacion(fa);
        case 4:
            cout << "Guardando datos y saliendo...\n";
            break;
        case 0:
            cout << "Guardando datos y saliendo...\n";
            fa.guardarDatos("estaciones_guardadas.txt");
            cout << "Saliendo...\n";
            break;
        default:
            cout << "Opcion no valida.\n";
        }
    } while (opcion != 0);


    return 0;
}

#include <iostream>
#include "funcionesapoyo.h"
#include "gestionred.h"
#include "simulacionventas.h"

using namespace std;

int main() {
    funcionesApoyo fa;
    gestionRed gr;
    simulacionVentas sv;

    fa.leerArchivo("estaciones.txt");
    fa.mostrarDatos();

    bool salir = false;  // Bandera para controlar el ciclo principal

    while (!salir) {
        // Verificar el login del usuario
        bool loginExitoso = fa.loginUsuario();

        if (!loginExitoso) {
            cout << "Desea intentar iniciar sesion nuevamente? (s/n): ";
            char respuesta;
            cin >> respuesta;

            if (respuesta == 'n' || respuesta == 'N') {
                salir = true;  // Salir si el usuario no quiere volver a intentar
            }
        } else {
            int opcion = 0;

            // Si el login fue exitoso, mostrar el menu correspondiente
            do {
                // Dependiendo del rol, se muestra el menu del administrador o del empleado
                if (fa.esGerente()) {
                    fa.mostrarMenuAdministrador();
                    cin >> opcion;

                    switch (opcion) {
                    case 1:
                        fa.mostrarSubMenuGestionRed();
                        cin >> opcion;
                        switch (opcion) {
                        case 1:
                            cout << "*******************************" << endl;
                            cout << " Vamos a AGREGAR una ESTACION " << endl;
                            cout << "*******************************" << endl;
                            gr.agregarEstacion(fa);
                            break;
                        case 2:
                            cout << "*******************************" << endl;
                            cout << " Vamos a ELIMINAR una ESTACION " << endl;
                            cout << "*******************************" << endl;
                            gr.eliminarEstacion(fa);
                            break;
                        case 3:
                            cout << "*****************************************************" << endl;
                            cout << " Vamos a CALCULAR las VENTAS de todas las ESTACIONES " << endl;
                            cout << "*****************************************************" << endl;
                            gr.calcularVentasPorEstacion(fa);
                            break;
                        case 4:
                            cout << "************************************************************" << endl;
                            cout << " Vamos a FIJAR los PRECIOS del COMBUSTIBLE para cada REGION " << endl;
                            cout << "************************************************************" << endl;
                            gr.fijarPreciosCombustible(fa);
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Opcion no valida.\n";
                        }
                        break;
                    case 2:
                        fa.mostrarSubMenuGestionEstaciones();
                        cin >> opcion;
                        switch (opcion) {
                        case 1:
                            // Logica para agregar/eliminar un surtidor
                            break;
                        case 2:
                            // Logica para activar/desactivar un surtidor
                            break;
                        case 3:
                            // Logica para consultar el historico de transacciones
                            break;
                        case 4:
                            // Logica para reportar litros vendidos
                            break;
                        case 5:
                            // Logica para simular una venta
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Opcion no valida.\n";
                        }
                        break;
                    case 3:
                        fa.mostrarSubMenuVerificacionFugas();
                        cin >> opcion;
                        if (opcion == 1) {
                            cout << "********************************************" << endl;
                            cout << " Vamos a VERIFICAR las FUGAS de COMBUSTIBLE " << endl;
                            cout << "********************************************" << endl;
                            sv.verificarFugas(fa);
                        }
                        break;
                    case 4:
                        fa.mostrarSubMenuSimulacionVentas();
                        cin >> opcion;
                        if (opcion == 1) {
                            cout << "***************************" << endl;
                            cout << " Vamos a SIMULAR una VENTA " << endl;
                            cout << "***************************" << endl;
                            sv.simularVenta(fa, gr);
                        }
                        break;
                    case 0:
                        break;
                    default:
                        cout << "Opcion no valida.\n";
                    }
                } else {  // Menu para empleados
                    fa.mostrarMenuEmpleado();
                    cin >> opcion;

                    switch (opcion) {
                    case 1:
                        fa.mostrarSubMenuGestionEstaciones();
                        cin >> opcion;
                        switch (opcion) {
                        case 1:
                            // Logica para agregar/eliminar un surtidor
                            break;
                        case 2:
                            // Logica para activar/desactivar un surtidor
                            break;
                        case 3:
                            // Logica para consultar el historico de transacciones
                            break;
                        case 4:
                            // Logica para reportar litros vendidos
                            break;
                        case 5:
                            // Logica para simular una venta
                            break;
                        case 0:
                            break;
                        default:
                            cout << "Opcion no valida.\n";
                        }
                        break;
                    case 2:
                        fa.mostrarSubMenuSimulacionVentas();
                        cin >> opcion;
                        if (opcion == 1) {
                            cout << "***************************" << endl;
                            cout << " Vamos a SIMULAR una VENTA " << endl;
                            cout << "***************************" << endl;
                            sv.simularVenta(fa, gr);
                        }
                        break;
                    case 0:
                        break;
                    default:
                        cout << "Opcion no valida.\n";
                    }
                }
            } while (opcion != 0);  // Continuar en el menu hasta que el usuario elija "0"

            // Preguntar si desea volver a iniciar sesion o salir
            cout << "Desea volver a iniciar sesion o salir? (1 para iniciar sesion nuevamente, 0 para salir): ";
            cin >> opcion;

            if (opcion == 0) {
                // Guardar datos solo cuando el usuario decide salir
                cout << "*****************" << endl;
                cout << " Guardando DATOS " << endl;
                cout << "*****************" << endl;
                fa.guardarDatos("estaciones.txt");
                salir = true;  // Terminar el ciclo principal y salir del programa
            }
        }
    }

    cout << "Saliendo del programa...\n";
    return 0;
}

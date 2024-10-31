#include <iostream>
#include "funcionesapoyo.h"
#include "gestionred.h"
#include "simulacionventas.h"
#include "gestiones.h"

using namespace std;

int main() {
    funcionesApoyo fa;
    gestionRed gr;
    simulacionVentas sv;
    GestionES ge;


    fa.leerArchivo("estaciones.txt");
    fa.leerArchivoPrecios("precios.txt");
    fa.mostrarPrecios();
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
                        case 1: {
                            int subOpcion;
                            cout << "Seleccione una opcion:\n";
                            cout << "1. Agregar un surtidor\n";
                            cout << "2. Eliminar un surtidor\n";
                            cout << "Ingrese su opcion: ";
                            cin >> subOpcion;

                            switch (subOpcion) {
                            case 1:
                                cout << "***********************************" << endl;
                                cout << " Vamos a AGREGAR una ISLA/SURTIDOR " << endl;
                                cout << "***********************************" << endl;
                                ge.agregarSurtidor(fa);
                                break;
                            case 2:
                                cout << "************************************" << endl;
                                cout << " Vamos a ELIMINAR una ISLA/SURTIDOR " << endl;
                                cout << "************************************" << endl;
                                ge.eliminarSurtidor(fa);
                                break;
                            default:
                                cout << "Opcion invalida. Por favor, seleccione 1 o 2.\n";
                                break;
                            }
                            break;
                        }

                        case 2:
                            cout << "***********************************************" << endl;
                            cout << " Vamos a CAMBIAR el ESTADO de la ISLA/SURTIDOR " << endl;
                            cout << "***********************************************" << endl;
                            ge.cambiarEstado(fa);
                            break;
                        case 3:
                            cout << "*****************************************************" << endl;
                            cout << " Vamos a CONSULTAR el HISTORICO de las TRANSACCIONES " << endl;
                            cout << "*****************************************************" << endl;
                            ge.consultarHistoricoTransacciones(fa);
                            break;
                        case 4:
                            cout << "******************************************************" << endl;
                            cout << " Vamos a ver el REPORTE de las VENTAS por COMBUSTIBLE " << endl;
                            cout << "******************************************************" << endl;
                            ge.ReporteCombustibleVendido(fa);
                            break;
                        case 5:
                            cout << "***************************" << endl;
                            cout << " Vamos a SIMULAR una VENTA " << endl;
                            cout << "***************************" << endl;
                            ge.ventaCombustible(fa);
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
                            sv.simularVenta(fa);
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
                    case 1: {
                        int subOpcion;
                        cout << "Seleccione una opcion:\n";
                        cout << "1. Agregar un surtidor\n";
                        cout << "2. Eliminar un surtidor\n";
                        cout << "Ingrese su opcion: ";
                        cin >> subOpcion;

                        switch (subOpcion) {
                        case 1:
                            cout << "***********************************" << endl;
                            cout << " Vamos a AGREGAR una ISLA/SURTIDOR " << endl;
                            cout << "***********************************" << endl;
                            ge.agregarSurtidor(fa);
                            break;
                        case 2:
                            cout << "************************************" << endl;
                            cout << " Vamos a ELIMINAR una ISLA/SURTIDOR " << endl;
                            cout << "************************************" << endl;
                            ge.eliminarSurtidor(fa);
                            break;
                        default:
                            cout << "Opcion invalida. Por favor, seleccione 1 o 2.\n";
                            break;
                        }
                        break;
                    }

                    case 2:
                        cout << "***********************************************" << endl;
                        cout << " Vamos a CAMBIAR el ESTADO de la ISLA/SURTIDOR " << endl;
                        cout << "***********************************************" << endl;
                        ge.cambiarEstado(fa);
                        break;
                    case 3:
                        cout << "*****************************************************" << endl;
                        cout << " Vamos a CONSULTAR el HISTORICO de las TRANSACCIONES " << endl;
                        cout << "*****************************************************" << endl;
                        ge.consultarHistoricoTransacciones(fa);
                        break;
                    case 4:
                        cout << "******************************************************" << endl;
                        cout << " Vamos a ver el REPORTE de las VENTAS por COMBUSTIBLE " << endl;
                        cout << "******************************************************" << endl;
                        ge.ReporteCombustibleVendido(fa);
                        break;
                    case 5:
                        cout << "***************************" << endl;
                        cout << " Vamos a SIMULAR una VENTA " << endl;
                        cout << "***************************" << endl;
                        ge.ventaCombustible(fa);
                        break;
                    case 0:
                        break;
                    default:
                        cout << "Opcion no valida.\n";
                    }
                    break;
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

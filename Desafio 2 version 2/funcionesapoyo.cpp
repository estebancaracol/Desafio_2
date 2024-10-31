#include "funcionesapoyo.h"
#include "gestionred.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

funcionesApoyo::funcionesApoyo() : totalEstaciones(0), totalIslas(0), totalTransacciones(0), totalnewEstacion(0), gerente(false){
    totalnewEstacion = 0;
    srand(time(0));
}

string funcionesApoyo::generarCodigoEstacion(){
    stringstream ss;
    ss << setfill('0') << setw(3) << totalEstaciones + 1;
    return ss.str();
}

string funcionesApoyo::generarCodigoIsla(const string &codigoEstacion) {
    // Verificar que `totalIslas` es mayor que cero
    cout << "Valor de totalIslas: " << totalIslas << endl;
    if (totalIslas <= 0) {
        cout << "Error: `totalIslas` es 0 o negativo, no hay islas para procesar." << endl;
        return "S01";  // Retorna un código inicial si no hay islas
    }

    int ultimoNumeroIsla = 0; // Almacena el número de isla más alto encontrado para la estación
    string codigoIsla = "S01";

    // Imprimir todos los datos de las islas para verificar el contenido
    cout << "Contenido de `islas` antes del ciclo:" << endl;
    for (int j = 0; j < totalIslas; ++j) {
        cout << "Isla " << j + 1 << ": " << islas[j][0] << " - " << islas[j][1] << endl;
    }

    // Recorrer todas las islas almacenadas en el arreglo
    for (int i = 0; i < totalIslas; ++i) {
        cout << "Revisando isla " << i + 1 << ": " << islas[i][0] << " - " << islas[i][1] << endl;  // Depuración adicional
        if (trim(islas[i][0]) == codigoEstacion) {  // Si la isla pertenece a la estación seleccionada
            codigoIsla = trim(islas[i][1]);  // Ejemplo: "S01"

            if (codigoIsla.length() > 1 && codigoIsla[0] == 'S') { // Comprobamos que el formato es "SXX"
                // Extraer el número de isla después de la 'S'
                try {
                    int numeroIsla = stoi(codigoIsla.substr(1));  // Convertimos a entero
                    // Actualizar el último número de isla si es mayor
                    if (numeroIsla > ultimoNumeroIsla) {
                        ultimoNumeroIsla = numeroIsla;
                    }
                } catch (const invalid_argument& e) {
                    cout << "Error de conversion en el codigo de isla: " << codigoIsla << endl;
                }
            }
        }
    }

    // Generar el nuevo código de isla con el siguiente número secuencial
    stringstream nuevoCodigoIsla;
    nuevoCodigoIsla << "S" << setw(2) << setfill('0') << (ultimoNumeroIsla + 1);

    // Convertir a string antes de imprimir
    cout << "Este es el nuevo codigo: " << nuevoCodigoIsla.str() << endl;

    return nuevoCodigoIsla.str(); // Devolver el nuevo código de isla
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
        cout << "Ingrese el nombre de la region: ";
        cin.ignore(); // Limpiar buffer
        getline(cin, regionManual);
        return regionManual;
    }
    default:
        cout << "Opcion no valida, se asigna 'Norte' por defecto.\n";
        return "Norte";
    }
}

string funcionesApoyo::seleccionarTipoGasolina() {
    int seleccion = 0;

    // Mostrar opciones de gasolina disponibles
    cout << "Selecciona el tipo de gasolina:" << endl;
    cout << "1. Regular" << endl;
    cout << "2. Premium" << endl;
    cout << "3. EcoExtra" << endl;

    // Solicitar la selección al usuario
    while (true) {
        cout << "Ingresa el numero correspondiente (1-3): ";
        cin >> seleccion;

        // Verificar si la entrada es válida
        if (cin.fail() || seleccion < 1 || seleccion > 3) {
            cin.clear(); // Limpiar el estado de error de cin
            string invalidInput;
            getline(cin, invalidInput); // Leer y descartar la entrada inválida
            cout << "Error: opcion no valida. Por favor, intenta de nuevo." << endl;
        } else {
            // Entrada válida, salir del bucle
            break;
        }
    }

    // Manejo de la selección de tipo de gasolina
    switch (seleccion) {
    case 1:
        cout << "Gasolina seleccionada: Regular" << endl;
        return "Regular";
    case 2:
        cout << "Gasolina seleccionada: Premium" << endl;
        return "Premium";
    case 3:
        cout << "Gasolina seleccionada: EcoExtra" << endl;
        return "EcoExtra";
    default:
        // Este caso no debería ocurrir, pero lo incluimos como manejo de errores
        cout << "Error inesperado." << endl;
        return "";
    }
}

string funcionesApoyo::seleccionarMetodoPago() {
    string seleccion;

    // Mostrar opciones de métodos de pago disponibles
    cout << "Selecciona el metodo de pago:" << endl;
    cout << "E. Efectivo" << endl;
    cout << "TC. Tarjeta de Credito" << endl;
    cout << "TD. Tarjeta de Debito" << endl;

    // Solicitar la selección al usuario
    while (true) {
        cout << "Ingresa el metodo de pago (E/TC/TD): ";
        cin >> seleccion;

        // Convertir la entrada a minúsculas para realizar las comparaciones
        if (seleccion == "e" || seleccion == "E") {
            cout << "Metodo de pago seleccionado: Efectivo" << endl;
            return "E";
        } else if (seleccion == "tc" || seleccion == "TC") {
            cout << "Metodo de pago seleccionado: Tarjeta de Credito" << endl;
            return "TC";
        } else if (seleccion == "td" || seleccion == "TD") {
            cout << "Metodo de pago seleccionado: Tarjeta de Debito" << endl;
            return "TD";
        } else {
            cout << "Error: opcion no valida. Por favor, intenta de nuevo." << endl;
        }
    }
}

string funcionesApoyo::seleccionarModeloIsla() {
    int opcion = 0;
    bool opcionValida = false;

    // Bucle hasta que el usuario ingrese una opción válida
    while (!opcionValida) {
        cout << "Seleccione el modelo de la isla:\n";
        cout << "1. Modelo-X\n";
        cout << "2. Modelo-Y\n";
        cout << "3. Modelo-Z\n";
        cout << "Ingrese el numero correspondiente a su seleccion: ";
        cin >> opcion;

        // Validar si la opción ingresada es válida
        switch (opcion) {
        case 1:
            return "Modelo-X";
        case 2:
            return "Modelo-Y";
        case 3:
            return "Modelo-Z";
        default:
            cout << "Error: Opcion invalida. Intente nuevamente.\n";
            cin.clear(); // Limpiar el estado de error de cin
            cin.ignore('\n'); // Ignorar la entrada incorrecta
            break;
        }
    }

    return "";  // Nunca debería llegar aquí, pero es una buena práctica
}


bool funcionesApoyo::validarIdUsuario(const string &idUsuario) {
    // Verificar que la longitud esté entre 8 y 10 caracteres
    int longitud = idUsuario.length();
    if (longitud < 8 || longitud > 10) {
        cout << "Error: El ID de usuario debe tener entre 8 y 10 digitos." << endl;
        return false;
    }

    // Verificar que todos los caracteres sean números
    for (int i = 0; i < longitud; i++) {
        if (idUsuario[i] < '0' || idUsuario[i] > '9') {
            cout << "Error: El ID de usuario solo puede contener numeros." << endl;
            return false;
        }
    }

    // Si pasa ambas validaciones
    return true;
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

string funcionesApoyo::addPadding(const string &str) {
    return "  " + str + "  ";  // Agrega un espacio antes y después de la cadena
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

void funcionesApoyo::leerArchivoPrecios(const string &archivoPrecios) {
    ifstream archivoEntrada(archivoPrecios);
    string linea;

    if (archivoEntrada.is_open()) {
        while (getline(archivoEntrada, linea)) {
            if (!linea.empty() && linea.find_first_not_of(' ') != string::npos) { // Verifica que la línea no esté vacía
                procesarPrecios(linea); // Procesa la línea si no está vacía
            }
        }
        archivoEntrada.close();
    } else {
        cerr << "Error: No se pudo abrir el archivo de precios." << endl;
    }
}

void funcionesApoyo::procesarPrecios(const string &linea) {
    if (linea[0] == '#' || linea.empty()) return;  // Ignorar comentarios o líneas vacías

    stringstream ss(linea);
    string region, regularStr, premiumStr, ecoExtraStr;
    double regular, premium, ecoExtra;

    // Leer el formato con el delimitador '|'
    getline(ss, region, '|');
    getline(ss, regularStr, '|');
    getline(ss, premiumStr, '|');
    getline(ss, ecoExtraStr, '|');

    // Quitar espacios en blanco alrededor de los valores
    region = trim(region);
    regular = stod(trim(regularStr));
    premium = stod(trim(premiumStr));
    ecoExtra = stod(trim(ecoExtraStr));

    // Guardar los precios en el arreglo 'precios'
    if (region == "Norte") {
        precios[0][0] = region;
        precios[0][1] = to_string(regular);
        precios[0][2] = to_string(premium);
        precios[0][3] = to_string(ecoExtra);
    } else if (region == "Sur") {
        precios[1][0] = region;
        precios[1][1] = to_string(regular);
        precios[1][2] = to_string(premium);
        precios[1][3] = to_string(ecoExtra);
    } else if (region == "Centro") {
        precios[2][0] = region;
        precios[2][1] = to_string(regular);
        precios[2][2] = to_string(premium);
        precios[2][3] = to_string(ecoExtra);
    }
}

double funcionesApoyo::solicitarPrecio(string tipoCombustible) {
    double precio;
    cout << "Ingrese el precio para " << tipoCombustible << ": ";
    cin >> precio;
    return precio;
}

double funcionesApoyo::obtenerPrecioGasolina(const string &region, const string &tipoGasolina) {
    int fila;
    double precioPorLitro = 0.0;

    // Determinar la fila de precios según la región
    if (region == "Norte") {
        fila = 0;
    } else if (region == "Centro") {
        fila = 2;
    } else if (region == "Sur") {
        fila = 1;
    } else {
        cout << "Region no valida." << endl;
        return 0; // Salimos de la función si la región no es válida
    }

    // Asignar el precio basado en el tipo de gasolina
    if (tipoGasolina == "Regular") {
        precioPorLitro = stod(trim(precios[fila][1])); // Regular
    } else if (tipoGasolina == "Premium") {
        precioPorLitro = stod(trim(precios[fila][2])); // Premium
    } else if (tipoGasolina == "EcoExtra") {
        precioPorLitro = stod(trim(precios[fila][3])); // EcoExtra
    } else {
        cout << "Tipo de gasolina no valido." << endl;
        return 0; // Salimos de la función si el tipo de gasolina no es válido
    }

    return precioPorLitro;
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

void funcionesApoyo::mostrarPrecios() {
    cout << "\nPrecios de Combustible:\n";

    cout << fixed << setprecision(2);  // Establece la precisión a 2 decimales

    // Convertir strings a double para aplicar el formato adecuado
    for (int i = 0; i < 3; ++i) {
        for (int j = 1; j <= 3; ++j) {
            // Convertir string a double y luego mostrar con 2 decimales
            double precio = stod(precios[i][j]);
            cout << fixed << setprecision(2) << precio;

            if (j == 1) cout << " (Regular) | ";
            else if (j == 2) cout << " (Premium) | ";
            else cout << " (EcoExtra)";
        }
        cout << endl;
    }
}


bool funcionesApoyo::loginUsuario() {
    string usuarioIngresado, contrasenaIngresada;
    string linea, usuarioArchivo, contrasenaArchivo;
    bool accesoConcedido = false;

    // Solicitar credenciales al usuario
    cout <<"\n";
    cout <<"Ingrese su usuario: " << endl;
    cin >> usuarioIngresado;
    cout <<"\n";
    cout <<"Ingrese su clave: " << endl;
    cin >> contrasenaIngresada;

    // Abrir el archivo de usuarios
    ifstream archivoUsuarios("usuarios.txt");

    if (archivoUsuarios.is_open()) {
        while (getline(archivoUsuarios, linea)) {
            stringstream ss(linea);
            getline(ss, usuarioArchivo, '|');
            getline(ss, contrasenaArchivo);

            // Quitar espacios en blanco
            usuarioArchivo = trim(usuarioArchivo);
            contrasenaArchivo = trim(contrasenaArchivo);

            // Validar credenciales
            if (usuarioIngresado == usuarioArchivo && contrasenaIngresada == contrasenaArchivo) {
                accesoConcedido = true;
                gerente = (usuarioIngresado != "empleado.estandar");

                // Mensaje de bienvenida
                if (gerente) {
                    cout << "\nBienvenido, " << usuarioIngresado << ".\n";
                } else {
                    cout << "\nBienvenido empleado.\n";
                }
                break;
            }
        }
        archivoUsuarios.close();
    } else {
        cerr << "No se pudo abrir el archivo de usuarios.\n";
    }

    if (!accesoConcedido) {
        cout << "Usuario o clave incorrectos. Intente de nuevo.\n";
        return false;
    }
    return true;
}

bool funcionesApoyo::esGerente() const{
    return gerente;
}

void funcionesApoyo::mostrarMenuAdministrador(){
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "--- Menu de Administrador ---\n";
    cout << "1 - Gestion de la red\n";
    cout << "2 - Gestion de estaciones de servicio\n";
    cout << "3 - Sistema nacional de verificacion de fugas\n";
    cout << "4 - Simulacion de ventas\n";
    cout << "0 - Salir\n";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "Seleccione una opcion: ";
}

void funcionesApoyo::mostrarMenuEmpleado(){
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "--- Menu de Empleado ---\n";
    cout << "1 - Gestion de estaciones de servicio\n";
    cout << "2 - Simulacion de ventas\n";
    cout << "0 - Salir\n";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "Seleccione una opcion: ";
}

void funcionesApoyo::mostrarSubMenuGestionRed() {
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " - Opciones de gestion de la red:\n";
    cout << "1. Agregar estacion de servicio.\n";
    cout << "2. Eliminar estacion de servicio (si no tiene surtidores activos).\n";
    cout << "3. Calcular monto total de ventas.\n";
    cout << "4. Fijar precios del combustible por region.\n";
    cout << "0. Volver al menu principal.\n";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "Seleccione una opcion: ";
}

void funcionesApoyo::mostrarSubMenuGestionEstaciones(){
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " - Gestion de estaciones de servicio:\n";
    cout << "1. Agregar/eliminar un surtidor a una E/S.\n";
    cout << "2. Activar/desactivar un surtidor de una E/S.\n";
    cout << "3. Consultar el historico de transacciones de cada surtidor de la E/S.\n";
    cout << "4. Reportar la cantidad de litros vendidos segun cada categoria de combustible.\n";
    cout << "5. Simular una venta de combustible.\n";
    cout << "0. Volver al menu principal\n";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "Seleccione una opcion: ";
}

void funcionesApoyo::mostrarSubMenuVerificacionFugas(){
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " - Sistema nacional de verificacion de fugas:\n";
    cout << "1. Detectar fugas en una estacion especifica.\n";
    cout << "0. Volver al menu principal\n";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "Seleccione una opcion: ";
}

void funcionesApoyo::mostrarSubMenuSimulacionVentas(){
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << " - Simulacion de ventas:\n";
    cout << "1. Simular una venta en una estacion de servicio.\n";
    cout << "0. Volver al menu principal\n";
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
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

void funcionesApoyo::agregarTransaccion(const string &codigoEstacion, const string &codigoIsla, const string &fecha, const string &hora, const string tipoGasolina, int litrosVendidos, const string &metodoPago, const string &idUsuario, int precioPorLitro, int montoPagado) {
    if (totalnewTransacciones < 1000) {
        // Asignar los valores al arreglo de transacciones
        newTransaccion[totalnewTransacciones][0] = codigoEstacion;
        newTransaccion[totalnewTransacciones][1] = codigoIsla;
        newTransaccion[totalnewTransacciones][2] = fecha;
        newTransaccion[totalnewTransacciones][3] = hora;
        newTransaccion[totalnewTransacciones][4] = tipoGasolina;
        newTransaccion[totalnewTransacciones][5] = to_string(litrosVendidos);
        newTransaccion[totalnewTransacciones][6] = metodoPago;
        newTransaccion[totalnewTransacciones][7] = idUsuario;
        newTransaccion[totalnewTransacciones][8] = to_string(precioPorLitro);
        newTransaccion[totalnewTransacciones][9] = to_string(montoPagado);

        // Incrementar el total de transacciones
        totalnewTransacciones++;
    } else {
        cout << "Error: No se pueden agregar mas transacciones, limite alcanzado." << endl;
    }
    transferirNuevaTransaccion();
}


void funcionesApoyo::agregarIsla(const string &codigoEstacion, const string &codigoIsla, const string &modelo, int estado, int vendidoRegular, int vendidoPremium, int vendidoEcoExtra) {
    bool estacionEncontrada = false;
    for (int i = 0; i < totalEstaciones; i++) {
        if (trim(estaciones[i][0]) == trim(codigoEstacion)) {
            estacionEncontrada = true;

            // Inicializar las capacidades por si no se encuentra una isla para esta estación
            int capacidadRegular = 0;
            int capacidadPremium = 0;
            int capacidadEcoExtra = 0;
            bool islaEncontrada = false;

            // Buscar las capacidades en el arreglo de islas
            for (int j = 0; j < totalIslas; j++) {
                if (trim(islas[j][0]) == trim(codigoEstacion)) {
                    capacidadRegular = stoi(islas[j][7]);
                    capacidadPremium = stoi(islas[j][8]);
                    capacidadEcoExtra = stoi(islas[j][9]);
                    islaEncontrada = true;
                    break;
                }
            }

            // Si no se encontró la isla en islas, tomar las capacidades de estaciones
            if (!islaEncontrada){
                for (int k = 0; k < totalEstaciones; k++) {
                    if (trim(estaciones[k][0]) == trim(codigoEstacion)){
                        capacidadRegular = stoi(estaciones[k][6]);
                        capacidadPremium = stoi(estaciones[k][7]);
                        capacidadEcoExtra = stoi(estaciones[k][8]);
                    }
                }
            }

            // Agregar la nueva isla al arreglo newIsla
            if (totalnewIsla < MAX_ISLAS) {
                newIsla[totalnewIsla][0] = codigoEstacion;
                newIsla[totalnewIsla][1] = codigoIsla;
                newIsla[totalnewIsla][2] = modelo;
                newIsla[totalnewIsla][3] = to_string(estado);
                newIsla[totalnewIsla][4] = to_string(vendidoRegular);
                newIsla[totalnewIsla][5] = to_string(vendidoPremium);
                newIsla[totalnewIsla][6] = to_string(vendidoEcoExtra);
                newIsla[totalnewIsla][7] = to_string(capacidadRegular);
                newIsla[totalnewIsla][8] = to_string(capacidadPremium);
                newIsla[totalnewIsla][9] = to_string(capacidadEcoExtra);

                totalnewIsla++;
            } else {
                cout << "Error: No se pueden agregar mas surtidores, limite alcanzado." << endl;
            }
            break;
        }
    }

    if (!estacionEncontrada) {
        cout << "Error: Estacion no encontrada." << endl;
    }

    // Transferir la nueva isla al arreglo islas
    transferirNuevaIsla();
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

void funcionesApoyo::cambiarEstadoEstacion(const string &codigoEstacion, const string &codigoIsla, int nuevoEstado) {
    bool estacionEncontrada = false;

    for (int i = 0; i < totalIslas; i++) {
        if (trim(islas[i][0]) == trim(codigoEstacion) && trim(islas[i][1]) == trim(codigoIsla)) {
            // Actualizar el estado de la estación (posición 3 en el arreglo islas)
            islas[i][3] = to_string(nuevoEstado);
            estacionEncontrada = true;
            cout << "Estado de la estacion " << codigoEstacion << " - Isla " << codigoIsla << " cambiado a " << nuevoEstado << endl;
            break;
        }
    }

    if (!estacionEncontrada) {
        cout << "Error: Estacion o isla no encontrada." << endl;
    }
}

// Función para mostrar el historial de transacciones filtrado
void funcionesApoyo::mostrarHistoricoTransacciones(const string& codigoEstacion, const string& codigoIsla, int opcionEstacion, int opcionIsla) {
    cout << "\nHistorico de Transacciones: " << endl;

    // Variables para saber si estamos en una nueva estación
    string estacionActual = "";

    for (int i = 0; i < totalTransacciones; i++) {
        // Filtrar por estación
        bool coincideEstacion = (opcionEstacion == 1) || (trim(transacciones[i][0]) == codigoEstacion);
        bool coincideIsla = (opcionIsla == 1) || (trim(transacciones[i][1]) == codigoIsla);

        // Si la transacción coincide con los filtros de estación e isla, se imprime
        if (coincideEstacion && coincideIsla) {
            // Verifica si se cambia de estación y muestra encabezado
            if (trim(transacciones[i][0]) != estacionActual) {
                estacionActual = trim(transacciones[i][0]);
                cout << "\nEstacion: " << estacionActual << endl;
            }

            cout << "Isla: " << transacciones[i][1]
                 << " | Fecha: " << transacciones[i][2]
                 << " | Hora: " << transacciones[i][3]
                 << " | Combustible: " << transacciones[i][4]
                 << " | Litros Vendidos: " << transacciones[i][5]
                 << " | Metodo de Pago: " << transacciones[i][6]
                 << " | ID Usuario: " << transacciones[i][7]
                 << " | Precio/Litro: " << transacciones[i][8]
                 << " | Total Venta: " << transacciones[i][9]
                 << endl;
        }
    }
}

void funcionesApoyo::mostrarReporteCVendido(int opcionCombustible){

    int totalRegular, totalPremium, totalEcoExtra;

    // Recorremos el arreglo para sumar los litros vendidos por tipo de combustible
    for (int i = 0; i < totalIslas; i++) {
    switch (opcionCombustible) {
    case 1: // Regular
        totalRegular += stoi(islas[i][4]);
        break;
    case 2: // Premium
        totalPremium += stoi(islas[i][5]);
        break;
    case 3: // EcoExtra
        totalEcoExtra += stoi(islas[i][6]);
        break;
    case 4: // Todos
        totalRegular += stoi(islas[i][4]);
        totalPremium += stoi(islas[i][5]);
        totalEcoExtra += stoi(islas[i][6]);
        break;
    default:
        cout << "Opcion invalida." << endl;
        return;
    }
}

    // Imprimimos el resultado del reporte según el tipo de combustible seleccionado
    cout << "\nReporte de Combustible Vendido:" << endl;
    if (opcionCombustible == 1 || opcionCombustible == 4) {
        cout << "Total Regular vendido: " << totalRegular << " litros" << endl;
    }
    if (opcionCombustible == 2 || opcionCombustible == 4) {
        cout << "Total Premium vendido: " << totalPremium << " litros" << endl;
    }
    if (opcionCombustible == 3 || opcionCombustible == 4) {
        cout << "Total EcoExtra vendido: " << totalEcoExtra << " litros" << endl;
    }
}

void funcionesApoyo::transferirNuevaEstacion(){
    // Copiar los datos de newEstacion al arreglo estaciones
    for (int i = 0; i < totalnewEstacion; i++) {
        for (int j = 0; j < 9; j++) {
            estaciones[totalEstaciones][j] = newEstacion[i][j];
        }
        totalEstaciones++; // Incrementar el contador de estaciones
    }

    // Limpiar el arreglo newEstacion y restablecer totalnewEstacion a 0
    for (int i = 0; i < totalnewEstacion; i++) {
        for (int j = 0; j < 9; j++) {
            newEstacion[i][j].clear(); // Limpiar cada campo de newEstacion
        }
    }
    totalnewEstacion = 0; // Reiniciar el contador de nuevas estaciones
}

void funcionesApoyo::transferirNuevaTransaccion() {
    // Copiar los datos de newTransaccion al arreglo transacciones
    for (int i = 0; i < totalnewTransacciones; i++) {
        for (int j = 0; j < 10; j++) {
            transacciones[totalTransacciones][j] = newTransaccion[i][j];
        }
        totalTransacciones++;
    }

    // Limpiar el arreglo newTransaccion y restablecer totalnewTransacciones a 0
    for (int i = 0; i < totalnewTransacciones; i++) {
        for (int j = 0; j < 10; j++) {
            newTransaccion[i][j].clear();
        }
    }
    totalnewTransacciones = 0; // Reiniciar el contador de nuevas transacciones
}

void funcionesApoyo::transferirNuevaIsla(){
    // Copiar los datos de newisla al arreglo islas
    for (int i = 0; i < totalnewIsla; i++) {
        for (int j = 0; j < 10; j++) {
            islas[totalIslas][j] = newIsla[i][j];
        }
        totalIslas++;
    }

    // Limpiar el arreglo newTransaccion y restablecer totalnewIsla a 0
    for (int i = 0; i < totalnewIsla; i++) {
        for (int j = 0; j < 10; j++) {
            newIsla[i][j].clear();
        }
    }
    totalnewIsla = 0; // Reiniciar el contador de nuevas islas
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

bool funcionesApoyo::obtenerDetallesEstacion(const string &codigoEstacion, string &nombreEstacion, string &regionEstacion) {
    for (int i = 0; i < totalEstaciones; ++i) {
        if (trim(estaciones[i][0]) == codigoEstacion) {
            nombreEstacion = trim(estaciones[i][1]);
            regionEstacion = trim(estaciones[i][4]);
            return true; // Detalles encontrados
        }
    }
    cout << "No se encontro la estacion con el codigo especificado." << endl;
    return false; // No se encontró la estación
}

string funcionesApoyo::seleccionarEstacion(){
    if (totalEstaciones == 0){
        cout << "No hay estaciones disponibles." << endl;
        return ""; // Indica que no hay estaciones
    }
    // Muestra todas las estaciones disponibles
    for (int i = 0; i < totalEstaciones; ++i) {
        cout << i + 1 << " - " << trim(estaciones[i][0]) << " - " << trim(estaciones[i][1]) << endl;
    }

    // Solicita al usuario que seleccione una estacion
    int seleccion = 0;
    cout << "Ingrese el numero de la estacion que desea seleccionar: ";
    cin >> seleccion;

    // Validar que la seleccion sea valida
    while (seleccion < 1 || seleccion > totalEstaciones) {
        cout << "Seleccion invalida. Intente de nuevo: ";
        cin >> seleccion;
    }

    // Retorna el código de la estación seleccionada
    return trim(estaciones[seleccion - 1][0]);
}

string funcionesApoyo::seleccionarIslaAleatoria(int codigoEstacion) {
    int contador = 0;
    cout << "Islas activas en la estacion " << codigoEstacion << ":" << endl;

    for (int i = 0; i < totalIslas; ++i) {
        // Verificar si la isla pertenece a la estación seleccionada y está activa
        if (stoi(trim(islas[i][0])) == codigoEstacion && trim(islas[i][3]) == "1") {
            cout << contador + 1 << ". Isla codigo: " << trim(islas[i][1]) << endl;
            islasActivas[contador] = trim(islas[i][1]);
            contador++;
        }
    }

    if (contador == 0) {
        cout << "No hay islas activas en esta estacion." << endl;
        return "";
    }

    // Semilla para generar numero aleatorios
    srand(static_cast<unsigned int>(time(0)));

    // Seleccionar un índice aleatorio en el rango de islas activas
    int indiceAleatorio = rand() % contador;

    // Devolver el codigo de la isla seleccionada aleatoriamente
    string islaSeleccionada = islasActivas[indiceAleatorio];
    cout << "Isla seleccionada aleatoriamente: " << islaSeleccionada << endl;
    return islaSeleccionada;
}

string funcionesApoyo::seleccionarIsla(string &codigoEstacion) {
    int contador = 0;
    cout << "Islas activas en la estacion " << codigoEstacion << ":" << endl;

    string islasActivas[100];

    for (int i = 0; i < totalIslas; ++i) {
        // Verificar si la isla pertenece a la estación seleccionada
        if (trim(islas[i][0]) == codigoEstacion) {
            cout << contador + 1 << ". Isla codigo: " << trim(islas[i][1]) << " - Estado: ";

            // Verificar el estado de la isla
            if (stoi(trim(islas[i][3])) == 1) {
                cout << "Activa" << endl;
            } else {
                cout << "Inactiva" << endl;
            }

            // Guardar el código de la isla activa
            islasActivas[contador] = trim(islas[i][1]);
            contador++;
        }
    }

    // Verificar si hay islas activas en la estación
    if (contador == 0) {
        cout << "No hay islas activas en esta estacion." << endl;
        return "";
    }

    // Solicita al usuario que seleccione una isla
    int seleccion = 0;
    cout << "Ingrese el numero de la isla que desea seleccionar: ";
    cin >> seleccion;

    // Validar que la selección sea válida
    while (seleccion < 1 || seleccion > contador) {
        cout << "Seleccion invalida. Intente de nuevo: ";
        cin >> seleccion;
    }

    // Retorna el código de la isla seleccionada
    return islasActivas[seleccion - 1];
}


int funcionesApoyo::generarVentaAleatoria(const string codigoEstacion, const string& tipoGasolina, const string& codigoIsla) {
    // Generar un número aleatorio entre 3 y 20 litros
    srand(static_cast<unsigned int>(time(0)));
    int litrosSolicitados = rand() % 18 + 3; // Genera un número entre 3 y 20

    // Buscar la estación seleccionada en el arreglo estaciones
    int indiceEstacion = -1;
    for (int i = 0; i < totalEstaciones; ++i) {
        if (trim(estaciones[i][0]) == codigoEstacion) {
            indiceEstacion = i;
            break;
        }
    }

    if (indiceEstacion == -1) {
        cout << "Error: Estacion no encontrada." << endl;
        return -1; // Error, estación no encontrada
    }

    // Verificar si hay suficiente gasolina disponible y realizar la venta
    realizarVenta(codigoEstacion, codigoIsla, litrosSolicitados, tipoGasolina);

    return litrosSolicitados; // Devuelve la cantidad de litros solicitados
}

int funcionesApoyo::verificarCantidadDisponible(const string &codigoEstacion, const string &codigoIsla, const string &tipoGasolina) {
    int cantidadDisponible = -1;

    // Buscar la isla correspondiente según el código de estación y el código de isla
    for (int i = 0; i < totalIslas; ++i) {
        if (trim(islas[i][0]) == trim(codigoEstacion) && trim(islas[i][1]) == trim(codigoIsla)) {
            // Verificar el tipo de gasolina y obtener la cantidad disponible
            if (tipoGasolina == "Regular") {
                cantidadDisponible = stoi(trim(islas[i][7])); // Cantidad de Regular
            } else if (tipoGasolina == "Premium") {
                cantidadDisponible = stoi(trim(islas[i][8])); // Cantidad de Premium
            } else if (tipoGasolina == "EcoExtra") {
                cantidadDisponible = stoi(trim(islas[i][9])); // Cantidad de EcoExtra
            } else {
                cout << "Error: Tipo de gasolina no valido." << endl;
            }
            break;
        }
    }
    if (cantidadDisponible == -1){
        cout << "Error: No se encontro la isla o el tipo de gasolina no es valido." << endl;
    }

    return cantidadDisponible; // Devolver la cantidad disponible
}

void funcionesApoyo::realizarVenta(const string &codigoEstacion, const string &codigoIsla, int litrosSolicitados, const string &tipoGasolina) {

    int indiceIsla = -1;

    // Buscar la isla correspondiente según el código de estación y el código de isla
    for (int i = 0; i < totalIslas; ++i) {
        if (trim(islas[i][0]) == trim(codigoEstacion) && trim(islas[i][1]) == trim(codigoIsla)) {
            indiceIsla = i;
            break;
        }
    }

    if (indiceIsla == -1){
        cout << "Error: No se encontro la isla especificada en la estacion." << endl;
        return;
    }
    // Verificar la cantidad disponible de gasolina
    int cantidadDisponible = verificarCantidadDisponible(codigoEstacion, codigoIsla, tipoGasolina);
    if (cantidadDisponible == -1) {
        cout << "Error al verificar la cantidad disponible." << endl;
        return;
    }

    // Determinar la cantidad a vender (mínimo entre litros solicitados y disponibles)
    int litrosAVender = std::min(litrosSolicitados, cantidadDisponible);

    if (litrosAVender > 0) {
        cout << "Se pueden vender " << litrosAVender << " litros de " << tipoGasolina << "." << endl;

        // Restar la cantidad vendida en la isla donde se realiza la venta
        int nuevaCantidad = cantidadDisponible - litrosAVender;
        cout << "La cantidad disponible era: " << cantidadDisponible << ". Se vendio la cantidad de: " << litrosAVender << ". La reserva de combustible queda en: " << nuevaCantidad << endl;

        // Actualizar la cantidad de gasolina en la isla donde se realiza la venta
        if (tipoGasolina == "Regular") {
            islas[indiceIsla][7] = addPadding(to_string(nuevaCantidad));
            actualizarVentasPorIsla(codigoEstacion, codigoIsla, litrosAVender, "Regular");
        } else if (tipoGasolina == "Premium") {
            islas[indiceIsla][8] = addPadding(to_string(nuevaCantidad));
            actualizarVentasPorIsla(codigoEstacion, codigoIsla, litrosAVender, "Premium");
        } else if (tipoGasolina == "EcoExtra") {
            islas[indiceIsla][9] = addPadding(to_string(nuevaCantidad));
            actualizarVentasPorIsla(codigoEstacion, codigoIsla, litrosAVender, "EcoExtra");
        }

        // Actualizar las cantidades restantes en todas las islas de la misma estación
        for (int i = 0; i < totalIslas; ++i) {
            if (trim(islas[i][0]) == codigoEstacion && i != indiceIsla) {
                // Actualizar la cantidad restante en las islas de la misma estación
                if (tipoGasolina == "Regular") {
                    islas[i][7] = addPadding(to_string(stoi(islas[i][7]) - litrosAVender)); // columna 7 para Regular
                } else if (tipoGasolina == "Premium") {
                    islas[i][8] = addPadding(to_string(stoi(islas[i][8]) - litrosAVender)); // columna 8 para Premium
                } else if (tipoGasolina == "EcoExtra") {
                    islas[i][9] = addPadding(to_string(stoi(islas[i][9]) - litrosAVender)); // columna 9 para EcoExtra
                }

                // Verificar si los tres tanques están en cero
                int regular = stoi(islas[i][7]);
                int premium = stoi(islas[i][8]);
                int ecoExtra = stoi(islas[i][9]);

                if (regular == 0 && premium == 0 && ecoExtra == 0) {
                    // Actualizar el estado de la isla a 0 (inactiva)
                    islas[i][3] = "0";
                    cout << "La isla con codigo " << islas[i][1] << " esta ahora inactiva porque todos los tanques estan vacios." << endl;
                }
            }
        }
    }else {
        cout << "No hay suficiente gasolina para completar la venta." << endl;
    }
}


void funcionesApoyo::actualizarVentasPorIsla(const string &codigoEstacion, const string &codigoIsla, int litrosVendidos, const string &tipoGasolina) {
    // Buscar la isla correspondiente
    for (int i = 0; i < totalIslas; ++i) {
        if (trim(islas[i][0]) == trim(codigoEstacion) && trim(islas[i][1]) == trim(codigoIsla)) {
            // Actualizar la cantidad de gasolina vendida según el tipo de gasolina
            if (tipoGasolina == "Regular") {
                islas[i][4] = addPadding(to_string(stoi(islas[i][4]) + litrosVendidos)); // columna 4 para Regular
            } else if (tipoGasolina == "Premium") {
                islas[i][5] = addPadding(to_string(stoi(islas[i][4]) + litrosVendidos)); // columna 5 para Premium
            } else if (tipoGasolina == "EcoExtra") {
                islas[i][6] = addPadding(to_string(stoi(islas[i][4]) + litrosVendidos)); // columna 6 para EcoExtra
            }

            cout << "Actualizada la venta en la isla " << codigoIsla << ": "
                 << litrosVendidos << " litros de " << tipoGasolina << endl;
            return;
        }
    }

    // Si la isla no se encuentra
    cout << "Error: No se encontro la isla con codigo " << codigoIsla << endl;
}


void funcionesApoyo::agregarsEstacion(const string &codigo, const string &nombre){
    if (totalEstaciones < MAX_ESTACIONES) {
        sEstacion[totalEstaciones][0] = codigo;  // Codigo de la estacion
        sEstacion [totalEstaciones][1] = nombre;  // Nombre de la estacion
        totalEstaciones++;
        // Mostrar las estaciones almacenadas
        cout << "Estaciones almacenadas:" << endl;
        for (int i = 0; i < totalEstaciones; ++i) {
            if (!sEstacion[i][0].empty() && !sEstacion[i][1].empty()){
            cout << sEstacion[i][0] << " - " << sEstacion[i][1] << endl;
            }
        }
    } else {
        cout << "No se pueden agregar mas estaciones." << endl;
    }
}

bool funcionesApoyo::eliminarIslaPorCodigo(const string& codigoEstacion, const string& idIsla) {
    int posicion = -1;

    // Buscar la posición de la isla con el código dado
    for (int i = 0; i < totalIslas; i++) {
        if (trim(islas[i][0]) == codigoEstacion && trim(islas[i][1]) == idIsla) {
            posicion = i;
            break;
        }
    }

    // Si no se encuentra la isla, retornar falso
    if (posicion == -1) {
        return false;
    }

    // Desplazar islas una posición hacia atrás para eliminar la isla
    for (int j = posicion; j < totalIslas - 1; j++) {
        for (int k = 0; k < MAX_COLUMNAS_I; k++) {
            islas[j][k] = islas[j + 1][k];
        }
    }

    // Decrementar el total de islas y retornar verdadero para indicar éxito
    totalIslas--;
    return true;
}

void funcionesApoyo::verificarTanque(double capacidadTanque, double nivelActual, double totalVentas, const string& tipoGasolina) {
    // Cálculo para verificar la fuga
    double porcentajeOperativo = (nivelActual + totalVentas) / capacidadTanque * 100.0;

    cout << fixed << setprecision(2);

    // Si el nivel es inferior al 95%, hay una posible fuga
    if (porcentajeOperativo < 95.0) {
        cout << "Posible fuga detectada en el tanque de " << tipoGasolina << ". Operando al " << setprecision(2) << porcentajeOperativo << "% de capacidad." << endl;
    } else {
        cout << "El tanque de " << tipoGasolina << " esta operando correctamente (" << setprecision(2) << porcentajeOperativo << "% de capacidad)." << endl;
    }
}

void funcionesApoyo::guardarPrecios(const string &archivoPrecios) {
    ofstream archivoSalida(archivoPrecios);

    if (archivoSalida.is_open()) {
        archivoSalida << fixed << setprecision(2);

        // Guardar los precios de la región Norte
        archivoSalida << precios[0][0] << " | " << stod(precios[0][1]) << " | " << stod(precios[0][2]) << " | " << stod(precios[0][3]) << endl;

        // Guardar los precios de la región Sur
        archivoSalida << precios[1][0] << " | " << stod(precios[1][1]) << " | " << stod(precios[1][2]) << " | " << stod(precios[1][3]) << endl;

        // Guardar los precios de la región Centro
        archivoSalida << precios[2][0] << " | " << stod(precios[2][1]) << " | " << stod(precios[2][2]) << " | " << stod(precios[2][3]) << endl;

        archivoSalida.close();
        cout << "Los precios han sido guardados exitosamente en el archivo." << endl;
    } else {
        cerr << "Error: No se pudo abrir el archivo para guardar los precios." << endl;
    }
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

void funcionesApoyo::guardarDatos(const string &nombreArchivo) {
    ofstream archivoSalida(nombreArchivo);

    if (!archivoSalida.is_open()) {
        cerr << "Error al abrir el archivo para guardar los datos.\n";
        return;
    }

    // Guardar estaciones
    archivoSalida << "%\n";
    for (int i = 0; i < totalEstaciones; ++i) {
        bool filaValida = false;

        // Verificar si hay al menos un campo no vacío
        for (int j = 0; j < 9; ++j) {
            if (!trim(estaciones[i][j]).empty()) {
                filaValida = true;
                break;
            }
        }

        // Solo guardar la estación si es válida (no está completamente vacía)
        if (filaValida) {
            for (int j = 0; j < 9; ++j) {
                archivoSalida << trim(estaciones[i][j]);
                if (j < 8) archivoSalida << " | "; // Agregar separador entre columnas
            }
            archivoSalida << "\n";
        }
    }
    archivoSalida << "%\n";

    // Guardar islas
    archivoSalida << "$\n";
    for (int i = 0; i < totalIslas; ++i) {
        for (int j = 0; j < 10; ++j) {
            archivoSalida << trim(islas[i][j]);
            if (j < 9) archivoSalida << " | "; // Agregar separador entre columnas
        }
        archivoSalida << "\n";
    }
    archivoSalida << "$\n";

    // Guardar transacciones
    archivoSalida << "&\n";
    for (int i = 0; i < totalTransacciones; ++i) {
        for (int j = 0; j < 10; ++j) {
            archivoSalida << trim(transacciones[i][j]);
            if (j < 9) archivoSalida << " | "; // Agregar separador entre columnas
        }
        archivoSalida << "\n";
    }
    archivoSalida << "&\n";

    archivoSalida.close();
    cout << "Datos guardados correctamente en " << nombreArchivo << endl;
}



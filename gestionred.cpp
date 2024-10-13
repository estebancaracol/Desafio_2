#include "gestionred.h"
#include <iostream>

using namespace std;

gestionRed::gestionRed() {

    precioCombustibleNorte[0] = 4500.0;  // Regular
    precioCombustibleNorte[1] = 4800.0;  // Premium
    precioCombustibleNorte[2] = 4700.0;  // EcoExtra

    precioCombustibleSur[0] = 4300.0;    // Regular
    precioCombustibleSur[1] = 4600.0;    // Premium
    precioCombustibleSur[2] = 4500.0;    // EcoExtra

    precioCombustibleCentro[0] = 4400.0; // Regular
    precioCombustibleCentro[1] = 4700.0; // Premium
    precioCombustibleCentro[2] = 4600.0; // EcoExtra

}

void gestionRed::fijarPreciosCombustible(double precioNorte[3], double precioSur[3], double precioCentro[3]){
    for (int i = 0; i < 3; ++i){
        precioCombustibleNorte[i] = precioNorte[i];
        precioCombustibleSur[i] = precioSur[i];
        precioCombustibleCentro[i] = precioCentro[i];
    }
}

void gestionRed::cambiarPrecioCombustiblePorRegion(const string &region, double nuevoPrecio[3]){
    if (region == "Norte") {
        for (int i = 0; i < 3; ++i) {
            precioCombustibleNorte[i] = nuevoPrecio[i];
        }
    } else if (region == "Sur") {
        for (int i = 0; i < 3; ++i) {
            precioCombustibleSur[i] = nuevoPrecio[i];
        }
    } else if (region == "Centro") {
        for (int i = 0; i < 3; ++i) {
            precioCombustibleCentro[i] = nuevoPrecio[i];
        }
    } else {
        cout << "Region no valida." << endl;
    }
}

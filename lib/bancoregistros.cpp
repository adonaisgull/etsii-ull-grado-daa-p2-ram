
#include "bancoregistros.h"
#include <iostream>

using namespace std;

void BancoRegistros::mostrar() {

    cout << "R[0] = " << registros[0] << " (ACUMULADOR)" << endl;

    for(unsigned i = 1; i < registros.size(); i++)
        cout << "R[" << i << "] = " << registros[i] << endl;
}

void BancoRegistros::mostrarEnLinea() {

    cout << "[";
    for(unsigned i = 0; i < registros.size(); i++)
        cout << i << ":" << registros[i] << ", ";
    cout << "]";
}

void BancoRegistros::inicializar() {
    for(unsigned i = 0; i < registros.size(); i++)
        registros[i] = 0;
}

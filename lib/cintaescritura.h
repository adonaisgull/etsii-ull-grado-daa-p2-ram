#ifndef CINTAESCRITURA_H
#define CINTAESCRITURA_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class CintaEscritura {

    vector<int> cinta;

public:
    CintaEscritura() {}
    inline void escribirDato(int dato) { cinta.push_back(dato); }

    void mostrar();
    void mostrarEnLinea();
    void inicializar() { cinta.clear(); }
    void volcar(string);
};

#endif // CINTAESCRITURA_H

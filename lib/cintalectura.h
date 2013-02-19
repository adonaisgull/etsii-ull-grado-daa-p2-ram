#ifndef CINTALECTURA_H
#define CINTALECTURA_H

#define IO_ERROR 999999999

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class CintaLectura {

    unsigned cabezal;
    vector<int> cinta;

public:
    CintaLectura() {}
    CintaLectura(vector<int> _cinta) { cinta = _cinta; cabezal = 0; }
    int leerDato();
    void mostrar();

    void inicializar() { cinta.clear(); cabezal = 0; }
    void cargar(string);
};

#endif // CINTALECTURA_H

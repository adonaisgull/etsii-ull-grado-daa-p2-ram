#ifndef DICCIONARIO_ETIQUETAS_H
#define DICCIONARIO_ETIQUETAS_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class DiccionarioEtiquetas {

    class Etiqueta {

        string etiqueta;
        int posicion_instruccion;
    public:
        inline Etiqueta(string etiq, int pos) { etiqueta = etiq; posicion_instruccion = pos; }
        inline string getEtiqueta() { return etiqueta; }
        inline int getPosicionInstruccion() { return posicion_instruccion; }
    };

    vector<Etiqueta> etiquetas;

public:

    DiccionarioEtiquetas() {};
    int obtenerPosicion(string);
    void insertarEtiqueta(string, int);
    void mostrar() {

        for(unsigned i = 0; i < etiquetas.size(); i++)
            cout << etiquetas[i]. getEtiqueta() << " -> " << etiquetas[i].getPosicionInstruccion() << endl;
    }
};

#endif // DICCIONARIO_ETIQUETAS_H

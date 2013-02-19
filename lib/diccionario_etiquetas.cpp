#include "diccionario_etiquetas.h"

int DiccionarioEtiquetas::obtenerPosicion(string etiq) {

    for(unsigned i = 0; i < etiquetas.size(); i++) {
        if(etiquetas[i].getEtiqueta() ==  etiq)
            return etiquetas[i].getPosicionInstruccion();
    }
    return -1;
}

void DiccionarioEtiquetas::insertarEtiqueta(string etiq, int pos) {

    etiquetas.push_back(Etiqueta(etiq, pos));
}

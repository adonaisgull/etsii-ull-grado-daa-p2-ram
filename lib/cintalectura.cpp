#include "cintalectura.h"
#include <fstream>

void CintaLectura::mostrar() {

    if(!cinta.size())
        cout << " Vacía" << endl;
    else
        for(unsigned i = 0; i < cinta.size(); i++)
            cout << " CL[" << i << "] -> " << cinta[i] << endl;
}

int CintaLectura::leerDato() {

    if(cabezal < cinta.size())
        return cinta[cabezal++];

    return IO_ERROR;
}

void CintaLectura::cargar(string nombre_fichero) {

    int dato;
    ifstream fichero(nombre_fichero.c_str(), ifstream::in);

    fichero >> dato;
    while(!fichero.eof()) {
        cinta.push_back(dato);
        fichero >> dato;
    }
    fichero.close();
}


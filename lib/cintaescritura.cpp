#include "cintaescritura.h"
#include <fstream>

void CintaEscritura::mostrar() {

    if(!cinta.size())
        cout << " Vacía" << endl;
    else
        for(unsigned i = 0; i < cinta.size(); i++)
            cout << " CE[" << i << "] -> " << cinta[i] << endl;
}

void CintaEscritura::volcar(string nombre_fichero) {

    ofstream fichero;

    fichero.open(nombre_fichero.c_str());

    for(unsigned i = 0; i < cinta.size(); i++)
        fichero << cinta[i] << endl;

    fichero.close();
}

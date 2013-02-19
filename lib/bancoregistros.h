#ifndef BANCOREGISTROS_H
#define BANCOREGISTROS_H

#include <vector>

using namespace std;

class BancoRegistros
{
    vector<int> registros;

public:
    BancoRegistros() { registros = vector<int>(32, 0); }

    inline void escribirRegistro(int numero, int dato) { registros[numero] = dato; }
    inline int leerRegistro(int numero) { return registros[numero]; }
    inline void escribirAcumulador(int dato) { registros[0] = dato; }
    inline int leerAcumulador() { return registros[0]; }

    void mostrar();
    void mostrarEnLinea();
    void inicializar();
};

#endif // BANCOREGISTROS_H

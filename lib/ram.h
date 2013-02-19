#ifndef RAM_H
#define RAM_H

#include <vector>
#include <iostream>
#include <string>
#include "instruccion.h"
#include "diccionario_etiquetas.h"
#include "cintalectura.h"
#include "cintaescritura.h"
#include "bancoregistros.h"

#define IO_ERROR 999999999

using namespace std;

class Ram {

    int pc;
    vector<Instruccion> programa;
    DiccionarioEtiquetas etiquetas;
    CintaLectura cinta_lectura;
    CintaEscritura cinta_escritura;
    BancoRegistros banco_registros;

    string fichero_codigo_fuente;
    string fichero_cinta_lectura;
    string fichero_cinta_escritura;

    enum { LOAD, STORE, ADD, SUB, MULT, DIV, READ, WRITE, JUMP, JGTZ, JZERO, HALT } CODIGO;
    enum { INMEDIATO, DIRECTO, INDIRECTO } MODO;

    // metodos privados
    void limpiarLinea(string &);          // limpia los espacios y tabuladores de la linea (por el principio) y los cometarios
    string extraerEtiqueta(string &);       // extrae la etiqueta de la linea y la elimina
    int extraerCodigoOperacion(string);
    int extraerDireccionamiento(string);
    string extraerOperando(string);
    bool hayDesbordamiento(long);

public:

    Ram() {}
    Ram(string, string, string);
    int cargarPrograma();
    void inicializar();
    void cargarCintaLectura();
    void volcarCintaEscritura();
    void ejecutarPrograma(bool);

    void mostrarRegistros();
    void mostrarCintaLectura();
    void mostrarCintaEscritura();
    void desensamblarPrograma();

    void exeLoad(int, int);
    void exeStore(int, int);
    bool exeAdd(int, int);
    bool exeSub(int, int);
    bool exeMult(int, int);
    bool exeDiv(int, int);
    void exeWrite(int, int);
    bool exeRead(int, int);
    bool exeJump(string);
    bool exeJgtz(string);
    bool exeJzero(string);

};

#endif // RAM_H

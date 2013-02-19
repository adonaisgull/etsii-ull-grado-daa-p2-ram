#ifndef INSTRUCCION_H
#define INSTRUCCION_H

#include <string>
#include <iostream>

using namespace std;

class Instruccion {

    int codigo_operacion;
    int modo_direccionamiento;
    string operando;
    int linea_en_fichero;

    enum { LOAD, STORE, ADD, SUB, MULT, DIV, READ, WRITE, JUMP, JGTZ, JZERO, HALT } CODIGO;
    enum { INMEDIATO, DIRECTO, INDIRECTO } MODO;

public:
    Instruccion() {}
    Instruccion(int, int);                   // instrucciones sin operandos
    Instruccion(int, int, string, int);      // resto de instrucciones

    inline void setCodigoOperacion(int codigo) { codigo_operacion = codigo; }
    inline void setModoDireccionamiento(int modo) { modo_direccionamiento = modo; }
    inline void setOperando(string op) { operando = op; }
    inline void setLineaEnFichero(int linea) { linea_en_fichero = linea; }

    inline int getCodigoOperacion() { return codigo_operacion; }
    inline int getModoDireccionamiento() { return modo_direccionamiento; }
    inline string getOperando() { return operando; }
    inline int getLineaEnFichero() { return linea_en_fichero; }

    string toString();
};

#endif // INSTRUCCION_H

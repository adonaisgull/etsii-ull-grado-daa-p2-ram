#include "instruccion.h"

// Constructor para instrucciones sin operandos (HALT)
Instruccion::Instruccion(int codigo, int linea) {
    setCodigoOperacion(codigo);
    setModoDireccionamiento(-1);
    setOperando("");
    setLineaEnFichero(linea);
}

// Constructor para el resto de instrucciones
Instruccion::Instruccion(int codigo, int modo, string operando, int linea) {
    setCodigoOperacion(codigo);
    setModoDireccionamiento(modo);
    setOperando(operando);
    setLineaEnFichero(linea);
}

string Instruccion::toString() {

    string instruccion;

    switch (codigo_operacion) {
    case LOAD:
        instruccion.append("LOAD");
        break;
    case STORE:
        instruccion.append("STORE");
        break;
    case ADD:
        instruccion.append("ADD");
        break;
    case SUB:
        instruccion.append("SUB");
        break;
    case MULT:
        instruccion.append("MULT");
        break;
    case DIV:
        instruccion.append("DIV");
        break;
    case READ:
        instruccion.append("READ");
        break;
    case WRITE:
        instruccion.append("WRITE");
        break;
    case JUMP:
        instruccion.append("JUMP");
        break;
    case JGTZ:
        instruccion.append("JGTZ");
        break;
    case JZERO:
        instruccion.append("JZERO");
        break;
    case HALT:
        instruccion.append("HALT");
        break;
    }

    switch(modo_direccionamiento) {

    case INMEDIATO:
        instruccion.append(" =");
        break;
    case DIRECTO:
        instruccion.append(" ");
        break;
    case INDIRECTO:
        instruccion.append(" *");
        break;
    }

    instruccion.append(operando);

    return instruccion;
}

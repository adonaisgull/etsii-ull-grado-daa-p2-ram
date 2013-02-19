#include "ram.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <limits>
#include "instruccion.h"
#include "diccionario_etiquetas.h"

using namespace std;

Ram::Ram(string cod_fuente, string cinta_esc, string cinta_lect) {
    fichero_codigo_fuente = cod_fuente;
    fichero_cinta_escritura = cinta_esc;
    fichero_cinta_lectura = cinta_lect;
}

int Ram::cargarPrograma() {

    string linea;
    string etiqueta;
    int codigo;
    string operando;
    int numero_linea;

    ifstream fichero(fichero_codigo_fuente.c_str(), ifstream::in);

    numero_linea = 1;
    getline(fichero, linea);
    while(!fichero.eof()) {

        etiqueta.clear();
        etiqueta = extraerEtiqueta(linea);    // Extraemos la etiqueta de la linea si la hubiera y se elimina lo que sobra

        if(etiqueta.size())
            etiquetas.insertarEtiqueta(etiqueta, programa.size());  // Insertarmos la etiqueta apuntando a la instruccion que estamos insertando

        if(linea.size()) {  // Si queda algo en la linea será una instruccion, por lo tanto procedemos a extraer sus elementos

            switch(codigo = extraerCodigoOperacion(linea)) {

            case LOAD:
            case STORE:
            case ADD:
            case SUB:
            case MULT:
            case DIV:
            case READ:
            case WRITE:
            case JUMP:
            case JGTZ:
            case JZERO:
                operando = extraerOperando(linea);
                programa.push_back(Instruccion(codigo, extraerDireccionamiento(linea), operando, numero_linea));
                break;
            case HALT:
                programa.push_back(Instruccion(codigo, numero_linea));
                break;
            }
        }
        numero_linea++;
        getline(fichero, linea);
    }

    fichero.close();

    return 1;
}

void Ram::inicializar() {

    pc = 0;
    programa.clear();
    cinta_lectura.inicializar();
    cinta_escritura.inicializar();
    banco_registros.inicializar();
}

void Ram::cargarCintaLectura() {

    cinta_lectura.cargar(fichero_cinta_lectura);
}

void Ram::volcarCintaEscritura() {

    cinta_escritura.volcar(fichero_cinta_escritura);
}

void Ram::ejecutarPrograma(bool traza) {

    bool parar = false;
    Instruccion instruccion;
    pc = 0;                     // Establecemos el PC en la primera posicion de la memoria
    int pos_memoria;
    char c;

    while(!parar){

        instruccion = programa[pc];
        pos_memoria = pc;

        if(traza) {
            cout << " Instruccion " << instruccion.toString() << endl;
            cout << " Estado anterior:" << endl;
            cout << "   PC: " << pc << endl;
            cout << "   AC: " << banco_registros.leerAcumulador() << endl;
            cout << "    R: "; banco_registros.mostrarEnLinea(); cout << endl;
        }

        switch (instruccion.getCodigoOperacion()) {
        case LOAD:
            exeLoad(instruccion.getModoDireccionamiento(), atoi(instruccion.getOperando().c_str()));
            pc++;
            break;
        case STORE:
            exeStore(instruccion.getModoDireccionamiento(), atoi(instruccion.getOperando().c_str()));
            pc++;
            break;
        case ADD:
            if(!exeAdd(instruccion.getModoDireccionamiento(), atoi(instruccion.getOperando().c_str()))) {
                cout << " ERROR en M[" << pos_memoria << "] -> '" << instruccion.toString() << "': MSG: desbordamiento." << endl;
                parar = true;
            }
            else
                pc++;
            break;
        case SUB:
            exeSub(instruccion.getModoDireccionamiento(), atoi(instruccion.getOperando().c_str()));
            pc++;
            break;
        case MULT:
            if(!exeMult(instruccion.getModoDireccionamiento(), atoi(instruccion.getOperando().c_str()))) {
                cout << " ERROR en M[" << pos_memoria << "] -> '" << instruccion.toString() << "': MSG: desbordamiento." << endl;
                parar = true;
            }
            else
                pc++;
            break;
        case DIV:
            if(!exeDiv(instruccion.getModoDireccionamiento(), atoi(instruccion.getOperando().c_str()))) {
                cout << " ERROR en M[" << pos_memoria << "] -> '" << instruccion.toString() << "': MSG: division por cero." << endl;
                parar = true;
            }
            else
                pc++;
            break;
        case READ:
            if(!exeRead(instruccion.getModoDireccionamiento(), atoi(instruccion.getOperando().c_str()))) {
                cout << " RROR en M[" << pos_memoria << "] -> '" << instruccion.toString() << "': MSG: no hay mas datos en la cinta de lectura." << endl;
                parar = true;
            }
            else
                pc++;
            break;
        case WRITE:
            exeWrite(instruccion.getModoDireccionamiento(), atoi(instruccion.getOperando().c_str()));
            pc++;
            break;
        case JUMP:
            if(!exeJump(instruccion.getOperando())) {
                cout << " ERROR en M[" << pos_memoria << "] -> '" << instruccion.toString() << "': MSG: etiqueta '" << instruccion.getOperando() << "' no definida." << endl;
                parar = true;
            }
            break;
        case JGTZ:
            if(!exeJgtz(instruccion.getOperando())) {
                cout << " ERROR en M[" << pos_memoria << "] -> '" << instruccion.toString() << "': MSG: etiqueta '" << instruccion.getOperando() << "' no definida." << endl;
                parar = true;
            }
            break;
        case JZERO:
            if(!exeJzero(instruccion.getOperando())) {
                cout << " ERROR en M[" << pos_memoria << "] -> '" << instruccion.toString() << "': MSG: etiqueta '" << instruccion.getOperando() << "' no definida." << endl;
                parar = true;
            }
            break;
        case HALT:
            volcarCintaEscritura();
            parar = true;
            break;
        }

        if(traza) {
            cout << " Estado posterior:" << endl;
            cout << "   PC: " << pc << endl;
            cout << "   AC: " << banco_registros.leerAcumulador() << endl;
            cout << "   R:  "; banco_registros.mostrarEnLinea(); cout << endl << endl;
            cin >> c;
        }
    }
}

// INSTRUCCIONES DE CARGA Y ALMACENAMIENTO

void Ram::exeLoad(int modo, int operando) {

    switch(modo) {

    case INMEDIATO:
        banco_registros.escribirAcumulador(operando);
        break;
    case DIRECTO:
        banco_registros.escribirAcumulador(banco_registros.leerRegistro(operando));
        break;
    case INDIRECTO:
        banco_registros.escribirAcumulador(banco_registros.leerRegistro(banco_registros.leerRegistro(operando)));

        break;
    }
}

void Ram::exeStore(int modo, int operando) {

    switch(modo) {

    case DIRECTO:
        banco_registros.escribirRegistro(operando, banco_registros.leerAcumulador());
        break;
    case INDIRECTO:
        banco_registros.escribirRegistro(banco_registros.leerRegistro(operando), banco_registros.leerAcumulador());
        break;
    }
}

// INSTRUCCIONES ARITMÉTICAS

bool Ram::exeAdd(int modo, int operando) {

    int acum = banco_registros.leerAcumulador();
    long resultado;

    switch(modo) {

    case INMEDIATO:
        resultado = (long)acum + (long)operando;
        if(hayDesbordamiento(resultado))
            return false;

        banco_registros.escribirAcumulador(acum + operando);
        break;
    case DIRECTO:
        resultado = (long)acum + (long)banco_registros.leerRegistro(operando);
        if(hayDesbordamiento(resultado))
            return false;
        banco_registros.escribirAcumulador(acum + banco_registros.leerRegistro(operando));
        break;
    case INDIRECTO:
        resultado = (long)acum + (long)banco_registros.leerRegistro(banco_registros.leerRegistro(operando));
        if(hayDesbordamiento(resultado))
            return false;
        banco_registros.escribirAcumulador(acum + banco_registros.leerRegistro(banco_registros.leerRegistro(operando)));

        break;
    }

    return true;
}

bool Ram::exeSub(int modo, int operando) {

    int acum = banco_registros.leerAcumulador();
    long resultado;

    switch(modo) {

    case INMEDIATO:
        resultado = (long)acum + (long)operando;
        if(hayDesbordamiento(resultado))
            return false;
        banco_registros.escribirAcumulador(acum - operando);
        break;
    case DIRECTO:
        resultado = (long)acum + (long)banco_registros.leerRegistro(operando);
        if(hayDesbordamiento(resultado))
            return false;
        banco_registros.escribirAcumulador(acum * banco_registros.leerRegistro(operando));
        break;
    case INDIRECTO:
        resultado = (long)acum + (long)banco_registros.leerRegistro(banco_registros.leerRegistro(operando));
        if(hayDesbordamiento(resultado))
            return false;
        banco_registros.escribirAcumulador(acum - banco_registros.leerRegistro(banco_registros.leerRegistro(operando)));
        break;
    }

    return true;
}

bool Ram::exeMult(int  modo, int operando) {

    int acum = banco_registros.leerAcumulador();
    long resultado;

    switch(modo) {

    case INMEDIATO:
        resultado = (long)acum + (long)operando;
        if(hayDesbordamiento(resultado))
            return false;
        banco_registros.escribirAcumulador(acum * operando);
        break;
    case DIRECTO:
        resultado = (long)acum + (long)banco_registros.leerRegistro(operando);
        if(hayDesbordamiento(resultado))
            return false;
        banco_registros.escribirAcumulador(acum * banco_registros.leerRegistro(operando));
        break;
    case INDIRECTO:
        resultado = (long)acum + (long)banco_registros.leerRegistro(banco_registros.leerRegistro(operando));
        if(hayDesbordamiento(resultado))
            return false;
        banco_registros.escribirAcumulador(acum * banco_registros.leerRegistro(banco_registros.leerRegistro(operando)));
        break;
    }
    return true;
}

bool Ram::exeDiv(int  modo, int operando) {

    if(operando == 0)
        return false;

    int acum = banco_registros.leerAcumulador();

    switch(modo) {

    case INMEDIATO:
        banco_registros.escribirAcumulador(acum / operando);
        break;
    case DIRECTO:
        banco_registros.escribirAcumulador(acum / banco_registros.leerRegistro(operando));
        break;
    case INDIRECTO:
        banco_registros.escribirAcumulador(acum / banco_registros.leerRegistro(banco_registros.leerRegistro(operando)));
        break;
    }

    return true;
}

// INSTRUCCIONES I/O

void Ram::exeWrite(int modo, int operando) {

    switch (modo) {
    case INMEDIATO:
        cinta_escritura.escribirDato(operando);
        break;
    case DIRECTO:
        cinta_escritura.escribirDato(banco_registros.leerRegistro(operando));
        break;
    case INDIRECTO:
        cinta_escritura.escribirDato(banco_registros.leerRegistro(banco_registros.leerRegistro(operando)));
        break;
    }
}

bool Ram::exeRead(int modo, int operando) {

    int dato = cinta_lectura.leerDato();

    if(dato == IO_ERROR)
        return false;

    switch (modo) {

    case DIRECTO:
        banco_registros.escribirRegistro(operando, dato);
        break;
    case INDIRECTO:
        banco_registros.escribirRegistro(banco_registros.leerRegistro(operando), dato);
        break;
    }

    return true;
}

// INSTRUCCIONES DE SALTO

bool Ram::exeJump(string etiqueta) {

    if((pc = etiquetas.obtenerPosicion(etiqueta)) < 0)
        return false;   // La etiqueta no esta difinida

    return true;
}

bool Ram::exeJgtz(string etiqueta) {

    int numero_instruccion;

    if((numero_instruccion = etiquetas.obtenerPosicion(etiqueta)) < 0)
        return false;   // La etiqueta no esta difinida

    if(banco_registros.leerAcumulador() > 0)
        pc = etiquetas.obtenerPosicion(etiqueta);
    else
        pc++;

    return true;
}

bool Ram::exeJzero(string etiqueta) {

    int numero_instruccion;

    if((numero_instruccion = etiquetas.obtenerPosicion(etiqueta)) < 0)
        return false;   // La etiqueta no esta difinida

    if(banco_registros.leerAcumulador() == 0)
        pc = etiquetas.obtenerPosicion(etiqueta);
    else
        pc++;

    return true;
}

// METODOS PARA MOSTRAR EL ESTADO DE LA MAQUINA

void Ram::mostrarRegistros() {
    banco_registros.mostrar();
}

void Ram::mostrarCintaLectura() {
    cinta_lectura.mostrar();
}

void Ram::mostrarCintaEscritura() {
    cinta_escritura.mostrar();
}

void Ram::desensamblarPrograma() {
    for(unsigned i = 0; i < programa.size(); i++)
        cout << " I[" << i << "] -> " << programa[i].toString() << endl;
}

// METODOS PRIVADOS AUXILIARES

void Ram::limpiarLinea(string & str) {

    char c;
    unsigned pos;

    // Limpiamos los espacioes y tabuladores por el principio
    int i = 0;
    do {
        c = str[i++];
    } while (c == ' ' || c == '\t');
    str.erase(0, i-1);

    // Eliminamos los comentarios que pudiera haber en la linea
    pos = str.find(';');
    if(pos < str.size()) {
        str.erase(pos, str.size()-1);
    }
}

string Ram::extraerEtiqueta(string & str) {

    string etiqueta = "";
    unsigned pos;

    limpiarLinea(str);  // Limpiamos la linea

    pos = str.find(':');
    if(pos < str.size()) {
        etiqueta = str.substr(0, pos);
        str.erase(0, pos+1);
    }

    limpiarLinea(str);  // Limpiamos de nuevo tras la extraccion de la etiqueta

    return etiqueta;
}

int Ram::extraerCodigoOperacion(string str) {

    string codigo;
    unsigned pos = str.find(' ');

    if(pos < str.size())
        codigo = str.substr(0, pos);
    else
        codigo = str;

    if(codigo[codigo.size()-1] == ' ')
        codigo = str.substr(0, codigo.size()-2);

    if(codigo == "LOAD" || codigo == "load")
        return LOAD;
    if(codigo == "STORE" || codigo == "store")
        return STORE;
    if(codigo == "ADD" || codigo == "add")
        return ADD;
    if(codigo == "SUB" || codigo == "sub")
        return SUB;
    if(codigo == "MULT" || codigo == "mult")
        return MULT;
    if(codigo == "DIV" || codigo == "div")
        return DIV;
    if(codigo == "READ" || codigo == "read")
        return READ;
    if(codigo == "WRITE" || codigo == "write")
        return WRITE;
    if(codigo == "JUMP" || codigo == "jump")
        return JUMP;
    if(codigo == "JGTZ" || codigo == "jgtz")
        return JGTZ;
    if(codigo == "JZERO" || codigo == "jzero")
        return JZERO;
    if(codigo == "HALT" || codigo == "halt")
        return HALT;

    return -1;
}

int Ram::extraerDireccionamiento(string str) {

    unsigned pos = str.find(' ');
    char c;

    if(pos < str.size()) {

        c = str[pos+1];

        if(c == '=')
            return INMEDIATO;
        if(c == '*')
            return INDIRECTO;

        return DIRECTO;
    }
    return -1;
}



string Ram::extraerOperando(string str) {

    unsigned pos = str.find(' ');
    char c;
    string temp;
    string oper = "";

    if(pos < str.size()) {

        c = str[pos+1];
        if(c == '=' || c == '*')
            temp = str.substr(pos+2, str.size()- pos-2);
        else
            temp = str.substr(pos+1, str.size());
    }

    for(unsigned i = 0; i < temp.size(); i++) {
        c = temp[i];
        if((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == '-' || c == '_')
            oper.push_back(temp[i]);
    }

    return oper;
}

bool Ram::hayDesbordamiento(long numero) {

    if(numero < numeric_limits<int>::min() || numero > numeric_limits<int>::max())
        return true;

    return false;
}

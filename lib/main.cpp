
#include "ram.h"
#include <cstdlib>
#include <string>
#include <stdio.h>



using namespace std;

char menu();

int main(int argc, char *argv[]) {

    if(argc < 4) {
        cout << endl << " ERROR: Son necesarios 3 argumentos para iniciar el programa." << endl;
        cout << " -> Pruebe así: ram fuente.ram escritura.txt lectura.txt" << endl << endl;
    }
    else {

        Ram maquina;
        char opcion;
        string c;

        string codigo_fuente(argv[1]);
        string cinta_escritura(argv[2]);
        string cinta_lectura(argv[3]);

        maquina = Ram(codigo_fuente, cinta_escritura, cinta_lectura);

        maquina.inicializar();
        maquina.cargarPrograma();
        maquina.cargarCintaLectura();

        system("clear");
        while((opcion = menu()) != 'x') {

            system("clear");

            switch(opcion) {
            case 'r':
                cout << endl << " Mostrando estado de los registros:" << endl << endl;
                maquina.mostrarRegistros();
                break;
            case 't':
                cout << endl << " Mostrando ejecucion con traza:" << endl << endl;
                maquina.inicializar();
                maquina.cargarPrograma();
                maquina.cargarCintaLectura();
                maquina.ejecutarPrograma(true);
                break;
            case 'g':
                cout << endl << " Ejecutando programa..." << endl << endl;
                maquina.inicializar();
                maquina.cargarPrograma();
                maquina.cargarCintaLectura();
                maquina.ejecutarPrograma(false);
                break;
            case 's':
                cout << endl << " Desensamblador:" << endl << endl;
                maquina.desensamblarPrograma();
                break;
            case 'i':
                cout << endl << " Mostrando cinta de lectura:" << endl << endl;
                maquina.mostrarCintaLectura();
                break;
            case 'o':
                cout << endl << " Mostrando cinta de escritura:" << endl << endl;
                maquina.mostrarCintaEscritura();
                break;
            case 'h':
                break;
            case 'x':
                break;
            }
        }
    }
}

char menu() {

    char opcion;

    cout << endl << "------------------------------------" << endl;
    cout << endl << " SIMULADOR MAQUINA RAM" << endl << endl;

    cout << " Opciones" << endl;
    cout << "   r: ver los registros" << endl;
    cout << "   t: traza" << endl;
    cout << "   g: go" << endl;
    cout << "   s: desensamblador" << endl;
    cout << "   i: ver cinta lectura" << endl;
    cout << "   o: ver cinta escritura" << endl;
    cout << "   h: ayuda" << endl << endl;
    cout << "   x: salir" << endl << endl;

    cout << " -> Tu opcion: ";
    cin >> opcion;

    return opcion;
}

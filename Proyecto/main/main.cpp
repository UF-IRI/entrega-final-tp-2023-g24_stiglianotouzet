#include "clientes.h"
#include "clases.h"
#include "asistencias.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


int main() {
   //----------------ABRIMOS ARCHIVOS---------------------------
    ifstream archivoCliente("../../iriClientesGYM.csv");
    ifstream archivoClases("../../iriClasesGYM.csv");
    ifstream archivoAsistencias("../../asistencias_1697673600000.dat", ios::binary);

    if (!archivoCliente.is_open()) {
        cout << "No pudimos abrir el archivo Clientes" << endl;
        return 0;
    }
    if (!archivoClases.is_open()) {
        cout << "No pudimos abrir el archivo Clases" << endl;
        return 0;
    }
    if (!archivoAsistencias.is_open()) {
        cout << "No pudimos abrir el archivo Asistencias" << endl;
        return 0;
    }

    string linea;
   //-------------------_CLIENTES--------------------------
    str encabezado;
    uint cantClientes = 0;
    getline(archivoCliente,encabezado);
    while (getline(archivoCliente, linea))
        cantClientes++;
    eClientes *clientes = new eClientes[cantClientes];
    eLectura resultadoClientes;
    resultadoClientes= ArchivoClientes(clientes, archivoCliente);

    //----------------CLASES------------------------
    uint realCantClases;
    uint cantClases = ContarClase(archivoClases, realCantClases);
    eClases *clases = new eClases[cantClases];
    eReserva *reservas = new eReserva[realCantClases];
    eOperacion resultadoClases;
    resultadoClases= leerClases(clases, reservas, archivoClases, cantClases);

    //----------------ASISTENCIAS----------------------------------

    eAsistencia *asistencias = new eAsistencia[5];
    uint cantAsistencias = 0;
    eGimnasio *gimnasio = new eGimnasio({clientes, cantClientes, asistencias, cantAsistencias,5, clases,cantClases, time(0), reservas, realCantClases});



    cout << "Cant clientes: " << gimnasio->cantClientes
         << " - Cant asistencias: " << gimnasio->cantAsistencias
         << " - Cant clases: " << gimnasio->cantClases
         << " - cant Reservas: " << gimnasio->cantReservas
         << " - dia: " << ctime(&gimnasio->hoy) << endl;


    imprimirAsistencias(gimnasio->asistencias, gimnasio->cantAsistencias);
//----------------CERRAMOS ARCHIVOS----------------------------------------
    delete[] clientes;
    delete[] clases;
    delete[] asistencias;
    delete[] reservas;
    archivoCliente.close();
    archivoClases.close();
    archivoAsistencias.close();
    return 0;
}



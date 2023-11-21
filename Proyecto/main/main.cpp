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
    getline(archivoClases,encabezado);
    uint cantClases=0;
    while(getline(archivoClases,linea)){
        cantClases++;
    }
    eClases *clases = new eClases[cantClases];
    eLectura resultadoClases;
    resultadoClases= leerClases(clases, archivoClases);
    //----------------ASISTENCIAS----------------------------------
    uint buffer;
    uint cantAsistencias = -1;

    while (!archivoAsistencias.eof()) {
        archivoAsistencias.read((char *)&buffer, sizeof(uint));
        archivoAsistencias.read((char *)&buffer, sizeof(uint));
        eInscripcion auxInscrip;
        for (uint i = 0; i < buffer; i++) {
            archivoAsistencias.read((char *)&auxInscrip, sizeof(eInscripcion));
        }
        cantAsistencias++;
    }
    eAsistencia *asistencias = new eAsistencia[cantAsistencias];
    eLectura resultadoAsistencias;
    resultadoAsistencias= ArchivoAsistencia(archivoAsistencias, asistencias);

  //------------------INSCRIPCION-------------------------------------------
    uint idReserva = numeroRandom(1, cantClases);
    uint idCliente = numeroRandom(1, cantClientes);
    eReserva* reservas;
    uint cantReservas;
    eOperacion resultadoReserva;

    eGimnasio* gimnasio= new eGimnasio({clientes, cantClientes, asistencias, cantAsistencias, 45, clases, cantClases, reservas, cantReservas});
    resultadoReserva = reservar(gimnasio, idReserva, idCliente);
    cout<< resultadoReserva;


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

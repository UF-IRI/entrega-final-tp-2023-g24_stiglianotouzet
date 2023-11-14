#include "clientes.h"
#include "clases.h"
#include "asistencias.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main() {
    //---------------------------------------ABERTURA DE ARCHIVOS----------------------------------------------------------

    ifstream archivoClientes("../../iriClientesGYM.csv");
    if(!archivoClientes.is_open()){
        cout<<" No abrio";
    }
    ifstream archivoClases("../../iriClasesGYM.csv");
    if(!archivoClases.is_open()){
        cout<<"No abrio";
    }
    ifstream archivoAsistencias("../../asistencias_1697673600000.dat",ios::binary);
    if(!archivoAsistencias.is_open()){
        cout<<"No abrio";
    }


    //-----------------------------------CLIENTES------------------------------------------------------

    archivoClientes.clear();
    archivoClientes.seekg(0);
    str encabezado;
    getline(archivoClientes,encabezado);
    str linea;
    int contClientes=0;
    while(getline(archivoClientes,linea))
        contClientes++;

    eClientes* clientes=new eClientes[contClientes];
    eLectura resultadoArchivoCliente;
    resultadoArchivoCliente=ArchivoClientes(clientes,archivoClientes);


    //------------------------------------CLASES----------------------------------------------------------------

    str encabezadoClases;
    archivoClases.clear();
    archivoClases.seekg(0);
    getline(archivoClases,encabezadoClases);
    int contClases=0;
    while(getline(archivoClases,linea))
        contClases++;

    eClases* clases=new eClases[contClases];
    eLectura resultadoArchivoClase;
    resultadoArchivoClase=ArchivoClases(clases,archivoClases);


    //---------------------------------ASISTENCIA--------------------------------------------------------------------

    archivoAsistencias.clear();
    archivoAsistencias.seekg(0);
    int contAsistencias=-1;//como no le saco el encabezado
    unsigned int auxLectura;
    while(!archivoAsistencias.eof()){
        archivoAsistencias.read((char*)&auxLectura,sizeof(unsigned int));
        archivoAsistencias.read((char*)&auxLectura,sizeof(unsigned int));
        eInscripcion auxInscripciones;
        for(unsigned int i=0;i<auxLectura;i++){
            archivoAsistencias.read((char*)&auxInscripciones,sizeof(eInscripcion));
        }
            contAsistencias++;
     }

//----------------------------------------PRUEBA BINARIOS--------------------------------
    cout << "asistencias" << contAsistencias << endl;
    Asistencia* asistencias = new Asistencia[contAsistencias - 1];
    eLectura resultadoAsistencias;
    resultadoAsistencias = ArchivoAsistencia(archivoAsistencias, asistencias);
    for(int i=0;i<contAsistencias;i++){
            cout<<""<<asistencias[i].idCliente<<endl;

    }

//---------------------------------------FUNCION RESERVA------------------------------------------





//--------------------------------ELIMINAR MEMORIA Y CERRAR ARCHIVOS------------------------------
    delete [] clientes;
    delete[] clases;
    delete[] asistencias;

    archivoClases.close();
    archivoClientes.close();
    archivoAsistencias.close();
    return 0;
}

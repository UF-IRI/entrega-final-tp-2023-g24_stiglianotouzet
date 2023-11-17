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
    str linea;
    getline(archivoClientes,encabezado);
    unsigned int contClientes = 0;
    while (getline(archivoClientes, linea))
        contClientes++;
    contClientes--;
    eClientes *clients = new eClientes[contClientes];
    eOperacion resClients = ArchivoClientes( clientes,  archivoClientes);


    //------------------------------------CLASES----------------------------------------------------------------

    str encabezadoClases;
    archivoClases.clear();
    archivoClases.seekg(0);
    unsigned int CantClases;
    unsigned int cantClases = ContarClases(archivoClases,CantClases);
    eClases *clases = new eClases[cantClases];
    eOperacion *reserva = new eOperacion[CantClases];
   eOperacion resClasses = leerClases(clases, reserva,archivoClases , CantClases);;


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
    Asistencia *asistencias = new Asistencia[5];
    uint contasistencia = 0;
    eGimnasio *gim = new eGimnasio({clientes, contClientes, asistencias, contasistencias,
                                    5, clases,
                                    contClases, time(0), reservas, realcontClases});


    cout <<"Cant clientes: " << gimnasio->cantClientes<< " - Cant assitances: " << gimnasio->cantAsistencias << " - Cant clases: " << gimnasio->cantClases
         << " - Cant books: " << gimnasio->cantReservas << " - Today: " << ctime(&gimnasio->hoy)  << endl ;



    for (int i = 0; i < 10; i++) {
        uint idBook = genRandomNumber(1, realcontClase);
        uint idClient = genRandomNumber(1, contClientes);
        eOperacion resultado = reservarClase(*gim, idReserva, to_string(idClient));
        cout<< "RES: " << res << " - Cant assitances:" << gim->cantAsistencias<< endl;
    }

    cout << "Cant clientes: " << gim->cantClientes
         << " - Cant assitances: " << gim->cantAsistencias
         << " - Cant classes: " << gim->contClases
         << " - Cant books: " << gim->ContReservas
         << " - Today: " << ctime(&gim->hoy) << endl;

    imprimirAsistencias(gim->asistencias, gim->cantAsistencias);





//--------------------------------ELIMINAR MEMORIA Y CERRAR ARCHIVOS------------------------------
    delete [] reserva;
    delete [] clientes;
    delete[] clases;
    delete[] asistencias;

    archivoClases.close();
    archivoClientes.close();
    archivoAsistencias.close();
    return 0;
}


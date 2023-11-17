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
    eAsistencia* asistencias = new Asistencia[contAsistencias-1];
    uint n=5;
    eGimnasio* gimnasio=new eGimnasio({})
    eGimnasio* gimnasio = new eGimnasio({clientes, contClientes, asistencias, contAsistencias, n, clases, contClases, time(0), reservas, realCantClases});


    cout <<"Cant clientes: " << gimnasio->cantClientes<< " - Cant assitances: " << gimnasio->cantAsistencias << " - Cant classes: " << gimnasio->cantClases
         << " - Cant books: " << gimnasio->cantReservas << " - Today: " << ctime(&gimnasio->hoy)  << endl ;


//----------------------------------------PRUEBA BINARIOS--------------------------------

    eLectura resultadoAsistencias;
    resultadoAsistencias = ArchivoAsistencia(archivoAsistencias, asistencias);

//---------------------------------------FUNCION RESERVA------------------------------------------





//--------------------------------ELIMINAR MEMORIA Y CERRAR ARCHIVOS------------------------------
    delete [] reservas;
    delete [] clientes;
    delete[] clases;
    delete[] asistencias;

    archivoClases.close();
    archivoClientes.close();
    archivoAsistencias.close();
    return 0;
}

    /* Asistencias
  int cantAssistances = countAssistences(fileAssistances);
  cout << "assitencias" << cantAssistances << endl;
  Asistencia *assitances = new Asistencia[cantAssistances - 1];
  eCodFile resAssistances = readAssistances(fileAssistances, assitances);
*/

    // printClasses(classes,cantClasses);
    // printAssistances(assitances,cantAssistances);
    // printClients(clients,countClients);
    Asistencia *assitances = new Asistencia[DEFAULT_MAX_ASSITANCES_CAPACITY];
    uint countAssitances = 0;
    eGym *gymData = new eGym({clients, countClients, assitances, countAssitances,
                              DEFAULT_MAX_ASSITANCES_CAPACITY, classes,
                              cantClasses, time(0), books, realCantClasses});





    delete[] clients;
    delete[] classes;
    delete[] assitances;
    delete[] books;
    fileClient.close();
    fileClasses.close();
    fileAssistances.close();
    return 0;
}

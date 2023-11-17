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
    int contClientes=0;
    while(getline(archivoClientes,linea))
        contClientes++;
    eLectura resultadoArchivoCliente;
    eClientes *clientes = new eClientes[contClientes];
    resultadoArchivoCliente= ArchivoClientes(clientes, archivoClientes);




    //------------------------------------CLASES----------------------------------------------------------------

    str encabezadoClases;
    archivoClases.clear();
    archivoClases.seekg(0);
    /*getline(archivoClases,encabezadoClases);*/
    /*int contClases=0;
    while(getline(archivoClases,linea))
        contClases++;*/
    int realCantClases;
    int contClases;
    contClases= ContarClases(archivoClases,realCantClases);
    eClases* clases=new eClases[contClases];
    eLectura resultadoArchivoClase;
    eReserva* reservas=new eReserva[realCantClases];
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
int main() {

    ifstream fileClient("../../iriClientesGYM.csv");
    ifstream fileClasses("../../iriClasesGYM.csv");
    ifstream fileAssistances("../../asistencias_1697673600000.dat", ios::binary);

    if (!fileClient.is_open()) {
        cout << "No pudimos abrir el archivo Clientes" << endl;
        return 0;
    }
    if (!fileClasses.is_open()) {
        cout << "No pudimos abrir el archivo Clases" << endl;
        return 0;
    }
    if (!fileAssistances.is_open()) {
        cout << "No pudimos abrir el archivo Asistencias" << endl;
        return 0;
    }

    string line;
    /* CLIENTES */
    uint countClients = 0;
    while (getline(fileClient, line))
        countClients++;
    countClients--;
    eClient *clients = new eClient[countClients];
    eCodFile resClients = leerClientes(clients, fileClient);

    /* Clases */
    uint realCantClasses;
    uint cantClasses = countClasses(fileClasses, realCantClasses);
    eClass *classes = new eClass[cantClasses];
    eBook *books = new eBook[realCantClasses];
    eCodFile resClasses = readClasses(classes, books, fileClasses, cantClasses);

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



    // printClients(gymData->clients,gymData->countClients);

    for (int i = 0; i < 10; i++) {
        uint idBook = genRandomNumber(1, realCantClasses);
        uint idClient = genRandomNumber(1, countClients);
        eBookClass res = bookClassGym(*gymData, idBook, to_string(idClient));
        cout<< "RES: " << res << " - Cant assitances:" << gymData->countAssistances<< endl;
    }

    cout << "Cant clientes: " << gymData->countClients
         << " - Cant assitances: " << gymData->countAssistances
         << " - Cant classes: " << gymData->countClasses
         << " - Cant books: " << gymData->countBooks
         << " - Today: " << ctime(&gymData->today) << endl;

    printAssistances(gymData->assistances, gymData->countAssistances);

    delete[] clients;
    delete[] classes;
    delete[] assitances;
    delete[] books;
    fileClient.close();
    fileClasses.close();
    fileAssistances.close();
    return 0;
}

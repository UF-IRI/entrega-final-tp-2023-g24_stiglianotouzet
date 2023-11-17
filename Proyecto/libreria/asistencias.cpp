#include "asistencias.h"
//funcion para hacer resize a la asistencia si alguien mas se quiere unir a la clase
eAsistencia* resizeAsistencia(eAsistencia* miLista,  unsigned int tam,  unsigned int nuevoTam) {
    eAsistencia* aux = new eAsistencia[nuevoTam];

    unsigned int longitud = (tam <  nuevoTam) ? tam : nuevoTam;

    if(aux != nullptr) {

        for( unsigned int i = 0; i < longitud; i++)
            aux[i] = miLista[i]; // *(miLista + i)

        delete[] miLista;
        return aux;
    }

    return nullptr;
}
void resizeasistencias(eAsistencia **miLista, uint tam, uint nuevoTam) {
    eAsistencia *aux = new eAsistencia[nuevoTam];

    if (aux == nullptr)
        return;

    uint longitud = (tam < nuevoTam) ? tam : nuevoTam;

    for (uint i = 0; i < longitud; i++)
        aux[i] = *miLista[i]; // **(miLista + i)

    delete[] *miLista;
    *miLista = aux;
}
eLectura ArchivoAsistencia(ifstream& ArchivoAsistencia,eAsistencia* asistencias){
    if(!ArchivoAsistencia.is_open())
        return eLectura::Errornoabrio;
    ArchivoAsistencia.clear();
    ArchivoAsistencia.seekg(0);


    eAsistencia* aux = asistencias;

    while (!ArchivoAsistencia.eof())
    {
        ArchivoAsistencia.read((char*)&aux->idCliente, sizeof( unsigned int));
        ArchivoAsistencia.read((char*)&aux->cantInscriptos, sizeof(unsigned int));

        eInscripcion* registrados = new eInscripcion[aux->cantInscriptos];
        eInscripcion* auxInscripciones = registrados;
        for( unsigned int i=0;i<aux->cantInscriptos;i++)
        {
            ArchivoAsistencia.read((char*)auxInscripciones,sizeof(eInscripcion));
            auxInscripciones++;
        }
        aux->CursosInscriptos = registrados;

        aux++;
    }


    return eLectura::exitoabrio;
}
void imprimirAsistencias(eAsistencia *asistencias, int cant) {
    eAsistencia *aux = asistencias;
    eAsistencia *ultimo = (asistencias) + (cant - 1);
    cout << "asistencia:" << endl;
    if (cant == 0)
        return;
    while (true) {
        cout << "id:" << aux->idCliente << endl;
        eInscripcion *aux2 = aux->CursosInscriptos;
        eInscripcion *ultimo2= (aux->CursosInscriptos)+(aux->cantInscriptos-1) ;
        cout << "Incripciones:";
        while (true) {
            cout << aux2->idClase << ",";
            if (aux2 == ultimo2)
                break;
            aux2++;
        }
        cout << endl;
        if (aux == ultimo)
            break;
        aux++;
    }
    cout << "................"<< endl;
}

eOperacion agregarAsistencia(eAsistencia* asistencias,uint cant ,eAsistencia asistencia){
    if(cant==0){
        asistencias[0] = asistencia;
        return eOperacion::nofuncion;
    }
    *(asistencias + cant -1) = asistencia;
    return eOperacion::funciono;
}


int ContarAsistencia(ifstream &archivoAsistencia) {
    if (!archivoAsistencia.is_open()) {
        cout << "No abrio" << endl;
        return 0;
    }
    archivoAsistencia.clear();
    archivoAsistencia.seekg(0);

    int cantAsistencias = -1;
    uint aux;
    while (!archivoAsistencia.eof()) {
        archivoAsistencia.read((char *)&aux, sizeof(uint));
        archivoAsistencia.read((char *)&aux, sizeof(uint));
        eInscripcion auxInscripciones;
        for (uint i = 0; i < aux; i++) {
            archivoAsistencia.read((char *)&aux, sizeof(eInscripcion));
        }
        cantAsistencias++;
    }
    return cantAsistencias;
}
eOperacion EscribirAsistencia(eAsistencia *asistencias, uint cant, str hoy) {
    ofstream archivoAsistencia("../../asistencias_" + hoy,ios::binary);
    if (!archivoAsistencia.is_open()) {
        return eOperacion::nofuncion;
    }
    eAsistencia *aux = asistencias;
    if (archivoAsistencia.is_open()) {
        for (uint i = 0; i < cant; i++) {
            archivoAsistencia.write((char *)&aux[i].idCliente, sizeof(uint));
            archivoAsistencia.write((char *)&aux[i].cantInscriptos, sizeof(uint));
            for (uint j = 0; j < aux[i].cantInscriptos; j++) {
                archivoAsistencia.write((char *)&aux[i].CursosInscriptos[j],
                                 sizeof(eInscripcion));
            }
        }
    }
    archivoAsistencia.close();
    return eOperacion::funciono;
}
eAsistencia* BuscarxAsistencia(eAsistencia* asistencias,uint cant ,str idCliente) {
    eAsistencia* aux = asistencias;
    eAsistencia* ultimo = (asistencias) +cant - 1;
    if(cant == 0){
        return nullptr;
    }
    while(true) {
        if (aux->idCliente == stoul(idCliente)) {
            return aux;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return nullptr;
}
eOperacion agregarInscripcion(eInscripcion* inscripciones,uint cant,eInscripcion inscripcion){
    if(cant == 0){
        *inscripciones = inscripcion;
    }
    *(inscripciones + cant - 1) = inscripcion;
    return eOperacion::funciono;
}


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
void ResizeAsistencia(eAsistencia* miLista, uint tam, uint nuevoTam) {
    Asistencia* aux = new Asistencia[nuevoTam];

    uint longitud = (tam <  nuevoTam) ? tam : nuevoTam;

    if(aux != nullptr) {

        for(uint i = 0; i < longitud; i++)
            aux[i] = miLista[i];

        delete[] miLista;
    }
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
void EscribirAsistencias(eAsistencia *asistencias, uint cant) {
    ofstream ArchivoAsistencia("../../asistencias_", ios::binary);
    if (!ArchivoAsistencia.is_open()) {
        cout << "No abrio el archivo";
        return;
    }
    eAsistencia *aux = asistencias;
    if (ArchivoAsistencia.is_open()) {
        for (uint i = 0; i < cant; i++) {
            ArchivoAsistencia.write((char *)&aux[i].idCliente, sizeof(uint));
            ArchivoAsistencia.write((char *)&aux[i].cantInscriptos, sizeof(uint));
            for (uint j = 0; j < aux[i].cantInscriptos; j++) {
                ArchivoAsistencia.write((char *)&aux[i].CursosInscriptos[j], sizeof(eInscripcion));
                cout<< "Asistencia nro " << i << "reservada" << endl;
            }
        }
    }
}

eAsistencia* buscarxAsistencia(eAsistencia* asistencias, uint cant, uint idCliente){
    eAsistencia* aux = asistencias;
    eAsistencia* ultimo = asistencias + (cant - 1);
    if(cant == 0){
        return nullptr;
    }
    while(true) {
        if (std::to_string(aux->idCliente) == std::to_string(idCliente)) {
            return aux;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return nullptr;
}

eOperacion NuevaAsistencia(eAsistencia* asistencias, uint cant, Asistencia asistencia){
    if(cant==0){
        asistencias[0] = asistencia;
        return eOperacion::exito;
    }
    *(asistencias + cant -1) = asistencia;
    return eOperacion::error;
}

eOperacion agregarInscripcion(eInscripcion* inscripciones, uint cant, eInscripcion inscripcion){
    if(cant == 0){
        *inscripciones  = inscripcion;
    }
    *(inscripciones + cant - 1) = inscripcion;
    return eOperacion::exito;
}


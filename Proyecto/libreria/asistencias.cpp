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

eLectura ArchivoAsistencia(ifstream& ArchivoAsistencia,eAsistencia* asistencias){
    // SABIENDO QUE ESTA ORDENADO EL ARCHIVO CLASES
    if(!ArchivoAsistencia.is_open())
        return eLectura::Errornoabrio;
    //Setear inicio
    ArchivoAsistencia.clear();
    ArchivoAsistencia.seekg(0);


    eAsistencia* aux = asistencias;

    while (!ArchivoAsistencia.eof())//mientras que no este en el ultimo
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

eLectura devolverAsistencia(ofstream &ArchivoAsistencia, eAsistencia* asistencias, int cant) {
    ofstream outfile("binary_file_out.bin", ios::binary);
    if (!outfile.is_open()) {
        return eLectura::Errornoabrio;
    }

    eAsistencia* aux = asistencias;//creo un puntero aux que es igual a asistencias para que asistencias se modifique localmente

    for (int i = 0; i < cant; i++) {
        ArchivoAsistencia.write((char* )&aux[i].idCliente, sizeof(unsigned int));
        ArchivoAsistencia.write((char*)&aux[i].cantInscriptos, sizeof(unsigned int));
        for (unsigned int j = 0; j < aux[i].cantInscriptos; j++) {
            ArchivoAsistencia.write((char *)&aux[i].CursosInscriptos[j],
                       sizeof(eInscripcion));
        }
    }

    return eLectura::exitoabrio;
}



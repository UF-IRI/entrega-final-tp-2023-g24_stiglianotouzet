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
eOperacion escribirAsistencias(ofstream &archivo, eAsistencia *asistencias, int cant) {
    ofstream EscribirAsistencias("binary_file_out.bin", ios::binary);
    if (!EscribirAsistencias.is_open()) {
        cout << "Error no abrio" << endl;
        return eOperacion::nofuncion;
    }

    Asistencia *aux = asistencias;

    for (int i = 0; i < cant; i++) {
        EscribirAsistencias.write((char *)&aux[i].idCliente, sizeof(uint));
        EscribirAsistencias.write((char *)&aux[i].cantInscriptos, sizeof(uint));
        for (uint j = 0; j < aux[i].cantInscriptos; j++) {
            EscribirAsistencias.write((char *)&aux[i].CursosInscriptos[j],sizeof(eInscripcion));
        }
    }

    return eOperacion::funciono;
}


int contarAsistencias(ifstream& Archivo){
    if (!Archivo.is_open()) {
        cout << "el archivo no esta abierto" << endl;
        return 0;
    }
    // reiniciar el file al inicio
    Archivo.clear();
    Archivo.seekg(0);

    int contAsistencias = -1;
    uint aux;
    while (!Archivo.eof()) {
        Archivo.read((char *)&aux, sizeof(uint));
        Archivo.read((char *)&aux, sizeof(uint));
        eInscripcion auxInscripciones;
        for (uint i = 0; i < aux; i++) {
            Archivo.read((char *)&auxInscripciones, sizeof(eInscripcion));
        }
        contAsistencias++;
    }
    return contAsistencias;
}

eOperacion escribirAsistencias(eAsistencia* asistencias,uint cant,time_t hoy){
    ofstream fileOutPut(&"../../"[hoy]);
}




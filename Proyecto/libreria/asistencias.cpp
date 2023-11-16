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
eOperacion escribirAsistencias(ofstream &archivo, eAsistencia *asistencias, int cant) {
    ofstream ArchivoAsistencia("binary_file_out.bin", ios::binary);
    if (!ArchivoAsistencia.is_open()) {
        cout << "Error no abrio" << endl;
        return eOperacion::nofuncion;
    }

    Asistencia *aux = asistencias;

    for (int i = 0; i < cant; i++) {
        ArchivoAsistencia.write((char *)&aux[i].idCliente, sizeof(unsigned int));
        ArchivoAsistencia.write((char *)&aux[i].cantInscriptos, sizeof(unsigned int));
        for (unsigned int j = 0; j < aux[i].cantInscriptos; j++) {
            ArchivoAsistencia.write((char *)&aux[i].CursosInscriptos[j],sizeof(eInscripcion));
        }
    }

    return eOperacion::funciono;
}

int contarAsistencias(ifstream& Archivo){
    if (!Archivo.is_open()) {
        cout << "el archivo no esta abierto" << endl;
        return 0;
    }
    Archivo.clear();
    Archivo.seekg(0);

    int contAsistencias = -1;//empiezo en -1 por el encabezado
    unsigned int aux;
    while (!Archivo.eof()) {
        Archivo.read((char *)&aux, sizeof(unsigned int));
        Archivo.read((char *)&aux, sizeof(unsigned int));
        eInscripcion auxInscripciones;
        for (unsigned int i = 0; i < aux; i++) {
            Archivo.read((char *)&auxInscripciones, sizeof(eInscripcion));
        }
        contAsistencias++;
    }
    return contAsistencias;
}

eAsistencia* BuscarxAsistencia(eAsistencia* asistencias,uint cant ,str IDCliente) {
    eAsistencia* aux = asistencias;
        eAsistencia* ultima = (asistencias) +cant - 1;
    while(true) {
        if (aux->idCliente== stoul(IDCliente)) {
            return aux;
        }
        if (aux == ultima)
            break;
        aux++;
    }
    return nullptr;
}

eOperacion EscribirAsistencia(ofstream &file, eAsistencia* asistencias, int cant) {
    ofstream ArchivoAsistencia("binary_file_out.bin", ios::binary);
    if (!ArchivoAsistencia.is_open()) {
        cout << "Error de abertura de Archivo" << endl;
        return eOperacion::nofuncion;
    }

    Asistencia *aux = asistencias;

    for (int i = 0; i < cant; i++) {
        file.write((char *)&aux[i].idCliente, sizeof(unsigned int));
        file.write((char *)&aux[i].cantInscriptos, sizeof(unsigned int));
        for (unsigned int j = 0; j < aux[i].cantInscriptos; j++) {
            file.write((char *)&aux[i].CursosInscriptos[j],
                       sizeof(eInscripcion));
        }
    }

    return eOperacion::funciono;
}

eOperacion EscribirAsistenciaxdia(eAsistencia* asistencia,unsigned int cant,time_t hoy){
    ofstream ArchivoAsistencia(&"../../"[hoy]);
}
eOperacion agregarReserva(eAsistencia* asistencias,uint cant ,eAsistencia asistencia){

    *(asistencias + cant) = asistencia;

    return eOperacion::funciono;
}
eOperacion EscribirDiaria(eAsistencia *asistencias, uint cant, str hoy) {
    ofstream ArchivoAsistencias("../../asistencias_" + hoy,ios::binary);
    if (!ArchivoAsistencias.is_open()) {
        return eOperacion::nofuncion;
    }
    Asistencia *aux = asistencias;
    if (ArchivoAsistencias.is_open()) {
        for (uint i = 0; i < cant; i++) {
            ArchivoAsistencias.write((char *)&aux[i].idCliente, sizeof(uint));
            ArchivoAsistencias.write((char *)&aux[i].cantInscriptos, sizeof(uint));
            for (uint j = 0; j < aux[i].cantInscriptos; j++) {
                ArchivoAsistencias.write((char *)&aux[i].CursosInscriptos[j],sizeof(eInscripcion));
            }
        }
    }
    ArchivoAsistencias.close();
    return eOperacion::nofuncion;
}






#ifndef ASISTENCIAS_H
#define ASISTENCIAS_H
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include "clientes.h"

using namespace std;
enum Archivo{ ExitoAbrio=1, Noabrio=-1};
typedef enum Archivo Archi;

struct sInscripcion{
    unsigned int idClase;
    time_t fechaInscripcion;
}; typedef struct sInscripcion eInscripcion;

struct Asistencia{
    unsigned int idCliente, cantInscriptos;
    eInscripcion* CursosInscriptos;
};typedef struct Asistencia eAsistencia;

Asistencia* resizeAsistencia(eAsistencia* miLista,  unsigned int tam,  unsigned int nuevoTam);
eLectura ArchivoAsistencia(ifstream& ArchivoAsistencia,eAsistencia* asistencias);
eOperacion EscribirAsistencia(ofstream &file, eAsistencia* asistencias, int cant);
eLectura devolverAsistencia(ofstream &ArchivoAsistencia, eAsistencia* asistencias, int cant);
eOperacion EscribirAsistenciaxdia(eAsistencia* asistencia,unsigned int cant,time_t hoy);
#endif // ASISTENCIAS_H

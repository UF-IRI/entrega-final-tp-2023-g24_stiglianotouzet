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
void imprimirAsistencias(eAsistencia *asistencias, int cant);
void resizeasistencias(eAsistencia **miLista, uint tam, uint nuevoTam);
void imprimirAsistencias(eAsistencia *asistencias, int cant);
eOperacion agregarAsistencia(eAsistencia* asistencias,uint cant ,eAsistencia asistencia);
int ContarAsistencia(ifstream &archivoAsistencia);
eOperacion EscribirAsistencia(eAsistencia *asistencias, uint cant, str hoy);
eAsistencia* BuscarxAsistencia(eAsistencia* asistencias,uint cant ,str idCliente);
eOperacion agregarInscripcion(eInscripcion* inscripciones,uint cant,eInscripcion inscripcion);

#endif // ASISTENCIAS_H

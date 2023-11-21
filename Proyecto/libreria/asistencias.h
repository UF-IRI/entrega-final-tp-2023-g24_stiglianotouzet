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
enum operacion{nofuncion=-1, funciono=1,error=-2,exito=2,Clienterep=-1,Horariorep=-1,Cuposagotado=-1,ExitoInscripto,CuotaImpaga=-1,NoexisteClase=-1};
typedef enum operacion eOperacion;

struct sInscripcion{
    unsigned int idClase;
    time_t fechaInscripcion;
}; typedef struct sInscripcion eInscripcion;

struct Asistencia{
    unsigned int idCliente, cantInscriptos;
    eInscripcion* CursosInscriptos;
};typedef struct Asistencia eAsistencia;
//resize que devuelve array de asistencias
eAsistencia* resizeAsistencia(eAsistencia* miLista,  unsigned int tam,  unsigned int nuevoTam);
//resize void
void ResizeAsistencia(eAsistencia* miLista, uint tam, uint nuevoTam);
//lectura archivo asistencias
eLectura ArchivoAsistencia(ifstream& ArchivoAsistencia,eAsistencia* asistencias);
//escribir asistencias
void EscribirAsistencias(eAsistencia *asistencias, uint cant);
//buscar por asistencia
eAsistencia* buscarxAsistencia(eAsistencia* asistencias, uint cant, uint idCliente);
//agregar inscripcion en el array de las asistencias
eOperacion agregarInscripcion(eInscripcion* inscripciones, uint cant, eInscripcion inscripcion);
//nueva asistencia
eOperacion NuevaAsistencia(eAsistencia* asistencias, uint cant, Asistencia asistencia);


#endif // ASISTENCIAS_H

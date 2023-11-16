#ifndef CLASES_H
#define CLASES_H
#include "clientes.h"
#include "asistencias.h"
#include <iostream>
#include <string>

using namespace std;
typedef std::string str;

struct clases{

    str idClase, horario, nombreclase;
    unsigned int cupo;//si el cupo es 0 es xq es musculacion
};typedef struct clases eClases;

struct reserva{
    unsigned int idReserva;
    str idClase;
    unsigned int Horario;
    str* Inscripciones;
    int cantInscripciones;
};typedef struct reserva eReserva;

const eReserva reservaNula = { 0,"",0,0,0};
const eClases ClaseNula = { "","","",0};

struct gimnasio {
    eClientes* clientes;
    unsigned int cantClientes;
    eAsistencia* asistencias;
    unsigned int cantAsistencias;
    unsigned int cantMaxasistencias;
    eClases* clases;
    unsigned int cantClases;
    time_t hoy;
    eReserva* reservas;
    unsigned int cantReservas;
};typedef struct gimnasio eGimnasio;

enum turnos{estaAnotado=-1,puedeAnotarse=1,Clientenulo=-1, ClienteExistente=1, Clasenula=-1, Claseexistente=1,Horariorepetido=-1, HorarioDisponible=1};
typedef enum turnos eTurnos;
//funcion de leer el archivo de clases
eLectura ArchivoClases(eClases* clases,ifstream& archivo);
//funcion de asignar cupo a las clases
unsigned int asignarcupos(str clase);
//funcion de fijarse si no esta repetido el cliente
eTurnos ClienteRepetido(str *inscriptions, unsigned int cant, str idClient);


eReserva estaClienteEnReserva(eGimnasio* gimnasio, str idCliente, str idClase);
#endif // CLASES_H

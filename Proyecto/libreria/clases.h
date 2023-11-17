#ifndef CLASES_H
#define CLASES_H
#include "clientes.h"
#include "asistencias.h"
#include <iostream>
#include <string>

using namespace std;
typedef std::string str;

struct clases{

    str idClase, nombreclase;
    int capacidadMaxima;
    str* horario;
    int contHorario;
    int largo;
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

enum turnos{estaAnotado=-1,puedeAnotarse=1,Clientenulo=-1, ClienteExistente=1, Clasenula=-1, Claseexistente=1,Horariorepetido=-1, HorarioDisponible=1, Nohayespacio=-1,exito=1,error=-1};
typedef enum turnos eTurnos;
//funcion de leer el archivo de clases
eLectura ArchivoClases(eClases* clases,ifstream& archivo);
//funcion de asignar cupo a las clases
unsigned int asignarcupos(str clase);
//buscar por reserva
eReserva BuscarxReserva(eReserva* reservas, unsigned int cant, unsigned int ID);
//funcion de fijarse si no esta repetido el cliente
eTurnos ClienteRepetido(str *inscriptions, unsigned int cant, str idClient);
//fijarse si la clase existe
bool Clasexistente(eReserva *reserva, uint cant, uint ID);
//buscar por clase
eClases BuscarxClase(eClases *clases, unsigned int cant, str IDclase);
//fijarse si el cliente ya reservo esa clase
eReserva estaClienteEnReserva(eGimnasio* gimnasio, str idCliente, str idClase);
//horario repetido
eTurnos HorarioRepetido(eReserva* reserva, unsigned int cant, unsigned int horario, str ID);
//cliente repetido
eTurnos ClienteRepetido(str *inscriptions, unsigned int cant, str idClient);
//contar clases
int ContarClases(ifstream& archivo, int realCantClases);
#endif // CLASES_H

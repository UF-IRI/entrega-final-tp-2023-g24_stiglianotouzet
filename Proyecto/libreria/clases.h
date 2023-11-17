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
const eClases ClaseNula = { "", "", 0, NULL, 0, 0, 0 };
struct reserva{
    unsigned int idReserva;
    str idClase;
    unsigned int Horario;
    str* Inscripciones;
    int cantInscripciones;
};typedef struct reserva eReserva;

const eReserva reservaNula = { 0,"",0,0,0};


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

enum turnos{estaAnotado=-1,puedeAnotarse=1,Clientenulo=-2, ClientesExistente=2, Clasenula=-3, Claseexistente=3,Horariorepetido=-4, HorarioDisponible=4, Nohayespacio=-5};
typedef enum turnos eTurnos;
void imprimirReservas(eReserva* reservas,uint cant);
eOperacion reservarClase(eGimnasio* gimnasio, uint idReserva, str idCliente);
eClases encontrarClase(eClases *clases, uint cant, str idClase);
bool existeReserva(eReserva *reserva, uint cant, uint id);
eReserva BuscarxReserva(eReserva *reserva, uint cant, uint id);
bool HorarioRepetido(eReserva *reservas, uint cant, uint horario, str idCliente);
bool clienteInscripto(str *inscripciones, uint cant, str idClient);
eOperacion leerClases(eClases *clases, eReserva *reservas, ifstream &file, int cant);
eClases buscarClase(eClases *clases, int cant, str idCLase);
eOperacion BuscarxClase(eClases *clases, int cant, str nombreClase);
uint ContarClase(ifstream &file, uint &realCantclases);
uint genRandomNumber(uint min,uint max);
#endif // CLASES_H

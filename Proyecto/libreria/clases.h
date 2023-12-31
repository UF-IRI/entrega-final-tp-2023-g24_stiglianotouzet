#ifndef CLASES_H
#define CLASES_H
#include "tipos.h"
#include "clientes.h"
#include "asistencias.h"
struct clases{

    uint idClase;
    str nombreclase;
    uint capacidadMaxima;
    uint capacidadActual;
    uint horario;
    unsigned int cupo;//si el cupo es 0 es xq es musculacion
};typedef struct clases eClases;
const eClases ClaseNula = { 0,"",0,0,0,0};

struct reserva{
    uint  idReserva;
    uint idClase;
    uint  Horario;
    str* Inscripciones;
    uint cantInscripciones;
};typedef struct reserva eReserva;
const eReserva reservaNula = { 0,0,0,NULL,0};


struct gimnasio {
    eClientes* clientes;
    uint  cantClientes;
    eAsistencia* asistencias;
    uint  cantAsistencias;
    uint  cantMaxasistencias;
    eClases* clases;
    uint  cantClases;
    eReserva* reservas;
    uint  cantReservas;
};typedef struct gimnasio eGimnasio;

//buscarXclase
eOperacion BuscarClase(eClases *clases, int cant, str nombreClase);
//asignarCuposmaximos
unsigned int asignarcupos(str clase);
//leer archivo
eLectura leerClases(eClases* clases, ifstream& ArchivoClases);
//horario repetido
bool HorarioRepetido(eReserva* reserva, uint cant, uint horario, uint idCliente);
//cliente repetido
bool ClienteRepetido(str* incripciones, uint cant, uint idCliente);
//estado del cliente
bool Estado(eClientes cliente);
//buscarXreserva
eReserva buscarxReserva(eReserva *reservas, uint cant, uint reserva);
//buscarXclase
eOperacion BuscarClase(eClases *clases, int cant, str nombreClase);
eClases buscarxClase(eClases *clases, uint cant, uint idClase);
//buscarXCliente
eClientes buscarxCliente(eGimnasio* gimnasio, uint idCliente);
//reservar Clase
eOperacion reservar(eGimnasio *gimnasio, uint idReserva, uint idCliente);
//numero random para generar reservas
uint numeroRandom(uint min,uint max);

#endif // CLASES_H

#ifndef CLASES_H
#define CLASES_H
#include "clientes.h"
#include "asistencias.h"
#include <iostream>
#include <string>

using namespace std;
typedef std::string str;

struct clases{

    uint idClase;
    str nombreclase;
    uint capacidadMaxima;
    str* horario;
    uint contHorario;
    uint largo;
    unsigned int cupo;//si el cupo es 0 es xq es musculacion
};typedef struct clases eClases;
const eClases ClaseNula = { 0, "", 0, NULL, 0, 0, 0 };
struct reserva{
    uint  idReserva;
    uint idClase;
    uint  Horario;
    str* Inscripciones;
    int cantInscripciones;
};typedef struct reserva eReserva;

const eReserva reservaNula = { 0,0,0,0,0};


struct gimnasio {
    eClientes* clientes;
    uint  cantClientes;
    eAsistencia* asistencias;
    uint  cantAsistencias;
    uint  cantMaxasistencias;
    eClases* clases;
    uint  cantClases;
    time_t hoy;
    eReserva* reservas;
    uint  cantReservas;
};typedef struct gimnasio eGimnasio;

enum turnos{estaAnotado=-1,puedeAnotarse=1,Clientenulo=-2, ClientesExistente=2, Clasenula=-3, Claseexistente=3,Horariorepetido=-4, HorarioDisponible=4, Nohayespacio=-5};
typedef enum turnos eTurnos;
//imprimi las reservas
void imprimirReservas(eReserva* reservas,uint cant);
//reservo clase (funcion global)
eOperacion reservarClase(eGimnasio* gimnasio, uint idReserva, str idCliente);
//busco clase y la retorno
eClases encontrarClase(eClases *clases, uint cant, str idClase);
//me fijo si no se anoto ya en esa clase
bool existeReserva(eReserva *reserva, uint cant, uint id);
//busco por reserva y la retorno
eReserva BuscarxReserva(eReserva *reserva, uint cant, uint id);
//me fijo si se puede anotar el cliente en el horario
bool HorarioRepetido(eReserva *reservas, uint cant, uint horario, str idCliente);
//me fijo si el cliente no esta inscripto
bool clienteInscripto(str *inscripciones, uint cant, str idClient);
//leo el archivo clase
eOperacion leerClases(eClases *clases, eReserva *reservas, ifstream &file, int cant);
//buscar la clase por el nombre
eOperacion BuscarxClase(eClases *clases, int cant, str nombreClase);
//cuento las clases para saber las que no estan repetidas y no son musculacion
uint ContarClase(ifstream &file, uint &realCantclases);
//numero random para generar reservas
uint numeroRandom(uint min,uint max);

#endif // CLASES_H

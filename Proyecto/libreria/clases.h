#ifndef CLASES_H
#define CLASES_H
#include "clientes.h"
#include <iostream>
#include <string>


using namespace std;
typedef std::string str;

struct clases{

    str idClase, horario, nombreclase;
    unsigned int cupo;//si el cupo es 0 es xq es musculacion
};typedef struct clases eClases;
//funcion de leer el archivo de clases
eLectura ArchivoClases(eClases* clases,ifstream& archivo);
//funcion de asignar cupo a las clases
unsigned int asignarcupos(str clase);
#endif // CLASES_H

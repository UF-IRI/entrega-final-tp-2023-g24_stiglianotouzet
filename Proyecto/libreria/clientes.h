#ifndef CLIENTES_H
#define CLIENTES_H
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;
typedef std::string str;
enum lectura{exitoabrio=1, Errornoabrio=-1};
typedef enum lectura eLectura;


struct clientes{

    str id,nombre, apellido, correo, telefono, fechaNac;
    int estado;
};typedef struct clientes eClientes;
//leer clientes del archivo
eLectura ArchivoClientes(eClientes* clientes,ifstream& archivo);
#endif // CLIENTES_H

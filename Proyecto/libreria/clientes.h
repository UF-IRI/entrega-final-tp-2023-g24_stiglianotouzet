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

enum operacion{nofuncion=-1, funciono=1};
typedef enum operacion eOperacion;

struct clientes{

    str id,nombre, apellido, correo, telefono, fechaNac;
    int estado;
};typedef struct clientes eClientes;

const eClientes clienteNulo{"", "", "", "", "", "", 0};
//leer clientes del archivo
eLectura ArchivoClientes(eClientes* clientes,ifstream& archivo);
//buscar por id
eClientes BuscarxID(eClientes* clientes,unsigned int cant, str id);
//retorno cliente
bool existeCliente(eClientes* clientes,unsigned int cant, str id);

#endif // CLIENTES_H



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

enum operacion{nofuncion=-1, funciono=1,error=-2,exito=2};
typedef enum operacion eOperacion;

struct clientes{

    str id,nombre, apellido, correo, telefono, fechaNac;
    int estado;
};typedef struct clientes eClientes;

const eClientes clienteNulo{"", "", "", "", "", "", 0};
//leer clientes del archivo
eLectura ArchivoClientes(eClientes* clientes,ifstream& file);
//reemplazar caracteres
void ReemplazarCaracteres(string &linea, string buscar,string reemplazar);
//imprimir clientes
void ImprimirClientes(eClientes *clientes, int cant);
//buscar por id
eClientes BuscarxCliente(eClientes *clientes, uint cant, str id);
//Cliente existente?
bool ClienteExistente(eClientes *clientes, uint cant, str id);

#endif // CLIENTES_H



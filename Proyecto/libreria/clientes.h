#ifndef CLIENTES_H
#define CLIENTES_H
#include "tipos.h"
struct clientes{

    unsigned int id;
    str nombre, apellido, correo, telefono, fechaNac,estado;
};typedef struct clientes eClientes;

const eClientes clienteNulo{0, "", "", "", "", "", 0};
//leer clientes del archivo
eLectura ArchivoClientes(eClientes* clientes,ifstream& file);
//reemplazar caracteres
void ReemplazarCaracteres(string &linea, string buscar,string reemplazar);
//imprimir clientes
void ImprimirClientes(eClientes *clientes, int cant);
//buscar por id
eClientes BuscarxCliente(eClientes *clientes, uint cant, str id);
//Cliente existente?
bool ClienteExistente(eClientes *clientes, uint cant, uint id);

#endif // CLIENTES_H



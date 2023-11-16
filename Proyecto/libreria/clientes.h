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
#endif // CLIENTES_H
/*eClientes clientes[4]{
    "45803941","amelia","aguilar","vulputate.eu.odio@aol.com","1-543-748-2254","02/12/1970","1";
    "23843098","Wyatt", "Walker","tempor@protonmail.edu","1-640-387-7958","23/04/1870",2;
    "35680981","Ramona","Martin","velit.eget@icloud.couk","1-640-387-7958","30/09/1992",-1;
    "00000000","0","0","","","",0;
};*/


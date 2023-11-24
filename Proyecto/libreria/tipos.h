#ifndef TIPOS_H
#define TIPOS_H



#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;
typedef std::string str;


typedef unsigned int uint;

enum lectura{exitoabrio=1, Errornoabrio=-1,exitolectura=2};
typedef enum lectura eLectura;


enum operacion{nofuncion=-1, funciono=1,error=-2,exito=2,Clienterep=-1,Horariorep=-1,Cuposagotado=-1,ExitoInscripto,CuotaImpaga=-1,NoexisteClase=-1};
typedef enum operacion eOperacion;

#endif // TIPOS_H

#include "clases.h"
//funcion de asignar cupo a la clase
unsigned int asignarcupos(str clase){
    unsigned int cupo=0;
    if(clase=="Spinning" || clase=="spinning"){
        cupo=45;
    }
    if(clase=="Yoga" || clase=="yoga"){
        cupo=25;
    }
    if(clase=="Pilates" || clase=="pilates"){
        cupo=15;
    }
    if(clase=="Stretching" || clase=="stretching"){
        cupo=40;
    }
    if(clase=="Zumba"|| clase=="zumba"){
        cupo=50;
    }
    if(clase=="Boxeo"|| clase=="boxeo"){
        cupo=30;
    }
    return cupo;
}
//funcion de lectura del archivo clase
eLectura ArchivoClases(eClases* clases,ifstream& archivo){
    if(!archivo.is_open())
        return eLectura::Errornoabrio;
    archivo.clear();
    archivo.seekg(0);

    str encabezado;

    getline(archivo, encabezado);
    eClases* aux = clases;
    while (archivo.good()) {
        str linea;
        getline(archivo, linea);
        if(archivo.eof())
            break;
        char delim = ',';
        string idClase, NombreClase, horario;
        std::istringstream iss(linea);
        getline(iss, idClase, delim);
        getline(iss, NombreClase, delim);
        getline(iss, horario, delim);
        aux->idClase = idClase;
        aux->nombreclase  = NombreClase;
        aux->horario  =stoi(horario);
        (aux->cupo=asignarcupos(NombreClase));
        aux++;
    }

    return eLectura::exitoabrio;
}

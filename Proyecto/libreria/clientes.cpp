#include "clientes.h"
//funcion de lectura del archivo cliente
eLectura ArchivoClientes(eClientes* clientes,ifstream& archivo){
        if(!archivo.is_open())
            return eLectura::Errornoabrio;
        archivo.clear();
        archivo.seekg(0);

        str encabezado;

        getline(archivo, encabezado);
        eClientes* aux = clientes;
        while (archivo.good()) {
            str linea;
            getline(archivo, linea);
            if(archivo.eof())
                break;
            char delim = ',';
            string idCliente, nombre, apellido, email, telefono, fechaNac, estado;
            str field;
            std::istringstream iss(linea);
            getline(iss, idCliente, delim);
            getline(iss, nombre, delim);
            getline(iss, apellido, delim);
            getline(iss, email, delim);
            getline(iss, telefono, delim);
            getline(iss, fechaNac, delim);
            getline(iss, estado, delim);
            aux->id = idCliente;
            aux->nombre  = nombre;
            aux->correo  = email;
            aux->apellido  = apellido;
            aux->telefono  = telefono;
            aux->fechaNac  = fechaNac;
            aux->estado  = stoi(estado);
            aux++;
        }

        return eLectura::exitoabrio;
}







/*void ArchDevolverClientes(eClientes* clientes, ifstream& archivo){

        str header;

        getline(archivo, header);
        eClientes* aux = clientes;
        while (archivo.good()) {
            str linea;
            getline(archivo, linea);
            if(archivo.eof())
                break;
            char delimitador = ',';
            string idCliente, nombre, apellido, email, telefono, fechaNac, estado;
            std::istringstream iss(linea);
            getline(iss, idCliente, delimitador);
            getline(iss, nombre, delimitador);
            getline(iss, apellido, delimitador);
            getline(iss, email, delimitador);
            getline(iss, telefono, delimitador);
            getline(iss, fechaNac, delimitador);
            getline(iss, estado, delimitador);
            aux->id = idCliente;
            aux->nombre = nombre;
            aux->correo  = email;
            aux->apellido  = apellido;
            aux->telefono  = telefono;
            aux->fechaNac  = fechaNac;
            aux->estado  = stoi(estado);
            aux++;
        }
        clientes=aux;
        delete [] aux;


}*/

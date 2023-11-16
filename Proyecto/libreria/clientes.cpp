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


eClientes BuscarxID(eClientes* clientes,unsigned int cant, str id) {
        eClientes* aux = clientes,
            * ultimo = (clientes) + cant - 1;
        while(true) {
            if (aux->id == id ) {
                return *aux;
            }
            if (aux == ultimo)
                break;
            aux++;
        }
        return clienteNulo;
}

bool existClient(eClientes* clientes,unsigned int cant, str id){

        return BuscarxID(clientes,cant,id).id != "" ;
}










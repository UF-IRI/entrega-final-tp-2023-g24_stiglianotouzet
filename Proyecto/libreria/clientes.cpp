#include "clientes.h"
//reemplazar caracteres

void ReemplazarCaracteres(string &linea, string buscar, string reemplazar) {
    string::size_type pos = linea.find(buscar);
    while (pos != string::npos) {
        linea.replace(pos, buscar.size(), reemplazar);
        pos = linea.find(buscar, pos + reemplazar.size());
    }
}

//funcion de lectura del archivo clientes
eLectura archivoClientes(eClientes *clientes, ifstream &file) {
        if (!file.is_open())
            return eLectura::Errornoabrio;
        // reiniciar el file al inicio
        file.clear();
        file.seekg(0);

        str header;

        getline(file, header);
        // ELIMINO EL HEADER DE MIERDA DE LAS LINEAS A LEER
        eClientes *aux = clientes;
        str line;
        while (getline(file, line)) {
            char delimiter = ',';
            string idCliente, nombre, apellido, email, telefono, fechaNac, estado;

                ReemplazarCaracteres(line, "á", "a");
                ReemplazarCaracteres(line, "é", "e");
                ReemplazarCaracteres(line, "í", "i");
                ReemplazarCaracteres(line, "ó", "o");
                ReemplazarCaracteres(line, "ú", "u");
                ReemplazarCaracteres(line, "ñ", "ni");
                ReemplazarCaracteres(line, "Á", "A");
                ReemplazarCaracteres(line, "É", "E");
                ReemplazarCaracteres(line, "Í", "I");
                ReemplazarCaracteres(line, "Ó", "O");
                ReemplazarCaracteres(line, "Ú", "U");
                ReemplazarCaracteres(line, "Ñ", "NI");
                ReemplazarCaracteres(line, "¿", "");
                ReemplazarCaracteres(line, "¡", "");
                std::istringstream iss(line);
            getline(iss, idCliente, delimiter);
            getline(iss, nombre, delimiter);
            getline(iss, apellido, delimiter);
            getline(iss, email, delimiter);
            getline(iss, telefono, delimiter);
            getline(iss, fechaNac, delimiter);
            getline(iss, estado, delimiter);
            aux->id = stoi(idCliente);
            aux->nombre = nombre;
            aux->correo = email;
            aux->apellido = apellido;
            aux->telefono = telefono;
            aux->fechaNac = fechaNac;
            aux->estado = estado;
            aux++;
        }

        return eLectura::exitoabrio;
}


void ImprimirClientes(eClientes *clientes, int cant) {
        eClientes *aux = clientes;
        eClientes* ultimo = (clientes) + (cant - 1);
        cout << "clientes:" << endl;
        if (cant == 0)
            return;

        while (true) {
            cout << "id:" << aux->nombre << endl;
            if (aux == ultimo)
                break;
            aux++; // aux = aux + 1 o aux+= 1
        }
        cout << "......" << endl;
}

eClientes BuscarxCliente(eClientes *clientes, uint cant, uint id) {
        eClientes *aux = clientes;
        eClientes *ultimo = (clientes) + cant - 1;
        while (true) {
            if (aux->id == id) {
                return *aux;
            }
            if (aux == ultimo)
                break;
            aux++;
        }
        return clienteNulo;
}

bool ClienteExistente(eClientes *clientes, uint cant, uint id) {

        return BuscarxCliente(clientes, cant, id).id != 0;
}












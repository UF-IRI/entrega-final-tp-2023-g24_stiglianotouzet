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
int ContarClases(ifstream& archivo, int realCantClases) {
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo binario" <<endl;
        return 0;
    }

    if (realCantClases != 0) {
        realCantClases = 0;
    }

    // Reiniciar el archivo al inicio
    archivo.clear();
    archivo.seekg(0);

    str linea;
    int cantClases = 0;
    str nombres = "";
    str auxNombre;
    char delim=',';

    getline(archivo, linea); // Obtener encabezado

    while (getline(archivo, linea)) {
        std::istringstream iss(linea);
        getline(iss, auxNombre, delim);
        getline(iss, auxNombre, delim);
        size_t pos = 0;
        str token;
        str nombreParaDividir = nombres;
        bool encontrado = false;

        if (nombreParaDividir.length() != 0) {
            while ((pos = nombreParaDividir.find(',')) != string::npos) {
                token = nombreParaDividir.substr(0, pos);
                nombreParaDividir.erase(0, pos + 1);
                if (token == auxNombre) {
                    encontrado = true;
                }
            }

            if (!encontrado && auxNombre.compare("Musculacion") != 0 &&
                auxNombre.compare("") != 0) {
                nombres += auxNombre + ',';
                cantClases++;
            }
        } else {
            nombres = auxNombre + ',';
            cantClases++;
        }

        realCantClases++;
    }

    return cantClases;
}

eTurnos ClienteRepetido(str *inscriptions, unsigned int cant, str idClient){
    str *inscripcion = (inscriptions);
    str *ultimaInscripcion = (inscriptions) + cant - 1;
    while (true) {
        if (*inscripcion == idClient) {
            return eTurnos::estaAnotado;
        }
        if (inscripcion == ultimaInscripcion)
            break;
        inscripcion++;
    }
    return eTurnos::puedeAnotarse;
}
eTurnos HorarioRepetido(eReserva* reserva, unsigned int cant, unsigned int horario, str ID) {
    eReserva *aux = reserva;
    eReserva *ultima = (reserva) + cant - 1;

    while (true) {

        if (aux->Horario == horario) {
            if (ClienteRepetido(aux->Inscripciones, aux->cantInscripciones,ID)) {
                return eTurnos::Horariorepetido;
            }
        }

        if (aux == ultima)
            break;
        aux++;
    }
    return eTurnos::HorarioDisponible;
}

eReserva BuscarxReserva(eReserva* reservas, unsigned int cant, unsigned int ID) {
    eReserva *aux = reservas;
    eReserva*ultimo = (reservas) + cant - 1;
    while (true) {
        if (aux->idReserva == ID) {
            return *aux;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return reservaNula;
}
eTurnos ClaseExistente(eReserva*reservas, unsigned int cant, unsigned int id) {

    return BuscarxReserva(reservas, cant, id).idClase != " ";
}

eClases findClass(eClases *clases, unsigned int cant, str idClase) {
    eClases *aux = clases, *ultimo = (clases) + cant - 1;
    while (true) {
        if (aux->idClase == idClase) {
            return *aux;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return ClaseNula;
}

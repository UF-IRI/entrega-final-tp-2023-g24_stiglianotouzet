#include "clases.h"
#include "asistencias.cpp"
//funcion de asignar cupo a la clase

eOperacion BuscarClase(eClases *clases, int cant, str nombreClase) {
    eClases *aux = clases;
    eClases* ultimo = (clases) + (cant - 1);
    while (true) {
        if (aux->nombreclase == nombreClase) {
            return eOperacion::exito;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return eOperacion::error;
}
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

eLectura leerClases(eClases* clases, ifstream& ArchivoClases){
    ArchivoClases.clear();
    ArchivoClases.seekg(0);
    str header;
    getline(ArchivoClases, header);
    eClases* aux = clases;
    str linea;
    while (getline(ArchivoClases,linea)) {
        char delim = ',';
        string idClase, nombre, horario;
        std::istringstream iss(linea);
        getline(iss, idClase, delim);
        getline(iss, nombre, delim);
        getline(iss, horario, delim);
        aux->idClase = stoi(idClase);
        aux->nombreclase  = nombre;
        aux->capacidadMaxima = asignarcupos(nombre);
        aux++;
    }
    cout << endl;
    return eLectura::exitolectura;
}


uint numeroRandom(uint min, uint max){
    uint n;
    n = (rand() % max) + min;
    return n;
}



bool ClienteRepetido(str* incripciones, uint cant, uint idCliente){
    str *aux = incripciones;
    str *ultimoInscripto = incripciones + (cant - 1);
    while (true) {
        if (*aux == std::to_string(idCliente)) {
            return true;
        }
        if (aux == ultimoInscripto)//esto significa que llegue al final
            break;
        aux++;
    }
    return false;
}

bool HorarioRepetido(eReserva* reserva, uint cant, uint horario, uint idCliente) {
    eReserva* aux = reserva;
    eReserva* ultimaReserva = reserva + (cant - 1);
    while (true) {
        if (aux->Horario == horario) {
            str* auxInscripciones = aux->Inscripciones;
            str* ultimaInscripcion = aux->Inscripciones + (aux->cantInscripciones - 1);
            while (true) {
                if (*auxInscripciones == std::to_string(idCliente)) {
                    return true;
                }
                if (auxInscripciones == ultimaInscripcion)
                    break;
                auxInscripciones++;
            }
        }
        if (aux == ultimaReserva)
            break;
        aux++;
    }
    return false;
}

eReserva buscarxReserva(eReserva *reservas, uint cant, uint reserva) {
    eReserva *aux = reservas;
    eReserva*ultimareserva = reservas + (cant - 1);
    while (true) {
        if (aux->idReserva == reserva) {
            return *aux;
        }
        if (aux == ultimareserva)
            break;
        aux++;
    }
    return reservaNula;
}

eClientes buscarxCliente(eGimnasio* gimnasio, uint idCliente) {
    eClientes* aux = gimnasio->clientes;
    eClientes* ultimoCliente = gimnasio->clientes + (gimnasio->cantClientes - 1);
    while(true) {
        if (aux->id == idCliente) {
            return *aux;
        }
        if (aux == ultimoCliente)
            break;
        aux++;
    }
    return clienteNulo;
}

bool Estado(eClientes cliente){
    if(stol(cliente.estado) >= 0){
        return true;
    }
    return false;
}
eClases buscarxClase(eClases *clases, uint cant, uint idClase) {
    eClases* aux = clases;
    eClases* ultimaClase = clases + (cant - 1);
    while (true) {
        if (aux->idClase == idClase) {
            return *aux;
        }
        if (aux == ultimaClase)//llegue al final
            break;
        aux++;
    }
    return ClaseNula;
}

eOperacion reservar(eGimnasio *gimnasio, uint idReserva, uint idCliente) {
    eClientes cliente;
    cliente= buscarxCliente(gimnasio, idCliente);
    if(!Estado(cliente)){
        return eOperacion::CuotaImpaga;
    }
    eReserva ReservarClase = buscarxReserva(gimnasio->reservas, gimnasio->cantReservas, idReserva);
    if (ReservarClase.idClase == 0) {
        return eOperacion::NoexisteClase;
    }
    eClases ClasesnoRepetidas = buscarxClase(gimnasio->clases, gimnasio->cantClases, ReservarClase.idClase);
    if (ReservarClase.cantInscripciones < ClasesnoRepetidas.capacidadMaxima) {
        return eOperacion::error;
    }
    if (HorarioRepetido(gimnasio->reservas, gimnasio->cantReservas, ReservarClase.Horario, idCliente) || ClienteRepetido(gimnasio->reservas->Inscripciones, gimnasio->reservas->cantInscripciones, idCliente)) {
        return eOperacion::error;
    }
    uint ClasesmaxCliente = numeroRandom(1, 5);
    EscribirAsistencias(gimnasio->asistencias, ClasesmaxCliente);
    return eOperacion::exito;
}

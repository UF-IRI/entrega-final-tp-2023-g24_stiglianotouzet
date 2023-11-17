#include "clases.h"
#include "asistencias.cpp"
//funcion de asignar cupo a la clase
eOperacion buscarClase(eClases *clases, int cant, str name) {
    eClases *aux = clases;
    eClases* ultimo = (clases) + cant - 1;
    while (true) {
        if (aux->nombreclase == name) {
            return eOperacion::nofuncion;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return eOperacion::funciono;
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
eOperacion leerClases(eClases *clases, eReserva *reservas, ifstream &file, int cant) {
    // SABIENDO QUE ESTA ORDENADO EL ARCHIVO CLASES
    if (!file.is_open())
        return eCodFile::ErrorOpening;
    // Setear inicio
    file.clear();
    file.seekg(0);

    str header;
    getline(file, header);
    eClases *aux = clases;
    eReserva *auxReservas = reservas;
    str *contHorario;
    bool firstLine = true;
    str line;
    while (getline(file, line)) {
        char delimiter = ',';
        string idClase, nombre, horario;
        str field;
        std::istringstream iss(line);
        getline(iss, idClase, delimiter);
        getline(iss, nombre, delimiter);
        getline(iss, horario, delimiter);

        eOperacion res = buscarClase(clases, cant, nombre);

        if (res == eOperacion::funciono && nombre != "Musculacion") {
            *contHorario = horario;
            contHorario++;
            aux->contHorario += 1;

            // Init Book
            auxReservas->idClase = stoul(idClase);
            auxReservas->cantInscripciones = 0;
            auxReservas->Inscripciones = new string[aux->capacidadMaxima];
            auxReservas->idClase = aux->idClase;
            auxReservas->Horario = stoul(horario);

        } else if (nombre != "Musculacion" && nombre != aux->nombreclase) {
            if (!firstLine) {
                aux++;
            } else {
                firstLine = false;
            }
            aux->idClase = idClase;
            aux->nombreclase = nombre;
            aux->largo = 60;
            aux->capacidadMaxima = 45;
            aux->horario = new str[10];
            aux->contHorario = 0;
            contHorario = aux->horario;

            // Init Book
            auxReservas->idReserva = stoul(idClase);
            auxReservas->cantInscripciones = 0;
            auxReservas->Inscripciones = new str[aux->capacidadMaxima];
            auxReservas->idClase = aux->idClase;
            auxReservas->Horario = stoul(horario);
        }
        auxReservas++;
    }

    return eOperacion::funciono;
}


void imprimirClases(eClases *clases, int cant) {
    eClases *aux = clases;
    eClases* ultimo = (clases) + (cant - 1);
    cout << "clases:" << endl;
    while (true) {
        cout << "nombre:" << aux->nombreclase << endl;
        str *auxHorario = aux->horario;
        str *ultimoHorario = (aux->horario) + (aux->contHorario - 1);
        cout << "Horarios:";
        while (true) {
            cout << *auxHorario << ",";
            if (auxHorario == ultimoHorario)
                break;
            auxHorario++;
        }
        cout << endl;
        if (aux == ultimo)
            break;
        aux++;
    }
    cout << "---------------------------------------" << endl;
}


uint ContarClase(ifstream &file, uint &realCantclases) {

    if (!file.is_open()) {
        cout << "Error opening binary file" << endl;
        return 0;
    }
    if (realCantclases != 0) {
        realCantclases = 0;
    }
    // reiniciar el file al inicio
    file.clear();
    file.seekg(0);

    str line;
    int cantClasses = 0;
    str nombres = "";
    str nombre;
    getline(file, line); // get header
    while (getline(file, line)) {
        std::istringstream iss(line);
        getline(iss, nombre, ',');
        getline(iss, nombre, ',');
        size_t pos = 0;
        str token;
        str nombresc = nombres;
        bool encontrar = false;
        if (nombresc.length() != 0) {
            while ((pos = nombresc.find(',')) != std::string::npos) {
                token = nombresc.substr(0, pos);
                nombresc.erase(0, pos + 1);
                if (token == nombre) {
                    encontrar = true;
                }
            }
            if (!encontrar && nombre.compare("Musculacion") != 0 &&
                nombre.compare("") != 0) {
                nombres += nombre + ',';
                cantClasses++;
            }
        } else {
            nombres = nombre + ',';
            cantClasses++;
        }
        if(nombre.compare("Musculacion") != 0){
            realCantclases++;
        }
    }

    return cantClasses;
}

eOperacion reservarClase(eGimnasio &gimnasio, uint idReserva, str idClient) {

    eReserva reserva = findBook(gimnasio.reservas, gimnasio.cantReservas, idReserva);
    eClases clase = findClass(gimnasio.clases, gimnasio.cantClases, reserva.idClase);

    // comprobar que la clase existe
    if (reserva.idClase == "") {
        return eOperacion::Clasenula;

        // comprobar que la clase tenga espacio
    } else if (reserva.cantInscripciones >= clase.capacidadMaxima) {
        return eOperacion::error;
    }

    // comprobar que existe el cliente
    if (!ClienteExistente(gimnasio.clientes, gimnasio.cantClientes, idClient)) {
        return eOperacion::error;

        /* Comprobar que el cliente no este inscripto en otra clase en el mismo
       horario, a su vez chequea que no este en ya inscripto en esta clase */
    } else if (HorarioRepetido(gimnasio.reservas, gimnasio.cantReservas, reserva.Horario,
                                  idClient)) {
        return eOperacion::error;
    }

    // revisar si sigue siendo hoy, sino reiniciar asistencias
    time_t now = time(0);
    uint diff = difftime(now, gym.today) / 60 / 60 / 24;
    if (diff >= 1) {
        // siguiente dia
        gym.today = now;
        // Guardo las asistencias en mi archivo
        stringstream ss;
        str timeAsString;
        ss << now << ',' << endl;
        getline(ss, timeAsString, ',');
        EscribirAsistencia(gimnasio.asistencias, gimnasio.cantAsistencias, timeAsString);

        // Reinicio las asistencias y paso de dia

        resizeasistencias(&gimnasio.asistencias, gimnasio.cantAsistencias, 0);
        gimnasio.cantAsistencias = 0;
    } else {

        eInscripcion nuevaInscripcion = {idReserva,time(0)};
        // CHEQUEAR QUE HAYA ESPACIO
        if (gimnasio.cantAsistencias < gimnasio.cantMaxasistencias) {
            // guardar asistencia
            Asistencia* asistencia =BuscarxAsistencia(gimnasio.asistencias, gimnasio.cantAsistencias, idClient);
            // chequear si existe
            if (asistencia == nullptr) {
                // crearla y agregar
                Asistencia nuevaAsistencia = {stoul(idClient),1,new eInscripcion[5]};
                *nuevaAsistencia.CursosInscriptos = nuevaInscripcion;
                gimnasio.cantAsistencias ++;
                agregarAsistencia(gimnasio.asistencias,gimnasio.cantAsistencias,nuevaAsistencia);
            } else {
                // agregar
                if(asistencia->cantInscriptos < 5){
                    asistencia->cantInscriptos++;
                    agregarAsistencia(asistencia->CursosInscriptos,asistencia->cantInscriptos,nuevaInscripcion);

                } else {
                    return eOperacion::error;
                }
            }
        } else {
            resizeAsistencia(&gimnasio.asistencias, gimnasio.contasistencias,
                              gimnasio.cantMaxasistencias * 2);
            gimnasio.cantAsistencias = gimnasio.cantMaxasistencias * 2;
            if (gimnasio.asistencias == nullptr) {
                return eOperacion::error;
            }
            ReservarClase(gimnasio,idReserva,idCliente);
        }
    }
    return eBookClass::SuccessBook;
}

bool clienteInscripto(str *inscripciones, uint cant, str idClient) {
    str *auxInscripciones = (inscripciones),
        *auxUltimaInscripcion = (inscripciones) + cant - 1;
    if(cant == 0){
        return false;
    }
    while (true) {
        if (*auxInscripciones == idClient) {
            return true;
        }
        if (auxInscripciones == auxUltimaInscripciones)
            break;
        auxInscripciones++;
    }
    return false;
}

bool isClientInSchedule(eReserva *reservas, uint cant, uint horario, str idCliente) {
    eReserva *aux = reservas;
    eReserva*ultimo = (reservas) + cant - 1;

    while (true) {

        if (aux->Horario == horario) {
            if (clienteInscripto(aux->Inscripciones, aux->cantInscripciones,
                                      idCliente)) {
                return true;
            }
        }

        if (aux == ultimo)
            break;
        aux++;
    }
    return false;
}

eOperacion buscarReserva(eReserva *reserva, uint cant, uint id) {
    eReserva *aux = reserva;
    eReserva *ultimo = (reserva) + cant - 1;
    while (true) {
        if (aux->idClase == id) {
            return *aux;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return reservaNula;
}

bool existeReserva(eReserva *reserva, uint cant, uint id) {

    return buscarReserva(reserva, cant, id).idClase != "";
}

eClases encontrarClase(eClases *clases, uint cant, str idClase) {
    eClases *aux = clases;
    eClases *ultimo = (clases) + cant - 1;
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

void imprimirReservas(eReserva* reservas,uint cant){
    eReserva *aux = reserva;
    eReserva* last = (reserva) + (cant - 1);
    cout << "reserva:" << endl;
    while (true) {
        cout << "nombre:" << aux->idReserva << endl;
        cout << "Cantidad de inscripciones:" << aux->cantInscripciones << endl;
        if(aux->cantInscripciones){
            str *auxH = aux->Inscripciones,
                *lastAux = (aux->Inscripciones) + (aux->cantInscripciones - 1);
            cout << "inscripciones:";
            while (true) {
                cout << *auxH << ",";
                if (auxH == lastAux)
                    break;
                auxH++;
            }
            cout << endl;
        }

        if (aux == last)
            break;

        aux++;
    }
    cout << "---------------------------------------" << endl;
}

uint genRandomNumber(uint min,uint max){
    srand((unsigned) time(0));
    uint randomNumber;
    randomNumber = (rand() % max) + min;
    return randomNumber;
}


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

        eInscripcion newInscription = {idReserva,time(0)};
        // CHEQUEAR QUE HAYA ESPACIO
        if (gimnasio.cantAsistencias < gimnasio.cantMaxasistencias) {
            // guardar asistencia
            Asistencia* asistencia =BuscarxAsistencia(gimnasio.asistencias, gimnasio.cantAsistencias, idClient);
            // chequear si existe
            if (asistencia == nullptr) {
                // crearla y agregar
                Asistencia newAssistance = {stoul(idClient),1,new eInscripcion[5]};
                *newAssistance.CursosInscriptos = newInscription;
                gimnasio.cantAsistencias ++;
                agregarAsistencia(gimnasio.asistencias,gimnasio.cantAsistencias,newAssistance);
            } else {
                // agregar
                if(asistencia->cantInscriptos < 5){
                    asistencias->cantInscriptos++;
                    addInscriptionAssistance(assistance->CursosInscriptos,assistance->cantInscriptos,newInscription);

                } else {
                    return eBookClass::ErrMaxInscriptionsReachedInClass;
                }
            }
        } else {
            resizeAssistences(&gym.assistances, gym.countAssistances,
                              gym.countMaxAssistances * 2);
            gym.countAssistances = gym.countMaxAssistances * 2;
            if (gym.assistances == nullptr) {
                return eBookClass::ErrSpace;
            }
            bookClassGym(gym,idBook,idClient);
        }
    }
    return eBookClass::SuccessBook;
}

bool isClientInInscription(str *inscriptions, uint cant, str idClient) {
    str *auxInscriptions = (inscriptions),
        *auxLastInscriptions = (inscriptions) + cant - 1;
    if(cant == 0){
        return false;
    }
    while (true) {
        if (*auxInscriptions == idClient) {
            return true;
        }
        if (auxInscriptions == auxLastInscriptions)
            break;
        auxInscriptions++;
    }
    return false;
}

bool isClientInSchedule(eBook *books, uint cant, uint schedule, str idClient) {
    eBook *aux = books, *ultimo = (books) + cant - 1;

    while (true) {

        if (aux->schedule == schedule) {
            if (isClientInInscription(aux->inscriptions, aux->countInscriptions,
                                      idClient)) {
                return true;
            }
        }

        if (aux == ultimo)
            break;
        aux++;
    }
    return false;
}

eBook findBook(eBook *books, uint cant, uint id) {
    eBook *aux = books, *ultimo = (books) + cant - 1;
    while (true) {
        if (aux->idBook == id) {
            return *aux;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return nullBook;
}

bool existBook(eBook *books, uint cant, uint id) {

    return findBook(books, cant, id).idClass != "";
}

eClass findClass(eClass *classes, uint cant, str idClass) {
    eClass *aux = classes, *ultimo = (classes) + cant - 1;
    while (true) {
        if (aux->idClass == idClass) {
            return *aux;
        }
        if (aux == ultimo)
            break;
        aux++;
    }
    return nullClass;
}

void printBooks(eBook* books,uint cant){
    eBook *aux = books, *last = (books) + (cant - 1);
    cout << "--------------Books--------------" << endl;
    while (true) {
        cout << "Name:" << aux->idBook << endl;
        cout << "Cant inscriptions:" << aux->countInscriptions << endl;
        if(aux->countInscriptions){
            str *auxH = aux->inscriptions,
                *lastAux = (aux->inscriptions) + (aux->countInscriptions - 1);
            cout << "Inscriptiones:";
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


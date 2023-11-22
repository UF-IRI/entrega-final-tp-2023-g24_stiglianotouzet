#include <catch2/catch.hpp>
#include "asistencias.h"
#include "clases.h"
#include "clientes.h"

TEST_CASE("My first test with Catch2", "[fancy]")
{
    REQUIRE(0 == 0);
}

TEST_CASE("FUNCION ASIGNAR CUPOS") {
    string yoga="yoga";
    string pilates="pilates";
    string stretching="stretching";
    string zumba="zumba";
    string boxeo="boxeo";
    uint cupoy, cupop, cupos,cupoz,cupob;
    SECTION("asignacion a yoga"){
        cupoy=asignarcupos(yoga);
        REQUIRE(cupoy==25);
    }
    SECTION("asignacion a pilates"){
        cupop=asignarcupos(pilates);
        REQUIRE(cupop==15);
    }
    SECTION("asignacion a stretching"){
    cupos=asignarcupos(stretching);
        REQUIRE(cupos==40);
    }
    SECTION("asignacion a zumba"){
        cupoz=asignarcupos(zumba);
        REQUIRE(cupoz==50);
    }
    SECTION("asignacion a boxeo"){
        cupob=asignarcupos(boxeo);
        REQUIRE(cupob==30);
    }



};
TEST_CASE("Buscar Clase en Gimnasio") {
    // Creo un gimnasio con diversas clase
    eGimnasio gimnasioPrueba;
    gimnasioPrueba.cantClases = 3;
    eClases clasesPrueba[3] = {
        {1, "Yoga", 20, 10, 1200, 0},
        {2, "Zumba", 15, 5, 1400, 0},
        {3, "Pilates", 25, 15, 1600, 0}
    };
    gimnasioPrueba.clases = clasesPrueba;

    SECTION("Buscar clase existente") {
        eOperacion resultado = BuscarClase(gimnasioPrueba.clases, gimnasioPrueba.cantClases, "Zumba");
        REQUIRE(resultado == eOperacion::exito);
    }

    SECTION("Buscar clase inexistente") {
        eOperacion resultado = BuscarClase(gimnasioPrueba.clases, gimnasioPrueba.cantClases, "Pilates");
        REQUIRE(resultado == eOperacion::error);
    }

    SECTION("Buscar clase en gimnasio vacío") {
    eGimnasio gimnasioVacio;
    gimnasioVacio.cantClases = 0;

    eOperacion resultado = BuscarClase(gimnasioVacio.clases, gimnasioVacio.cantClases, "Yoga");
    REQUIRE(resultado == eOperacion::error);
    }
};
TEST_CASE("Verificar Cliente Repetido") {
    // Creo un array de inscripciones
    uint cantInscripciones = 5;
    str inscripcionesPrueba[5] = {"101", "102", "103", "104", "105"};

    SECTION("Cliente  ya inscripto") {
    bool resultado = ClienteRepetido(inscripcionesPrueba, cantInscripciones, 103);
    REQUIRE(resultado == true);
    }

    SECTION("Cliente no inscripto ") {
    bool resultado = ClienteRepetido(inscripcionesPrueba, cantInscripciones, 106);
    REQUIRE(resultado == false);
    }

    SECTION("Cliente repetido en una inscripcion sin nadie inscripto") {
    uint cantInscripcionesVacias = 0;
    bool resultado = ClienteRepetido(nullptr, cantInscripcionesVacias, 101);
    REQUIRE(resultado == false);
}
};
TEST_CASE("Horario repetido") {
// array de reservas
uint cantReservas = 3;
eReserva reservasPrueba[3] = {
    {1, 101, 1200, nullptr, 0},
    {2, 102, 1400, nullptr, 0},
    {3, 103, 1600, nullptr, 0}
};

// agrego inscripciones para la reservas
str inscripciones1[2] = {"101", "102"};
reservasPrueba[0].Inscripciones = inscripciones1;
reservasPrueba[0].cantInscripciones = 2;

str inscripciones2[1] = {"103"};
reservasPrueba[2].Inscripciones = inscripciones2;
reservasPrueba[2].cantInscripciones = 1;

SECTION("Horario Repetido") {
    // El horario 1400 esta repetido para el cliente?
    bool resultado = HorarioRepetido(reservasPrueba, cantReservas, 1400, 102);
    REQUIRE(resultado == true);
    // Debe devolver true porque el cliente ya esta reservado
}

SECTION("Horario No Repetido") {
    // El horario 1800 esta repetido para el cliente 103
    bool resultado = HorarioRepetido(reservasPrueba, cantReservas, 1800, 103);
    REQUIRE(resultado == false); // Se espera que el resultado sea false porque 1800 no está ocupado por el cliente 103
}

SECTION("Horario Repetido en reserva sin nada") {
    // El horario 1200 esta repetido para el cliente 101?
    bool resultado = HorarioRepetido(nullptr, 0, 1200, 101);
    REQUIRE(resultado == false); // El resultado debe ser false xq no hay reservas
}
};
TEST_CASE("Buscar en las reservas por el ID") {
// Crear array de reservas
uint cantReservas = 3;
eReserva reservasPrueba[3] = {
    {1, 101, 1200, nullptr, 0},
    {2, 102, 1400, nullptr, 0},
    {3, 103, 1600, nullptr, 0}
  };

    SECTION("reserva encontrada") {
    // Buscar la reserva con ID 2 en las reservas
    eReserva resultado = buscarxReserva(reservasPrueba, cantReservas, 2);
    REQUIRE(resultado.idReserva == 2); // ID de la reserva debe ser 2
    REQUIRE(resultado.idClase == 102); //ID de la clase de la reserva sea 102
    REQUIRE(resultado.Horario == 1400); //horario de la reserva sea 1400
    }

    SECTION("Reserva No Encontrada") {
    // Buscar reserva con ID que no existe en las reservas
    eReserva resultado = buscarxReserva(reservasPrueba, cantReservas, 4);
    REQUIRE(resultado.idReserva == reservaNula.idReserva); // no debe encontrarla por lo cual le devuelve reserva nula
    }

    SECTION("Buscar en Reservas Vacías") {
    // Buscar en array vacio
    eReserva resultado = buscarxReserva(nullptr, 0, 1);
    REQUIRE(resultado.idReserva == reservaNula.idReserva); //  no debe encontrarla por lo cual le devuelve reserva nula
    }
};
TEST_CASE("Buscar Cliente por ID") {
    // Array de gimnasio con clientes
    eGimnasio gimnasioPrueba;
    gimnasioPrueba.cantClientes = 3;
    eClientes clientesPrueba[3] = {
        {101, "Juan", "Perez", "juan@example.com", "123-456-7890", "01/01/1990", "0"},
        {102, "Maria", "Gonzalez", "maria@example.com", "987-654-3210", "15/03/1985", "-1"},
        {103, "Carlos", "Lopez", "carlos@example.com", "555-123-4567", "10/07/2000", "0"}
    };
    gimnasioPrueba.clientes = clientesPrueba;

    SECTION("Cliente Encontrado") {
    // Busco el ID 102 en el gim
    eClientes resultado = buscarxCliente(&gimnasioPrueba, 102);
    REQUIRE(resultado.id == 102); // el id encontrado tiene que ser 102
    REQUIRE(resultado.nombre == "Maria"); // el nombre encontrado debe ser maria
    REQUIRE(resultado.apellido == "Gonzalez"); // el apellido encontrado debe ser gonzales
    REQUIRE(resultado.estado == "-1"); // el estado del cliente debe ser -1
    }

    SECTION("Cliente No Encontrado") {
    // Buscar un id no registrado
    eClientes resultado = buscarxCliente(&gimnasioPrueba, 104);
    REQUIRE(resultado.id == clienteNulo.id); // el cliente no se encuentra
    }

    SECTION("gim sin clientes") {
    // gim sin clientes
    eGimnasio gimnasioVacio;
    gimnasioVacio.cantClientes = 0;

    eClientes resultado = buscarxCliente(&gimnasioVacio, 101);
    REQUIRE(resultado.id == clienteNulo.id); // no va a encontrarlo asi que devuelve cliente nulo
    }
};
TEST_CASE("Verificar Estado") {
    // Clientes con distintos estado
    eClientes clienteConEstadoPositivo = {101, "Juan", "Perez", "juan@example.com", "123-456-7890", "01/01/1990", "1"};
    eClientes clienteConEstadoNegativo = {102, "Maria", "Gonzalez", "maria@example.com", "987-654-3210", "15/03/1985", "-1"};
    eClientes clienteConEstadoInvalido = {103, "Carlos", "Lopez", "carlos@example.com", "555-123-4567", "10/07/2000", "frase"};

    SECTION("Estado Positivo") {
    // el estado es positivo?
    bool resultado = Estado(clienteConEstadoPositivo);
    REQUIRE(resultado == true); // el resultado del estado debe ser 1
    }

    SECTION("Estado Negativo") {
    // Verificar si el estado del cliente es negativo
    bool resultado = Estado(clienteConEstadoNegativo);
    REQUIRE(resultado == false); // el estado debe ser negativo asi que retorno false "-1"
    }

    SECTION("Estado sin ser numero") {
    // si el estado no es un numero
    bool resultado = Estado(clienteConEstadoInvalido);
    REQUIRE(resultado == false); // el resultado tiene que ser false por no ser un numero
    }
};
TEST_CASE("Buscar Clase por ID") {
    // array de prueba
    uint cantClases = 3;
    eClases clasesPrueba[3] = {
        {1, "Yoga", 20, 10, 1200, 0},
        {2, "Zumba", 15, 5, 1400, 0},
        {3, "Pilates", 25, 15, 1600, 0}
    };

    SECTION("Clase Encontrada") {
    // Buscar la clase con ID 2 en el array
    eClases resultado = buscarxClase(clasesPrueba, cantClases, 2);
    REQUIRE(resultado.idClase == 2); // el id encontrado deberia ser 2
    REQUIRE(resultado.nombreclase == "Zumba"); // el nombre encontrado deberia ser zumba
    REQUIRE(resultado.capacidadMaxima == 15); // la capacidad encontrada deberia ser 15
    }

    SECTION("Clase que no va a encontrar") {
    // Buscar una clase por un id que no va a encontrar
    eClases resultado = buscarxClase(clasesPrueba, cantClases, 4);
    REQUIRE(resultado.idClase == ClaseNula.idClase); // No va a encontrar la clase y tendria que devolver clase nula
    }

    SECTION("Buscar en Clases Vacías") {
    // array vacio
    eClases resultado = buscarxClase(nullptr, 0, 1);
    REQUIRE(resultado.idClase == ClaseNula.idClase); // No va a encontrar la clase y tendria que devolver clase nula
}
};

/*TEST_CASE("Buscar Cliente por ID") {
// Crear un array de clientes de prueba
uint cantClientes = 3;
eClientes clientesPrueba[3] = {
    {101, "Juan", "Perez", "juan@example.com", "123-456-7890", "01/01/1990", "0"},
    {102, "Maria", "Gonzalez", "maria@example.com", "987-654-3210", "15/03/1985", "-1"},
    {103, "Carlos", "Lopez", "carlos@example.com", "555-123-4567", "10/07/2000", "0"}
};

    SECTION("Cliente Encontrado") {
    // Buscar Cliente con id 102
    eClientes resultado = BuscarxCliente(clientesPrueba, cantClientes, 102);
    REQUIRE(resultado.id == 102); // se espera que el id del cliente encontrado sea 102
    REQUIRE(resultado.nombre == "Maria"); // se espera que el nombre del cliente encontrado sea 102
    REQUIRE(resultado.apellido == "Gonzalez"); // se espera que el apellido del cliente encontrado sea gonzales
    REQUIRE(resultado.estado == "Inactivo"); // se espera que el estado sea -1

    SECTION("Cliente No Encontrado") {
    // Buscar un id no registrado
    eClientes resultado = BuscarxCliente(clientesPrueba, cantClientes, 104);
    REQUIRE(resultado.id == clienteNulo.id); // el cliente que va a encontrar va a ser el nulo
    }

    SECTION("Buscar en Clientes Vacíos") {
    // array vacio
    eClientes resultado = BuscarxCliente(nullptr, 0, 101);
    REQUIRE(resultado.id == clienteNulo.id); // El cliente que va a devolver es el nulo
    }
 };
 TEST_CASE("existe el cliente?") {
    // Clientes de prueba
    uint cantClientes = 3;
    eClientes clientesPrueba[3] = {
        {101, "Juan", "Perez", "juan@example.com", "123-456-7890", "01/01/1990", "-1"},
        {102, "Maria", "Gonzalez", "maria@example.com", "987-654-3210", "15/03/1985", "0"},
        {103, "Carlos", "Lopez", "carlos@example.com", "555-123-4567", "10/07/2000", "0"}
    };

    SECTION("Cliente Existe") {
    bool resultado = ClienteExistente(clientesPrueba, cantClientes, 102);
    REQUIRE(resultado == true); //el id 102 existe
    }

    SECTION("Cliente No Existe") {
    bool resultado = ClienteExistente(clientesPrueba, cantClientes, 104);
    REQUIRE(resultado == false); // el id 104 no esta en el array
    }

    SECTION("array vacio") {
    bool resultado = ClienteExistente(nullptr, 0, 101);
    REQUIRE(resultado == false); // el resultado deberia ser false xq no hay clientes
    }
 };
 TEST_CASE("ResizeAsistencia") {
    // asistencias de prueba
    uint tamOriginal = 3;
    eInscripcion inscripcionesPrueba[3] = {
        {1, 1634559725}, // inscripción con idClase 1 y fecha de inscripción
        {2, 1634563325}, // inscripción con idClase 2 y fecha de inscripción
        {3, 1634570525}  // inscripción con idClase 3 y fecha de inscripción
    };
    eAsistencia listaPrueba = {101, 3, inscripcionesPrueba}; // asistencia con idCliente 101 y 3 inscripciones
    eAsistencia* miLista = new eAsistencia[tamOriginal];
    miLista[0] = listaPrueba;

    SECTION("hago que el array tenga un tamano mayor") {
    uint nuevoTam = 5;
    ResizeAsistencia(miLista, tamOriginal, nuevoTam);

    // se agrando?
    REQUIRE(miLista != nullptr);
    REQUIRE(miLista[0].cantInscriptos == 3); // la cantidad de inscripciones no deberia cambiar aunque se modifique el tamano
    }

     SECTION("achicar lista") {
    uint nuevoTam = 2;
    ResizeAsistencia(miLista, tamOriginal, nuevoTam);

    // se achico?
    REQUIRE(miLista != nullptr);
    REQUIRE(miLista[0].cantInscriptos == 3); // La cantidad de inscripciones tendria que ser igual
    }


    delete[] miLista;
 }
};*/

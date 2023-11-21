#include <catch2/catch.hpp>
#include "asistencias.h"
#include "clases.h"
#include "clientes.h"
#include "clases.cpp"

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


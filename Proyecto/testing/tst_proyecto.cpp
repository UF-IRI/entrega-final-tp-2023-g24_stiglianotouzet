#include <catch2/catch.hpp>

TEST_CASE("My first test with Catch2", "[fancy]")
{
    REQUIRE(0 == 0);
}
TEST_CASE("FUNCION ASIGNAR CUPOS") {
        // Definir clases para las pruebas
    str clases;
    clases[6]= {"Spinning", "Yoga", "Pilates", "Stretching", "Zumba", "Boxeo"};



        for (int i = 0; i < 6; i++) {


            SECTION("Prueba aleatoria #" + std::to_string(i + 1) + ": " + randomClase) {
                unsigned int resultado = asignarc(randomClase);

                // Imprimir información sobre la prueba (opcional)
                std::cout << "Clase: " << randomClase << ", Cupo asignado: " << resultado << std::endl;

                // Verificar que el resultado esté dentro de los rangos esperados
                REQUIRE(resultado >= 0);
                REQUIRE(resultado <= 50);  // Puedes ajustar este valor según tus necesidades
            }
        }
    }
}

#include "catch.hpp"
#include "../src/matematicas.hpp"

TEST_CASE( "Las sumas son calculadas correctamente", "[sumar]" ) {
    REQUIRE( sumar(1, 2) == 3 );
    REQUIRE( sumar(-1, -1) == -2 );
    REQUIRE( sumar(0, 0) == 0 );
}

# Reglas del Proyecto (Antigravity)

Este proyecto usa **CMake** y **Catch2 (v2)**.

- **Compilación de pruebas**: No uses g++ directamente. Ve a la carpeta `ejemplo` y usa `cmake .` seguido de `cmake --build .`
- **Ejecución de pruebas**: Utiliza `ctest` para ejecutar las pruebas compiladas.
- **Estructura**: El código fuente está en `src/` y los tests en `tests/`.
- **Catch2**: Las pruebas se definen con `TEST_CASE` y usan `REQUIRE`. No modifiques `catch.hpp` ni `test_main.cpp`.

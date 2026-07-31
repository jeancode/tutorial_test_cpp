---
name: cpp-testing-cmake
description: Skill para guiar a una Inteligencia Artificial sobre cómo configurar e implementar tests en C++ usando CMake y Catch2 desde cero.
---

# Implementación de Pruebas en C++ con CMake y Catch2

Cuando el usuario solicite implementar pruebas automatizadas para un proyecto en C++, o configurar un entorno de testing, DEBES seguir estrictamente esta arquitectura basada en dos ejecutables separados (uno para producción y otro para pruebas).

## 1. Arquitectura de Archivos Requerida

Nunca mezcles el código de producción con el código de pruebas. Asegúrate de estructurar el directorio de la siguiente manera:

```text
/
├── CMakeLists.txt          (Configuración de compilación)
├── src/                    (Código de producción)
│   ├── main.cpp            (Punto de entrada de la app, contiene int main())
│   └── [tus_archivos].cpp/hpp 
└── tests/                  (Código de pruebas)
    ├── catch.hpp           (Header de Catch2 v2 descargado)
    ├── test_main.cpp       (Punto de entrada exclusivo para tests)
    └── [tus_tests].cpp     (Archivos con macros TEST_CASE)
```

## 2. Configuración de Catch2

1. **Obtener el Framework:** Si `tests/catch.hpp` no existe, descárgalo (Catch2 v2 single-header).
2. **El Entry Point (test_main.cpp):** DEBE existir un archivo dedicado exclusivamente a generar el `main` de las pruebas. Este archivo solo debe contener:
   ```cpp
   #define CATCH_CONFIG_MAIN
   #include "catch.hpp"
   ```
3. **Escritura de Tests:** Los tests se escriben en archivos separados (ej. `test_logica.cpp`). Estos deben incluir `#include "catch.hpp"` y usar las macros `TEST_CASE("desc", "[tag]")` y `REQUIRE(condicion)`.

## 3. Configuración del CMakeLists.txt

El archivo CMakeLists de la raíz debe crear DOS ejecutables y registrar el de pruebas con CTest. Utiliza esta plantilla:

```cmake
cmake_minimum_required(VERSION 3.10)
project(MiProyecto)

enable_testing()

# 1. EJECUTABLE DE PRODUCCIÓN (Excluye la carpeta tests/)
add_executable(app_produccion 
    src/main.cpp 
    src/logica.cpp
)

# 2. EJECUTABLE DE PRUEBAS (Excluye src/main.cpp para no duplicar int main())
add_executable(app_tests 
    tests/test_main.cpp 
    tests/test_logica.cpp 
    src/logica.cpp
)

# Registrar con CTest
add_test(NAME MisPruebas COMMAND app_tests)
```

## 4. Instrucciones de Ejecución

Para compilar y correr las pruebas, ejecuta la siguiente secuencia en la terminal (PowerShell o Bash):

1. `cmake .` (Para generar los archivos del build system)
2. `cmake --build .` (Para compilar ambos ejecutables)
3. `ctest` (Para ejecutar `app_tests` e imprimir el reporte)

## Notas Críticas para la IA
* NUNCA intentes compilar usando `g++` directamente. Siempre usa `cmake --build .`.
* NUNCA incluyas `src/main.cpp` en el comando `add_executable` de los tests. Provocará un error de "múltiples definiciones de la función main".
* Si modificas un archivo en `src/`, asume que debes verificar o actualizar su contraparte en `tests/`.

# Tutorial Básico: Cómo hacer Tests en C++ (y por qué necesitas dos EXEs)

Si estás empezando con C++ y quieres saber cómo implementar pruebas (tests) automatizadas en un proyecto real, este tutorial es para ti.

Una de las confusiones más grandes al inicio es cómo se compilan los tests. En C++, la estructura correcta requiere crear **dos ejecutables separados**:
1. **El ejecutable de tu aplicación (`mi_programa.exe`)**: El programa real que le entregas al usuario.
2. **El ejecutable de pruebas (`mis_tests.exe`)**: Un programa de uso interno para el programador. Su único trabajo es ejecutarse, verificar que el código fuente funciona correctamente y cerrarse.

Para lograr esto de forma automática, usaremos **CMake** (como nuestro gerente de compilación) y **Catch2** (como nuestro framework de pruebas).

---

## 1. Estructura de Carpetas

En un proyecto profesional, nunca mezclamos el código de la aplicación con el de los tests. La estructura ideal se ve así:

```text
MiProyecto/
├── CMakeLists.txt          <-- El "gerente" que crea los dos EXEs
├── src/                    <-- Aquí va TODO tu código real
│   ├── main.cpp            <-- El punto de entrada de tu app real
│   ├── matematicas.cpp     <-- Lógica: implementaciones
│   └── matematicas.hpp     <-- Lógica: declaraciones
└── tests/                  <-- Aquí van TODOS tus tests
    ├── catch.hpp           <-- El framework Catch2 (descargado de internet)
    ├── test_main.cpp       <-- Genera el main() de los tests
    └── test_matematicas.cpp<-- Tus pruebas reales
```

---

## 2. El Código Fuente (`src/`)

Primero, vamos a crear la lógica que queremos probar.

**`src/matematicas.hpp`**
```cpp
#ifndef MATEMATICAS_HPP
#define MATEMATICAS_HPP

int sumar(int a, int b);

#endif
```

**`src/matematicas.cpp`**
```cpp
#include "matematicas.hpp"

int sumar(int a, int b) {
    return a + b;
}
```

**`src/main.cpp`**
```cpp
#include <iostream>
#include "matematicas.hpp"

int main() {
    std::cout << "La suma de 2 + 3 es: " << sumar(2, 3) << std::endl;
    return 0;
}
```

---

## 3. El Código de Pruebas (`tests/`)

Para que los tests funcionen, necesitamos descargar el archivo `catch.hpp` desde su repositorio oficial y colocarlo en la carpeta `tests/`.

Luego, creamos un archivo solo para inicializar el framework:

**`tests/test_main.cpp`**
```cpp
#define CATCH_CONFIG_MAIN // Le dice a Catch2 que genere la función main()
#include "catch.hpp"
```

Y ahora, nuestras pruebas reales:

**`tests/test_matematicas.cpp`**
```cpp
#include "catch.hpp"
#include "../src/matematicas.hpp"

TEST_CASE( "Las sumas son calculadas correctamente", "[sumar]" ) {
    REQUIRE( sumar(1, 2) == 3 );
    REQUIRE( sumar(-1, -1) == -2 );
    REQUIRE( sumar(0, 0) == 0 );
}
```

---

## 4. CMake (El Gerente)

En la raíz del proyecto, creamos nuestro `CMakeLists.txt` para decirle al compilador cómo construir ambos ejecutables.

**`CMakeLists.txt`**
```cmake
cmake_minimum_required(VERSION 3.10)
project(TutorialTestCpp)

# Habilitar tests en el proyecto
enable_testing()

# ==========================================
# 1. EJECUTABLE PARA EL USUARIO
# ==========================================
add_executable(mi_programa 
    src/main.cpp 
    src/matematicas.cpp
)

# ==========================================
# 2. EJECUTABLE DE PRUEBAS
# ==========================================
add_executable(mis_tests 
    tests/test_main.cpp 
    tests/test_matematicas.cpp 
    src/matematicas.cpp
)

# Registrar el ejecutable como un test para CTest
add_test(NAME PruebasDeMatematicas COMMAND mis_tests)
```

---

## 5. Compilación y Ejecución

Abre tu terminal en la carpeta principal del proyecto y ejecuta:

1. **Configurar el proyecto:**
   ```bash
   cmake .
   ```
2. **Compilar los ejecutables:**
   ```bash
   cmake --build .
   ```
   *Esto generará `mi_programa.exe` y `mis_tests.exe`.*

3. **Ejecutar las pruebas:**
   ```bash
   ctest
   ```
   *O alternativamente, puedes ejecutar directamente `./mis_tests` (o `mis_tests.exe` en Windows) para ver el reporte detallado de Catch2.*

¡Y eso es todo! Has separado correctamente el código de producción del código de pruebas usando CMake.

cmake_minimum_required(VERSION 3.10)
project(EjemploTestCpp)

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

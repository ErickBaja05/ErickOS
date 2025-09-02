# 1. Versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.15)

# 2. Nombre de tu proyecto y lenguaje usado
project(ErickOS LANGUAGES CXX)

# 3. Estándar de C++ a usar (por ejemplo C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Incluimos la carpeta 'include' para los headers
include_directories(include)

# 5. Agrupamos todos los archivos fuente (.cpp)
set(SOURCES
        src/main.cpp
        src/toDo/toDo.cpp
        src/notesApp/notesApp.cpp
        src/utils/utils.cpp
        src/bankSimulatorApp/bankSimulatorApp.cpp
        # Agrega más src si tienes otros módulos
)

# 6. Definimos el ejecutable y los archivos que debe compilar
add_executable(ErickOS ${SOURCES})

# 7. (Opcional) Si quieres que los warnings se muestren como errores, útil para calidad
# target_compile_options(ErickOS PRIVATE -Wall -Wextra -Werror)

# 8. (Opcional) Aquí puedes enlazar librerías externas si en un futuro usas alguna


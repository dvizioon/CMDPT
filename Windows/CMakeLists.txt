cmake_minimum_required(VERSION 3.0)
project(CMDPT)

# Forçar o CMake a usar o mingw-w64
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

# Definir o padrão C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adicionar todos os seus arquivos de origem
file(GLOB_RECURSE SOURCES_CPP "/home/dvizioon/Sistemas/src/main.cpp" "src/*.cpp" "include/*.cpp")
file(GLOB_RECURSE SOURCES_C "src/*.c" "include/*.c" "include/Serve.c")

# Incluir diretórios de cabeçalhos locais
include_directories("/usr/x86_64-w64-mingw32/include")
include_directories("/usr/local/include")  # Ajuste este caminho conforme necessário

# Diretórios das bibliotecas
link_directories("/usr/x86_64-w64-mingw32/lib")
link_directories("/usr/local/lib")  # Ajuste este caminho conforme necessário

# Remover a opção -rdynamic ao compilar para Windows
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
    set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
endif()

# Adicionar o executável do seu projeto
add_executable(CMDPT ${SOURCES_CPP} ${SOURCES_C})

# Adicionar as bibliotecas ao seu executável
target_link_libraries(CMDPT curl cjson)
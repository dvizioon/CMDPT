cmake_minimum_required(VERSION 3.0)
project(CMDPT)

# Definir o padrão C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adicionar todos os seus arquivos de origem
file(GLOB_RECURSE SOURCES_CPP "src/*.cpp" "include/*.cpp")
file(GLOB_RECURSE SOURCES_C "src/*.c" "include/*.c" "include/Serve.c")

# Adicionar todas as bibliotecas necessárias aqui
find_package(CURL REQUIRED)
find_library(CJSON_LIBRARY NAMES cjson cJSON)

if (NOT CJSON_LIBRARY)
    message(FATAL_ERROR "Could not find the cJSON library")
endif()

# Adicionar o executável do seu projeto
add_executable(CMDPT ${SOURCES_CPP} ${SOURCES_C})

# Adicionar as bibliotecas ao seu executável
target_link_libraries(CMDPT PUBLIC CURL::libcurl ${CJSON_LIBRARY})

# Incluir diretórios de cabeçalhos
include_directories(include)

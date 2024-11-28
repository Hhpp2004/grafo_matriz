cmake_minimum_required(VERSION 3.22.1)

project(grafo_matriz C)

set(CMAKE_C_STANDARD 11)

add_executable(grafo_matriz
    main.c
    lista_dupla.c
)

target_link_libraries(grafo_matriz m)
target_compile_options(grafo_matriz PRIVATE -Wall -Wextra -g)
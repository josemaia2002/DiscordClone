cmake_minimum_required(VERSION 3.16.3)
project(teste VERSION 2.1 LANGUAGES CXX )

set(CMAKE_CXX_FLAGS "-g")

include_directories( include )

add_executable( program
                src/main.cpp
                src/Usuario.cpp                
                src/Mensagem.cpp
                src/Canal.cpp
                src/CanalVoz.cpp 
                src/CanalTexto.cpp
                src/Servidor.cpp
                src/Sistema.cpp )

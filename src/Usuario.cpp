#include <iostream>
#include <string>
#include "Usuario.h"

using namespace std;

Usuario::Usuario() {
    this->id = 0;
    this->nome = " ";
    this->email = " ";
    this->senha = " ";
}

Usuario::Usuario(int id, string nome, string email, string senha) {
    this->id = id;
    this->nome = nome;
    this->email = email;
    this->senha = senha;
}

int Usuario::getId() {
    return this->id;
}

void Usuario::setId(int id) {
    this->id = id;
}

string Usuario::getNome() {
    return this->nome;
}

void Usuario::setNome(string nome) {
    this->nome = nome;
}

string Usuario::getEmail() {
    return this->email;
}

void Usuario::setEmail(string email) {
    this->email = email;
}

string Usuario::getSenha() {
    return this->senha;
}

void Usuario::setSenha(string senha) {
    this->senha = senha;
}  
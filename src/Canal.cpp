#include <iostream>
#include <string>
#include "Canal.h"

using namespace std;

Canal::Canal() {
    this->nome = " ";
}

Canal::Canal(string nome) {
    this->nome = nome;
}

string Canal::getNome() {
    return this->nome;
}

void Canal::setNome(string nome) {
    this->nome = nome;
}
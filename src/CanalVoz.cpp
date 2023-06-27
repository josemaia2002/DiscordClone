#include <iostream>
#include <string>
#include "CanalVoz.h"

using namespace std;

CanalVoz::CanalVoz(string nome) {
    this->setNome(nome);
}

Mensagem CanalVoz::getultimaMensagem() {
    return this->ultimaMensagem;
}
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

void CanalVoz::setultimaMensagem(Mensagem ultimaMensagem) {
    this->ultimaMensagem.setConteudo(ultimaMensagem.getConteudo());
    this->ultimaMensagem.setdataHora(ultimaMensagem.getdataHora());
    this->ultimaMensagem.setenviadaPor(ultimaMensagem.getenviadaPor());
}
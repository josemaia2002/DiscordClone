#include <iostream>
#include <string>
#include "Mensagem.h"

using namespace std;

Mensagem::Mensagem() {
    this->enviadaPor = 0;
    this->conteudo = " ";
}

Mensagem::Mensagem(time_t dataHora, int enviadaPor, string conteudo) {
    this->dataHora = dataHora;
    this->enviadaPor = enviadaPor;
    this->conteudo = conteudo;
}

ostream &operator<<( ostream &output, const Mensagem &M ) { 
    output << "dataHora: " << M.dataHora << "; enviadaPor: " << M.enviadaPor << "; conteudo: " << M.conteudo;
    return output;            
}

time_t Mensagem::getdataHora() {
    return this->dataHora;
}

void Mensagem::setdataHora(time_t dataHora) {
    this->dataHora = dataHora;
}

int Mensagem::getenviadaPor() {
    return this->enviadaPor;
}

void Mensagem::setenviadaPor(int enviadaPor) {
    this->enviadaPor = enviadaPor;
}

string Mensagem::getConteudo() {
    return this->conteudo;
}

void Mensagem::setConteudo(string conteudo) {
    this->conteudo = conteudo;
}
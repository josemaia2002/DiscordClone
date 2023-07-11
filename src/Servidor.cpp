#include <iostream>
#include <string>
#include "Servidor.h"

using namespace std;

Servidor::Servidor() {
    this->usuarioDonoId = 0;
    this->nome = " ";
    this->descricao = " ";
    this->codigoConvite = " ";
}

Servidor::Servidor(int usuarioDonoId, const string& nome, const string& descricao, const string& codigoConvite) {
    this->usuarioDonoId = usuarioDonoId;
    this->nome = nome;
    this->descricao = descricao;
    this->codigoConvite = codigoConvite;
}

void Servidor::adicionarParticipante(int id) {
    participantesIDs.push_back(id);
}

void Servidor::adicionarCanal(Canal* canal) {
    canais.push_back(canal);
} 

int Servidor::getusuarioDonoId() {
    return this->usuarioDonoId;
}

void Servidor::setusuarioDonoId(int usuarioDonoId) {
    this->usuarioDonoId = usuarioDonoId;
}

string Servidor::getNome() {
    return this->nome;
}

void Servidor::setNome(string nome) {
    this->nome = nome;
}

string Servidor::getDescricao() {
    return this->descricao;
}

void Servidor::setDescricao(string descricao) {
    this->descricao = descricao;
}

string Servidor::getcodigoConvite() {
    return this->codigoConvite;
}

void Servidor::setcodigoConvite(string codigoConvite) {
    this->codigoConvite = codigoConvite;
}

vector<Canal*> Servidor::getCanais() {
    return this->canais;
}

vector<int> Servidor::getparticipantesIDs() {
    return this->participantesIDs;
}
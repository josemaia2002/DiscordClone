#include <iostream>
#include <string>
#include "CanalTexto.h"

using namespace std;

CanalTexto::CanalTexto(string nome) {
    this->setNome(nome);
}

void CanalTexto::adicionarMensagem(const Mensagem& mensagem) {
    mensagens.push_back(mensagem);
}
vector<Mensagem>& CanalTexto::getMensagens() {
    return mensagens;
}
#include <iostream>
#include <vector>
#include <string>
#include "Canal.h"
#include "Mensagem.h"

using namespace std;

#ifndef CANALTEXTO_H
#define CANALTEXTO_H

/**
 * \brief Represents a text channel.
 * 
 * This is a class that represents a text channel, 
 * listing all its messages.
 */
class CanalTexto : public Canal {
private:
    /**
     * \brief The channel's list of messages.
     * 
     * Represents all the messages of the channel.
     */ 
    vector<Mensagem> mensagens;

public:
    /**
     * \brief Creates a new text channel.
     * 
     * Creates a text channel and set its name with 
     * the value received as a parameter.
     * 
     * \param nome The name that's going to be assigned 
     * to the new text channel.
     */ 
    CanalTexto(string nome);

    /**
     * \brief Add a message to the channel.
     * 
     * Receives a message as a parameter and adds
     * it to the channel's list of messages.
     * 
     * \param mensagem The message that's going to be added 
     * to the text channel.
     */ 
    void adicionarMensagem(const Mensagem& mensagem);

    vector<Mensagem>& getMensagens();

};

#endif
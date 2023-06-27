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
     * \brief The channel's list of messages.
     * 
     * Represents all the messages of the channel.
     * 
     * \param nome The name that's going to be assigned 
     * to the new text channel.
     */ 
    CanalTexto(string nome);
};

#endif
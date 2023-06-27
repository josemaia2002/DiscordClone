#include <iostream>
#include <string>
#include "Canal.h"
#include "Mensagem.h"

using namespace std;

#ifndef CANALVOZ_H
#define CANALVOZ_H

/**
 * \brief Represents a voice channel.
 * 
 * This is a class that represents a voice channel, 
 * listing the last message.
 */
class CanalVoz : public Canal {
private:
    /**
     * \brief The channel's last message.
     * 
     * Represents the last message of the channel.
     */ 
    Mensagem ultimaMensagem;

public:
    /**
     * \brief The channel's list of messages.
     * 
     * Represents all the messages of the channel.
     */ 
    CanalVoz(string nome);

    /**
     * \brief The channel's list of messages.
     * 
     * Represents all the messages of the channel.
     */ 
    Mensagem getultimaMensagem();

};

#endif
#include <iostream>
#include <string>

using namespace std;

#ifndef MENSAGEM_H
#define MENSAGEM_H

/**
 * \brief Represents a message.
 * 
 * This is a class that represents a message, 
 * specifying the message's time, origin and content.
 */
class Mensagem {
private:
    /**
     * \brief The message's time.
     * 
     * Represents the time of the message.
     */ 
    string dataHora;

    /**
     * \brief The message's origin.
     * 
     * Represents the origin of the message.
     */ 
    int enviadaPor;

    /**
     * \brief The message's content.
     * 
     * Represents the content of the message.
     */ 
    string conteudo;

public:
    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    Mensagem();

    /**
     * \brief Creates a new message with the specified values.
     * 
     * Creates a new message and sets its
     * time, origin and content to the received parameters.
     * 
     * \param dataHora The message's time.
     * \param enviadaPor The message's origin.
     * \param conteudo The message's content.
     */
    Mensagem(string dataHora, int enviadaPor, string conteudo);    

    friend ostream &operator<<(ostream &output, const Mensagem &M);

    string getdataHora();
    void setdataHora(string dataHora);

    int getenviadaPor();
    void setenviadaPor(int enviadaPor);

    string getConteudo();
    void setConteudo(string conteudo);
};

#endif
#include <iostream>
#include <vector>
#include <string>
#include "Canal.h"
#include "CanalTexto.h"
#include "CanalVoz.h"
#include "Mensagem.h"
#include "Usuario.h"
#include "Servidor.h"

using namespace std;

#ifndef SISTEMA_H
#define SISTEMA_H

/**
 * \brief Represents a message.
 * 
 * This is a class that represents a message, 
 * specifying the message's time, origin and content.
 */
class Sistema {
private:
    /**
     * \brief The message's time.
     * 
     * Represents the time of the message.
     */ 
    vector<Usuario> usuarios;

    /**
     * \brief The message's origin.
     * 
     * Represents the origin of the message.
     */ 
    vector<Servidor> servidores;

    /**
     * \brief The message's content.
     * 
     * Represents the content of the message.
     */ 
    Usuario* usuarioLogado;

    /**
     * \brief The message's origin.
     * 
     * Represents the origin of the message.
     */ 
    Servidor* servidorAtual;

    /**
     * \brief The message's content.
     * 
     * Represents the content of the message.
     */ 
    Canal* canalAtual;


public:
    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    Sistema();

    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    void start();

    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    bool readInput();

    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    void quit();

    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    void createUser(const string& email, const string& senha, const string& nome);

    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    void login(const string& email, const string& senha);

    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    void disconnect();

    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    void createServer(const string& nome);

    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    void changeServerDesc(const string& nome, const string& descricao);

    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    void changeServerCode(const string& nome, const string& codigoConvite);

    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    void listServers();

    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    void removeServer(const string& nome);

    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    void enterServer(const string& nome, const string& codigoConvite);

    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    void leaveServer();

    /** 
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    void listMembers();

    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    void listChannels();

    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    void createChannel(const string& nome, const string& tipo);

    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    void enterChannel(const string& nome);

    /**
     * \brief Creates a new message.
     * 
     * Creates a new message and sets its
     * atributes with standard values.
     */
    void leaveChannel();
};

#endif
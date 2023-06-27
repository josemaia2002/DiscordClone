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
 * \brief Represents the system.
 * 
 * This is a class that represents the system and 
 * deals with the user interaction, serving as 
 * an interface, and integrating all the project.
 */
class Sistema {
private:
    /**
     * \brief The system's users.
     * 
     * Represents the list of the system's users.
     */ 
    vector<Usuario> usuarios;

    /**
     * \brief The system's servers.
     * 
     * Represents the list of the system's servers.
     */ 
    vector<Servidor> servidores;

    /**
     * \brief The currently logged user.
     * 
     * Represents the user that is currently logged.
     */ 
    Usuario* usuarioLogado;

    /**
     * \brief The current server.
     * 
     * Represents the server where the user is.
     */ 
    Servidor* servidorAtual;

    /**
     * \brief The The current channel.
     * 
     * Represents the channel where the user is
     */ 
    Canal* canalAtual;
    
public:
    /**
     * \brief Creates a new system.
     * 
     * Creates a new system and sets its
     * atributes with standard values.
     */
    Sistema();

    /**
     * \brief Initialize the system.
     * 
     * This method is first to be called, and
     * is responsable for triggering all the other methods.
     */
    void start();

    /**
     * \brief Process the users's commands.
     * 
     * This method receivers the user's input and proccess it.
     */
    bool readInput();

    /**
     * \brief Terminate the program.
     * 
     * This method is called to quit the system.
     */
    bool quit();

    /**
     * \brief Creates a new user.
     * 
     * Creates a new user and sets its
     * atributes with the received values.
     * 
     * \param email The email of the user.
     * \param senha The password of the user.
     * \param nome The name of the user.
     */
    void createUser(const string& email, const string& senha, const string& nome);

    /**
     * \brief Login function.
     * 
     * This method controls the access to the system.
     * It asks for the user's email and password, and checks
     * if they exist.
     * 
     * \param email The email of the user.
     * \param senha The password of the user.
     */
    void login(const string& email, const string& senha);

    /**
     * \brief Log out from the system.
     * 
     * This method verifies if the user is currently
     * logged in, then it disconnects the user from the system.
     */
    void disconnect();

    /**
     * \brief Creates a new server.
     * 
     * Creates a new system and sets its
     * name with the received value.
     * 
     * \param nome The name of the new server.
     */
    void createServer(const string& nome);




    /**
     * \brief Creates a new system.
     * 
     * Creates a new system and sets its
     * atributes with standard values.
     */
    void changeServerDesc(const string& nome, const string& descricao);

    /**
     * \brief Creates a new system.
     * 
     * Creates a new system and sets its
     * atributes with standard values.
     */
    void changeServerCode(const string& nome, const string& codigoConvite);

    /**
     * \brief Creates a new system.
     * 
     * Creates a new system and sets its
     * atributes with standard values.
     */
    void listServers();

    /**
     * \brief Creates a new system.
     * 
     * Creates a new system and sets its
     * atributes with standard values.
     */
    void removeServer(const string& nome);

    /**
     * \brief Creates a new system.
     * 
     * Creates a new system and sets its
     * atributes with standard values.
     */
    void enterServer(const string& nome, const string& codigoConvite);

    /**
     * \brief Creates a new system.
     * 
     * Creates a new system and sets its
     * atributes with standard values.
     */
    void leaveServer();

    /** 
     * \brief Creates a new system.
     * 
     * Creates a new system and sets its
     * atributes with standard values.
     */
    void listMembers();

    /**
     * \brief Creates a new system.
     * 
     * Creates a new system and sets its
     * atributes with standard values.
     */
    void listChannels();

    /**
     * \brief Creates a new system.
     * 
     * Creates a new system and sets its
     * atributes with standard values.
     */
    void createChannel(const string& nome, const string& tipo);

    /**
     * \brief Creates a new system.
     * 
     * Creates a new system and sets its
     * atributes with standard values.
     */
    void enterChannel(const string& nome);

    /**
     * \brief Creates a new system.
     * 
     * Creates a new system and sets its
     * atributes with standard values.
     */
    void leaveChannel();
};

#endif
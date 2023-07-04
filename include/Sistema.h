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
     * \brief Load the data.
     * 
     * This method is responsible for loading
     * the initial data of the system.
     */
    void load();

    /**
     * \brief Get the data from a file.
     * 
     * This method access a file and get its content.
     */
    vector<string> accessFile(string fileName);

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
     * \brief Changes the server's description.
     * 
     * Receive the server's name and a text to describe it.
     * 
     * \param nome The name of the server.
     * \param descricao The text that will be new description of the server.
     */
    void changeServerDesc(const string& nome, const string& descricao);

    /**
     * \brief Changes the server's description.
     * 
     * Receive the server's name and a text to describe it.
     * 
     * \param nome The name of the server.
     * \param codigoConvite The code that will be the new 
     * invitation code of the server.
     */
    void changeServerCode(const string& nome, const string& codigoConvite);

    /**
     * \brief List all the servers of the system.
     * 
     * Traverses the list of servers and displays their names.
     * 
     */
    void listServers();

    /**
     * \brief Remove a server from the system.
     * 
     * Traverses the list untill the desired server is found,
     * then removes it.
     * 
     * \param nome The name of the server to be deleted.
     */
    void removeServer(const string& nome);

    /**
     * \brief Control the access to a server.
     * 
     * Receives a server name and invitation code from the 
     * user, verifies if it is valid, then adds the user to the server.
     * 
     * \param nome The name of the server.
     * \param codigoConvite The invitation code of the server.
     */
    void enterServer(const string& nome, const string& codigoConvite);

    /**
     * \brief Method to leave the current server.
     * 
     * This method verifies if the user is currently logged
     * and inside a server, then it removes the user from the server .
     * 
     */
    void leaveServer();

    /**
     * \brief List all the members of the server.
     * 
     * Traverses the list of the system's users and 
     * displays the names of those whose id is in the 
     * current server's list of member's ids.
     * 
     */
    void listMembers();

    /**
     * \brief List all the channels of the system.
     * 
     * Traverses the list of the system's channels and 
     * displays their names.
     * 
     */
    void listChannels();

    /**
     * \brief Creates a new channel.
     * 
     * Creates a channel with name and type specified by the user.
     * 
     * \param nome The name of the channel.
     * \param tipo The channel's type.
     */
    void createChannel(const string& nome, const string& tipo);

    /**
     * \brief Control the access to a channel.
     * 
     * Receives a server name, checks if it exists,
     * then add the user to the desired channel.
     * 
     * \param nome The name of the channel.
     */
    void enterChannel(const string& nome);

    /**
     * \brief Method to leave the current channel.
     * 
     * This method verifies if the user is currently logged, 
     * inside a server and inside a channel, then it 
     * removes the user from the channel.
     * 
     */
    void leaveChannel();

    /**
     * \brief Method to send a message to the current channel.
     * 
     * This method verifies if the user is currently logged, 
     * inside a server and inside a channel, then it 
     * send to the channel the message defined by the user.
     * 
     */
    void sendMessage(const string& mensagem);

    /**
     * \brief Method to list the channel's messages.
     * 
     * This method verifies if the user is currently logged, 
     * inside a server and inside a channel, then it
     * list all the messages sent to the channel.
     * 
     */
    void listMessages();

    string getNomeUsuario(int id); 
};

#endif
#include <iostream>
#include <vector>
#include <string>
#include "Canal.h"

using namespace std;

#ifndef SERVIDOR_H
#define SERVIDOR_H

/**
 * \brief Represents a server.
 * 
 * This is a class that represents a server, 
 * specifying the server's owner id, name, description,
 * invitation code, channels and members ids.
 */
class Servidor {
private:
    /**
     * \brief The server's owner id.
     * 
     * Represents the owner's id of the server.
     */ 
    int usuarioDonoId;

    /**
     * \brief The server's name.
     * 
     * Represents name of the server.
     */ 
    string nome;

    /**
     * \brief The server's description.
     * 
     * Represents the description of the server.
     */ 
    string descricao;

    /**
     * \brief The server's invitation code.
     * 
     * Represents the invitation code of the server.
     */
    string codigoConvite;

    /**
     * \brief The server's channels.
     * 
     * Represents the list of channels of the server.
     */
    vector<Canal*> canais;

    /**
     * \brief The server's members.
     * 
     * Represents the list of IDs of the server's members.
     */
    vector<int> participantesIDs;


public:
    /**
     * \brief Creates a new server.
     * 
     * Creates a new server and sets its
     * atributes with standard values.
     */
    Servidor();  

    /**
     * \brief Creates a new server based on parameters.
     * 
     * Creates a new server and sets its
     * atributes with standard values.
     * 
     * \param usuarioDonoId The name that's going to be assigned 
     * to the new text channel.
     * \param nome The name that's going to be assigned 
     * to the new server.
     * \param descricao A text describing the server.
     * \param codigoConvite A code required to enter the server.
     */
    Servidor(int usuarioDonoId, const std::string& nome, const std::string& descricao, const std::string& codigoConvite); 

    /**
     * \brief Add a memeber to the server.
     * 
     * Add a member based on the id received from the user.
     * 
     * \param id The identification of the user.
     */
    void adicionarParticipante(int id);

    /**
     * \brief Add a channel to the server.
     * 
     * This methods lets the server admin to add
     * a channel to the server.
     * 
     * \param canal A pointer to the channel
     * that will be added.
     */
    void adicionarCanal(Canal* canal); 

    int getusuarioDonoId();
    void setusuarioDonoId(int usuarioDonoId);

    string getNome();
    void setNome(string nome);

    string getDescricao();
    void setDescricao(string descricao);

    string getcodigoConvite();
    void setcodigoConvite(string codigoConvite);

    vector<Canal*> getCanais();

    vector<int> getparticipantesIDs();

/*
    // Destrutor
    ~Servidor() {
        for (auto canal : canais) {
            delete canal;
        }
    }
*/


};

#endif
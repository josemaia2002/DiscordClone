#include <iostream>
#include <string>

using namespace std;

#ifndef CANAL_H
#define CANAL_H

/**
 * \brief Represents a channel.
 * 
 * This is a base class that represents a channel, 
 * specifying the channel's name.
 */
class Canal {
private:
    /**
     * \brief The user's name.
     * 
     * Represents the name of the user.
     */ 
    string nome;

public:
    /**
     * \brief Creates a new user.
     * 
     * Creates a new user and sets its
     * atributes with standard values.
     */
    Canal();

    /**
     * \brief Creates a new channel with the specifieds values.
     * 
     * Creates a new User and sets its
     * nome to the received parameters.
     * 
     * \param nome The channel's name.
     */
    Canal(string nome);    

    string getNome();
    void setNome(string nome);

    virtual ~Canal() {}
};

#endif
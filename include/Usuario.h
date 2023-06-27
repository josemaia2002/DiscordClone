#include <iostream>
#include <string>

using namespace std;

#ifndef USUARIO_H
#define USUARIO_H

/**
 * \brief Represents a user.
 * 
 * This is a class that represents a user, 
 * specifying the user's name, id, email and password.
 */
class Usuario {
private:
    /**
     * \brief The user's id.
     * 
     * Represents the id of the user.
     */ 
    int id;

    /**
     * \brief The user's name.
     * 
     * Represents the name of the user.
     */ 
    string nome;

    /**
     * \brief The user's email.
     * 
     * Represents the email of the user.
     */ 
    string email;

    /**
     * \brief The user's password.
     * 
     * Represents the password of the user.
     */  
    string senha;

public:
    /**
     * \brief Creates a new user.
     * 
     * Creates a new user and sets its
     * atributes with standard values.
     */
    Usuario();

    /**
     * \brief Creates a new user with the specifieds values.
     * 
     * Creates a new User and sets its
     * id, nome, email and password to the received parameters.
     * 
     * \param id The user's id.
     * \param nome The user's name.
     * \param email The user's email.
     * \param senha The user's password.
     */
    Usuario(int id, string nome, string email, string senha);    

    int getId();
    void setId(int id);

    string getNome();
    void setNome(string nome);

    string getEmail();
    void setEmail(string email);

    string getSenha();
    void setSenha(string senha);
};

#endif
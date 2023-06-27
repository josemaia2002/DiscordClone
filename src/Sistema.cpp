#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Sistema.h"

using namespace std;

Sistema::Sistema() {
    this->usuarioLogado = nullptr;
    this->servidorAtual = nullptr;
    this->canalAtual = nullptr;
}

void Sistema::load() {
    // createUser(email, senha, nome);

    int file_size = 0;

    fstream arquivo;
    string text;

    arquivo.open("../data/users.txt",ios::in);
    while(getline(arquivo, text)){
        file_size++;
    }
    arquivo.close(); 


    string lines[file_size];
    int i = 0;
       
    arquivo.open("../data/users.txt",ios::in);
    if(arquivo.is_open()){   
        while(getline(arquivo, text)){
            lines[i] = text;
            i++;
        }
        arquivo.close(); 
    }
    arquivo.close();

    string line;
    string email;
    string senha;
    string nome;

    vector<string> testUsers;

     // Leitura de cada linha
    for(int step = 0; step < file_size; step++){
        line = lines[step];
        cout << line << endl;
        istringstream iss(line);
        getline(iss, email, ' ');
        getline(iss, senha, ' ');
        getline(iss, nome);

        
        testUsers.push_back(nome);
    }

    cout << "##########################" << endl;


    for(auto& nome : testUsers) {
        cout << nome << endl;
    }
}

void Sistema::start() {
    cout << "Concord Servers Management" << endl;

    while(true) 
        if(!readInput())
            break;
}

bool Sistema::readInput() {
    cout << endl << "Enter a command: ";

    string line;
    string command;
    string args;

    getline(cin, line);
    istringstream iss(line);

    getline(iss, command, ' ');
    getline(iss, args);


    if(command == "quit") {
        return quit();
    }
    else if(command == "create-user") {
        string email;
        string senha;
        string nome;
        istringstream iss(args);
        getline(iss, email, ' ');
        getline(iss, senha, ' ');
        getline(iss, nome, ' ');
        createUser(email, senha, nome);
        getline(iss, email, ' ');
    }
    else if(command == "login") {
        string email;
        string senha;

        istringstream iss(args);
        getline(iss, email, ' ');
        getline(iss, senha, ' ');
        login(email, senha);
        getline(iss, email, ' ');
    }
    else if(command == "disconnect") {
        disconnect();
    }
    else if(command == "create-server") {
        string serverName;

        istringstream iss(args);
        getline(iss, serverName, ' ');
        createServer(serverName);
        getline(iss, serverName, ' ');
    }
    else if(command == "set-server-desc"){
        string serverName;
        string description;

        istringstream iss(args);
        getline(iss, serverName, ' ');
        iss.ignore();
        getline(iss, description, '"');
        changeServerDesc(serverName, description);
        getline(iss, serverName, ' ');        
    }
    else if(command == "set-server-invite-code") {
        string serverName;
        string inviteCode;

        istringstream iss(args);
        getline(iss, serverName, ' ');
        getline(iss, inviteCode, ' ');
        changeServerCode(serverName, inviteCode);
        getline(iss, serverName, ' ');
    }
    else if(command == "list-servers") {
        listServers();
    }
    else if(command == "remove-server") {
        string serverName;

        istringstream iss(args);
        getline(iss, serverName, ' ');
        removeServer(serverName);
        getline(iss, serverName, ' ');
    }
    else if(command == "enter-server") {
        string serverName;
        string inviteCode;

        istringstream iss(args);
        getline(iss, serverName, ' ');
        getline(iss, inviteCode, ' ');
        enterServer(serverName, inviteCode);
        getline(iss, serverName, ' ');
    }
    else if(command == "leave-server") {
        leaveServer();
    }
    else if(command == "list-participants") {
        listMembers();
    }
    else if(command == "list-channels") {
        listChannels();
    }
    else if(command == "create-channel") {
        string channelName;
        string channelType;

        istringstream iss(args);
        getline(iss, channelName, ' ');
        getline(iss, channelType, ' ');
        createChannel(channelName, channelType);
    }
    else if(command == "enter-channel") {
        string ChanelName;

        istringstream iss(args);
        getline(iss, ChanelName, ' ');
        enterChannel(ChanelName);
    }
    else if(command == "leave-channel") {
        leaveChannel();
    }
    else {
        cout << "Error! Invalid command." << endl;
    }

    return true;
}

bool Sistema::quit() {
    cout << "Leaving the system" << endl;
    return false;
}

void Sistema::createUser(const string& email, const string& senha, const string& nome) {
    for(auto& usuario : usuarios) {
        if(usuario.getEmail() == email) {
            cout << "Error: Already used email." << endl;
            return;
        }
    }

    int novoId = usuarios.size() + 1;

    Usuario novoUsuario(novoId, nome, email, senha);
    usuarios.push_back(novoUsuario);

    cout << "User successfully created." << endl;
    cout << novoUsuario.getId() << endl;
}

void Sistema::login(const string& email, const string& senha) {
    if(usuarioLogado != nullptr) {
        cout << "Error - Already logged." << endl;
        return;
    }

    for(auto& usuario : usuarios) {
        if(usuario.getEmail() == email && usuario.getSenha() == senha) {
            usuarioLogado = &usuario;
            cout << "Successfull login." << endl;
            return;
        }
    }

    cout << "Error - Wrong email or password." << endl;
}

void Sistema::disconnect() {
    if(usuarioLogado == nullptr) {
        cout << "Error - no user logged." << endl;
        return;
    }

    cout << "Disconnecting user " << usuarioLogado->getEmail() << endl;
    usuarioLogado = nullptr;
}

void Sistema::createServer(const string& nome) {
    if(usuarioLogado == nullptr) {
        cout << "Error - not logged." << endl;
        return;
    }

    for(auto& servidor : servidores) {
        if(servidor.getNome() == nome) {
            cout << "Error - Already existing server." << endl;
            return;
        }
    }

    Servidor novoServidor(usuarioLogado->getId(), nome, "", "");
    servidores.push_back(novoServidor);
    cout << "Server created" << endl;    
}

void Sistema::changeServerDesc(const string& nome, const string& descricao) {
    if(usuarioLogado == nullptr) {
        cout << "Error - Not logged." << endl;
        return;
    }

    for(auto& servidor : servidores) {
        if(servidor.getNome() == nome) {
            if(servidor.getusuarioDonoId() == usuarioLogado->getId()) {
                servidor.setDescricao(descricao);
                cout << "Server description '" << nome << "' changed!" << endl;
            } else {
                cout << "Error - Not allowed to change." << endl;
            }
            return;
        }
    }

    cout << "Error - Server '" << nome << "' does not exist." << endl;
}

void Sistema::changeServerCode(const string& nome, const string& codigoConvite) {
    if(usuarioLogado == nullptr) {
        cout << "Error - Not logged." << endl;
        return;
    }

    for(auto& servidor : servidores) {
        if(servidor.getNome() == nome) {
            if(servidor.getusuarioDonoId() == usuarioLogado->getId()) {
                servidor.setcodigoConvite(codigoConvite);
                if(codigoConvite.empty()) {
                    cout << "Server invitation code '" << nome << "' removed!" << endl;
                } else {
                    cout << "Server invitation code '" << nome << "' modified!" << endl;
                }
            } else {
                cout << "Error - Not allowed." << endl;
            }
            return;
        }
    }

    cout << "Error - Server '" << nome << "' does not exist." << endl;
}

void Sistema::listServers() {
    for(auto& servidor : servidores) {
        cout << servidor.getNome() << endl;
    }
}

void Sistema::removeServer(const string& nome) {
    if(usuarioLogado == nullptr) {
        cout << "Error - Not logged." << endl;
        return;
    }

    for(auto current_server = servidores.begin(); current_server != servidores.end(); ++current_server) {
        if(current_server->getNome() == nome) {
            if(current_server->getusuarioDonoId() == usuarioLogado->getId()) {
                servidores.erase(current_server);
                cout << "Server '" << nome << "' removed" << endl;
            } else {
                cout << "Error - Not allowed." << endl;
            }
            return;
        }
    }

    cout << "Error - Server '" << nome << "' not found." << endl;
}

void Sistema::enterServer(const string& nome, const string& codigoConvite) {
    if(usuarioLogado == nullptr) {
        cout << "Error - Not logged." << endl;
        return;
    }

    for(auto& servidor : servidores) {
        if(servidor.getNome() == nome) {
            if(servidor.getcodigoConvite().empty() || servidor.getusuarioDonoId() == usuarioLogado->getId() || servidor.getcodigoConvite() == codigoConvite) {
                servidor.adicionarParticipante(usuarioLogado->getId());
                servidorAtual = &servidor;
                cout << "Entered server" << endl;
            } else {
                cout << "Error - Invitation code required" << endl;
            }
            return;
        }
    }

    cout << "Error - Server '" << nome << "' not found." << endl;
}

void Sistema::leaveServer() {
    if(usuarioLogado == nullptr) {
        cout << "Error - Not logged." << endl;
        return;
    }

    if(servidorAtual == nullptr) {
        cout << "Error - Not inside a server." << endl;
        return;
    }

    cout << "Leaving server '" << servidorAtual->getNome() << "'" << endl;
    servidorAtual = nullptr;
}

void Sistema::listMembers() {
    if(usuarioLogado == nullptr) {
        cout << "Error - Not logged." << endl;
        return;
    }

    if(servidorAtual == nullptr) {
        cout << "Error - Not inside a server." << endl;
        return;
    }

    for(int id : servidorAtual->getparticipantesIDs()) {
        for(auto& usuario : usuarios) {
            if(usuario.getId() == id) {
                cout << usuario.getNome() << endl;
                break;
            }
        }
    }
}

void Sistema::listChannels() {
    if(usuarioLogado == nullptr) {
        cout << "Error - Not logged." << endl;
        return;
    }

    if(servidorAtual == nullptr) {
        cout << "Error - Not inside a server." << endl;
        return;
    }

    cout << "Voice channels" << endl;
    for(const auto& canal : servidorAtual->getCanais()) {
        if(dynamic_cast<const CanalVoz*>(canal) != nullptr) {
            cout << canal->getNome() << endl;
        }
    }

    cout << "Text channels" << endl;
    for(const auto& canal : servidorAtual->getCanais()) {
        if(dynamic_cast<const CanalTexto*>(canal) != nullptr) {
            cout << canal->getNome() << endl;
        }
    }
}

void Sistema::createChannel(const string& nome, const string& tipo) {
    if(usuarioLogado == nullptr) {
        cout << "Error - Not logged." << endl;
        return;
    }

    if(servidorAtual == nullptr) {
        cout << "Error - Not inside a server." << endl;
        return;
    }

    for(const auto& canal : servidorAtual->getCanais()) {
        if(canal->getNome() == nome && ((tipo == "texto" && dynamic_cast<const CanalTexto*>(canal) != nullptr) || (tipo == "voz" && dynamic_cast<const CanalVoz*>(canal) != nullptr))) {
            cout << "Error: Channel of type " << tipo << " '" << nome << "' already exists!" << endl;
            return;
        }
    }

    if(tipo == "texto") {
        CanalTexto* novoCanal = new CanalTexto(nome);
        servidorAtual->adicionarCanal(novoCanal);
        cout << "Channel of type texto '" << nome << "' created" << endl;
    } else if (tipo == "voz") {
        CanalVoz* novoCanal = new CanalVoz(nome);
        servidorAtual->adicionarCanal(novoCanal);
        cout << "Channel of type voz '" << nome << "' created" << endl;
    } else {
        cout << "Error - Invalid channel type." << endl;
    }
}

void Sistema::enterChannel(const string& nome) {
    if(usuarioLogado == nullptr) {
        cout << "Error - Not logged." << endl;
        return;
    }

    if(servidorAtual == nullptr) {
        cout << "Error - Not inside a server." << endl;
        return;
    }

    for(auto& canal : servidorAtual->getCanais()) {
        if(canal->getNome() == nome) {
            canalAtual = canal;
            cout << "Entered channel '" << nome << "'" << endl;
            return;
        }
    }

    cout << "Error - Channel '" << nome << "' does not exist." << endl;
}

void Sistema::leaveChannel() {
    if(usuarioLogado == nullptr) {
        cout << "Error - Not logged." << endl;
        return;
    }

    if(servidorAtual == nullptr) {
        cout << "Error - Not inside a server." << endl;
        return;
    }

    if(canalAtual == nullptr) {
        cout << "Error - Not inside a channel." << endl;
        return;
    }

    cout << "Leaving channel" << endl;
    canalAtual = nullptr;
}
#include <iostream>
#include <vector>
#include <string>
#include <bits/stdc++.h> 
#include <sstream>
#include <fstream>
#include "Sistema.h"

using namespace std;

Sistema::Sistema() {
    this->usuarioLogado = nullptr;
    this->servidorAtual = nullptr;
    this->canalAtual = nullptr;
}

void Sistema::start() {
    cout << "Concord Servers Management" << endl;

    load();

    while(true) 
        if(!readInput())
            break;
}

void Sistema::loadUsers() {
    fstream arquivo;
    string text;
    vector<string> lines;

    arquivo.open("../data/users.txt", ios::in);
    if(arquivo.is_open()){   
        while(getline(arquivo, text)){
            lines.push_back(text);
        }
        arquivo.close(); 
    }

    string email;
    string senha;
    string nome;
    int id;

    for(int i = 1; i < lines.size() - 2; i+=4){
        id = stoi(lines.at(i));
        nome = lines.at(i+1);
        email = lines.at(i+2);
        senha = lines.at(i+3);

        Usuario novoUsuario(id, nome, email, senha);
        usuarios.push_back(novoUsuario);

    }
}

void Sistema::loadServers() {
    fstream arquivo;
    string text;
    vector<string> lines;

    arquivo.open("../data/servers.txt", ios::in);
    if(arquivo.is_open()){   
        while(getline(arquivo, text)){
            lines.push_back(text);
        }
        arquivo.close(); 
    }
    
    int ownerID;
    string serverName;
    string serverDesc;
    string serverCode;
    int numberUsers;
    vector<int> userIdList;
    
    int currentLine = 0;

    int numberServers = stoi(lines.at(currentLine));
    currentLine++;

    for(int serverLoop = 0; serverLoop < numberServers; serverLoop++) {
        ownerID = stoi(lines.at(currentLine));
        serverName = lines.at(currentLine + 1);
        serverDesc = lines.at(currentLine + 2);
        serverCode = lines.at(currentLine + 3);
        numberUsers = stoi(lines.at(currentLine + 4));

        currentLine += 5;

        int memberID;

        Servidor novoServidor(ownerID, serverName, serverDesc, serverCode);
        servidores.push_back(novoServidor);

        for(int loop = currentLine; currentLine < loop + numberUsers; currentLine++){
            memberID = stoi(lines.at(currentLine));

            for(auto& servidor : servidores) {
                if(servidor.getNome() == serverName) {
                    servidor.adicionarParticipante(memberID);
                    servidorAtual = &servidor;
                }
            }
        }

        int numberChannels;
        string channelName;
        string channelType;
        int numberMessages;

        numberChannels = stoi(lines.at(currentLine));

        int userID;

        for(int i = 0; i < numberChannels; i++){
            char dataBefore[20];
            char bufferDataAfter[20];
            struct tm tm;
            time_t t;
            string content;
            Mensagem m;

            channelName = lines.at(currentLine + 1);
            channelType = lines.at(currentLine + 2);
            numberMessages = stoi(lines.at(currentLine + 3));

            currentLine += 4;

            if(channelType == "texto") {
                CanalTexto* novoCanal = new CanalTexto(channelName);

                for(auto& servidor : servidores) {
                    if(servidor.getNome() == serverName) {
                        servidor.adicionarCanal(novoCanal);
                        servidorAtual = &servidor;
                    }
                }

                for(int i = 0; i < numberMessages; i++) {
                    userID = stoi(lines.at(currentLine));
                    strcpy(dataBefore, (lines.at(currentLine + 1)).c_str()); 
                    strptime(dataBefore, "%d/%m/%Y - %H:%M", &tm);
                    strftime(bufferDataAfter, sizeof(bufferDataAfter), "%d/%m/%Y - %H:%M", &tm);
                    time_t t = mktime(&tm);

                    content = lines.at(currentLine + 2);

                    m.setdataHora(t);
                    m.setenviadaPor(userID);
                    m.setConteudo(content);

                    novoCanal->adicionarMensagem(m);

                    currentLine += 3;
                }
            } 
            else if (channelType == "voz") {
                CanalVoz* novoCanal = new CanalVoz(channelName);

                for(auto& servidor : servidores) {
                    if(servidor.getNome() == serverName) {
                        servidor.adicionarCanal(novoCanal);
                        servidorAtual = &servidor;
                    }
                }

                userID = stoi(lines.at(currentLine));

                strcpy(dataBefore, (lines.at(currentLine + 1)).c_str()); 
                strptime(dataBefore, "%d/%m/%Y - %H:%M", &tm);
                strftime(bufferDataAfter, sizeof(bufferDataAfter), "%d/%m/%Y - %H:%M", &tm);
                time_t t = mktime(&tm);

                content = lines.at(currentLine + 2);

                m.setdataHora(t);
                m.setenviadaPor(userID);
                m.setConteudo(content);

                novoCanal->setultimaMensagem(m);

                currentLine += 2;
            }
        }
    }
}

void Sistema::load() {
    loadUsers();
    loadServers();
}

void Sistema::saveUsers() {
    fstream arquivo;
    
    arquivo.open("../data/users.txt", ios::out);
    arquivo << usuarios.size() << endl;

    for(auto& usuario : usuarios) {
        arquivo << usuario.getId() << endl;
        arquivo << usuario.getNome() << endl;
        arquivo << usuario.getEmail() << endl;
        arquivo << usuario.getSenha() << endl;
    }

    arquivo.close();
}

void Sistema::saveServers() {
    fstream arquivo;
    
    arquivo.open("../data/servers.txt", ios::out);
    arquivo << servidores.size() << endl;

    for(auto& servidor : servidores) {
        arquivo << servidor.getusuarioDonoId() << endl;
        arquivo << servidor.getNome() << endl;
        arquivo << servidor.getDescricao() << endl;
        arquivo << servidor.getcodigoConvite() << endl;

        arquivo << servidor.getparticipantesIDs().size() << endl;
        for(auto& id : servidor.getparticipantesIDs())
            arquivo << id << endl;

        arquivo << servidor.getCanais().size() << endl;
        for(auto& canal : servidor.getCanais()) {
            arquivo << canal->getNome() << endl;
            if(dynamic_cast<const CanalTexto*>(canal) != nullptr) {
                arquivo << "texto" << endl;
                CanalTexto* canalTexto = dynamic_cast<CanalTexto*>(canal);
                arquivo << canalTexto->getMensagens().size() << endl;
                vector<Mensagem>& mensagens = canalTexto->getMensagens();

                for(Mensagem& mensagem : mensagens) {
                    arquivo << mensagem.getenviadaPor() << endl;

                    time_t dataHora = mensagem.getdataHora();
                    char bufTime[20];
                    strftime(bufTime, sizeof(bufTime), "%d/%m/%Y - %H:%M", localtime(&dataHora));

                    arquivo << bufTime << endl;
                    arquivo << mensagem.getConteudo() << endl;
                }
            }
            else if(dynamic_cast<const CanalVoz*>(canal) != nullptr) {
                arquivo << "voz" << endl;
                CanalVoz* canalVoz = dynamic_cast<CanalVoz*>(canal);
                arquivo << "1" << endl;

                Mensagem voiceMessage = canalVoz->getultimaMensagem();
                string nome = getNomeUsuario(voiceMessage.getenviadaPor()); 
                time_t data = voiceMessage.getdataHora();
                char bufTime[20];
                strftime(bufTime, sizeof(bufTime), "%d/%m/%Y - %H:%M", localtime(&data));

                arquivo << voiceMessage.getenviadaPor() << endl;
                arquivo << bufTime << endl;
                arquivo << voiceMessage.getConteudo() << endl;
            }
        }
    }
    arquivo.close();
}

void Sistema::save() {
    saveUsers();
    saveServers();
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

        save();
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

        save();
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

        save();    
    }
    else if(command == "set-server-invite-code") {
        string serverName;
        string inviteCode;

        istringstream iss(args);
        getline(iss, serverName, ' ');
        getline(iss, inviteCode, ' ');
        changeServerCode(serverName, inviteCode);
        getline(iss, serverName, ' ');

        save();
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

        save();
    }
    else if(command == "enter-server") {
        string serverName;
        string inviteCode;

        istringstream iss(args);
        getline(iss, serverName, ' ');
        getline(iss, inviteCode, ' ');
        enterServer(serverName, inviteCode);
        getline(iss, serverName, ' ');

        save();
    }
    else if(command == "leave-server") {
        leaveServer();

        save();
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

        save();
    }
    else if(command == "enter-channel") {
        string ChanelName;

        istringstream iss(args);
        getline(iss, ChanelName, ' ');
        enterChannel(ChanelName);

        save();
    }
    else if(command == "leave-channel") {
        leaveChannel();

        save();
    }
    else if (command == "send-message") {
        string mensagem;

        istringstream iss(args);
        getline(iss, mensagem);
        sendMessage(mensagem);

        save();
    }
    else if (command == "list-messages") {
        listMessages();
    }
    else if(command == "help") {
        cout << "quit - Leave the system" << endl;
        cout << "create-user [email] [password] [name] - Create a new user" << endl;
        cout << "login [email] [password] - Log in the system" << endl;
        cout << "disconnect - Disconnect the current user" << endl;
        cout << "create-server [name] - Create a new server" << endl;
        cout << "set-server-desc [name] [descrição] - Define the server's description" << endl;
        cout << "set-server-invite-code [name] [code] - Define the server's invitation code" << endl;
        cout << "list-servers - List all servers" << endl;
        cout << "remove-server [name] - Remove a server" << endl;
        cout << "enter-server [name] [code] - Enter in a server" << endl;
        cout << "leave-server - Leave the current server" << endl;
        cout << "list-participants - List all the server's participants" << endl;
        cout << "list-channels - Listar the server's channels" << endl;
        cout << "create-channel [name] [type] - Create a chanel in the current server" << endl;
        cout << "enter-channel [name] - Enter in a channel of the current server" << endl;
        cout << "leave-channel - Leave the current channel" << endl;
        cout << "send-message [message] - Send a message to the current channel" << endl;
        cout << "list-messages - Send a message to the current channel" << endl;
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

    for(auto& server : servidores) {
        if(server.getNome() == nome) {
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

    for(auto& server : servidores) {
        if(server.getNome() == nome) {
            if(server.getusuarioDonoId() == usuarioLogado->getId()) {
                server.setcodigoConvite(codigoConvite);
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

void Sistema::removeServer(const string& name) {
    if(usuarioLogado == nullptr) {
        cout << "Error - Not logged." << endl;
        return;
    }

    for(auto current_server = servidores.begin(); current_server != servidores.end(); ++current_server) {
        if(current_server->getNome() == name) {
            if(current_server->getusuarioDonoId() == usuarioLogado->getId()) {
                servidores.erase(current_server);
                cout << "Server '" << name << "' removed" << endl;
            } else {
                cout << "Error - Not allowed." << endl;
            }
            return;
        }
    }

    cout << "Error - Server '" << name << "' not found." << endl;
}

void Sistema::enterServer(const string& name, const string& code) {
    if(usuarioLogado == nullptr) {
        cout << "Error - Not logged." << endl;
        return;
    }

    for(auto& server : servidores) {
        if(server.getNome() == name) {
            if(server.getcodigoConvite().empty() || server.getusuarioDonoId() == usuarioLogado->getId() || server.getcodigoConvite() == code) {
                server.adicionarParticipante(usuarioLogado->getId());
                servidorAtual = &server;
                cout << "Entered server" << endl;
            } else {
                cout << "Error - Invitation code required" << endl;
            }
            return;
        }
    }

    cout << "Error - Server '" << name << "' not found." << endl;
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
        for(auto& user : usuarios) {
            if(user.getId() == id) {
                cout << user.getNome() << endl;
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
    for(const auto& channel : servidorAtual->getCanais()) {
        if(dynamic_cast<const CanalVoz*>(channel) != nullptr) {
            cout << channel->getNome() << endl;
        }
    }

    cout << "Text channels" << endl;
    for(const auto& channel : servidorAtual->getCanais()) {
        if(dynamic_cast<const CanalTexto*>(channel) != nullptr) {
            cout << channel->getNome() << endl;
        }
    }
}

void Sistema::createChannel(const string& name, const string& type) {
    if(usuarioLogado == nullptr) {
        cout << "Error - Not logged." << endl;
        return;
    }

    if(servidorAtual == nullptr) {
        cout << "Error - Not inside a server." << endl;
        return;
    }

    for(const auto& channel : servidorAtual->getCanais()) {
        if(channel->getNome() == name && ((type == "texto" && dynamic_cast<const CanalTexto*>(channel) != nullptr) || (type == "voz" && dynamic_cast<const CanalVoz*>(channel) != nullptr))) {
            cout << "Error: Channel of type " << type << " '" << name << "' already exists!" << endl;
            return;
        }
    }

    if(type == "texto") {
        CanalTexto* novoCanal = new CanalTexto(name);
        servidorAtual->adicionarCanal(novoCanal);
        cout << "Channel of type texto '" << name << "' created" << endl;
    } else if (type == "voz") {
        CanalVoz* novoCanal = new CanalVoz(name);
        servidorAtual->adicionarCanal(novoCanal);
        cout << "Channel of type voz '" << name << "' created" << endl;
    } else {
        cout << "Error - Invalid channel type." << endl;
    }
}

void Sistema::enterChannel(const string& name) {
    if(usuarioLogado == nullptr) {
        cout << "Error - Not logged." << endl;
        return;
    }

    if(servidorAtual == nullptr) {
        cout << "Error - Not inside a server." << endl;
        return;
    }

    for(auto& channel : servidorAtual->getCanais()) {
        if(channel->getNome() == name) {
            canalAtual = channel;
            cout << "Entered channel '" << name << "'" << endl;
            return;
        }
    }

    cout << "Error - Channel '" << name << "' does not exist." << endl;
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

void Sistema::sendMessage(const string& message) {
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

    Mensagem newMessage;
    newMessage.setConteudo(message);
    newMessage.setdataHora(time(nullptr));
    newMessage.setenviadaPor(usuarioLogado->getId());

    CanalTexto* canalTexto = dynamic_cast<CanalTexto*>(canalAtual);
    CanalVoz* canalVoz = dynamic_cast<CanalVoz*>(canalAtual);

    if(dynamic_cast<const CanalTexto*>(canalAtual) != nullptr) {
        canalTexto->adicionarMensagem(newMessage);
    }

    if(dynamic_cast<const CanalVoz*>(canalAtual) != nullptr) {
        canalVoz->setultimaMensagem(newMessage);
    }
}

void Sistema::listMessages() {
    if(usuarioLogado == nullptr) {
        cout << "Error - Not logged." << endl;
        return;
    }

    if(servidorAtual == nullptr) {
        cout << "Error - Not inside a server." << std::endl;
        return;
    }


    if(canalAtual == nullptr) {
        cout << "Error - Not inside a channel." << std::endl;
        return;
    }

    CanalTexto* txtChannel = dynamic_cast<CanalTexto*>(canalAtual);
    CanalVoz* voiceChannel = dynamic_cast<CanalVoz*>(canalAtual);

    if(dynamic_cast<const CanalTexto*>(canalAtual) != nullptr) {
        vector<Mensagem>& messages = txtChannel->getMensagens();
        if(messages.empty()) {
            cout << "Error - No messages found." << endl;
            return;
        }

        for(Mensagem& message : messages) {
            string userName = getNomeUsuario(message.getenviadaPor());

            time_t dateTime = message.getdataHora();
            char bufTime[20];
            strftime(bufTime, sizeof(bufTime), "%d/%m/%Y - %H:%M", localtime(&dateTime));

            cout << userName << "<" << bufTime << ">: " << message.getConteudo() << endl;
        }
    }

    if(dynamic_cast<const CanalVoz*>(canalAtual) != nullptr) {
        Mensagem voiceMessage = voiceChannel->getultimaMensagem();

        string name = getNomeUsuario(voiceMessage.getenviadaPor()); 
        time_t dateTime = voiceMessage.getdataHora();
        char bufTime[20];
        strftime(bufTime, sizeof(bufTime), "%d/%m/%Y - %H:%M", localtime(&dateTime));

        cout << name << "<" << bufTime << ">: " << voiceMessage.getConteudo() << endl;
    }
}

string Sistema::getNomeUsuario(int id) {
    for(Usuario& user : usuarios)
        if(user.getId() == id)
            return user.getNome();

    return "";
}
#include "ComChannel.hh"
#include <iostream>
#include <cstring>

ComChannel::ComChannel() : _socket(-1) {}

ComChannel::~ComChannel() {
    Close();
}

bool ComChannel::Connect(const char* host, int port) {
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket < 0) {
        std::cerr << "Blad tworzenia gniazda" << std::endl;
        return false;
    }
    
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    inet_pton(AF_INET, host, &server_addr.sin_addr);
    
    if (connect(_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Blad polaczenia z serwerem" << std::endl;
        return false;
    }
    
    return true;
}

bool ComChannel::Send(const std::string& cmd) {
    if (_socket < 0) return false;
    
    std::string fullCmd = cmd + "\n";
    ssize_t sent = send(_socket, fullCmd.c_str(), fullCmd.length(), 0);
    
    return sent > 0;
}

void ComChannel::Close() {
    if (_socket >= 0) {
        Send("Close");
        close(_socket);
        _socket = -1;
    }
}

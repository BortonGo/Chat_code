#pragma once

#include <vector>
#include <unordered_map>
#include "User.h"
#include "Message.h"

class Chat {
private:
    std::unordered_map<std::string, User> users;
    std::vector<Message> messages;
    User* currentUser = nullptr;

    User* findUserByLogin(const std::string& login) const; 
    void showMenu() const;

public:
    ~Chat() = default;

    void registerUser();
    void login();
    void logout();
    void sendPrivateMessage();
    void sendBroadcastMessage();
    void showMessages() const;
    void run();
};
#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


using namespace std;
class User;  
class Message;

class Chat {
private:
    vector<User> users;
    vector<Message> messages;
    User* currentUser = nullptr;

    User* findUserByLogin(const string& login);

public:
    ~Chat();

    void registerUser();
    void login();
    void logout();
    void sendPrivateMessage();
    void sendBroadcastMessage();
    void showMessages();
    void showMenu();
    void run();
};
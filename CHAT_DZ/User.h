#pragma once
#include <string>


using namespace std;

class User {
private:
    string login;
    string password;
    string name;

public:
    User(const string& l, const string& p, const string& n);

    const string& getLogin() const;
    const string& getPassword() const;
    const string& getName() const;

    bool checkPassword(const string& p) const;
        
};
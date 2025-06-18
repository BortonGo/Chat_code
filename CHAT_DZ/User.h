#pragma once

#include <string>

class User {
private:
    std::string login;
    std::string password;
    std::string name;

public:
    User(const std::string& l, const std::string& p, const std::string& n);

    const std::string& getLogin() const;
    const std::string& getPassword() const;
    const std::string& getName() const;

    bool checkPassword(const std::string& p) const;
};
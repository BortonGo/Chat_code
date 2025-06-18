#include "User.h"

User::User(const std::string& l, const std::string& p, const std::string& n)
    : login(l), password(p), name(n) {
}

const std::string& User::getLogin() const {
    return login;
}

const std::string& User::getPassword() const {
    return password;
}

const std::string& User::getName() const {
    return name;
}

bool User::checkPassword(const std::string& p) const {
    return password == p;
}
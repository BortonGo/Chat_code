#include "User.h"

using namespace std;

User::User(const string& l, const string& p, const string& n): login(l), password(p), name(n) {}

const string& User:: getLogin() const 
{ 
    return login; 
}
const string& User::getPassword() const 
{ 
    return password; 
}
const string& User::getName() const 
{ 
    return name; 
}

bool User::checkPassword(const string& p) const 
{
    return password == p;
}

#pragma once
#include <string>

using namespace std;

class Message {
private:
    string from;
    string to;
    string text;

public:
    Message(const string& f, const string& t, const string& txt);

    const string& getFrom() const;
    const string& getTo() const;
    const string& getText() const;
};
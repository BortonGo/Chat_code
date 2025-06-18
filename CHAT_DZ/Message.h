#pragma once

#include <string>

class Message {
private:
    std::string from;
    std::string to;
    std::string text;

public:
    Message(const std::string& f, const std::string& t, const std::string& txt);

    const std::string& getFrom() const;
    const std::string& getTo() const;
    const std::string& getText() const;
};
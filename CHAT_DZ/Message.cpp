#include "Message.h"

Message::Message(const std::string& f, const std::string& t, const std::string& txt)
    : from(f), to(t), text(txt) {
}

const std::string& Message::getFrom() const {
    return from;
}

const std::string& Message::getTo() const {
    return to;
}

const std::string& Message::getText() const {
    return text;
}

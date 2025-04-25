#include "Message.h"

using namespace std;

Message::Message(const string& f, const string& t, const string& txt): from(f), to(t), text(txt) {}

const string& Message::getFrom() const 
{ 
	return from; 
}
const string& Message::getTo() const 
{ 
	return to; 
}
const string& Message::getText() const 
{ 
	return text; 
}

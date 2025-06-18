#include "Chat.h"
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    Chat chat;
    chat.run();
    return 0;
}
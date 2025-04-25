#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

class User {
private:
    string login;
    string password;
    string name;

public:
    User(const string& l, const string& p, const string& n)
        : login(l), password(p), name(n) {
    }

    const string& getLogin() const { return login; }
    const string& getPassword() const { return password; }
    const string& getName() const { return name; }

    bool checkPassword(const string& p) const {
        return password == p;
    }
};

class Message {
private:
    string from;
    string to;
    string text;

public:
    Message(const string& f, const string& t, const string& txt)
        : from(f), to(t), text(txt) {
    }

    const string& getFrom() const { return from; }
    const string& getTo() const { return to; }
    const string& getText() const { return text; }
};

class Chat {
private:
    vector<User> users;
    vector<Message> messages;
    User* currentUser = nullptr;

    User* findUserByLogin(const string& login) {
        auto it = find_if(users.begin(), users.end(),
            [&login](const User& u) { return u.getLogin() == login; });
        return it != users.end() ? &(*it) : nullptr;
    }

public:
    ~Chat() {
        if (currentUser) {
            delete currentUser;
        }
    }

    void registerUser() {
        string login, password, name;
        cout << "Регистрация нового пользователя\n";
        cout << "Логин: ";
        cin >> login;

        if (findUserByLogin(login)) {
            cout << "Пользователь с таким логином уже существует!\n";
            return;
        }

        cout << "Пароль: ";
        cin >> password;
        cout << "Имя: ";
        cin.ignore();
        getline(cin, name);

        users.emplace_back(login, password, name);
        cout << "Пользователь успешно зарегистрирован!\n";
    }

    void login() {
        if (currentUser) {
            cout << "Вы уже вошли как: " << currentUser->getName() << endl;
            return;
        }

        string login, password;
        cout << "Вход в чат\n";
        cout << "Логин: ";
        cin >> login;
        cout << "Пароль: ";
        cin >> password;

        User* user = findUserByLogin(login);
        if (user && user->checkPassword(password)) {
            currentUser = new User(*user);
            cout << "Добро пожаловать, " << user->getName() << "!\n";
        }
        else {
            cout << "Неверный логин или пароль!\n";
        }
    }

    void logout() {
        if (currentUser) {
            cout << "До свидания, " << currentUser->getName() << "!\n";
            delete currentUser;
            currentUser = nullptr;
        }
        else {
            cout << "Вы не вошли в систему!\n";
        }
    }

    void sendPrivateMessage() {
        if (!currentUser) {
            cout << "Вы не вошли в систему!\n";
            return;
        }

        string toLogin;
        cout << "Кому отправить сообщение (логин): ";
        cin >> toLogin;

        if (toLogin == currentUser->getLogin()) {
            cout << "Нельзя отправить сообщение самому себе!\n";
            return;
        }

        User* toUser = findUserByLogin(toLogin);
        if (!toUser) {
            cout << "Пользователь с таким логином не найден!\n";
            return;
        }

        cout << "Сообщение для " << toUser->getName() << ": ";
        string text;
        cin.ignore();
        getline(cin, text);

        messages.emplace_back(currentUser->getLogin(), toLogin, text);
        cout << "Сообщение отправлено!\n";
    }

    void sendBroadcastMessage() {
        if (!currentUser) {
            cout << "Вы не вошли в систему!\n";
            return;
        }

        cout << "Сообщение для всех: ";
        string text;
        cin.ignore();
        getline(cin, text);

        messages.emplace_back(currentUser->getLogin(), "all", text);
        cout << "Сообщение отправлено всем пользователям!\n";
    }

    void showMessages() {
        if (!currentUser) {
            cout << "Вы не вошли в систему!\n";
            return;
        }

        cout << "--- Ваши сообщения ---\n";
        for (const auto& msg : messages) {
            if (msg.getTo() == currentUser->getLogin() ||
                msg.getFrom() == currentUser->getLogin() ||
                msg.getTo() == "all") {

                string from = (msg.getFrom() == currentUser->getLogin()) ?
                    "Вы" : findUserByLogin(msg.getFrom())->getName();

                string to;
                if (msg.getTo() == "all") {
                    to = "всем";
                }
                else if (msg.getTo() == currentUser->getLogin()) {
                    to = "Вам";
                }
                else {
                    to = findUserByLogin(msg.getTo())->getName();
                }

                cout << from << " -> " << to << ": " << msg.getText() << endl;
            }
        }
        cout << "----------------------\n";
    }

    void showMenu() {
        if (!currentUser) {
            cout << "\n1. Регистрация\n2. Вход\n3. Выход\n";
        }
        else {
            cout << "\n1. Отправить личное сообщение\n2. Отправить сообщение всем\n";
            cout << "3. Просмотреть сообщения\n4. Выйти из аккаунта\n5. Выход\n";
        }
    }

    void run() {
        int choice;
        bool running = true;

        while (running) {
            showMenu();
            cout << "Выберите действие: ";
            cin >> choice;

            if (!currentUser) {
                switch (choice) {
                case 1: registerUser(); break;
                case 2: login(); break;
                case 3: running = false; break;
                default: cout << "Неверный выбор!\n";
                }
            }
            else {
                switch (choice) {
                case 1: sendPrivateMessage(); break;
                case 2: sendBroadcastMessage(); break;
                case 3: showMessages(); break;
                case 4: logout(); break;
                case 5: running = false; break;
                default: cout << "Неверный выбор!\n";
                }
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Chat chat;
    chat.run();
    return 0;
}
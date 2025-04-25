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
        cout << "����������� ������ ������������\n";
        cout << "�����: ";
        cin >> login;

        if (findUserByLogin(login)) {
            cout << "������������ � ����� ������� ��� ����������!\n";
            return;
        }

        cout << "������: ";
        cin >> password;
        cout << "���: ";
        cin.ignore();
        getline(cin, name);

        users.emplace_back(login, password, name);
        cout << "������������ ������� ���������������!\n";
    }

    void login() {
        if (currentUser) {
            cout << "�� ��� ����� ���: " << currentUser->getName() << endl;
            return;
        }

        string login, password;
        cout << "���� � ���\n";
        cout << "�����: ";
        cin >> login;
        cout << "������: ";
        cin >> password;

        User* user = findUserByLogin(login);
        if (user && user->checkPassword(password)) {
            currentUser = new User(*user);
            cout << "����� ����������, " << user->getName() << "!\n";
        }
        else {
            cout << "�������� ����� ��� ������!\n";
        }
    }

    void logout() {
        if (currentUser) {
            cout << "�� ��������, " << currentUser->getName() << "!\n";
            delete currentUser;
            currentUser = nullptr;
        }
        else {
            cout << "�� �� ����� � �������!\n";
        }
    }

    void sendPrivateMessage() {
        if (!currentUser) {
            cout << "�� �� ����� � �������!\n";
            return;
        }

        string toLogin;
        cout << "���� ��������� ��������� (�����): ";
        cin >> toLogin;

        if (toLogin == currentUser->getLogin()) {
            cout << "������ ��������� ��������� ������ ����!\n";
            return;
        }

        User* toUser = findUserByLogin(toLogin);
        if (!toUser) {
            cout << "������������ � ����� ������� �� ������!\n";
            return;
        }

        cout << "��������� ��� " << toUser->getName() << ": ";
        string text;
        cin.ignore();
        getline(cin, text);

        messages.emplace_back(currentUser->getLogin(), toLogin, text);
        cout << "��������� ����������!\n";
    }

    void sendBroadcastMessage() {
        if (!currentUser) {
            cout << "�� �� ����� � �������!\n";
            return;
        }

        cout << "��������� ��� ����: ";
        string text;
        cin.ignore();
        getline(cin, text);

        messages.emplace_back(currentUser->getLogin(), "all", text);
        cout << "��������� ���������� ���� �������������!\n";
    }

    void showMessages() {
        if (!currentUser) {
            cout << "�� �� ����� � �������!\n";
            return;
        }

        cout << "--- ���� ��������� ---\n";
        for (const auto& msg : messages) {
            if (msg.getTo() == currentUser->getLogin() ||
                msg.getFrom() == currentUser->getLogin() ||
                msg.getTo() == "all") {

                string from = (msg.getFrom() == currentUser->getLogin()) ?
                    "��" : findUserByLogin(msg.getFrom())->getName();

                string to;
                if (msg.getTo() == "all") {
                    to = "����";
                }
                else if (msg.getTo() == currentUser->getLogin()) {
                    to = "���";
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
            cout << "\n1. �����������\n2. ����\n3. �����\n";
        }
        else {
            cout << "\n1. ��������� ������ ���������\n2. ��������� ��������� ����\n";
            cout << "3. ����������� ���������\n4. ����� �� ��������\n5. �����\n";
        }
    }

    void run() {
        int choice;
        bool running = true;

        while (running) {
            showMenu();
            cout << "�������� ��������: ";
            cin >> choice;

            if (!currentUser) {
                switch (choice) {
                case 1: registerUser(); break;
                case 2: login(); break;
                case 3: running = false; break;
                default: cout << "�������� �����!\n";
                }
            }
            else {
                switch (choice) {
                case 1: sendPrivateMessage(); break;
                case 2: sendBroadcastMessage(); break;
                case 3: showMessages(); break;
                case 4: logout(); break;
                case 5: running = false; break;
                default: cout << "�������� �����!\n";
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
#include <iostream>
#include "User.h"
#include "Message.h"
#include "Chat.h"

using namespace std;

 User* Chat::findUserByLogin(const string& login)
 {
    auto it = find_if(users.begin(), users.end(), [&login](const User& u) 
        {
            return u.getLogin() == login; 
        });
        return it != users.end() ? &(*it) : nullptr;
 }

 Chat:: ~Chat() 
 {
    if (currentUser) 
    {
        delete currentUser;
    }
 }

 void Chat::registerUser() 
 {
    string login, password, name;
    cout << "����������� ������ ������������\n";
    cout << "�����: ";
    cin >> login;

    if (findUserByLogin(login)) 
    {
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

  void Chat::login() 
  {
    if (currentUser) 
    {
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
    if (user && user->checkPassword(password)) 
    {
        currentUser = new User(*user);
        cout << "����� ����������, " << user->getName() << "!\n";
    }
    else 
    {
        cout << "�������� ����� ��� ������!\n";
    }
  }

  void Chat::logout() 
  {
      if (currentUser) 
      {
          cout << "�� ��������, " << currentUser->getName() << "!\n";
          delete currentUser;
          currentUser = nullptr;
      }
      else 
      {
          cout << "�� �� ����� � �������!\n";
      }
  }

  void Chat::sendPrivateMessage() 
  {
      if (!currentUser) 
      {
          cout << "�� �� ����� � �������!\n";
          return;
      }

      string toLogin;
      cout << "���� ��������� ��������� (�����): ";
      cin >> toLogin;

      if (toLogin == currentUser->getLogin()) 
      {
          cout << "������ ��������� ��������� ������ ����!\n";
          return;
      }

      User* toUser = findUserByLogin(toLogin);
      if (!toUser) 
      {
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

  void Chat::sendBroadcastMessage() 
  {
      if (!currentUser) 
      {
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

  void Chat::showMessages() 
  {
      if (!currentUser) 
      {
          cout << "�� �� ����� � �������!\n";
          return;
      }

      cout << "--- ���� ��������� ---\n";
      for (const auto& msg : messages) 
      {
          if (msg.getTo() == currentUser->getLogin() ||
              msg.getFrom() == currentUser->getLogin() ||
              msg.getTo() == "all") 
          {

              string from = (msg.getFrom() == currentUser->getLogin()) ?"��" : findUserByLogin(msg.getFrom())->getName();

              string to;
              if (msg.getTo() == "all") 
              {
                  to = "����";
              }
              else if (msg.getTo() == currentUser->getLogin())
              {
                  to = "���";
              }
              else 
              {
                  to = findUserByLogin(msg.getTo())->getName();
              }

              cout << from << " -> " << to << ": " << msg.getText() << endl;
          }
      }
      cout << "----------------------\n";
  }

  void Chat::showMenu() 
  {
      if (!currentUser) 
      {
          cout << "\n1. �����������\n2. ����\n3. �����\n";
      }
      else 
      {
          cout << "\n1. ��������� ������ ���������\n2. ��������� ��������� ����\n";
          cout << "3. ����������� ���������\n4. ����� �� ��������\n5. �����\n";
      }
  }

  void Chat::run() 
  {
      int choice;
      bool running = true;

      while (running) 
      {
          showMenu();
          cout << "�������� ��������: ";
          cin >> choice;

          if (!currentUser) 
          {
              switch (choice) 
              {
              case 1: registerUser(); break;
              case 2: login(); break;
              case 3: running = false; break;
              default: cout << "�������� �����!\n";
              }
          }
          else 
          {
              switch (choice) 
              {
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
#pragma once
#ifndef console_chat_h
#define console_chat_h

#include <string>
#include <vector>
// �������� ����� ��������� � ������������ �����, ����� �� ���� ������� � ���������.
template <typename T>
class User
{
private:
    T m_login;
    T m_password;
    T m_name;

public:
    User() = default; // ���������� ������������ �� ���������.
    User(const T& login, const T& password, const T& name)
        : m_login(login), m_password(password), m_name(name)
    {
    }

    const T& getLogin() const
    {
        return m_login;
    }

    const T& getPassword() const
    {
        return m_password;
    }

    const T& getName() const
    {
        return m_name;
    }
};

class Chat
{
private:
    bool isLoggedIn() const;
    std::vector<User<std::string>> m_users; // ����� ���������� ������������ ���������� ��� ��� User �������, �������� std::string.
    User<std::string> m_currentUser; // �� �� ����� �����, ������������ ���������� ��� std::string.
    std::vector<std::string> m_messages;

public:
    Chat(); // ���������� ������������ �� ���������.
    void registerUser();
    bool login();
    void sendMessage();
    void displayMessages();
    void run();
};

#endif // console_chat_h
#pragma once
#ifndef console_chat_h
#define console_chat_h

#include <string>
#include <vector>
// Ўаблоный класс полностью в заголовочном файле, чтобы не было проблем с линковкой.
template <typename T>
class User
{
private:
    T m_login;
    T m_password;
    T m_name;

public:
    User() = default; // ќбъ€вление конструктора по умолчанию.
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
    std::vector<User<std::string>> m_users; // «десь необходимо использовать конкретный тип дл€ User вектора, например std::string.
    User<std::string> m_currentUser; // “о же самое здесь, используетс€ конкретный тип std::string.
    std::vector<std::string> m_messages;

public:
    Chat(); // ќбъ€вление конструктора по умолчанию.
    void registerUser();
    bool login();
    void sendMessage();
    void displayMessages();
    void run();
};

#endif // console_chat_h
#include "console_chat.h"
#include <iostream>
#include <stdexcept>

// ќпределение конструктора по умолчанию.
Chat::Chat() = default;

// ѕровер€ем, авторизован ли текущий пользователь чата.
bool Chat::isLoggedIn() const
{
    return !m_currentUser.getLogin().empty();
}

// –егистрируем и добавл€ем в конец массива пользователей нового пользовател€.
void Chat::registerUser()
{
    try
    {
        std::string login, password, name;
        std::cout << "Enter login: ";
        std::cin >> login;

        for (const User<std::string>& user : m_users) // ѕровер€ем, что пользователь с таким логином уже зарегистрирован или нет.
        {
            if (user.getLogin() == login)
            {
                throw std::runtime_error("User with this login already exists.");
            }
        }

        std::cout << "Enter password: ";
        std::cin >> password;

        std::cout << "Enter name: ";
        std::cin >> name;
        std::cout << "\n";

        m_users.push_back(User<std::string>(login, password, name));
        std::cout << "User registered successfully." << std::endl;
        std::cout << "_________________________________\n\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "_________________________________\n\n";
    }
}

// ѕросим пользовател€ залогинитьс€. —равниваем логин и пароль с ранее зарегистрированными.
bool Chat::login()
{
    try
    {
        std::string login, password;
        std::cout << "Enter login: ";
        std::cin >> login;

        std::cout << "Enter password: ";
        std::cin >> password;
        std::cout << "\n";

        for (const User<std::string>& user : m_users)
        {
            if (user.getLogin() == login && user.getPassword() == password)
            {
                m_currentUser = user;
                return true;
            }
        }

        throw std::runtime_error("Invalid login or password.");
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        return false;
    }
}

// «апрашиваем логин получател€ и текст сообщени€, выводим информацию об отправленном сообщении и добавл€ем его в массив сообщений чата.
void Chat::sendMessage()
{
    try
    {
        if (!isLoggedIn())
        {
            throw std::runtime_error("You need to be logged in to send a message.");
        }

        std::string receiver, message;
        std::cout << "Enter receiver's login: ";
        std::cin >> receiver;
        std::cout << "\n";

        std::cout << "Enter message: ";
        std::getline(std::cin >> std::ws, message);
        std::cout << "\n";

        if (receiver == m_currentUser.getLogin())
        {
            throw std::runtime_error("You can't send a message to yourself.");
        }

        std::cout << "Message sent to " << receiver << ": " << message << std::endl;
        std::cout << "_________________________________\n\n";

        m_messages.push_back(m_currentUser.getName() + " -> " + receiver + ": " + message);
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "_________________________________\n\n";
    }
}

// ќтображаем все сообщени€, хран€щиес€ в векторе m_messages, которые содержат логин текущего пользовател€.
void Chat::displayMessages()
{
    try
    {
        if (!isLoggedIn())
        {
            throw std::runtime_error("You need to be logged in to view messages.");
        }

        std::cout << "Displaying all messages: " << std::endl;
        for (const std::string& message : m_messages)
        {
            if (message.find(m_currentUser.getLogin()) != std::string::npos)
            {
                std::cout << message << std::endl;
            }
        }
        std::cout << "_________________________________\n\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "_________________________________\n\n";
    }
}

// «апускаем консольный чат.
void Chat::run()
{
    try
    {
        int choice;
        do
        {
            std::cout << "Choose an option:" << std::endl;
            std::cout << "To register, press 1;" << std::endl;
            std::cout << "To login, press 2;" << std::endl;
            std::cout << "To send a message, press 3;" << std::endl;
            std::cout << "To view messages, press 4;" << std::endl;
            std::cout << "To exit the chat, press 5.\n" << std::endl;
            std::cout << "Enter your choice: ";

            if (!(std::cin >> choice))
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                throw std::runtime_error("Invalid input. Please enter a valid choice.");
            }

            std::cout << "\n";

            switch (choice)
            {
            case 1:
                registerUser();
                break;
            case 2:
                if (login())
                {
                    std::cout << "Logged in as " << m_currentUser.getName() << "." << std::endl;
                }
                else
                {
                    std::cout << "Please try again." << std::endl;
                }
                std::cout << "_________________________________\n\n";
                break;
            case 3:
                sendMessage();
                break;
            case 4:
                displayMessages();
                break;
            case 5:
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                std::cout << "_________________________________\n\n";
                break;
            }
        } while (true);
    }
    catch (const std::exception& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "_________________________________\n\n";
        run(); // –екурсивно вызываем run() дл€ возвращени€ к первоначальному меню после обработки исключени€
    }
}
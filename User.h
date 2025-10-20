#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    int id;
    std::string name;
    std::string phone;
    int loginState; // 0 = not confirmed, 1 = logged in

    User(int id = 0, const std::string& name = "default", const std::string& phone = "0000000000", int loginState = 0);
    void displayUser() const;
    bool isLoggedIn() const;
    void confirmLogin(const std::string& name, const std::string& phone);
};

#endif

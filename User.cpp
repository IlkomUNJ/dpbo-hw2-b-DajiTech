#include "User.h"
#include <iostream>

User::User(int id, const std::string& name, const std::string& phone, int loginState)
    : id(id), name(name), phone(phone), loginState(loginState) {}

void User::displayUser() const {
    std::cout << "User ID: " << id << ", Name: " << name << ", Phone: " << phone << std::endl;
}

bool User::isLoggedIn() const {
    return loginState == 1;
}

void User::confirmLogin(const std::string& name, const std::string& phone) {
    this->name = name;
    this->phone = phone;
    this->loginState = 1;
}

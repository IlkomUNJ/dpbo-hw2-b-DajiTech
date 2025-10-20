#ifndef MENU_H
#define MENU_H

#include <vector>
#include "User.h"
#include "Contact.h"

class Menu {
    std::vector<User>& users;
    std::vector<Contact>& contacts;
    User* currentUser;

public:
    Menu(std::vector<User>& users, std::vector<Contact>& contacts);
    void start();
private:
    void loginMenu();
    void registerUser();
    void userMenu();
    void addContact();
    void listContacts();
    void checkCurrentUser();
    void searchUser();
    void editUser();
    bool phoneExists(const std::string& phone);
};

#endif

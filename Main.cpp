#include <iostream>
#include <vector>
#include "User.h"
#include "Contact.h"
#include "Storage.h"
#include "Menu.h"

int main() {
    std::vector<User> users;
    std::vector<Contact> contacts;

    // Load data from file
    Storage::loadData(users, contacts, "appdata.bin");

    // Create default user if no users
    if (users.empty()) {
        users.emplace_back(1, "default", "0000000000", 0);
    }

    Menu menu(users, contacts);
    menu.start();

    // On program exit save data
    Storage::saveData(users, contacts, "appdata.bin");

    return 0;
}

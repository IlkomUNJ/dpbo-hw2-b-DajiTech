#include "Menu.h"
#include "storage.h"
#include <iostream>
#include <limits>

Menu::Menu(std::vector<User>& users, std::vector<Contact>& contacts)
    : users(users), contacts(contacts), currentUser(nullptr) {}

void Menu::start() {
    while (true) {
        loginMenu();
    }
}

void Menu::loginMenu() {
    std::cout << "\n--- Login Menu ---\n";
    std::cout << "1. Login\n";
    std::cout << "2. Register\n";
    std::cout << "3. Exit\n";
    std::cout << "Choose option: ";
    int option;
    std::cin >> option;

    switch (option) {
        case 1: {
            std::cout << "Enter user ID: ";
            int id; std::cin >> id;
            currentUser = nullptr;
            for (auto& u : users) {
                if (u.id == id) {
                    if (u.loginState == 0) {
                        std::string name, phone;
                        std::cout << "Confirm Name: ";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::getline(std::cin, name);
                        std::cout << "Confirm Phone: ";
                        std::getline(std::cin, phone);
                        if (u.name == name && u.phone == phone) {
                            u.loginState = 1;
                            currentUser = &u;
                            std::cout << "Login successful.\n";
                        } else {
                            std::cout << "Name or phone does not match. Login failed.\n";
                        }
                    } else {
                        currentUser = &u;
                        std::cout << "Login successful.\n";
                    }
                    break;
                }
            }
            if (!currentUser) {
                std::cout << "User ID not found.\n";
            } else {
                userMenu();
            }
            break;
        }
        case 2:
            registerUser();
            break;
        case 3:
            std::exit(0);
        default:
            std::cout << "Invalid option.\n";
    }
}

void Menu::registerUser() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string name, phone;
    std::cout << "Enter new user name: ";
    std::getline(std::cin, name);
    std::cout << "Enter new user phone: ";
    std::getline(std::cin, phone);

    int newId = users.empty() ? 1 : users.back().id + 1;
    users.emplace_back(newId, name, phone, 0);
    std::cout << "User registered with ID: " << newId << ". Please login and confirm name and phone.\n";
}

void Menu::userMenu() {
    while (true) {
        std::cout << "\n--- User Menu ---\n";
        std::cout << "1. Add Contact\n";
        std::cout << "2. List All Contacts\n";
        std::cout << "3. Check Current User Data\n";
        std::cout << "4. Search User by ID, Name, or Phone\n";
        std::cout << "5. Edit User by ID\n";
        std::cout << "6. Logout\n";
        std::cout << "Choose option: ";
        int option;
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (option) {
            case 1:
                addContact();
                break;
            case 2:
                listContacts();
                break;
            case 3:
                checkCurrentUser();
                break;
            case 4:
                searchUser();
                break;
            case 5:
                editUser();
                break;
            case 6:
                currentUser = nullptr;
                return;
            default:
                std::cout << "Invalid option.\n";
        }
    }
}

bool Menu::phoneExists(const std::string& phone) {
    if (currentUser && currentUser->phone == phone) {
        return true;
    }
    for (const auto& c : contacts) {
        if (c.phone == phone) return true;
    }
    return false;
}

void Menu::addContact() {
    std::string name, phone;
    while (true) {
        std::cout << "Enter contact name: ";
        std::getline(std::cin, name);
        std::cout << "Enter contact phone: ";
        std::getline(std::cin, phone);
        if (phoneExists(phone)) {
            std::cout << "Phone number already exists. Try again.\n";
        } else {
            break;
        }
    }
    int newId = contacts.empty() ? 1 : contacts.back().id + 1;
    contacts.emplace_back(newId, name, phone);
    std::cout << "Contact added.\n";
}

void Menu::listContacts() {
    std::cout << "\n-- All Contacts --\n";
    for (const auto& c : contacts) {
        c.displayContact();
    }
    if (contacts.empty()) {
        std::cout << "No contacts found.\n";
    }
}

void Menu::checkCurrentUser() {
    if (currentUser) {
        std::cout << "Current logged in user:\n";
        currentUser->displayUser();
    } else {
        std::cout << "No user is currently logged in.\n";
    }
}

void Menu::searchUser() {
    std::cout << "Search by (1) ID, (2) Complete Name, (3) Complete Phone: ";
    int opt; std::cin >> opt; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if (opt == 1) {
        int id;
        std::cout << "Enter user ID: ";
        std::cin >> id; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        for (const auto& u : users) {
            if (u.id == id) {
                u.displayUser();
                return;
            }
        }
        std::cout << "User with ID not found.\n";
    } else if (opt == 2) {
        std::string searchName;
        std::cout << "Enter complete name: ";
        std::getline(std::cin, searchName);
        bool found = false;
        for (const auto& u : users) {
            if (u.name == searchName) {
                u.displayUser();
                found = true;
            }
        }
        if (!found) std::cout << "User with name not found.\n";
    } else if (opt == 3) {
        std::string searchPhone;
        std::cout << "Enter complete phone: ";
        std::getline(std::cin, searchPhone);
        bool found = false;
        for (const auto& u : users) {
            if (u.phone == searchPhone) {
                u.displayUser();
                found = true;
            }
        }
        if (!found) std::cout << "User with phone not found.\n";
    } else {
        std::cout << "Invalid search option.\n";
    }
}

void Menu::editUser() {
    std::cout << "Enter user ID to edit: ";
    int id; std::cin >> id; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (auto& u : users) {
        if (u.id == id) {
            std::string newName, newPhone;
            std::cout << "Current Name: " << u.name << "\nEnter new name (or press enter to keep): ";
            std::getline(std::cin, newName);
            if (!newName.empty()) u.name = newName;
            
            while (true) {
                std::cout << "Current Phone: " << u.phone << "\nEnter new phone (or press enter to keep): ";
                std::getline(std::cin, newPhone);
                if (newPhone.empty() || !phoneExists(newPhone) || newPhone == u.phone) {
                    if (!newPhone.empty()) u.phone = newPhone;
                    break;
                }
                std::cout << "Phone number already exists. Try again.\n";
            }
            std::cout << "User updated.\n";
            return;
        }
    }
    std::cout << "User ID not found.\n";
}

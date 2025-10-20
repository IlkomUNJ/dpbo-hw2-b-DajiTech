#include "Contact.h"
#include <iostream>

Contact::Contact(int id, const std::string& name, const std::string& phone)
    : id(id), name(name), phone(phone) {}

void Contact::displayContact() const {
    std::cout << "Contact ID: " << id << ", Name: " << name << ", Phone: " << phone << std::endl;
}

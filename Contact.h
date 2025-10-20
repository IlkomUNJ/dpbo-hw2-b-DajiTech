#ifndef CONTACT_H
#define CONTACT_H

#include <string>

class Contact {
public:
    int id;
    std::string name;
    std::string phone;

    Contact(int id = 0, const std::string& name = "", const std::string& phone = "");
    void displayContact() const;
};

#endif

#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <string>
#include "User.h"
#include "Contact.h"

class Storage {
public:
    static void saveData(const std::vector<User>& users, const std::vector<Contact>& contacts, const std::string& filename);
    static void loadData(std::vector<User>& users, std::vector<Contact>& contacts, const std::string& filename);
};

#endif

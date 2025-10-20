#include "Storage.h"
#include <fstream>
#include <iostream>

void Storage::saveData(const std::vector<User>& users, const std::vector<Contact>& contacts, const std::string& filename) {
    std::ofstream ofs(filename, std::ios::binary);
    if (!ofs) {
        std::cerr << "Error opening file for saving data.\n";
        return;
    }

    size_t userCount = users.size();
    ofs.write(reinterpret_cast<const char*>(&userCount), sizeof(userCount));
    for (const auto& u : users) {
        size_t len;

        ofs.write(reinterpret_cast<const char*>(&u.id), sizeof(u.id));

        len = u.name.size();
        ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
        ofs.write(u.name.c_str(), len);

        len = u.phone.size();
        ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
        ofs.write(u.phone.c_str(), len);

        ofs.write(reinterpret_cast<const char*>(&u.loginState), sizeof(u.loginState));
    }

    size_t contactCount = contacts.size();
    ofs.write(reinterpret_cast<const char*>(&contactCount), sizeof(contactCount));
    for (const auto& c : contacts) {
        size_t len;

        ofs.write(reinterpret_cast<const char*>(&c.id), sizeof(c.id));

        len = c.name.size();
        ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
        ofs.write(c.name.c_str(), len);

        len = c.phone.size();
        ofs.write(reinterpret_cast<const char*>(&len), sizeof(len));
        ofs.write(c.phone.c_str(), len);
    }
}

void Storage::loadData(std::vector<User>& users, std::vector<Contact>& contacts, const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs) {
        std::cerr << "Data file not found, starting fresh.\n";
        return;
    }
    users.clear();
    contacts.clear();

    size_t userCount, contactCount;
    ifs.read(reinterpret_cast<char*>(&userCount), sizeof(userCount));
    for (size_t i = 0; i < userCount; i++) {
        int id;
        size_t len;
        std::string name, phone;
        int loginState;

        ifs.read(reinterpret_cast<char*>(&id), sizeof(id));

        ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
        name.resize(len);
        ifs.read(&name[0], len);

        ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
        phone.resize(len);
        ifs.read(&phone[0], len);

        ifs.read(reinterpret_cast<char*>(&loginState), sizeof(loginState));

        users.emplace_back(id, name, phone, loginState);
    }

    ifs.read(reinterpret_cast<char*>(&contactCount), sizeof(contactCount));
    for (size_t i = 0; i < contactCount; i++) {
        int id;
        size_t len;
        std::string name, phone;

        ifs.read(reinterpret_cast<char*>(&id), sizeof(id));
        
        ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
        name.resize(len);
        ifs.read(&name[0], len);
        
        ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
        phone.resize(len);
        ifs.read(&phone[0], len);

        contacts.emplace_back(id, name, phone);
    }
}

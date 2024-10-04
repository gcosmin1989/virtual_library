#include "UserManager.h"


User* UserManager::addUser(const std::string user_name) {
    User user(user_name);
  
	users.push_back(user);
	return &users.back();
}

User* UserManager::getUserById(int user_id) {
    for (auto& user : users) {
        if (user.getUserId() == user_id)
            return &user;
    }
    return nullptr;
}

bool UserManager::userExists(int user_id) const {
    for (const auto& user : users) {
        if (user.getUserId() == user_id)
            return true;
    }
    return false;
}

bool UserManager::logedIn(int user_id) {
    User* user = getUserById(user_id);
    if (user != nullptr) {
        user->setLogInStatus(true);
        return true;
    }
    return false;
}

void UserManager::printUsers() const {
    std::cout << "Library Users:\n";
    for (const auto& user : users) {
        std::cout << user.getUserId() << " || " << user.getUserName() << " || ";
        if (user.getAdminRights()) {
            std::cout << "Admin" << std::endl;
        }
        else {
            std::cout << "User" << std::endl;
        }
    }
}


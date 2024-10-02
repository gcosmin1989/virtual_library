#include "User.h"

int User::increment = 0;


User::User()
    : user_id(0), user_name(""), is_admin(false), is_loged_in(false) {}

User::User(std::string user_name, int user_id, bool is_admin, bool is_loged_in)
    : user_name(user_name), is_admin(is_admin), is_loged_in(is_loged_in) {
    if (user_id == 0) {
        increment++;
        this->user_id = increment;
    }
    else {
        this->user_id = user_id;
    }
}


User& User::operator=(const User& other) {
    if (this != &other) {
        this->user_id = other.user_id;
        this->user_name = other.user_name;
        this->is_admin = other.is_admin;
        this->is_loged_in = other.is_loged_in;
    }
    return *this;
}


std::string User::getUserName() const {
    return user_name;
}

bool User::getAdminRights() const {
    return is_admin;
}

bool User::getLogInStatus() const {
    return is_loged_in;
}

int User::getUserId() const {
    return user_id;
}


void User::setUserName(std::string user) {
    user_name = user;
}

void User::setAdminRights(bool has_rights) {
    is_admin = has_rights;
}

void User::setLogInStatus(bool is_loged) {
    is_loged_in = is_loged;
}

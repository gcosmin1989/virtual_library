#pragma once

#include <string>

class User {
private:
    int user_id;
    std::string user_name;
    bool is_admin;
    bool is_loged_in;

public:
    static int increment;


    User();
    User(std::string user_name, int user_id = 0, bool is_admin = false, bool is_loged_in = false);


    User& operator=(const User& other);


    std::string getUserName() const;
    bool getAdminRights() const;
    bool getLogInStatus() const;
    int getUserId() const;

    void setUserName(std::string user);
    void setAdminRights(bool has_rights = true);
    void setLogInStatus(bool is_loged = true);
};

#pragma once

#include <iostream>
#include <vector>
#include "User.h"

class UserManager
{
private:
	std::vector<User> users{
	   User("TestUser", 111, false, false),
	   User("TestAdmin", 222, true, false)
	};
public:

	User* addUser(const std::string user_name);
	void printUsers() const;
	User* getUserById(int user_id);
	bool userExists(int user_id) const;
	bool logedIn(int user_id);
};


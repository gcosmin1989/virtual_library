#pragma once
#include <string>
#include <vector>
#include "Library.h"
#include "UserManager.h"
#include <conio.h>
#include <cstdlib>
#include <limits>

#define MAX_LEN 60
#define MIN_LEN 2
#define KEY_UP 72
#define KEY_DOWN 80
#define ENTER 13

class LibraryApp {
private:

    Library lib;
    UserManager user_manager;
    User user;
                
    std::string first_panel[2] = { "User", "Admin" };
    std::string user_log_in_panel[4] = { "New User", "Existing User", "Back", "Quit" };
    std::string admin_panel[9] = { "Display Books", "Rented Books", "Add Books","Edit Book", "Delete Book","Add Admin","Remove Admin Rights", "Back", "Quit" };
    std::string admin_log_in_panel[3] = { "Log in Admin", "Back", "Quit" };
    std::string user_panel[4] = { "Display Books", "Return a Book", "Back", "Quit" };
    std::string sort_panel[7] = { "Rent" ,"Sort by Name", "Sort by Author", "Sort by Pages", "Sort by Rating", "Back", "Quit" };
    std::string book_add_panel[4] = { "New Book", "Add copies of an existing Book", "Back", "Quit" };
    std::string book_remove_panel[4] = { "Delete Book", "Remove copies of a book", "Back", "Quit"};
    std::string edit_book_panel[5] = { "Edit Title", "Edit Author", "Edit Pages", "Edit Year", "Edit Genre" };

public:

    void navigateMenu();
    void drawMessage(std::string);
    std::string invalid_input = "!!! Invalid Input !!!";
private:
    
    void displayUserRentals(const std::vector<Rental>& userRentals);
    void showMenu(std::string panel[], int size, int selection);
    int selectOption(std::string panel[], int size, std::string message = "");
    template <size_t N>
    int getSizeOfMenu(std::string(&menu_array)[N]);

    void inputStringValidation(std::string& input, const std::string& inputName);
    void inputYearValidation(int& input);
    void inputPagesValidation(int& input);

    User* addUserInput();
    User* checkExistingUserInput();
    User* checkAdminRightsInput();

    void addBookInput();
    void checkBookExistsInput(int& book_id);
    void removeBookInput();
    void removeBookCopiesInput();
    void addCopiesInput();
    int editBookInput();
    bool validateGenreAndAuthorString(const std::string book_genre);

    void giveAdminRightsInput();
    void removeAdminRightsInput();

    void returnBookInput(User* user);
    void rentBookInput(User* user);
};

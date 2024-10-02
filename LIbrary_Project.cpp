
#include <iostream>
#include <string>

#include <iomanip> //Precision
#include <stdexcept>//Exceptions
#include <conio.h> //Folosirea taste
#include <cstdlib>
#include <limits> // inputs

#define TEXTTABLE_ENCODE_MULTIBYTE_STRINGS
#define TEXTTABLE_USE_EN_US_UTF8
#include "Book.h"
#include "User.h"
#include "TextTable.h"
#include "UserManager.h"
#include "Rental.h"
#include "Library.h"

#define MAX_LEN 60
#define MIN_LEN 1
#define KEY_UP 72
#define KEY_DOWN 80
#define ENTER 13



std::string draw_message = "Discover, Explore, and Enjoy Your Next Read!";



static void drawWelcomeMessage(std::string show_text="Discover, Explore, and Enjoy Your Next Read!") {

    int total_length = 56;
    int inner_length = total_length - 2;
    int total_padding = inner_length - show_text.length();
    int left_padding = total_padding / 2;
    int right_padding = total_padding - left_padding;

    std::string second_text_draw = "*"
        + std::string(left_padding, ' ')
        + show_text
        + std::string(right_padding, ' ')
        + "*";

    std::string separator_draw =    "********************************************************";
    std::string box_draw =          "*                                                      *";
    std::string first_text_draw =   "*           WELCOME TO YOUR VIRTUAL LIBRARY!           *";
    std::string spaces = "                    ";
    std::cout << spaces << separator_draw << std::endl;
    std::cout << spaces << box_draw << std::endl;
    std::cout << spaces << first_text_draw << std::endl;
    std::cout << spaces << box_draw << std::endl;
    std::cout << spaces << separator_draw << std::endl;
    std::cout << spaces << box_draw << std::endl;
    std::cout << spaces << second_text_draw << std::endl;
    std::cout << spaces << box_draw << std::endl;
    std::cout << spaces << separator_draw << std::endl << std::endl;

    
}

std::string first_panel[2]      =   { "User", "Admin" };
std::string user_log_in_panel[4]=   { "New User", "Existing User", "Back", "Quit"};
std::string admin_panel[9]      =   { "Display Books", "Rented Books", "Add Books","Edit Book", "Delete Book","Add Admin","Remove Admin Rights", "Back", "Quit"};
std::string admin_log_in_panel[3] = { "Log in Admin", "Back", "Quit" };
std::string user_type[4]        =   { "New Use", "Existing User", "Back", "Quit" };
std::string user_panel[4]       =   { "Rent a Book", "Return a Book", "Back", "Quit" };
std::string sort_panel[8]       =   { "Rent" ,"Sort by Name", "Sort by Author", "Sort by Pages", "Sort by Rating", "Back", "Quit"};
std::string book_add_panel[4]   =   { "New Book", "Add copies of an existing Book", "Back", "Quit" };
std::string book_remove_panel[2] =  { "Delete Book", "Remove copies of a book" };
std::string edit_book_panel[5]  =   { "Edit Title", "Edit Author", "Edit Pages", "Edit Year", "Edit Genre" };



static void showMenu(std::string panel[], int size, int selection) {
    
    std::cout << "\r";
    for (int i = 0; i < size; i++) {
        if (i == selection) {

            std::cout << "> " << panel[i] << " <" << std::endl;
            
        }
        else {
           
            std::cout << "  " << panel[i] << "  " << std::endl;
            
        }
       
    }

}

static int selectOption(std::string panel[], int size, std::string message = "") {
    int selection = 0;
    bool is_running = true;

   
    if (!message.empty()) {
        drawWelcomeMessage(message);
    }

    showMenu(panel, size, selection);

    while (is_running) {
        int key = _getch();
        if (key == 0 || key == 224) {
            key = _getch();
            switch (key)
            {
            case KEY_UP:
                if (selection > 0) {
                    selection--;
                }
                break;
            case KEY_DOWN:
                if (selection < size - 1) {
                    selection++;
                }
                break;
            default:
                break;
            }

                system("cls");
            

            
            if (!message.empty()) {
                drawWelcomeMessage(message);
            }
            showMenu(panel, size, selection);
        }
        else if (key == ENTER) {
            is_running = false;
            system("cls");
        }
    }
    return selection;
}

int menu_navigate = 0;

static void inputStringValidation(std::string& input, const std::string& inputName) {
    while (input.length() <= MIN_LEN || input.length() > MAX_LEN) {
        std::cout << "Enter a valid " << inputName << ": " << std::endl;
        std::getline(std::cin, input);

    }
}


static void inputYearValidation(int& input) {

    while (input > 2024 || input < 1500) {
        std::cout << "Enter a valid year between 1500 and 2024: ";
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

static void inputPagesValidation(int& input) {

    while (input < 5) {
        std::cout << "The number of pages must be greater than 5: ";
        std::cin >> input;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

static User* addUserInput(UserManager& um) {
    std::string user_name;
    std::cout << "Enter new user name:" << std::endl;
    std::getline(std::cin, user_name);
    std::cin.clear();
    inputStringValidation(user_name, "user name");
    User user(user_name);
    User* newUser = um.addUser(user);
    if (newUser != nullptr) {
        newUser->setLogInStatus(true);
        std::cout << "User added and logged in successfully! Your User ID is: " << newUser->getUserId() << std::endl;
    }
    return newUser;
}

static User* checkExistingUserInput(UserManager& um) {
    int user_id;
    std::cout << "Enter your user id: ";
    std::cin >> user_id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    User* found_user = um.getUserById(user_id);
    if (found_user != nullptr) {
        found_user->setLogInStatus(true);
        return found_user;
    }
    else {
        return nullptr;
    }
}
static User* logInUser(UserManager& um) {
    User* user_found = checkExistingUserInput(um);
    if (user_found != nullptr) {
        std::cout << "Hello, " << user_found->getUserName() << ". You have logged in successfully!" << std::endl;
        return user_found;
    }
    else {
        std::cout << "The user does not exist." << std::endl;
        return nullptr;
    }
}

static User* checkAdminRightsInput(UserManager& um) {
    int admin_id;
    std::cout << "Enter your admin id: ";
    std::cin >> admin_id;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    User* is_admin = um.getUserById(admin_id);
    if (is_admin != nullptr ) {
        if(is_admin->getAdminRights()){
        std::cout<< "Hello, " << is_admin->getUserName() << ". You hage loged in succesfully as admin!" << std::endl;
        return is_admin;
        }
        else {
            std::cout << "You do not have admin rights for user: " << is_admin->getUserName() << std::endl;
            return nullptr;
        }
    }
    else {
        std::cout << "The admin does not exist" << std::endl;
        return nullptr;
    }
}

static void addBookInput(Library& lib) {
    std::string     book_title;
    std::string     book_author;
    int             book_pages;
    int             book_year;
    std::string     book_genre;

    std::cout << "Enter the Book Title:"<<std:: endl;
    std::getline(std::cin, book_title);
    inputStringValidation(book_title, "book name");

    std::cout << "Enter the Book Author:" << std::endl;
    std::getline(std::cin, book_author);
    inputStringValidation(book_author, "book author");

    std::cout << "Enter the Book Genre:" << std::endl;
    std::getline(std::cin, book_genre);
    inputStringValidation(book_genre, "genre");
    
    std::cout << "Enter the Book Pages:" << std::endl;
    std::cin >> book_pages;
    inputPagesValidation(book_pages);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter the Book Year:" << std::endl;
    std::cin >> book_year;
    inputYearValidation(book_year);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
  
    
    Book book(book_title, book_author, book_pages, book_year, book_genre);
    lib.addBook(book);

}
static void checkBookExistsInput(Library& lib, int& book_id) {
    while (!lib.bookExists(book_id)) {
        lib.print();
        std::cout << "The book does not exists in the Library, enter a valid Book id: ";
        std::cin >> book_id;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}
static void removeBookInput(Library& lib) 
{
    int book_id;
    lib.print();
    std::cout << "Enter the book id to delete:" << std::endl;
    std::cin >> book_id;

    checkBookExistsInput(lib, book_id);
    lib.removeBook(book_id);
}
static void removeBookCopiesInput(Library& lib) {
    int book_id;
    int book_copies;
    lib.print();
    std::cout << "Enter the book id to remove copies: " << std::endl;
    std::cin >> book_id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    Book* book;
    checkBookExistsInput(lib, book_id);
    if (lib.bookExists(book_id)) {
        book = lib.getBookById(book_id);
        int current_copies = book->getNoPieces();
        std::cout << "Enter the number of copies:" << std::endl;
        std::cin >> book_copies;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        while (book_copies < 1 || book_copies > current_copies) {
            std::cout << "The number of copies must be between 1 and " << current_copies << ": ";
            std::cin >> book_copies;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        book->removeCopy(book_copies);
    }
}
static void addCopiesInput(Library& lib) {
    int book_id;
    int book_copies;
    lib.print();
    std::cout << "Enter the book id:" << std::endl;
    std::cin >> book_id;
    Book* book;
    checkBookExistsInput(lib, book_id);
        if (lib.bookExists(book_id)) {
            book = lib.getBookById(book_id);
            std::cout << "Enter the number of copies:" << std::endl;
            std::cin >> book_copies;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            while (book_copies < 1 || book_copies>999) {
                std::cout << "The number of copies must be between 1 and 1000: ";
                std::cin >> book_copies;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            book->addCopy(book_copies);
        }
}
static int editBookInput(Library& lib){

    int book_id;

    std::cout << "Enter the book id you want to edit:";
    std::cin >> book_id; 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
 
    return book_id;
    

}
template <size_t N>
static int getSizeOfMenu(std::string(&menu_array)[N]) {
    return N;
}

static void giveAdminRightsInput(UserManager& um) {
    int user_id;
    std::cout << "Enter the user id you want to give Admin Rights:" << std::endl;
    std::cin >> user_id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    User* user;
    if (um.userExists(user_id)) {
        user = um.getUserById(user_id);

        if (user->getAdminRights()) {
            std::cout << "The User already has Admin Rights" << std::endl;
        }
        else {
            user->setAdminRights();
            um.printUsers();
        }
    }
    else {
        std::cout << "The id you have entered does not exist" << std::endl;
    }
    
}
static void removeAdminRightsInput(UserManager& um) {
    int user_id;
    std::cout << "Enter the user id you want to Remove the admin :" << std::endl;
    std::cin >> user_id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    User* user;
    if (um.userExists(user_id)) {
        user = um.getUserById(user_id);

        if (user->getAdminRights()) {
            user->setAdminRights(false);
        }
        else {
            std::cout << "The User does not have Admin Rights" << std::endl;
            um.printUsers();
        }
    }
    else {
        std::cout << "The id you have entered does not exist" << std::endl;
    }
   

}
static void returnBookInput(Library& lib, User* user) {

    std::vector<Rental> userRentals = lib.getUserRentals(user->getUserId());

    if (userRentals.empty()) {
        std::cout << "You have no rented books to return.\n";
        return;
    }
    TextTable t('-', '|', '+');
    t.add("Rental Code");
    t.add("Book Id");
    t.add("Book Title");
    t.add("Rent Date");
    t.add("Return Date");;
    t.endOfRow();

    std::cout << "Your rented books:\n";
    for (const auto& rental : userRentals) {
        Book* book = lib.getBookById(rental.book_id);
        if (book) { 
            t.add(std::to_string(rental.rent_id));
            t.add(std::to_string(book->getUniqueCode()));
            t.add(book->getName());
            t.add(std::to_string(rental.rent_date));
            t.add(std::to_string(rental.return_date));
           
            t.endOfRow();
           
           
            
        }
        
    }
    std::cout << t << std::endl;
    int book_id;

    std::cout << "Enter the Book ID you want to return: ";
    std::cin >> book_id;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    auto it = std::find_if(userRentals.begin(), userRentals.end(),
        [book_id](const Rental& rental) {
            return rental.book_id == book_id;
        });

    if (it == userRentals.end()) {
        std::cout << "You have not rented this book.\n";
        return;
    }

    int rating;

    while (true) {
        std::cout << "Enter a rating between 1 and 5: ";
        if (std::cin >> rating) {
            if (rating >= 1 && rating <= 5) {
                break;
            }
            else {
                std::cout << "Invalid rating. It must be between 1 and 5.\n";
            }
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 5.\n";
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    lib.returnBook(book_id, user->getUserId(), rating);
}


static void rentBookInput(Library& lib, User* user, UserManager& um) {
    int book_id;

    while (true) {
        std::cout << "Enter the book id you want to rent: ";
        if (std::cin >> book_id) {
            if (lib.bookExists(book_id)) {
                lib.rentBook(book_id, user->getUserId(), um);
                break; 
            }
            else {
                std::cout << "The Book id was not found.\n";
            }
        }
        else {

            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid Book id. Please enter a valid book id.\n";
        }
    }

}



static void navigateMenu() {
    bool is_running = true;
    Library lib;
    UserManager user_manager;
   
    while (is_running) {
       
        int menu_selection = selectOption(first_panel, getSizeOfMenu(first_panel),"Main Menu");
        //system("cls");
        // User Menu
        if (menu_selection == 0) { 
            bool in_user_menu = true;
            while (in_user_menu) {
                // User Panel
                int selection_user_log_in = selectOption(user_log_in_panel, getSizeOfMenu(user_log_in_panel),"User Menu");
                //system("cls");

                // New User
                if (selection_user_log_in == 0) { 
                    User* loggedInUser = addUserInput(user_manager);
                    if (loggedInUser != nullptr) {
                        bool in_user_panel = true;

                        while (in_user_panel) {
                            // User Panel
                            int user_selection = selectOption(user_panel, getSizeOfMenu(user_panel),"New User");
                            //system("cls");
                            // Rent a Book
                            if (user_selection == 0) { 
                                bool in_display_panel = true;;
                                while (in_display_panel) {
                                    // Display and Sort Books
                                    
                                    int display_selection = selectOption(sort_panel, getSizeOfMenu(sort_panel),"Rent Book");
                                    //lib.printBooks();
                                    //system("cls");

                                    // Rent
                                    if (display_selection == 0) { 
                                        lib.print();
                                        rentBookInput(lib, loggedInUser, user_manager);
                                    }
                                    // Sort Book
                                    else if (display_selection > 0 && display_selection < 5) {
                                        lib.sortBooks(display_selection);
                                        lib.printSortedBooks();
                                    }
                                    // Back
                                    else if (display_selection == 5) { 
                                        in_display_panel = false;
                                    }
                                    // Quit
                                    else if (display_selection == 6) { 
                                        exit(0);
                                    }
                                }
                            }
                            // Return Book
                            else if (user_selection == 1) { 
                                returnBookInput(lib, loggedInUser);
                            }
                            // Back to User Login Menu
                            else if (user_selection == 2) { 
                                in_user_panel = false;
                                loggedInUser->setLogInStatus(false);
                            }
                            // Quit
                            else if (user_selection == 3) { 
                                exit(0);
                            }
                        }
                    }
                }
                else if (selection_user_log_in == 1) {
                    User* loggedInUser = logInUser(user_manager);
                    if (loggedInUser != nullptr) {
                        bool in_user_panel = true;
                        while (in_user_panel) {
                            // User Panel
                            int user_selection = selectOption(user_panel, getSizeOfMenu(user_panel));
                            //system("cls");
                            // Rent Book
                            if (user_selection == 0) { 
                                bool in_display_panel = true;
                                while (in_display_panel) {
                                 
                                    int display_selection = selectOption(sort_panel, getSizeOfMenu(sort_panel));
                                    //system("cls");
                                    // Rent
                                    if (display_selection == 0) {
                                        lib.print();
                                        rentBookInput(lib, loggedInUser, user_manager);
                                    }
                                    else if (display_selection > 0 && display_selection < 5) {
                                        lib.sortBooks(display_selection);
                                        lib.printSortedBooks();
                                    }
                                    // Back
                                    else if (display_selection == 5) { 
                                        in_display_panel = false;
                                    }
                                    // Quit
                                    else if (display_selection == 6) {
                                        exit(0);
                                    }
                                }
                            }
                            // Return a Book
                            else if (user_selection == 1) {
                                returnBookInput(lib, loggedInUser);
                            }
                            // Back
                            else if (user_selection == 2) {
                                in_user_panel = false;
                                loggedInUser->setLogInStatus(false);
                            }
                            // Quit
                            else if (user_selection == 3) {
                                exit(0);
                            }
                        }
                    }
                    
                }
                // Back to Main Menu
                else if (selection_user_log_in == 2) { 
                    in_user_menu = false;
                }
                // Quit
                else if (selection_user_log_in == 3) {
                    exit(0);
                }
            }
        }
        else if (menu_selection == 1) { // Admin Menu
            bool in_admin_menu = true;
            while (in_admin_menu) {
                // Admin Login Menu
                int selection_admin_log_in = selectOption(admin_log_in_panel, getSizeOfMenu(admin_log_in_panel));
                system("cls");

                if (selection_admin_log_in == 0) { // Log in Admin
                    User* adminUser = checkAdminRightsInput(user_manager);
                    if (adminUser != nullptr) {
                        bool in_admin_panel = true;
                        while (in_admin_panel) {
                            // Admin Panel
                            int selection_admin_panel = selectOption(admin_panel, getSizeOfMenu(admin_panel));
                            system("cls");

                            if (selection_admin_panel == 0) { // Display Books
                                lib.printBooks();
                            }
                            else if (selection_admin_panel == 1) { // Rented Books
                                lib.printRentedBooks();
                            }
                            else if (selection_admin_panel == 2) { // Add Books
                                int selection_book = selectOption(book_add_panel, getSizeOfMenu(book_add_panel));
                                system("cls");

                                if (selection_book == 0) { // New Book
                                    addBookInput(lib);
                                }
                                else if (selection_book == 1) { // Add copies of an existing Book
                                    addCopiesInput(lib);
                                }
                                else if (selection_book == 2) { // Back
                                    // Do nothing, just return to admin panel
                                }
                                else if (selection_book == 3) { // Quit
                                    exit(0);
                                }
                            }
                            else if (selection_admin_panel == 3) { // Edit Book
                                bool in_edit_menu = true;
                                while (in_edit_menu) {
                                    lib.printBooks();
                                    int book_id = editBookInput(lib);
                                    int selection_book_edit = selectOption(edit_book_panel, getSizeOfMenu(edit_book_panel));
                                    system("cls");

                                    if (selection_book_edit >= 0 && selection_book_edit < 5) {
                                        lib.editBook(book_id, selection_book_edit);
                                        lib.printBook(book_id);
                                        in_edit_menu = false;
                                    }
                                    else {
                                        std::cout << "Invalid selection. Try again." << std::endl;
                                    }
                                }
                            }
                            else if (selection_admin_panel == 4) { // Delete Book
                                int selection_book = selectOption(book_remove_panel, getSizeOfMenu(book_remove_panel));
                                system("cls");

                                if (selection_book == 0) { // Delete Book
                                    removeBookInput(lib);
                                }
                                else if (selection_book == 1) { // Remove copies of a book
                                    removeBookCopiesInput(lib);
                                }
                            }
                            else if (selection_admin_panel == 5) { // Add Admin
                                giveAdminRightsInput(user_manager);
                            }
                            else if (selection_admin_panel == 6) { // Remove Admin Rights
                                removeAdminRightsInput(user_manager);
                            }
                            else if (selection_admin_panel == 7) { // Back to Admin Login Menu
                                in_admin_panel = false;
                            }
                            else if (selection_admin_panel == 8) { // Quit
                                exit(0);
                            }
                        }
                    }
                }
                else if (selection_admin_log_in == 1) { // Back to Main Menu
                    in_admin_menu = false;
                }
                else if (selection_admin_log_in == 2) { // Quit
                    exit(0);
                }
            }
        }
    }
}




int main()
{
    //drawWelcomeMessage(text);
    navigateMenu();
   
 
    return 0;

}


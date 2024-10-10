#include "LibraryApp.h"
#include <iostream>
#include "TextTable.h"




std::string draw_message;
std::string invalid_input;
bool is_visible = true;



void LibraryApp::drawMessage(std::string show_text = "Main Menu") {
    system("cls");
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

    std::string separator_draw = "********************************************************";
    std::string box_draw = "*                                                      *";
    std::string first_text_draw = "*           WELCOME TO YOUR VIRTUAL LIBRARY!           *";
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



void LibraryApp::showMenu(std::string panel[], int size, int selection) {
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

int LibraryApp::selectOption(std::string panel[], int size, std::string message) {
    int selection = 0;
    bool is_running = true;


   

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
                drawMessage(message);
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

template <size_t N>
int LibraryApp::getSizeOfMenu(std::string(&menu_array)[N]) {
    return N;
}

void LibraryApp::inputStringValidation(std::string& input, const std::string& input_name) {
    while (true) {
        bool isValid = true;
        if (input.length() < MIN_LEN || input.length() > MAX_LEN) {
             drawMessage(invalid_input);
            std::cout << "Enter a valid " << input_name << " between "<< MIN_LEN << " and " << MAX_LEN << " characters: ";
            isValid = false;
        }

        if ((input_name == "genre" || input_name =="author") && !validateGenreAndAuthorString(input)) { 
            drawMessage(invalid_input);
            std::cout << "Enter a valid " << input_name << ", only characters: ";
            isValid = false;
        }
        
        if (isValid) {
           system("cls");
            break;
        }
        std::getline(std::cin, input);
    }
}

void LibraryApp::inputYearValidation(int& input) {
    while (true) {
        if (std::cin >> input) {
            if (input >= 1500 && input <= 2024) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            else {
                drawMessage(invalid_input);
                std::cout << "Year must be between 1500 and 2024: ";
            }
        }
        else {
            drawMessage(invalid_input);
            std::cout << "Please enter a numeric value: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void LibraryApp::inputPagesValidation(int& input) {


    while (true) {
        if (std::cin >> input) {
            if (input > 5) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                break; 
            }
            else {
                drawMessage(invalid_input);
                std::cout << "The number of pages must be greater than 5: ";
            }
        }
        else {
            drawMessage(invalid_input);
            std::cout << "Please enter a numeric value: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

User* LibraryApp::addUserInput() {
    std::string user_name;
    std::cout << "Enter new user name: ";

    while (true) {
        std::getline(std::cin, user_name);
        if (user_name.length() > MIN_LEN && user_name.length() <= MAX_LEN) {
            User* newUser = user_manager.addUser(user_name);
          
                if (newUser != nullptr) {
                    newUser->setLogInStatus(true);
                    drawMessage("Your User ID is: " + std::to_string(newUser->getUserId()));
                    std::cout << "User added and logged in successfully!"<< std::endl;
                    return newUser;
                }

            
        }
        else {
            drawMessage(invalid_input);
           std::cout << "Enter a username between " << MIN_LEN << " and " << MAX_LEN << " char long: ";

        }
    }


}

User* LibraryApp::checkExistingUserInput() {
    int user_id;
   
    while (true) {
        std::cout << "Enter your user id: ";
        if (std::cin >> user_id) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            User* found_user = user_manager.getUserById(user_id);
            if (found_user != nullptr) {
                found_user->setLogInStatus(true);
                drawMessage("Logged in successfully with id: " + std::to_string(found_user->getUserId()));
                return found_user;
            }
            else {
               drawMessage( "!!! The user does not exist !!!");
                return nullptr;
            }
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            drawMessage("!!! Invalid input. Enter numeric value !!!");
            return nullptr;

        }
    }

}

User* LibraryApp::checkAdminRightsInput() {
    int admin_id;
    
    while (true) {
        std::cout << "Enter your admin id: ";
        if (std::cin >> admin_id) {
            User* is_admin = user_manager.getUserById(admin_id);
            if (is_admin != nullptr) {
                if (is_admin->getAdminRights()) {
                    drawMessage("Admin Panel");
                    return is_admin;
                }
                else {
                    drawMessage("!!! You do not have admin rights !!!!");
                    return nullptr;
                }
            }
            else {
                drawMessage("The id does not exists !!!");
                return nullptr;
            }
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            drawMessage(invalid_input);
            return nullptr;
            
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool LibraryApp::validateGenreAndAuthorString(const std::string text)
{
    for (const char c : text) {
        if (!isalpha(c) && !isspace(c))
            return false;
    }

    return true;
}

void LibraryApp::addBookInput() {
    std::string     book_title;
    std::string     book_author;
    int             book_pages;
    int             book_year;
    std::string     book_genre;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter the Book Title: ";
    std::getline(std::cin, book_title);
    inputStringValidation(book_title, "book title");

    drawMessage("Add New Book");
    std::cout << "Enter the Book Author: ";
    std::getline(std::cin, book_author);
    inputStringValidation(book_author, "author");

    drawMessage("Add New Book");
    std::cout << "Enter the Book Genre: ";
    std::getline(std::cin, book_genre);
    inputStringValidation(book_genre, "genre");
   
    drawMessage("Add New Book");
    std::cout << "Enter the Book Pages: ";
    inputPagesValidation(book_pages);

    drawMessage("Add New Book");
    std::cout << "Enter the Book Year: ";
    inputYearValidation(book_year);

    Book book(book_title, book_author, book_pages, book_year, book_genre);
    lib.addBook(book);
    drawMessage("Book added successfully!");
    book.print();
}

void LibraryApp::checkBookExistsInput(int& book_id) {
    while (!lib.bookExists(book_id)) {
        lib.print();
        std::cout << "The book does not exist in the Library, enter a valid Book ID: ";
        std::cin >> book_id;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void LibraryApp::removeBookInput() {
    int book_id;
    lib.print();
    while (true) {
        std::cout << "Enter the Book ID to delete: ";
        if (std::cin >> book_id) {
            if (lib.bookExists(book_id)) {

                drawMessage("Delete Book");
                break;
            }
            else {
                drawMessage("!!! Book does not exist !!!");
                lib.print();
            }
        }
        else {
            drawMessage(invalid_input);
            lib.print();
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    lib.removeBook(book_id);
}

void LibraryApp::removeBookCopiesInput() {
    int book_id;
    int book_copies;

    lib.print();

    while (true) {
        std::cout << "Enter the Book ID to remove copies: ";
        if (std::cin >> book_id) {
            if (lib.bookExists(book_id)) {
                drawMessage("Remove book copies");
                break;
            }
            else {
                drawMessage("!!! Book does not exist !!!");
                lib.print();
            }
        }
        else {
            drawMessage(invalid_input);
            lib.print();
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }


    Book* book = lib.getBookById(book_id);
    if (book) {
        int current_copies = book->getNoPieces();

        while (true) {
            std::cout << "Enter the number of copies to remove (1-" << current_copies << "): ";
            if (std::cin >> book_copies) {
                if (book_copies >= 1 && book_copies <= current_copies) {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    break;
                }
                else {
                    drawMessage("!!! Invalid number of copies !!!");
                }
            }
            else {
                drawMessage(invalid_input);
                std::cin.clear();
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        book->removeCopy(book_copies);
        drawMessage("Copies removed successfully!");
    }
    else {
        std::cout << "Book not found." << std::endl;
    }
}

void LibraryApp::addCopiesInput() {
    int book_id;
    int book_copies;
    lib.print();
    while (true) {
        std::cout << "Enter the Book ID: ";
        if (std::cin >> book_id) {
            if (lib.bookExists(book_id)) {
                drawMessage("Add book copies");
                break;
            }
            else {
                drawMessage("!!! Book does not exist !!!");
                lib.print();
            }
        }
        else {
            drawMessage(invalid_input);
            lib.print();
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  
    while (true) {
        
        lib.print();
        std::cout << "Enter the number of copies to add: ";
        if (std::cin >> book_copies) {
            if (book_copies > 0) {
                break;
            }
            else {
                drawMessage("!!! Invalid number of copies !!!");
            }
        }
        else {
            drawMessage(invalid_input);
            std::cin.clear();
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Book* book = lib.getBookById(book_id);
    if (book) {
        book->addCopy(book_copies);
        drawMessage("Copies added successfully!");  
    }
}

int LibraryApp::editBookInput() {

    int book_id;

    while (true) {
        
        lib.print();
        std::cout << "Enter the book ID you want to edit: ";
        if (std::cin >> book_id) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            Book* book = lib.getBookById(book_id);
            if (book) {
                drawMessage("Edit Book");
                return book_id;
            }
            else {
                drawMessage("!!! Book does not exist !!!");
            }
        }
        else {
            drawMessage("!!! Invalid Input !!!");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}



void LibraryApp::giveAdminRightsInput() {
    int user_id;
    User* user = nullptr;

    while (true) {
        std::cout << "Enter the user ID you want to give Admin Rights: ";
        if (std::cin >> user_id) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            user = user_manager.getUserById(user_id);
            if (user) {
                break;
            }
            else {
                system("cls");
                drawMessage("!!! The id does not exist !!!");
            }

        }
        else {
            system("cls");
            //drawMessage("!!! Invalid input !!!");
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    if (user->getAdminRights()) {
        system("cls");
        //drawMessage("!!! Already has Admin Rights !!!");
    }else{
         user->setAdminRights();
         system("cls");
         //drawMessage("Admin rights granted successfully!");
    }
}

void LibraryApp::removeAdminRightsInput() {
    int user_id;
    User* user = nullptr;

    while (true) {
        std::cout << "Enter the user ID you want to remove Admin Rights: ";
        if (std::cin >> user_id) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            user = user_manager.getUserById(user_id);
            if (user) {
                break;
            }
            else {
                drawMessage("!!! The ID does not exist !!!");
            }
        }
        else {
            drawMessage(invalid_input);
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    if (user->getAdminRights()) {
        user->setAdminRights(false);
        drawMessage("Admin rights removed successfully!");
    }
    else {
        drawMessage("!!! The user does not have Admin Rights !!!");
    }
}
void LibraryApp::displayUserRentals(const std::vector<Rental>& userRentals) {
    TextTable t('-', '|', '+');
    t.add("Rental Code");
    t.add("Book ID");
    t.add("Book Title");
    t.add("Rent Date");
    t.add("Return Date");
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
}
void LibraryApp::returnBookInput(User* user) {
    std::vector<Rental> userRentals = lib.getUserRentals(user->getUserId());

    if (userRentals.empty()) {
    
        drawMessage("You have no rented books to return");
        return;
    }

    displayUserRentals(userRentals);

    int book_id;
    int rating;

    while (true) {
        std::cout << "Enter the Book ID you want to return: ";
        if (std::cin >> book_id) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            auto it = std::find_if(userRentals.begin(), userRentals.end(),
                [book_id](const Rental& rental) {
                    return rental.book_id == book_id;
                });

            if (it == userRentals.end()) {

                drawMessage("!!! You have not rented this book !!!");
                displayUserRentals(userRentals);
            }
            else {
                break;
            }
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            drawMessage("!!! Invalid Book ID !!!");
            displayUserRentals(userRentals);
        }
    }

    while (true) {
        std::cout << "Enter a rating between 1 and 5: ";
        if (std::cin >> rating) {
            if (rating >= 1 && rating <= 5) {
                break;
            }
            else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                drawMessage("!!! Invalid rating. It must be between 1 and 5 !!!");
                displayUserRentals(userRentals);
            }
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            drawMessage(invalid_input);
            displayUserRentals(userRentals);

        }
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    lib.returnBook(book_id, user->getUserId(), rating);
    drawMessage("Book returned successfully");
}


void LibraryApp::rentBookInput(User* user) {
    int book_id;
    bool show = true;
    while (true) {
        if (show) {
            drawMessage("Rent Books");
            
        }
        lib.print();
        std::cout << "Enter the book ID you want to rent: ";
        if (std::cin >> book_id) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            system("cls");
            if (lib.bookExists(book_id)) {
                lib.rentBook(book_id, user->getUserId(), user_manager);
                show = false;
                break;
            }
            else {
                drawMessage("!!! The Book ID was not found !!!");
                show = false;
            }
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          
            drawMessage("!!! Invalid Book ID !!!");
            show = false;
        }
    }
}

void LibraryApp::navigateMenu() {
    bool is_running = true;
    LibraryApp libapp;
    while (is_running) {
        drawMessage("Main Menu");
        int menu_selection = selectOption(first_panel, getSizeOfMenu(first_panel), "Main Menu");

        if (menu_selection == 0) { // User Menu
            drawMessage("User Menu");
            bool in_user_menu = true;
            while (in_user_menu) {
                int selection_user_log_in = selectOption(user_log_in_panel, getSizeOfMenu(user_log_in_panel), "User Menu");

                if (selection_user_log_in == 0) { // New User
                    drawMessage("New User");
                    User* loggedInUser = addUserInput();
                    if (loggedInUser != nullptr) {
                        bool in_user_panel = true;
                        while (in_user_panel) {

                            int user_selection = selectOption(user_panel, getSizeOfMenu(user_panel), "Logged in with id: "+std::to_string(loggedInUser->getUserId()));
                            if (user_selection == 0) { // Rent a Book
                                bool in_display_panel = true;
                                bool show = true;

                                if (show) {
                                    drawMessage("Rent & Sort");
                                }
                                show = false;
                                while (in_display_panel) {

                                    int display_selection = selectOption(sort_panel, getSizeOfMenu(sort_panel), "Rent & Sort");
                                   
                                    if (display_selection == 0) { // Rent
                                        
                                        rentBookInput(loggedInUser);
                                    }
                                    else if (display_selection > 0 && display_selection < 5) { // Sort Books
                                        drawMessage(sort_panel[display_selection]);
                                        lib.sortBooks(display_selection);
                                        lib.printSortedBooks();
                                        is_visible = true;
                                    }
                                    else if (display_selection == 5) {// Back
                                        in_display_panel = false;
                                        drawMessage("Loged in with id : "+std::to_string(loggedInUser->getUserId()));
                                    }
                                    else if (display_selection == 6) { // Quit
                                        exit(0);
                                    }
                                }
                            }
                            else if (user_selection == 1) { // Return Book
                                drawMessage("Return Book");
                                returnBookInput(loggedInUser);
                            }
                            else if (user_selection == 2) { // Back to User Login Menu
                                drawMessage("User Menu");
                                in_user_panel = false;
                                loggedInUser->setLogInStatus(false);
                            }
                            else if (user_selection == 3) { // Quit
                                exit(0);
                            }
                        }
                    }
                }
                else if (selection_user_log_in == 1) { // Existing User
                    drawMessage("Existing User");
                    User* loggedInUser = checkExistingUserInput();
                   
                    if (loggedInUser != nullptr) {
                        bool in_user_panel = true;
                        while (in_user_panel) {
                            int user_selection = selectOption(user_panel, getSizeOfMenu(user_panel), "Logged in with id: " + std::to_string(loggedInUser->getUserId()));

                            if (user_selection == 0) { // Rent a Book
                                bool in_display_panel = true;
                                bool show = true;

                                if (show) {
                                    drawMessage("Rent & Sort");
                                }
                                show = false;
                                while (in_display_panel) {
                                    int display_selection = selectOption(sort_panel, getSizeOfMenu(sort_panel), "Rent & Sort");

                                    if (display_selection == 0) { // Rent
                                        
                                        rentBookInput(loggedInUser);
                                    }
                                    else if (display_selection > 0 && display_selection < 5) { // Sort Books

                                        drawMessage(sort_panel[display_selection]);
                                        lib.sortBooks(display_selection);
                                        lib.printSortedBooks();
                                    }
                                    else if (display_selection == 5) { // Back
                                        in_display_panel = false;
                                        drawMessage("Loged in with id : " + std::to_string(loggedInUser->getUserId()));
                                    }
                                    else if (display_selection == 6) { // Quit
                                        exit(0);
                                    }
                                }
                            }
                            else if (user_selection == 1) { // Return Book
                                returnBookInput(loggedInUser);
                                //drawMessage("Return Book");
                            }
                            else if (user_selection == 2) { // Back
                                drawMessage("User Menu");
                                in_user_panel = false;
                                loggedInUser->setLogInStatus(false);
                            }
                            else if (user_selection == 3) { // Quit
                                exit(0);
                            }
                        }
                    }
                }
                else if (selection_user_log_in == 2) { // Back to Main Menu
                    in_user_menu = false;
                }
                else if (selection_user_log_in == 3) { // Quit
                    exit(0);
                }
            }
        }
        else if (menu_selection == 1) { // Admin Menu
            bool in_admin_menu = true;
            bool show = true;
            while (in_admin_menu) {
              
                if (show) {
                    drawMessage("Admin Menu");
                }
                show = false;
                int selection_admin_log_in = selectOption(admin_log_in_panel, getSizeOfMenu(admin_log_in_panel), "Admin Menu");

                if (selection_admin_log_in == 0) { // Log in Admin
                    drawMessage("Log in Admin");
                    User* adminUser = checkAdminRightsInput();
                    show = false;
                    if (adminUser != nullptr) {
                        bool in_admin_panel = true;
                        show = true;
                          if (show) {
                              drawMessage("Admin Menu");
                          }
                      //show = false;
                        while (in_admin_panel) {
                            int selection_admin_panel = selectOption(admin_panel, getSizeOfMenu(admin_panel), "Admin Panel");
                          
                            if (selection_admin_panel == 0) { // Display Books
                                drawMessage("Library Books");
                                lib.print();
                            }
                            else if (selection_admin_panel == 1) { // Rented Books
                                drawMessage("Library Rented Books");
                                if (lib.getRentedSize() < 1) {
                                    drawMessage("There are no rented books");
                                }
                                else {
                                    lib.printRentedBooks();
                                }
                                
                            }
                            else if (selection_admin_panel == 2) { // Add Books
                                show = true;
                                if (show) {
                                    drawMessage("Add Books");
                                }
                                show = false;
                                int selection_book = selectOption(book_add_panel, getSizeOfMenu(book_add_panel), "Add Books");

                                if (selection_book == 0) { // New Book
                                    drawMessage("Add New Book");
                                    addBookInput();
                                }
                                else if (selection_book == 1) { // Add copies of an existing Book
                                    drawMessage("Add Copies of Book");
                                    addCopiesInput();
                                }
                                else if (selection_book == 2) { // Back
                                    drawMessage("Admin Panel");
                                    in_admin_menu = false;
                                }
                                else if (selection_book == 3) { // Quit
                                    exit(0);
                                }
                            }
                            else if (selection_admin_panel == 3) { // Edit Book
                                bool in_edit_menu = true;
                                while (in_edit_menu) {
                                    drawMessage("Edit Book");
                                    int book_id = editBookInput();
                                    int selection_book_edit = selectOption(edit_book_panel, getSizeOfMenu(edit_book_panel), "Edit Book");

                                    if (selection_book_edit >= 0 && selection_book_edit < 5) {
                                        drawMessage(edit_book_panel[selection_book_edit]);
                                        lib.editBook(book_id, selection_book_edit);
                                        drawMessage("Book updated successfully!");
                                        lib.printBook(book_id);
                                        in_edit_menu = false;
                                    }
                                }
                            }
                            else if (selection_admin_panel == 4) { // Delete Book
                                show = true;
                                if (show) {
                                    drawMessage("Delete Books");
                                }
                                show = false;
                                int selection_book = selectOption(book_remove_panel, getSizeOfMenu(book_remove_panel), "Delete Book");
                               
                                if (selection_book == 0) { // Delete Book
                                    
                                    drawMessage(book_remove_panel[0]);
                                    removeBookInput();
                                    drawMessage("Book deleted successfully!");
                                }
                                else if (selection_book == 1) { // Remove copies of a book
                                    drawMessage(book_remove_panel[1]);
                                    removeBookCopiesInput();
                                    drawMessage("Copies removed successfully!");
                                }
                                else if (selection_book == 2) { // Back
                                    drawMessage("Admin Panel");
                                    in_admin_menu = false;
                                    
                                }
                                else if (selection_book == 3) { // Quit
                                    exit(0);
                                }
                            }
                            else if (selection_admin_panel == 5) { // Add Admin
                                drawMessage("Add Admin");
                                giveAdminRightsInput();
                            }
                            else if (selection_admin_panel == 6) { // Remove Admin Rights
                                drawMessage("Remove Admin");
                                removeAdminRightsInput();
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

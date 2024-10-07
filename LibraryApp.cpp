#include "LibraryApp.h"
#include <iostream>
#include "TextTable.h"




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

    if (!message.empty()) {
        std::cout << message << std::endl;
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
                std::cout << message << std::endl;
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
    while (input.length() < MIN_LEN || input.length() > MAX_LEN) {
        if (input_name == "genre" && !validateGenreString(input)) {
            std::cout << "The " << input_name << " can not contain numbers"<<std::endl ;
        }
        std::cout << "Enter a valid " << input_name << " between "<<MIN_LEN<<" and "<<MAX_LEN<<" char: " ;
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
                std::cout << "Year must be between 1500 and 2024: " << std::endl;;
            }
        }
        else {
            std::cout << "Invalid input. Please enter a numeric value: " << std::endl;
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
                std::cout << "The number of pages must be greater than 5: " << std::endl;
            }
        }
        else {
            std::cout << "Invalid input. Please enter a numeric value: " << std::endl;
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
                    std::cout << "User added and logged in successfully! Your User ID is: " << newUser->getUserId() << std::endl;
                    return newUser;
                }

            
        }
        else {
            std::cout << "Invalid input." << std::endl;  std::cout << "Enter a username between " << MIN_LEN << " and " << MAX_LEN << " char long: ";

        }
    }


}




User* LibraryApp::checkExistingUserInput() {
    int user_id;
    std::cout << "Enter your user id: ";

    while (true) {
        if (std::cin >> user_id) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            User* found_user = user_manager.getUserById(user_id);
            if (found_user != nullptr) {
                found_user->setLogInStatus(true);
                std::cout << "Hello, " << found_user->getUserName() << ". You have logged in successfully!" << std::endl;
                return found_user;
            }
            else {
                std::cout << "The user does not exist." << std::endl;
                return nullptr;
            }
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a numeric value: ";

        }
    }


}

User* LibraryApp::checkAdminRightsInput() {
    int admin_id;
    std::cout << "Enter your admin id: ";

    while (true) {
        if (std::cin >> admin_id) {
            User* is_admin = user_manager.getUserById(admin_id);
            if (is_admin != nullptr) {
                if (is_admin->getAdminRights()) {
                    std::cout << "Hello, " << is_admin->getUserName() << ". You have logged in successfully as admin!" << std::endl;
                    return is_admin;
                }
                else {
                    std::cout << "You do not have admin rights for user: " << is_admin->getUserName() << std::endl;
                    return nullptr;
                }
            }
            else {
                std::cout << "The id does not exist" << std::endl;
                return nullptr;
            }
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a numeric value: ";
        }
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool LibraryApp::validateGenreString(const std::string book_genre)
{
    for (const char c : book_genre) {
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

    std::cout << "Enter the Book Title:" << std::endl;
    std::getline(std::cin, book_title);
    inputStringValidation(book_title, "book name");

    std::cout << "Enter the Book Author:" << std::endl;
    std::getline(std::cin, book_author);
    inputStringValidation(book_author, "book author");

    std::cout << "Enter the Book Genre:" << std::endl;
    std::getline(std::cin, book_genre);
    inputStringValidation(book_genre, "genre");
   

    std::cout << "Enter the Book Pages:" << std::endl;
    inputPagesValidation(book_pages);

    std::cout << "Enter the Book Year:" << std::endl;
    inputYearValidation(book_year);

    Book book(book_title, book_author, book_pages, book_year, book_genre);
    lib.addBook(book);
    system("cls");
    std::cout << "Book added successfully!" << std::endl;
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
    std::cout << "Enter the book ID to delete:" << std::endl;
    std::cin >> book_id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    checkBookExistsInput(book_id);
    lib.removeBook(book_id);
}

void LibraryApp::removeBookCopiesInput() {
    int book_id;
    int book_copies;

    lib.print();
    std::cout << "Enter the book ID to remove copies: " << std::endl;

    while (!(std::cin >> book_id)) {
        std::cout << "Invalid input. Please enter a numeric Book ID: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    checkBookExistsInput(book_id);
    Book* book = lib.getBookById(book_id);

    if (book) {
        int current_copies = book->getNoPieces();
        while (true) {
            std::cout << "Enter the number of copies to remove (1-" << current_copies << "): " << std::endl;

            if (std::cin >> book_copies) {
                if (book_copies >= 1 && book_copies <= current_copies) {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                    break; 
                }
                else {
                    std::cout << "The number of copies must be between 1 and " << current_copies << "." << std::endl;
                }
            }
            else {
                std::cout << "Invalid input. Please enter a numeric value." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        book->removeCopy(book_copies);
        std::cout << "Copies removed successfully!" << std::endl;
    }
    else {
        std::cout << "Book not found." << std::endl;
    }
}

void LibraryApp::addCopiesInput() {
    int book_id;
    int book_copies;
    lib.print();
    std::cout << "Enter the book ID:" << std::endl;
    while (!(std::cin >> book_id)) {
        std::cout << "Invalid input. Please enter a numeric Book ID: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Enter the numbers of copies: " << std::endl;
    checkBookExistsInput(book_id);
    Book* book = lib.getBookById(book_id);
    if (book) {
        inputPagesValidation(book_copies);
        book->addCopy(book_copies);
        std::cout << "Copies added successfully!" << std::endl;
    }
    else {
        std::cout << "Book not found." << std::endl;
    }
}

int LibraryApp::editBookInput() {

    int book_id;

    while (true) {
        std::cout << "Enter the book ID you want to edit: ";
        if (std::cin >> book_id) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            Book* book = lib.getBookById(book_id);
            if (book) {
                return book_id;
            }
            else {
                std::cout << "Book with ID " << book_id << " does not exist. " << std::endl;
            }
        }
        else {
            std::cout << "Invalid input. Please enter a numeric Book ID." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}



void LibraryApp::giveAdminRightsInput() {
    int user_id;
    User* user = nullptr;

    while (true) {
        std::cout << "Enter the user ID you want to give Admin Rights:" << std::endl;
        if (std::cin >> user_id) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            user = user_manager.getUserById(user_id);
            if (user) {
                break;
            }
            else {
                std::cout << "The ID you have entered does not exist. Please try again." << std::endl;
            }
        }
        else {
            std::cout << "Invalid input. Please enter a numeric User ID." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    if (user->getAdminRights()) {
        std::cout << "The user already has Admin Rights!" << std::endl;
    }else{
         user->setAdminRights();
         std::cout << "Admin rights granted successfully!" << std::endl;
    }
}

void LibraryApp::removeAdminRightsInput() {
    int user_id;
    User* user = nullptr;

    while (true) {
        std::cout << "Enter the user ID you want to remove Admin Rights:" << std::endl;

        if (std::cin >> user_id) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            user = user_manager.getUserById(user_id);
            if (user) {
                break;
            }
            else {
                std::cout << "The ID you have entered does not exist. Please try again." << std::endl;
            }
        }
        else {
            std::cout << "Invalid input. Please enter a numeric User ID." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }
    }
    if (user->getAdminRights()) {
        user->setAdminRights(false);
        std::cout << "Admin rights removed successfully!" << std::endl;
    }
    else {
        std::cout << "The user does not have Admin Rights." << std::endl;
    }
}

void LibraryApp::returnBookInput(User* user) {
    std::vector<Rental> userRentals = lib.getUserRentals(user->getUserId());

    if (userRentals.empty()) {
        std::cout << "You have no rented books to return.\n";
        return;
    }
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
    int book_id;

    while (true) {
        std::cout << "Enter the Book ID you want to return: ";
        if (std::cin >> book_id) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            auto it = std::find_if(userRentals.begin(), userRentals.end(),
                [book_id](const Rental& rental) {
                    return rental.book_id == book_id;
                });
            break;
            if (it == userRentals.end()) {
                std::cout << "You have not rented this book.\n";
            }
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid Book ID. Please enter a valid book ID.\n";
        }
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

void LibraryApp::rentBookInput(User* user) {
    int book_id;

    while (true) {
        std::cout << "Enter the book ID you want to rent: ";
        if (std::cin >> book_id) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (lib.bookExists(book_id)) {
                lib.rentBook(book_id, user->getUserId(), user_manager);
                break;
            }
            else {
                std::cout << "The Book ID was not found.\n";
            }
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid Book ID. Please enter a valid book ID.\n";
        }
    }
}

void LibraryApp::navigateMenu() {
    bool is_running = true;

    while (is_running) {

        int menu_selection = selectOption(first_panel, getSizeOfMenu(first_panel), "Main Menu");

        if (menu_selection == 0) { // User Menu
            bool in_user_menu = true;
            while (in_user_menu) {
                int selection_user_log_in = selectOption(user_log_in_panel, getSizeOfMenu(user_log_in_panel), "User Menu");

                if (selection_user_log_in == 0) { // New User
                    User* loggedInUser = addUserInput();
                    if (loggedInUser != nullptr) {
                        bool in_user_panel = true;

                        while (in_user_panel) {
                            int user_selection = selectOption(user_panel, getSizeOfMenu(user_panel), "User Menu");

                            if (user_selection == 0) { // Rent a Book
                                bool in_display_panel = true;
                                while (in_display_panel) {
                                    int display_selection = selectOption(sort_panel, getSizeOfMenu(sort_panel), "Rent Book");

                                    if (display_selection == 0) { // Rent
                                        lib.print();
                                        rentBookInput(loggedInUser);
                                    }
                                    else if (display_selection > 0 && display_selection < 5) { // Sort Books
                                        lib.sortBooks(display_selection);
                                        lib.printSortedBooks();
                                    }
                                    else if (display_selection == 5) { // Back
                                        in_display_panel = false;
                                    }
                                    else if (display_selection == 6) { // Quit
                                        exit(0);
                                    }
                                }
                            }
                            else if (user_selection == 1) { // Return Book
                                returnBookInput(loggedInUser);
                            }
                            else if (user_selection == 2) { // Back to User Login Menu
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
                    User* loggedInUser = checkExistingUserInput();
                    if (loggedInUser != nullptr) {
                        bool in_user_panel = true;
                        while (in_user_panel) {
                            int user_selection = selectOption(user_panel, getSizeOfMenu(user_panel), "User Menu");

                            if (user_selection == 0) { // Rent a Book
                                bool in_display_panel = true;
                                while (in_display_panel) {
                                    int display_selection = selectOption(sort_panel, getSizeOfMenu(sort_panel), "Rent Book");

                                    if (display_selection == 0) { // Rent
                                        lib.print();
                                        rentBookInput(loggedInUser);
                                    }
                                    else if (display_selection > 0 && display_selection < 5) { // Sort Books
                                        lib.sortBooks(display_selection);
                                        lib.printSortedBooks();
                                    }
                                    else if (display_selection == 5) { // Back
                                        in_display_panel = false;
                                    }
                                    else if (display_selection == 6) { // Quit
                                        exit(0);
                                    }
                                }
                            }
                            else if (user_selection == 1) { // Return Book
                                returnBookInput(loggedInUser);
                            }
                            else if (user_selection == 2) { // Back
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
            while (in_admin_menu) {
                int selection_admin_log_in = selectOption(admin_log_in_panel, getSizeOfMenu(admin_log_in_panel), "Admin Menu");

                if (selection_admin_log_in == 0) { // Log in Admin
                    User* adminUser = checkAdminRightsInput();
                    if (adminUser != nullptr) {
                        bool in_admin_panel = true;
                        while (in_admin_panel) {
                            int selection_admin_panel = selectOption(admin_panel, getSizeOfMenu(admin_panel), "Admin Panel");

                            if (selection_admin_panel == 0) { // Display Books
                                lib.print();
                            }
                            else if (selection_admin_panel == 1) { // Rented Books
                                lib.printRentedBooks();
                            }
                            else if (selection_admin_panel == 2) { // Add Books
                                int selection_book = selectOption(book_add_panel, getSizeOfMenu(book_add_panel), "Add Books");

                                if (selection_book == 0) { // New Book
                                    addBookInput();
                                }
                                else if (selection_book == 1) { // Add copies of an existing Book
                                    addCopiesInput();
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
                                    lib.print();
                                    int book_id = editBookInput();
                                    int selection_book_edit = selectOption(edit_book_panel, getSizeOfMenu(edit_book_panel), "Edit Book");

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
                                int selection_book = selectOption(book_remove_panel, getSizeOfMenu(book_remove_panel), "Delete Book");

                                if (selection_book == 0) { // Delete Book
                                    removeBookInput();
                                }
                                else if (selection_book == 1) { // Remove copies of a book
                                    removeBookCopiesInput();
                                }
                            }
                            else if (selection_admin_panel == 5) { // Add Admin
                                giveAdminRightsInput();
                            }
                            else if (selection_admin_panel == 6) { // Remove Admin Rights
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

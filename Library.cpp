#include "Library.h"


Library::Library() {
    books = {
    {"Barte1", "Autor1", 200, 1989, "Romance"},
    {"Darte2", "Autor2", 100, 2019, "Drama"},
    {"Aarte3", "Autor3", 300, 2020, "Thriller"}
    };
}


int Library::getSize() const {
    return books.size();
}

int Library::getRentedSize() const {
    return rentedBooks.size();
}

void Library::addBook(const Book& book) {
    for (auto& existingBook : books) {
        if (book.getUniqueCode() == existingBook.getUniqueCode()) {
            existingBook.addCopy();
            return;
        }
    }
    books.push_back(book);
}

void Library::removeCopies(int book_id, int copies) {
    for (auto& existingBook : books) {
        if (existingBook.getUniqueCode() == book_id) {
            existingBook.removeCopy(copies);
            return;
        }
    }
}

int Library::getNumberOfCopies(int book_id) {
    for (auto& existingBook : books) {
        if (existingBook.getUniqueCode() == book_id) {
            return existingBook.getNoPieces();
        }
    }
    return 0;
}

void Library::removeBook(int book_id) {
    for (auto it = books.begin(); it != books.end(); ++it) {
        if (it->getUniqueCode() == book_id) {
            books.erase(it);
            std::cout << "Book with ID " << book_id << " was removed." << std::endl;
            return;
        }
    }
    std::cout << "Book with ID " << book_id << " not found." << std::endl;
}

bool Library::bookExists(int book_id) const {
    for (const auto& book : books) {
        if (book.getUniqueCode() == book_id)
            return true;
    }
    return false;
}

void Library::addCopies(int book_id, int copies) {
    for (auto& existingBook : books) {
        if (existingBook.getUniqueCode() == book_id) {
            existingBook.addCopy(copies);
            return;
        }
    }
}

Book* Library::getBookById(int book_id) {
    for (auto& book : books) {
        if (book.getUniqueCode() == book_id) {
            return &book;
        }
    }
    return nullptr;
}

void Library::getBookCopies(int book_id) {
    Book* book = getBookById(book_id);
    if (book) {
        std::cout << "Number of copies for Book ID " << book_id << ": " << book->getNoPieces() << std::endl;
    }
    else {
        std::cout << "Book ID " << book_id << " not found." << std::endl;
    }
}

void Library::rentBook(int book_id, int user_id, UserManager& userManager) {
    int rent_date = getRentDate();
    int return_date = getReturnDate(15);
    if (!bookExists(book_id)) {
        std::cout << "Book ID " << book_id << " does not exist in the library.\n";
        return;
    }

    if (!userManager.userExists(user_id)) {
        std::cout << "User ID " << user_id << " does not exist.\n";
        return;
    }

    Book* book = getBookById(book_id);
    if (book) {
        if (book->getNoPieces() > 0) {
            Rental rental(book_id, user_id, rent_date, return_date);
            rentedBooks.push_back(rental);
            book->removeCopy();
            std::cout << "Book ID " << book_id << " has been rented by User ID " << user_id << ".\n";
        }
        else {
            std::cout << "No copies available for Book ID " << book_id << ".\n";
        }
    }
}

void Library::returnBook(int book_id, int user_id, int rating) {
    auto it = std::find_if(rentedBooks.begin(), rentedBooks.end(),
        [book_id, user_id](const Rental& rental) {
            return rental.book_id == book_id && rental.user_id == user_id;
        });

    if (it == rentedBooks.end()) {
        std::cout << "Rental not found for Book ID " << book_id << " and User ID " << user_id << ".\n";
    }
    else {
        rentedBooks.erase(it);

        Book* book = getBookById(book_id);
        if (book) {
            book->addCopy();
            book->addRating(rating);
            std::cout << "Book ID " << book_id << " has been returned by User ID " << user_id << ".\n";
        }
        else {
            std::cout << "Book ID " << book_id << " not found during return.\n";
        }
    }
}

std::vector<Rental> Library::getUserRentals(int user_id) const {
    std::vector<Rental> userRentals;
    for (const auto& rental : rentedBooks) {
        if (rental.user_id == user_id) {
            userRentals.push_back(rental);
        }
    }
    return userRentals;
}


void Library::print() const {
    TextTable t('-', '|', '+');

    t.add("Code");
    t.add("Title");
    t.add("Author");
    t.add("Pages");
    t.add("Year");
    t.add("Genre");
    t.add("Rating");
    t.add("Copies");
    t.endOfRow();

    for (const auto& book : books) {
        t.add(std::to_string(book.getUniqueCode()));
        t.add(book.getName());
        t.add(book.getAuthor());
        t.add(std::to_string(book.getPages()));
        t.add(std::to_string(book.getYear()));
        t.add(book.getGenre());
        t.add(std::to_string(book.getRating()));
        t.add(book.getNoPieces() == 0 ? "Not Available" : std::to_string(book.getNoPieces()));
        t.endOfRow();
    }
    std::cout << t << std::endl;
}

void Library::printBooks() const {
    std::cout << "Books in Library:\n";
    for (const auto& book : books) {
        book.print();
    }
}

void Library::printBook(int book_id) {
    Book* book = getBookById(book_id);
    if (book == nullptr) {
        std::cout << "Book not found." << std::endl;
        return;
    }
    book->print();
}

void Library::printRentedBooks() const {
    
    if (rentedBooks.empty()) {
        std::cout << "There are no rented books!" << std::endl;
    }
    else {
        TextTable t('-', '|', '+');

        t.add("Rent ID");
        t.add("Book ID");
        t.add("User ID");
        t.add("Rent Date");
        t.add("Return Date");
        t.endOfRow();
        std::cout << "Rented Books:\n";
        for (const auto& rental : rentedBooks) {
            t.add(std::to_string(rental.rent_id));
            t.add(std::to_string(rental.book_id));
            t.add(std::to_string(rental.user_id));
            t.add(std::to_string(rental.rent_date));
            t.add(std::to_string(rental.return_date));
            t.endOfRow();
        }
        std::cout << t << std::endl;
    }
   
}

void Library::sortBooks(int sortBy) {
    sortedBooks = books;

    std::sort(sortedBooks.begin(), sortedBooks.end(), [sortBy](const Book& first, const Book& second) {
        switch (sortBy) {
        case 1: return first.getName() < second.getName();
        case 2: return first.getAuthor() < second.getAuthor();
        case 3: return first.getPages() < second.getPages();
        case 4: return first.getYear() < second.getYear();
        case 5: return first.getRating() > second.getRating();
        default: return false;
        }
        });
}

void Library::printSortedBooks() const {
    TextTable t('-', '|', '+');
    t.add("Code");
    t.add("Title");
    t.add("Author");
    t.add("Pages");
    t.add("Year");
    t.add("Genre");
    t.add("Rating");
    t.endOfRow();

    for (const auto& sorted : sortedBooks) {
        t.add(std::to_string(sorted.getUniqueCode()));
        t.add(sorted.getName());
        t.add(sorted.getAuthor());
        t.add(std::to_string(sorted.getPages()));
        t.add(std::to_string(sorted.getYear()));
        t.add(sorted.getGenre());
        t.add(std::to_string(sorted.getRating()));
        t.endOfRow();
    }

    std::cout << t << std::endl;
}

void Library::editBook(int book_id, int book_attribute) {
    Book* book = getBookById(book_id);
    if (book == nullptr) {
        std::cout << "Book not found." << std::endl;
        return;
    }
    switch (book_attribute) {
    case 0: {
        std::string new_title;
        std::cout << "Enter new title: ";
        std::getline(std::cin >> std::ws, new_title);
        book->setName(new_title);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }
    case 1: {
        std::string new_author;
        std::cout << "Enter new author: ";
        std::getline(std::cin >> std::ws, new_author);
        book->setAuthor(new_author);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }
    case 2: {
        int new_pages;
        std::cout << "Enter new number of pages: ";
        std::cin >> new_pages;
        book->setPages(new_pages);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }
    case 3: {
        int new_year;
        std::cout << "Enter new year: ";
        std::cin >> new_year;
        book->setYear(new_year);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }
    case 4: {
        std::string new_genre;
        std::cout << "Enter new genre: ";
        std::getline(std::cin >> std::ws, new_genre);
        book->setGenre(new_genre);
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        break;
    }
    default:
        std::cout << "Invalid option." << std::endl;
        break;
    }

    std::cout << "Book updated successfully!" << std::endl;
}

int Library::formatDate(time_t timeValue) {
    tm ltm_s;
    localtime_s(&ltm_s, &timeValue);

    int year = 1900 + ltm_s.tm_year;
    int month = 1 + ltm_s.tm_mon;
    int day = ltm_s.tm_mday;

    int date = year * 10000 + month * 100 + day;
    return date;
}

int Library::getRentDate() {
    time_t now = time(0);
    return formatDate(now);
}

int Library::getReturnDate(int n) {
    time_t now = time(0);
    time_t return_time = now + n * 86400; 
    return formatDate(return_time);
}

#include "Book.h"
#include <iostream>
#include <stdexcept>


int Book::increment = 100;
int Book::increment_pieces = 0;


void Book::setRating(double book_rating) {
    rating = book_rating;
}

Book::Book(std::string title, std::string author, int pages, int year, std::string genre)
    : book_title(title), book_author(author), book_pages(pages), book_year(year), book_genre(genre), all_rented(false), rating(0) {
    increment++;
    unique_code = increment;
    no_pieces = 1;
    ratings.assign(5, 0);
}

// Copy constructor
Book::Book(const Book& src)
    : book_title(src.book_title),
    book_author(src.book_author),
    book_pages(src.book_pages),
    book_year(src.book_year),
    book_genre(src.book_genre),
    unique_code(src.unique_code), 
    all_rented(src.all_rented),
    no_pieces(src.no_pieces),
    ratings(src.ratings),
    rating(src.rating) {}

// Assignment operator
Book& Book::operator=(const Book& src) {
    if (this == &src)
        return *this;

    book_title = src.book_title;
    book_author = src.book_author;
    book_pages = src.book_pages;
    book_year = src.book_year;
    book_genre = src.book_genre;
    unique_code = src.unique_code;
    all_rented = src.all_rented;
    no_pieces = src.no_pieces;
    rating = src.rating;
    ratings = src.ratings;

    return *this;
}

// Default constructor
Book::Book()
    : book_title(""),
    book_author(""),
    book_pages(0),
    book_year(0),
    book_genre(""),
    all_rented(false),
    no_pieces(0),
    rating(0) {
    increment++;
    unique_code = increment;
    increment_pieces = 0;
    ratings.assign(5, 0);
}


void Book::setName(std::string title) {
    if (title.length() < 1) {
        std::cout << "Error: The title is too short!" << std::endl;
        book_title = "Anonim";
    }
    else {
        book_title = title;
    }
}

void Book::setAuthor(std::string author) {
    try {
        if (author.length() < 1) {
            throw std::invalid_argument("The author name is too short!");
        }
        book_author = author;
    }
    catch (const std::exception& e) {
        book_author = "Anonim";
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Book::setPages(int pages) {
    try {
        if (pages < 10) {
            throw std::invalid_argument("Number of pages must be at least 10.");
        }
        book_pages = pages;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Book::setYear(int year) {
    try {
        if (year > 2024 || year < 1500) {
            throw std::invalid_argument("Year must be between 1500 and 2024");
        }
        book_year = year;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Book::setGenre(std::string genre) {
    try {
        if (genre.length() < 1) {
            throw std::invalid_argument("The genre is too short!");
        }
        book_genre = genre;
    }
    catch (const std::exception& e) {
        book_genre = "N/A";
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Book::setRented(bool rented) {
    all_rented = rented;
}

void Book::setPieces(int pieces) {
    no_pieces = pieces;
}


std::string Book::getName() const {
    return book_title;
}

std::string Book::getAuthor() const {
    return book_author;
}

int Book::getPages() const {
    return book_pages;
}

int Book::getYear() const {
    return book_year;
}

std::string Book::getGenre() const {
    return book_genre;
}

int Book::getUniqueCode() const {
    return unique_code;
}

bool Book::getIsRented() const {
    return all_rented;
}

int Book::getNoPieces() const {
    return no_pieces;
}

double Book::getRating() const {
    return rating;
}


void Book::addCopy(int pieces) {
    no_pieces += pieces;
    if (no_pieces > 0) {
        all_rented = false;
    }
}

void Book::removeCopy(int pieces) {
    if (no_pieces > 0) {
        no_pieces -= pieces;
        if (no_pieces == 0) {
            all_rented = true;
        }
    }
}

void Book::addRating(int rating) {
    try {
        if (rating < 1 || rating > 5) {
            throw std::runtime_error("Rating must be between 1 and 5.");
        }
        ratings[rating - 1]++;
        calculateRating();
    }
    catch (std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void Book::calculateRating() {
    int sum = 0;
    int N = 0;

    for (int i = 0; i < 5; i++) {
        sum += ratings[i] * (i + 1);
        N += ratings[i];
    }
    if (N > 0) {
        rating = static_cast<double>(sum) / N;
    }
}

void Book::print() const {
    std::cout << "Code: " << unique_code << " || "
        << "Title: " << book_title << " || "
        << "Author: " << book_author << " || "
        << "Pages: " << book_pages << " || "
        << "Year: " << book_year << " || "
        << "Genre: " << book_genre << " || "
        << "Rating: " << rating << std::endl;
}

void Book::generateNewUniqueCode() {
    increment++;
    unique_code = increment;
}

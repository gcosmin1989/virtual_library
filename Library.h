#pragma once

#include <vector>
#include <iomanip> 
#include <sstream>
#include <iostream>
#include <ctime>
#include <algorithm>
#include "Book.h"
#include "Rental.h"
#include "UserManager.h"
#include "TextTable.h"


class Library {
private:
    std::vector<Book> books;
    std::vector<Rental> rentedBooks;
    std::vector<Book> sortedBooks;


    static int formatDate(time_t timeValue);
    static int getRentDate();
    static int getReturnDate(int n);

public:

    Library()=default;


    int getSize() const;
    int getRentedSize() const;


    void addBook(const Book& book);
    void removeCopies(int book_id, int copies);
    int getNumberOfCopies(int book_id);
    void removeBook(int book_id);
    bool bookExists(int book_id) const;
    void addCopies(int book_id, int copies);
    Book* getBookById(int book_id);
    void getBookCopies(int book_id);
    void editBook(int book_id, int book_attribute);


    void rentBook(int book_id, int user_id, UserManager& userManager);
    void returnBook(int book_id, int user_id, int rating);
    std::vector<Rental> getUserRentals(int user_id) const;

    void print() const;
    void printBooks() const;
    void printBook(int book_id);
    void printRentedBooks() const;
    void sortBooks(int sortBy);
    void printSortedBooks() const;
};


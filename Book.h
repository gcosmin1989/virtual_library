#pragma once
#include "Texttable.h"
#include <string>
#include <vector>
#include <iomanip> 
#include <sstream> 

class Book {
private:
    std::string book_title;
    std::string book_author;
    int book_pages;
    int book_year;
    std::string book_genre;
    int unique_code;
    bool all_rented;
    int no_pieces;
    double rating;
    std::vector<int> ratings;

    void setRating(double book_rating);

public:
    static int increment;
    static int increment_pieces;

    Book(std::string title, std::string author, int pages, int year, std::string genre);
    Book(const Book& src); // Copy constructor
    Book& operator=(const Book& src);
    Book(); // Default constructor


    void setName(std::string title);
    void setAuthor(std::string author);
    void setPages(int pages);
    void setYear(int year);
    void setGenre(std::string genre);
    void setRented(bool rented);
    void setPieces(int pieces);

    std::string getName() const;
    std::string getAuthor() const;
    int getPages() const;
    int getYear() const;
    std::string getGenre() const;
    int getUniqueCode() const;
    bool getIsRented() const;
    int getNoPieces() const;
    double getRating() const;

    void addCopy(int pieces = 1);
    void removeCopy(int pieces = 1);
    void addRating(int rating);
    void calculateRating();
    void print() const;
    void generateNewUniqueCode();
};

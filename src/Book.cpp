#include "../include/Book.h"
#include <iostream>

Book::Book(std::string id, std::string title, std::string a, int year,
            std::string isbn, int pages, std::string genre, bool hardCover)
    : LibraryItem(id, title, author, year),
        isbn(isbn), numPages(pages), genre(genre), isHardcover(hardCover){
        lateFeePerDay = 0.5;
}

Book::~Book() {}

void Book::displayInfo() const
{
    std::cout << "=== BOOK ===" << std::endl;
    std::cout << "ID: " << itemId << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Publication Year: " << publicationYear << std::endl;
    std::cout << "ISBN: " << isbn << std::endl;
    std::cout << "Pages: " << numPages << std::endl;
    std::cout << "Genre: " << genre << std::endl;
    std::cout << "Type: " << (isHardcover ? "Hardcover" : "Paperback") << std::endl;
    std::cout << "Available: " << (isAvailable ? "Yes" : "No") << std::endl;
}

double Book::calculateLateFee(int daysLate) const
{
    return daysLate * lateFeePerDay;
}

std::string Book::getItemType() const
{
    return "Book";
}

std::string Book::getIsbn() const
{
    return isbn;
}

std::string Book::getGenre() const
{
    return genre;
}
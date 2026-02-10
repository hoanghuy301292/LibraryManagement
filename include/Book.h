#ifndef BOOK_H
#define BOOK_H

#include "LibraryItem.h"

class Book : public LibraryItem {
    private:
        std::string isbn;
        int numPages;
        std::string genre;
        bool isHardcover;

    public:
        Book(std::string id, std::string title, std::string author, int year,
            std::string isbn, int numPages, std::string genre, bool hardCover);
        ~Book() override;

        void displayInfo() const override;
        double calculateLateFee(int daysLate) const override;
        std::string getItemType() const override;

        // Getters
        std::string getIsbn() const;
        std::string getGenre() const;
};

#endif // BOOK_H
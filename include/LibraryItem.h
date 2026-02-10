#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <string>

class LibraryItem {
    protected:
        std::string itemId;
        std::string title;
        std::string author;
        int publicationYear;
        bool isAvailable;
        double lateFeePerDay;

    public:
        LibraryItem(std::string id, std::string title, std::string author, int year);
        virtual ~LibraryItem();

        // Pure virtual functions
        virtual void displayInfo() const = 0;
        virtual double calculateLateFee(int daysLate) const = 0;
        virtual std::string getItemType() const = 0;

        // Common functions
        bool checkAvailability() const;        
        void setAvailability(bool availability);

        // Getters
        std::string getItemId() const;
        std::string getTitle() const;
        std::string getAuthor() const;
};

#endif // LIBRARYITEM_H
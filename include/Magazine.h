#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "LibraryItem.h"

class Magazine : public LibraryItem
{
    private:
        int issueNumber;
        std::string month;
        std::string publisher;

    public:
        Magazine(std::string id, std::string title, std::string author, int year,
                int issueNum, std::string month, std::string publisher);
        ~Magazine() override;

        void displayInfo() const override;
        double calculateLateFee(int daysLate) const override;
        std::string getItemType() const override;
};

#endif // MAGAZINE_H
#include "../include/Magazine.h"
#include <iostream>

Magazine::Magazine(std::string id, std::string title, std::string author, int year,
                int issueNum, std::string month, std::string publisher)
        :LibraryItem(id, title, author, year), issueNumber(issueNum), month(month), publisher(publisher) {
            lateFeePerDay = 0.25;
        }

Magazine::~Magazine() {}

void Magazine::displayInfo() const
{
    std::cout << "=== MAGAZINE ===" << std::endl;
    std::cout << "ID: " << itemId << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Publication Year: " << publicationYear << std::endl;
    std::cout << "Issue Number: " << issueNumber << std::endl;
    std::cout << "Month: " << month << std::endl;
    std::cout << "Publisher: " << publisher << std::endl;
}

double Magazine::calculateLateFee(int daysLate) const
{
    return daysLate * lateFeePerDay;
}

std::string Magazine::getItemType() const
{
    return "Magazine";
}
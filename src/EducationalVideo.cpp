#include "../include/EducationalVideo.h"

#include <iostream>


EducationalVideo::EducationalVideo(std::string id, std::string title, std::string author, int year,
                        int duration, std::string resolution, std::string subject, std::string language)
                :LibraryItem(id, title, author, year), durationMinutes(duration), resolution(resolution),
                subject(subject), language(language) {
                    lateFeePerDay = 1.0;
}

EducationalVideo::~EducationalVideo() {}

void EducationalVideo::displayInfo() const
{
    std::cout << "=== EDUCATIONAL VIDEO ===" << std::endl;
    std::cout << "ID: " << itemId << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Publication Year: " << publicationYear << std::endl;
    std::cout << "Duration: " << durationMinutes << std::endl;
    std::cout << "Subject: " << subject << std::endl;
    std::cout << "Language: " << language << std::endl;
}

double EducationalVideo::calculateLateFee(int daysLate) const
{
    return daysLate * lateFeePerDay;
}

std::string EducationalVideo::getItemType() const
{
    return "Educational Video";
}
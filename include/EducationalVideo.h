#ifndef EDUCATIONAL_VIDEO_H
#define EDUCATIONAL_VIDEO_H

#include "LibraryItem.h"

class EducationalVideo : public LibraryItem
{
    private:
        int durationMinutes;
        std::string resolution;
        std::string subject;
        std::string language;

    public:
        EducationalVideo(std::string id, std::string title, std::string author, int year,
                        int duration, std::string resolution, std::string subject, std::string language);

        ~EducationalVideo() override;

        void displayInfo() const override;
        double calculateLateFee(int daysLate) const override;
        std::string getItemType() const override;
};


#endif // EDUCATIONAL_VIDEO_H
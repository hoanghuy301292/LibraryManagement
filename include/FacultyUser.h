#ifndef FACULTYUSER_H
#define FACULTYUSER_H

#include "User.h"

class FacultyUser : public User {
private:
    std::string department;
    std::string position;

public:
    // Constructor
    FacultyUser(std::string id, std::string name, std::string email, std::string phone,
                std::string dept, std::string pos);
    
    // Override methods from User
    double getDiscountRate() const override;
    void displayUserInfo() const;
    
    // Faculty-specific getters
    std::string getDepartment() const;
    std::string getPosition() const;
    
    // Faculty-specific setters
    void setDepartment(std::string dept);
    void setPosition(std::string pos);
    
    // Faculty-specific utility methods
    bool isSeniorFaculty() const;
    bool isEligibleForExtendedLoan() const;
    double calculateDiscountedFine(double originalFine) const;
    void displayFacultyStatus() const;
    void requestResearchMaterial(std::string materialTitle, std::string materialType) const;
    void displayBorrowingStatistics() const;
    bool canRequestInterLibraryLoan() const;
    void displayFullProfile() const;
};

#endif
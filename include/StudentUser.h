#ifndef STUDENTUSER_H
#define STUDENTUSER_H

#include "User.h"

class StudentUser : public User {
private:
    std::string studentId;
    std::string major;
    int yearOfStudy;

public:
    // Constructor
    StudentUser(std::string id, std::string name, std::string email, std::string phone,
                std::string studId, std::string major, int year);
    
    // Override methods from User
    double getDiscountRate() const override;
    void displayUserInfo() const;
    
    // Student-specific getters
    std::string getStudentId() const;
    std::string getMajor() const;
    int getYearOfStudy() const;
    
    // Student-specific setters
    void setYearOfStudy(int year);
    
    // Student-specific utility methods
    bool isGraduatingSoon() const;
    double calculateDiscountedFine(double originalFine) const;
    void displayStudentStatus() const;
};

#endif
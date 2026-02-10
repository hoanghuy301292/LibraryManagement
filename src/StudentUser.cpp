#include "../include/StudentUser.h"
#include "../include/Transaction.h"
#include <iostream>

// Constructor
StudentUser::StudentUser(std::string id, std::string name, std::string email, std::string phone,
                         std::string studId, std::string maj, int year)
    : User(id, name, email, phone, 7),  // Students get limit of 7 books
      studentId(studId),
      major(maj),
      yearOfStudy(year) {
    
    std::cout << "Student user created: " << name 
         << " (Major: " << major << ", Year " << year << ")" << std::endl;
}

// Override: Get discount rate for students
double StudentUser::getDiscountRate() const {
    return 0.20;  // Students get 20% discount on late fees
}

// Override: Display user info with student-specific details
void StudentUser::displayUserInfo() const {
    std::cout << "========================================" << std::endl;
    std::cout << "STUDENT USER INFORMATION" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "User ID: " << userId << std::endl;
    std::cout << "Student ID: " << studentId << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Phone: " << phoneNumber << std::endl;
    std::cout << "Major: " << major << std::endl;
    std::cout << "Year of Study: " << yearOfStudy << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Borrow Limit: " << maxBorrowLimit << " items" << std::endl;
    std::cout << "Current Active Borrows: " << getCurrentBorrowCount() << std::endl;
    std::cout << "Total Fines: $" << totalFines << std::endl;
    std::cout << "Discount Rate: " << (getDiscountRate() * 100) << "%" << std::endl;
    std::cout << "Can Borrow: " << (canBorrow() ? "Yes" : "No") << std::endl;
    
    // Display borrow history
    if (borrowHistory.empty()) {
        std::cout << "\nNo borrowing history" << std::endl;
    } else {
        std::cout << "\n📚 Borrowing History (" << borrowHistory.size() 
             << " transactions):" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        
        for (size_t i = 0; i < borrowHistory.size(); i++) {
            std::cout << "[" << (i + 1) << "] ";
            borrowHistory[i]->displayTransactionInfo();
            std::cout << std::endl;
        }
    }
    
    // Student-specific recommendations
    if (totalFines > 0) {
        std::cout << "\n💡 Student Tip: Pay your fines early to maintain " 
             << "your borrowing privileges!" << std::endl;
    }
    
    if (getCurrentBorrowCount() >= maxBorrowLimit - 2) {
        std::cout << "\n⚠️  Warning: You're close to your borrow limit. "
             << "Consider returning some items." << std::endl;
    }
    
    std::cout << "========================================" << std::endl;
}

// Additional helper methods specific to students

// Get student ID
std::string StudentUser::getStudentId() const {
    return studentId;
}

// Get major
std::string StudentUser::getMajor() const {
    return major;
}

// Get year of study
int StudentUser::getYearOfStudy() const {
    return yearOfStudy;
}

// Update year of study (e.g., when student advances to next year)
void StudentUser::setYearOfStudy(int year) {
    if (year < 1 || year > 6) {  // Assuming max 6 years
        std::cout << "Invalid year of study. Must be between 1 and 6." << std::endl;
        return;
    }
    
    yearOfStudy = year;
    std::cout << "Year of study updated to: " << year << std::endl;
}

// Check if student is graduating soon (useful for notifications)
bool StudentUser::isGraduatingSoon() const {
    return yearOfStudy >= 4;  // Assuming 4-year program
}

// Calculate discounted fine amount
double StudentUser::calculateDiscountedFine(double originalFine) const {
    double discount = originalFine * getDiscountRate();
    double discountedAmount = originalFine - discount;
    
    std::cout << "Original Fine: $" << originalFine << std::endl;
    std::cout << "Student Discount (" << (getDiscountRate() * 100) 
         << "%): -$" << discount << std::endl;
    std::cout << "Amount to Pay: $" << discountedAmount << std::endl;
    
    return discountedAmount;
}

// Display student status summary
void StudentUser::displayStudentStatus() const {
    std::cout << "\n┌─────────────────────────────────────┐" << std::endl;
    std::cout << "│     STUDENT STATUS SUMMARY          │" << std::endl;
    std::cout << "├─────────────────────────────────────┤" << std::endl;
    std::cout << "│ Name: " << name << std::endl;
    std::cout << "│ ID: " << studentId << std::endl;
    std::cout << "│ Major: " << major << std::endl;
    std::cout << "│ Year: " << yearOfStudy << std::endl;
    std::cout << "├─────────────────────────────────────┤" << std::endl;
    std::cout << "│ Books Borrowed: " << getCurrentBorrowCount() 
         << "/" << maxBorrowLimit << std::endl;
    std::cout << "│ Outstanding Fines: $" << totalFines << std::endl;
    std::cout << "│ Status: " << (canBorrow() ? "✓ Active" : "✗ Restricted") << std::endl;
    std::cout << "└─────────────────────────────────────┘" << std::endl;
}
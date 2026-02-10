#include "../include/FacultyUser.h"
#include "../include/Transaction.h"
#include <iostream>

using namespace std;

// Constructor
FacultyUser::FacultyUser(std::string id, std::string name, std::string email, std::string phone,
                         std::string dept, std::string pos)
    : User(id, name, email, phone, 15),  // Faculty get limit of 15 books
      department(dept),
      position(pos) {
    
    std::cout << "Faculty user created: " << name 
         << " (" << position << ", " << department << " Department)" << std::endl;
}

// Override: Get discount rate for faculty
double FacultyUser::getDiscountRate() const {
    return 0.50;  // Faculty get 50% discount on late fees
}

// Override: Display user info with faculty-specific details
void FacultyUser::displayUserInfo() const {
    std::cout << "========================================" << std::endl;
    std::cout << "FACULTY USER INFORMATION" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "User ID: " << userId << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Position: " << position << std::endl;
    std::cout << "Department: " << department << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Phone: " << phoneNumber << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Borrow Limit: " << maxBorrowLimit << " items" << std::endl;
    std::cout << "Current Active Borrows: " << getCurrentBorrowCount() << std::endl;
    std::cout << "Total Fines: $" << totalFines << std::endl;
    std::cout << "Faculty Discount Rate: " << (getDiscountRate() * 100) << "%" << std::endl;
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
    
    // Faculty-specific recommendations
    if (totalFines > 0) {
        std::cout << "\n💼 Faculty Note: Remember to settle outstanding fines "
             << "to maintain your research privileges." << std::endl;
    }
    
    if (getCurrentBorrowCount() >= maxBorrowLimit - 3) {
        std::cout << "\n⚠️  Notice: Your borrowed items are approaching the limit. "
             << "Consider returning materials not currently in use." << std::endl;
    }
    
    // Special privileges note
    std::cout << "\n✨ Faculty Privileges:" << std::endl;
    std::cout << "   • Extended borrow limit (" << maxBorrowLimit << " items)" << std::endl;
    std::cout << "   • 50% discount on late fees" << std::endl;
    std::cout << "   • Priority access to new acquisitions" << std::endl;
    
    std::cout << "========================================" << std::endl;
}

// Get department
std::string FacultyUser::getDepartment() const {
    return department;
}

// Get position
std::string FacultyUser::getPosition() const {
    return position;
}

// Set department (for faculty transfers)
void FacultyUser::setDepartment(std::string dept) {
    if (dept.empty()) {
        std::cout << "Error: Department name cannot be empty." << std::endl;
        return;
    }
    
    std::string oldDept = department;
    department = dept;
    
    std::cout << "Department updated from '" << oldDept 
         << "' to '" << department << "'" << std::endl;
}

// Set position (for promotions)
void FacultyUser::setPosition(std::string pos) {
    if (pos.empty()) {
        std::cout << "Error: Position cannot be empty." << std::endl;
        return;
    }
    
    std::string oldPos = position;
    position = pos;
    
    std::cout << "Position updated from '" << oldPos 
         << "' to '" << position << "'" << std::endl;
    std::cout << "🎉 Congratulations on your new role!" << std::endl;
}

// Check if faculty member is senior (Professor or above)
bool FacultyUser::isSeniorFaculty() const {
    // Check if position contains "Professor" or senior titles
    return (position.find("Professor") != std::string::npos ||
            position.find("Dean") != std::string::npos ||
            position.find("Chair") != std::string::npos ||
            position.find("Director") != std::string::npos);
}

// Check if faculty is eligible for extended loan period
bool FacultyUser::isEligibleForExtendedLoan() const {
    // Senior faculty or those with good standing (low fines)
    return isSeniorFaculty() || (totalFines < 10.0);
}

// Calculate discounted fine amount with detailed breakdown
double FacultyUser::calculateDiscountedFine(double originalFine) const {
    double discount = originalFine * getDiscountRate();
    double discountedAmount = originalFine - discount;
    
    std::cout << "\n┌────────── FACULTY FINE CALCULATION ──────────┐" << std::endl;
    std::cout << "│ Original Fine:        $" << originalFine << std::endl;
    std::cout << "│ Faculty Discount (" << (getDiscountRate() * 100) 
         << "%):  -$" << discount << std::endl;
    std::cout << "├──────────────────────────────────────────────┤" << std::endl;
    std::cout << "│ Total Amount Due:     $" << discountedAmount << std::endl;
    std::cout << "└──────────────────────────────────────────────┘" << std::endl;
    
    return discountedAmount;
}

// Display faculty status summary
void FacultyUser::displayFacultyStatus() const {
    std::cout << "\n╔═════════════════════════════════════════════╗" << std::endl;
    std::cout << "║       FACULTY STATUS SUMMARY                ║" << std::endl;
    std::cout << "╠═════════════════════════════════════════════╣" << std::endl;
    std::cout << "║ Name:       " << name << std::endl;
    std::cout << "║ Position:   " << position << std::endl;
    std::cout << "║ Department: " << department << std::endl;
    std::cout << "╠═════════════════════════════════════════════╣" << std::endl;
    std::cout << "║ Items Borrowed: " << getCurrentBorrowCount() 
         << "/" << maxBorrowLimit << std::endl;
    std::cout << "║ Fines:          $" << totalFines << std::endl;
    std::cout << "║ Discount Rate:  " << (getDiscountRate() * 100) << "%" << std::endl;
    std::cout << "╠═════════════════════════════════════════════╣" << std::endl;
    std::cout << "║ Status:         " 
         << (canBorrow() ? "✓ Active & Good Standing" : "✗ Restricted") << std::endl;
    std::cout << "║ Seniority:      " 
         << (isSeniorFaculty() ? "✓ Senior Faculty" : "Regular Faculty") << std::endl;
    std::cout << "║ Extended Loan:  " 
         << (isEligibleForExtendedLoan() ? "✓ Eligible" : "✗ Not Eligible") << std::endl;
    std::cout << "╚═════════════════════════════════════════════╝" << std::endl;
}

// Request research materials (special faculty privilege)
void FacultyUser::requestResearchMaterial(std::string materialTitle, 
                                          std::string materialType) const {
    std::cout << "\n╔════════ RESEARCH MATERIAL REQUEST ════════╗" << std::endl;
    std::cout << "║ Requested by: " << name << std::endl;
    std::cout << "║ Position:     " << position << std::endl;
    std::cout << "║ Department:   " << department << std::endl;
    std::cout << "╟────────────────────────────────────────────╢" << std::endl;
    std::cout << "║ Material:     " << materialTitle << std::endl;
    std::cout << "║ Type:         " << materialType << std::endl;
    std::cout << "╟────────────────────────────────────────────╢" << std::endl;
    
    if (isSeniorFaculty()) {
        std::cout << "║ Priority:     🌟 HIGH (Senior Faculty)" << std::endl;
        std::cout << "║ Processing:   Expedited (2-3 business days)" << std::endl;
    } else {
        std::cout << "║ Priority:     STANDARD" << std::endl;
        std::cout << "║ Processing:   Regular (5-7 business days)" << std::endl;
    }
    
    std::cout << "╚════════════════════════════════════════════╝" << std::endl;
    std::cout << "Request submitted successfully!" << std::endl;
}

// Generate borrowing statistics for faculty member
void FacultyUser::displayBorrowingStatistics() const {
    int totalBorrowed = borrowHistory.size();
    int currentlyBorrowed = getCurrentBorrowCount();
    int returned = totalBorrowed - currentlyBorrowed;
    
    int overdueCount = 0;
    for (Transaction* trans : borrowHistory) {
        if (trans != nullptr && trans->isOverdue() && !trans->isReturned()) {
            overdueCount++;
        }
    }
    
    std::cout << "\n╔════════ BORROWING STATISTICS ════════╗" << std::endl;
    std::cout << "║ Faculty: " << name << std::endl;
    std::cout << "╠═══════════════════════════════════════╣" << std::endl;
    std::cout << "║ Total Transactions:    " << totalBorrowed << std::endl;
    std::cout << "║ Currently Borrowed:    " << currentlyBorrowed << std::endl;
    std::cout << "║ Returned:              " << returned << std::endl;
    std::cout << "║ Currently Overdue:     " << overdueCount << std::endl;
    std::cout << "╠═══════════════════════════════════════╣" << std::endl;
    
    // Calculate return rate
    if (totalBorrowed > 0) {
        double returnRate = (static_cast<double>(returned) / totalBorrowed) * 100;
        std::cout << "║ Return Rate:           " << returnRate << "%" << std::endl;
    }
    
    // Calculate average fine per transaction
    if (totalBorrowed > 0) {
        double avgFine = totalFines / totalBorrowed;
        std::cout << "║ Avg Fine/Transaction:  $" << avgFine << std::endl;
    }
    
    std::cout << "╚═══════════════════════════════════════╝" << std::endl;
    
    // Performance assessment
    std::cout << "\n📊 Performance Assessment: ";
    if (totalFines == 0 && overdueCount == 0) {
        std::cout << "⭐ EXCELLENT - Perfect record!" << std::endl;
    } else if (totalFines < 5.0 && overdueCount <= 1) {
        std::cout << "✅ GOOD - Responsible borrower" << std::endl;
    } else if (totalFines < 20.0) {
        std::cout << "⚠️  FAIR - Please return items on time" << std::endl;
    } else {
        std::cout << "❌ NEEDS IMPROVEMENT - Multiple overdue items" << std::endl;
    }
}

// Check if faculty can request inter-library loan
bool FacultyUser::canRequestInterLibraryLoan() const {
    // Requirements: Good standing, low fines, not at borrow limit
    return canBorrow() && 
           totalFines < 25.0 && 
           getCurrentBorrowCount() < maxBorrowLimit - 2;
}

// Display full faculty profile
void FacultyUser::displayFullProfile() const {
    std::cout << "\n";
    std::cout << "╔═══════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              FACULTY MEMBER PROFILE                   ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════════════╝" << std::endl;
    
    // Basic info
    displayUserInfo();
    
    // Statistics
    std::cout << std::endl;
    displayBorrowingStatistics();
    
    // Status
    std::cout << std::endl;
    displayFacultyStatus();
    
    // Additional privileges
    std::cout << "\n📋 Additional Privileges & Services:" << std::endl;
    std::cout << "   • Inter-library Loan: " 
         << (canRequestInterLibraryLoan() ? "✓ Available" : "✗ Not Available") << std::endl;
    std::cout << "   • Research Consultation: ✓ Available" << std::endl;
    std::cout << "   • Private Study Room: ✓ Reservable" << std::endl;
    std::cout << "   • Digital Archive Access: ✓ Full Access" << std::endl;
}
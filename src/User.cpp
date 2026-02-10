#include "../include/User.h"
#include "../include/Transaction.h"
#include <iostream>
// #include <algorithm>

using namespace std;

// Constructor
User::User(std::string id, std::string n, std::string em, std::string phone, int limit)
    : userId(id), name(n), email(em), phoneNumber(phone), 
      maxBorrowLimit(limit), totalFines(0.0) {
    // borrowHistory vector is automatically initialized as empty
}

// Copy Constructor (Deep Copy)
User::User(const User& other) 
    : userId(other.userId), 
      name(other.name),
      email(other.email),
      phoneNumber(other.phoneNumber),
      maxBorrowLimit(other.maxBorrowLimit),
      totalFines(other.totalFines) {
    
    // Deep copy of borrowHistory
    // Note: We're copying pointers, not creating new Transaction objects
    // If you need true deep copy, you'd need to clone Transaction objects
    borrowHistory = other.borrowHistory;
    
    std::cout << "User copy constructor called for: " << name << std::endl;
}

// Destructor
User::~User() {
    // Note: We don't delete Transaction* pointers here
    // because Library class owns and manages Transaction objects
    // User only holds references to them
    borrowHistory.clear();
    
    std::cout << "User destructor called for: " << name << std::endl;
}

// Check if user can borrow more items
bool User::canBorrow() const {
    // Count only active (unreturned) transactions
    int activeBorrows = getCurrentBorrowCount();
    
    // Check borrow limit
    if (activeBorrows >= maxBorrowLimit) {
        return false;
    }
    
    // Optional: Check if user has outstanding fines
    // Some libraries don't allow borrowing if fines exceed certain amount
    const double MAX_ALLOWED_FINES = 50.0;
    if (totalFines > MAX_ALLOWED_FINES) {
        return false;
    }
    
    return true;
}

// Add a transaction to user's history
void User::addTransaction(Transaction* trans) {
    if (trans == nullptr) {
        cerr << "Error: Attempted to add null transaction" << std::endl;
        return;
    }
    
    borrowHistory.push_back(trans);
    std::cout << "Transaction added to " << name << "'s history" << std::endl;
}

// Pay fine
void User::payFine(double amount) {
    if (amount <= 0) {
        std::cout << "Invalid payment amount" << std::endl;
        return;
    }
    
    if (amount > totalFines) {
        std::cout << "Payment amount exceeds total fines" << std::endl;
        std::cout << "Total fines: $" << totalFines << std::endl;
        std::cout << "Payment amount: $" << amount << std::endl;
        return;
    }
    
    totalFines -= amount;
    std::cout << "Payment of $" << amount << " received" << std::endl;
    std::cout << "Remaining fines: $" << totalFines << std::endl;
}

// Display user information
void User::displayUserInfo() const {
    std::cout << "========================================" << std::endl;
    std::cout << "USER INFORMATION" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "User ID: " << userId << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "Phone: " << phoneNumber << std::endl;
    std::cout << "Borrow Limit: " << maxBorrowLimit << std::endl;
    std::cout << "Current Active Borrows: " << getCurrentBorrowCount() << std::endl;
    std::cout << "Total Fines: $" << totalFines << std::endl;
    std::cout << "Can Borrow: " << (canBorrow() ? "Yes" : "No") << std::endl;
    
    // Display borrow history
    if (borrowHistory.empty()) {
        std::cout << "\nNo borrowing history" << std::endl;
    } else {
        std::cout << "\nBorrowing History (" << borrowHistory.size() << " transactions):" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        
        for (size_t i = 0; i < borrowHistory.size(); i++) {
            std::cout << (i + 1) << ". ";
            borrowHistory[i]->displayTransactionInfo();
            std::cout << std::endl;
        }
    }
    std::cout << "========================================" << std::endl;
}

// Get current number of active (unreturned) borrows
int User::getCurrentBorrowCount() const {
    int count = 0;
    
    for (Transaction* trans : borrowHistory) {
        if (trans != nullptr && !trans->isReturned()) {
            count++;
        }
    }
    
    return count;
}

// Getter: User ID
std::string User::getUserId() const {
    return userId;
}

// Getter: Name
std::string User::getName() const {
    return name;
}

// Getter: Total Fines
double User::getTotalFines() const {
    return totalFines;
}

// Virtual method for discount rate (can be overridden by derived classes)
double User::getDiscountRate() const {
    return 0.0;  // Regular users get no discount (0%)
}
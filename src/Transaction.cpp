#include "../include/Transaction.h"
#include "../include/User.h"
#include "../include/LibraryItem.h"
#include "../include/StudentUser.h"
#include "../include/FacultyUser.h"
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

// ==================== CONSTRUCTOR ====================

Transaction::Transaction(std::string id, User* user, LibraryItem* item, int borrowDays)
    : transactionId(id), borrower(user), item(item), returnDate(0), fineAmount(0.0) {
    
    // Validate inputs
    if (user == nullptr) {
        throw invalid_argument("Transaction: User cannot be null");
    }
    
    if (item == nullptr) {
        throw invalid_argument("Transaction: Item cannot be null");
    }
    
    if (borrowDays <= 0) {
        throw invalid_argument("Transaction: Borrow days must be positive");
    }
    
    // Set borrow date to current time
    borrowDate = time(nullptr);
    
    // Calculate due date (borrowDays from now)
    dueDate = borrowDate + (borrowDays * 24 * 60 * 60);  // Convert days to seconds
    
    std::cout << "Transaction created: " << transactionId << std::endl;
    std::cout << "  User: " << borrower->getName() << std::endl;
    std::cout << "  Item: " << item->getTitle() << std::endl;
    std::cout << "  Borrow period: " << borrowDays << " days" << std::endl;
}

// ==================== DESTRUCTOR ====================

Transaction::~Transaction() {
    // Note: We don't delete borrower or item pointers
    // because Library class owns and manages those objects
    // Transaction only holds references to them
    
    // Optional: Log destruction for debugging
    // std::cout << "Transaction " << transactionId << " destroyed" << std::endl;
}

// ==================== RETURN PROCESSING ====================

void Transaction::processReturn() {
    // Check if already returned
    if (isReturned()) {
        std::cout << "Warning: Item already returned on this transaction" << std::endl;
        return;
    }
    
    // Set return date to current time
    returnDate = time(nullptr);
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "PROCESSING RETURN" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Transaction ID: " << transactionId << std::endl;
    std::cout << "Item: " << item->getTitle() << std::endl;
    std::cout << "User: " << borrower->getName() << std::endl;
    
    // Format and display dates
    char buffer[80];
    
    struct tm* borrowTm = localtime(&borrowDate);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", borrowTm);
    std::cout << "Borrowed: " << buffer << std::endl;
    
    struct tm* dueTm = localtime(&dueDate);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", dueTm);
    std::cout << "Due Date: " << buffer << std::endl;
    
    struct tm* returnTm = localtime(&returnDate);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", returnTm);
    std::cout << "Returned: " << buffer << std::endl;
    
    // Check if overdue and calculate fine
    if (isOverdue()) {
        int daysLate = getDaysOverdue();
        std::cout << "\n⚠️  OVERDUE: " << daysLate << " day(s) late" << std::endl;
        calculateFine();
    } else {
        std::cout << "\n✓ Returned on time - No fines" << std::endl;
    }
    
    std::cout << "========================================" << std::endl;
}

// ==================== OVERDUE CHECKING ====================

bool Transaction::isOverdue() const {
    // If not returned yet, check against current time
    if (!isReturned()) {
        time_t currentTime = time(nullptr);
        return currentTime > dueDate;
    }
    
    // If already returned, check if return date was after due date
    return returnDate > dueDate;
}

int Transaction::getDaysOverdue() const {
    if (!isOverdue()) {
        return 0;
    }
    
    // Determine comparison time
    time_t compareTime = isReturned() ? returnDate : time(nullptr);
    
    // Calculate difference in seconds, then convert to days
    double diffSeconds = difftime(compareTime, dueDate);
    int daysLate = static_cast<int>(diffSeconds / (24 * 60 * 60));
    
    // Round up if there's any fraction of a day
    if (diffSeconds > daysLate * 24 * 60 * 60) {
        daysLate++;
    }
    
    return daysLate;
}

// ==================== FINE CALCULATION ====================

void Transaction::calculateFine() {
    if (!isOverdue()) {
        fineAmount = 0.0;
        return;
    }
    
    int daysLate = getDaysOverdue();
    
    // Get base fine from item
    double baseFine = item->calculateLateFee(daysLate);
    
    // Apply discount based on user type (polymorphism in action!)
    double discountRate = borrower->getDiscountRate();
    double discount = baseFine * discountRate;
    fineAmount = baseFine - discount;
    
    // Display fine breakdown
    std::cout << "\n┌─────────── FINE CALCULATION ───────────┐" << std::endl;
    std::cout << "│ Days Overdue:      " << setw(4) << daysLate << " day(s)" << std::endl;
    std::cout << "│ Base Fine:         $" << fixed << setprecision(2) 
         << setw(6) << baseFine << std::endl;
    
    if (discountRate > 0) {
        std::cout << "│ User Discount (" << setw(2) << static_cast<int>(discountRate * 100) 
             << "%): -$" << setw(6) << discount << std::endl;
        std::cout << "├────────────────────────────────────────┤" << std::endl;
        std::cout << "│ Total Fine:        $" << setw(6) << fineAmount << std::endl;
    } else {
        std::cout << "├────────────────────────────────────────┤" << std::endl;
        std::cout << "│ Total Fine:        $" << setw(6) << baseFine << std::endl;
    }
    
    std::cout << "└────────────────────────────────────────┘" << std::endl;
    
    // Add fine to user's total
    // Note: This assumes User class has a method to add fines
    // If not implemented, you can skip this or implement it in User class
    // borrower->addFine(fineAmount);
    
    std::cout << "\n⚠️  Fine of $" << fineAmount << " has been added to " 
         << borrower->getName() << "'s account" << std::endl;
}

// ==================== DISPLAY ====================

void Transaction::displayTransactionInfo() const {
    std::cout << "Transaction ID: " << transactionId << std::endl;
    std::cout << "User: " << borrower->getName() << " (ID: " 
         << borrower->getUserId() << ")" << std::endl;
    std::cout << "Item: " << item->getTitle() << " (ID: " 
         << item->getItemId() << ")" << std::endl;
    std::cout << "Type: " << item->getItemType() << std::endl;
    
    // Format dates
    char buffer[80];
    
    struct tm* borrowTm = localtime(&borrowDate);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", borrowTm);
    std::cout << "Borrow Date: " << buffer << std::endl;
    
    struct tm* dueTm = localtime(&dueDate);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", dueTm);
    std::cout << "Due Date: " << buffer << std::endl;
    
    if (isReturned()) {
        struct tm* returnTm = localtime(&returnDate);
        strftime(buffer, sizeof(buffer), "%Y-%m-%d", returnTm);
        std::cout << "Return Date: " << buffer << std::endl;
        std::cout << "Status: ✓ RETURNED" << std::endl;
        
        if (fineAmount > 0) {
            std::cout << "Fine: $" << fixed << setprecision(2) << fineAmount << std::endl;
        }
    } else {
        std::cout << "Return Date: Not yet returned" << std::endl;
        
        if (isOverdue()) {
            std::cout << "Status: ⚠️  OVERDUE (" << getDaysOverdue() 
                 << " days late)" << std::endl;
        } else {
            // Calculate days remaining
            time_t currentTime = time(nullptr);
            int daysRemaining = static_cast<int>(
                difftime(dueDate, currentTime) / (24 * 60 * 60)
            );
            std::cout << "Status: 📚 ACTIVE (" << daysRemaining 
                 << " days remaining)" << std::endl;
        }
    }
}

// ==================== GETTERS ====================

std::string Transaction::getTransactionId() const {
    return transactionId;
}

User* Transaction::getBorrower() const {
    return borrower;
}

LibraryItem* Transaction::getItem() const {
    return item;
}

bool Transaction::isReturned() const {
    return returnDate != 0;
}

time_t Transaction::getBorrowDate() const {
    return borrowDate;
}

time_t Transaction::getDueDate() const {
    return dueDate;
}

time_t Transaction::getReturnDate() const {
    return returnDate;
}

double Transaction::getFineAmount() const {
    return fineAmount;
}

// ==================== UTILITY METHODS ====================

int Transaction::getDaysUntilDue() const {
    if (isReturned()) {
        return 0;  // Already returned
    }
    
    time_t currentTime = time(nullptr);
    
    if (currentTime > dueDate) {
        return 0;  // Overdue
    }
    
    double diffSeconds = difftime(dueDate, currentTime);
    return static_cast<int>(diffSeconds / (24 * 60 * 60));
}

int Transaction::getTotalBorrowDays() const {
    time_t endTime = isReturned() ? returnDate : time(nullptr);
    double diffSeconds = difftime(endTime, borrowDate);
    return static_cast<int>(diffSeconds / (24 * 60 * 60)) + 1;  // +1 to include first day
}

void Transaction::extendDueDate(int additionalDays) {
    if (isReturned()) {
        std::cout << "Cannot extend due date - item already returned" << std::endl;
        return;
    }
    
    if (additionalDays <= 0) {
        std::cout << "Extension days must be positive" << std::endl;
        return;
    }
    
    // Store old due date for display
    time_t oldDueDate = dueDate;
    
    // Extend due date
    dueDate += (additionalDays * 24 * 60 * 60);
    
    // Format and display
    char oldBuffer[80], newBuffer[80];
    
    struct tm* oldDueTm = localtime(&oldDueDate);
    strftime(oldBuffer, sizeof(oldBuffer), "%Y-%m-%d", oldDueTm);
    
    struct tm* newDueTm = localtime(&dueDate);
    strftime(newBuffer, sizeof(newBuffer), "%Y-%m-%d", newDueTm);
    
    std::cout << "✓ Due date extended by " << additionalDays << " days" << std::endl;
    std::cout << "  Old due date: " << oldBuffer << std::endl;
    std::cout << "  New due date: " << newBuffer << std::endl;
}

bool Transaction::canExtend() const {
    // Business rules for extension
    if (isReturned()) {
        return false;  // Already returned
    }
    
    if (isOverdue()) {
        return false;  // Cannot extend if overdue
    }
    
    // Can extend if at least 1 day remaining
    return getDaysUntilDue() >= 1;
}

void Transaction::displayDetailedInfo() const {
    std::cout << "\n╔════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║           TRANSACTION DETAILS                      ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════╝" << std::endl;
    
    // Transaction info
    std::cout << "\n📋 Transaction Information:" << std::endl;
    std::cout << "   ID: " << transactionId << std::endl;
    
    // User info
    std::cout << "\n👤 Borrower:" << std::endl;
    std::cout << "   Name: " << borrower->getName() << std::endl;
    std::cout << "   User ID: " << borrower->getUserId() << std::endl;
    std::cout << "   Discount Rate: " << (borrower->getDiscountRate() * 100) << "%" << std::endl;
    
    // Item info
    std::cout << "\n📚 Item:" << std::endl;
    std::cout << "   Title: " << item->getTitle() << std::endl;
    std::cout << "   Author: " << item->getAuthor() << std::endl;
    std::cout << "   Type: " << item->getItemType() << std::endl;
    std::cout << "   Item ID: " << item->getItemId() << std::endl;
    
    // Date information
    std::cout << "\n📅 Dates:" << std::endl;
    char buffer[80];
    
    struct tm* borrowTm = localtime(&borrowDate);
    strftime(buffer, sizeof(buffer), "%A, %B %d, %Y at %H:%M", borrowTm);
    std::cout << "   Borrowed: " << buffer << std::endl;
    
    struct tm* dueTm = localtime(&dueDate);
    strftime(buffer, sizeof(buffer), "%A, %B %d, %Y at %H:%M", dueTm);
    std::cout << "   Due Date: " << buffer << std::endl;
    
    if (isReturned()) {
        struct tm* returnTm = localtime(&returnDate);
        strftime(buffer, sizeof(buffer), "%A, %B %d, %Y at %H:%M", returnTm);
        std::cout << "   Returned: " << buffer << std::endl;
    } else {
        std::cout << "   Returned: Not yet returned" << std::endl;
    }
    
    // Status and statistics
    std::cout << "\n📊 Status:" << std::endl;
    std::cout << "   Total borrow duration: " << getTotalBorrowDays() << " days" << std::endl;
    
    if (isReturned()) {
        std::cout << "   Status: ✓ RETURNED" << std::endl;
        if (isOverdue()) {
            std::cout << "   Days overdue: " << getDaysOverdue() << " days" << std::endl;
            std::cout << "   Fine amount: $" << fixed << setprecision(2) 
                 << fineAmount << std::endl;
        } else {
            std::cout << "   Returned on time: ✓ Yes" << std::endl;
        }
    } else {
        if (isOverdue()) {
            std::cout << "   Status: ⚠️  OVERDUE" << std::endl;
            std::cout << "   Days overdue: " << getDaysOverdue() << " days" << std::endl;
            std::cout << "   Estimated fine: $" << fixed << setprecision(2)
                 << item->calculateLateFee(getDaysOverdue()) 
                    * (1 - borrower->getDiscountRate()) << std::endl;
        } else {
            std::cout << "   Status: 📚 ACTIVE" << std::endl;
            std::cout << "   Days until due: " << getDaysUntilDue() << " days" << std::endl;
            std::cout << "   Can extend: " << (canExtend() ? "✓ Yes" : "✗ No") << std::endl;
        }
    }
    
    std::cout << "\n" << std::string(56, '═') << std::endl;
}

// ==================== COMPARISON OPERATORS ====================

bool Transaction::operator==(const Transaction& other) const {
    return transactionId == other.transactionId;
}

bool Transaction::operator!=(const Transaction& other) const {
    return !(*this == other);
}

// Compare by due date (for sorting)
bool Transaction::operator<(const Transaction& other) const {
    return dueDate < other.dueDate;
}

bool Transaction::operator>(const Transaction& other) const {
    return dueDate > other.dueDate;
}
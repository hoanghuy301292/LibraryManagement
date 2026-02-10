#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

// Forward declarations
class User;
class LibraryItem;

class Transaction {
private:
    std::string transactionId;
    User* borrower;           // Pointer to borrower (not owned)
    LibraryItem* item;        // Pointer to item (not owned)
    time_t borrowDate;        // When item was borrowed
    time_t dueDate;           // When item should be returned
    time_t returnDate;        // When item was actually returned (0 if not returned)
    double fineAmount;        // Fine amount if overdue

public:
    // ==================== CONSTRUCTOR & DESTRUCTOR ====================
    
    /**
     * Create a new transaction
     * @param id Transaction ID
     * @param user Pointer to borrowing user
     * @param item Pointer to borrowed item
     * @param borrowDays Number of days for the loan period
     * @throws invalid_argument if user or item is null, or borrowDays <= 0
     */
    Transaction(std::string id, User* user, LibraryItem* item, int borrowDays = 14);
    
    /**
     * Destructor - does not delete user or item (Library owns them)
     */
    ~Transaction();
    
    // ==================== RETURN PROCESSING ====================
    
    /**
     * Process the return of the item
     * Sets return date, calculates fines if overdue
     */
    void processReturn();
    
    // ==================== OVERDUE CHECKING ====================
    
    /**
     * Check if transaction is overdue
     * @return true if past due date, false otherwise
     */
    bool isOverdue() const;
    
    /**
     * Get number of days overdue
     * @return Number of days past due date (0 if not overdue)
     */
    int getDaysOverdue() const;
    
    /**
     * Get number of days until due date
     * @return Number of days remaining (0 if overdue or returned)
     */
    int getDaysUntilDue() const;
    
    // ==================== FINE CALCULATION ====================
    
    /**
     * Calculate and apply late fee
     * Considers item type and user discount rate
     */
    void calculateFine();
    
    // ==================== DISPLAY ====================
    
    /**
     * Display basic transaction information
     */
    void displayTransactionInfo() const;
    
    /**
     * Display comprehensive transaction details
     */
    void displayDetailedInfo() const;
    
    // ==================== GETTERS ====================
    
    std::string getTransactionId() const;
    User* getBorrower() const;
    LibraryItem* getItem() const;
    bool isReturned() const;
    time_t getBorrowDate() const;
    time_t getDueDate() const;
    time_t getReturnDate() const;
    double getFineAmount() const;
    
    // ==================== UTILITY METHODS ====================
    
    /**
     * Get total number of days item has been/was borrowed
     * @return Total borrow duration in days
     */
    int getTotalBorrowDays() const;
    
    /**
     * Extend the due date
     * @param additionalDays Number of days to extend
     */
    void extendDueDate(int additionalDays);
    
    /**
     * Check if transaction can be extended
     * @return true if extension is allowed, false otherwise
     */
    bool canExtend() const;
    
    // ==================== OPERATORS ====================
    
    bool operator==(const Transaction& other) const;
    bool operator!=(const Transaction& other) const;
    bool operator<(const Transaction& other) const;   // Compare by due date
    bool operator>(const Transaction& other) const;
};

#endif
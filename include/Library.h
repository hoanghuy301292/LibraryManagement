#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "LibraryItem.h"
#include "User.h"
#include "Transaction.h"

using namespace std;

class Library {
private:
    // Singleton instance
    static Library* instance;
    
    // Collections
    std::vector<LibraryItem*> items;
    std::vector<User*> users;
    std::vector<Transaction*> transactions;
    
    // Private constructor for Singleton pattern
    Library();
    
    // Prevent copying
    Library(const Library&) = delete;
    Library& operator=(const Library&) = delete;

public:
    // Singleton access
    static Library* getInstance();
    
    // Destructor
    ~Library();
    
    // ==================== ITEM MANAGEMENT ====================
    
    /**
     * Add a new item to the library catalog
     * @param item Pointer to LibraryItem (Book, Magazine, or EducationalVideo)
     */
    void addItem(LibraryItem* item);
    
    /**
     * Search for an item by its unique ID
     * @param id Item ID to search for
     * @return Pointer to LibraryItem if found
     * @throws ItemNotFoundException if item not found
     */
    LibraryItem* searchItemById(std::string id);
    
    /**
     * Search for items by title (partial match, case-insensitive)
     * @param keyword Keyword to search in titles
     * @return Vector of matching LibraryItem pointers
     */
    std::vector<LibraryItem*> searchByTitle(std::string keyword) const;
    
    /**
     * Search for items by author (partial match, case-insensitive)
     * @param author Author name to search for
     * @return Vector of matching LibraryItem pointers
     */
    std::vector<LibraryItem*> searchByAuthor(std::string author) const;
    
    /**
     * Search for items by type
     * @param type Item type: "Book", "Magazine", or "EducationalVideo"
     * @return Vector of matching LibraryItem pointers
     */
    std::vector<LibraryItem*> searchByType(std::string type) const;
    
    /**
     * Get all available (not borrowed) items
     * @return Vector of available LibraryItem pointers
     */
    std::vector<LibraryItem*> getAvailableItems() const;
    
    /**
     * Display all items in the library catalog
     * Grouped by type (Books, Magazines, Videos)
     */
    void displayAllItems() const;
    
    /**
     * Remove an item from the library
     * @param itemId ID of item to remove
     * @return true if removed successfully, false otherwise
     * @note Cannot remove items that are currently borrowed
     */
    bool removeItem(std::string itemId);
    
    // ==================== USER MANAGEMENT ====================
    
    /**
     * Register a new user in the library system
     * @param user Pointer to User (User, StudentUser, or FacultyUser)
     */
    void addUser(User* user);
    
    /**
     * Search for a user by their unique ID
     * @param id User ID to search for
     * @return Pointer to User if found
     * @throws UserNotFoundException if user not found
     */
    User* searchUserById(std::string id);
    
    /**
     * Display all registered users
     * Shows detailed information for each user
     */
    void displayAllUsers() const;
    
    /**
     * Remove a user from the library system
     * @param userId ID of user to remove
     * @return true if removed successfully, false otherwise
     * @note Cannot remove users with active transactions
     */
    bool removeUser(std::string userId);
    
    // ==================== TRANSACTION MANAGEMENT ====================
    
    /**
     * Process a borrow transaction
     * @param userId ID of user borrowing the item
     * @param itemId ID of item to borrow
     * @param days Number of days for the loan period (default: 14)
     * @return Pointer to created Transaction
     * @throws UserNotFoundException if user not found
     * @throws ItemNotFoundException if item not found
     * @throws BorrowLimitExceededException if user at borrow limit
     * @throws ItemNotAvailableException if item is already borrowed
     */
    Transaction* borrowItem(std::string userId, std::string itemId, int days = 14);
    
    /**
     * Process a return transaction
     * @param transactionId ID of transaction to process
     * @return true if returned successfully, false otherwise
     * Automatically calculates fines if overdue
     */
    bool returnItem(std::string transactionId);
    
    /**
     * Display all overdue transactions
     * Shows items that are past due date and not yet returned
     */
    void displayOverdueTransactions() const;
    
    /**
     * Get all active transactions for a specific user
     * @param userId ID of user
     * @return Vector of active (unreturned) Transaction pointers
     */
    std::vector<Transaction*> getUserActiveTransactions(std::string userId) const;
    
    // ==================== STATISTICS & REPORTING ====================
    
    /**
     * Get total number of items in library
     * @return Total item count
     */
    int getTotalItems() const;
    
    /**
     * Get total number of registered users
     * @return Total user count
     */
    int getTotalUsers() const;
    
    /**
     * Get total number of transactions (all time)
     * @return Total transaction count
     */
    int getTotalTransactions() const;
    
    /**
     * Get number of currently available items
     * @return Count of items not borrowed
     */
    int getAvailableItemsCount() const;
    
    /**
     * Get number of currently borrowed items
     * @return Count of items currently on loan
     */
    int getBorrowedItemsCount() const;
    
    /**
     * Display comprehensive library statistics
     * Shows collection stats, user stats, and transaction stats
     */
    void displayStatistics() const;
    
    /**
     * Generate complete library report
     * Includes statistics, collection breakdown, and overdue items
     */
    void generateReport() const;
    
    // ==================== HELPER METHODS ====================
    
    /**
     * Get direct access to items std::vector (for advanced operations)
     * @return Const reference to items std::vector
     */
    const std::vector<LibraryItem*>& getItems() const;
    
    /**
     * Get direct access to users std::vector (for advanced operations)
     * @return Const reference to users std::vector
     */
    const std::vector<User*>& getUsers() const;
    
    /**
     * Get direct access to transactions std::vector (for advanced operations)
     * @return Const reference to transactions std::vector
     */
    const std::vector<Transaction*>& getTransactions() const;
};

#endif
#include "../include/Library.h"
#include "../include/Book.h"
#include "../include/Magazine.h"
#include "../include/EducationalVideo.h"
#include "../include/LibraryException.h"
#include <iostream>
#include <algorithm>

using namespace std;

// Initialize static member
Library* Library::instance = nullptr;

// Private Constructor (Singleton Pattern)
Library::Library() {
    std::cout << "Library System initialized successfully!" << std::endl;
    std::cout << "========================================" << std::endl;
}

// Destructor - Clean up all dynamically allocated memory
Library::~Library() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "Shutting down Library System..." << std::endl;
    std::cout << "========================================" << std::endl;
    
    // Delete all transactions
    std::cout << "Cleaning up " << transactions.size() << " transactions..." << std::endl;
    for (Transaction* trans : transactions) {
        delete trans;
    }
    transactions.clear();
    
    // Delete all users
    std::cout << "Cleaning up " << users.size() << " users..." << std::endl;
    for (User* user : users) {
        delete user;
    }
    users.clear();
    
    // Delete all items
    std::cout << "Cleaning up " << items.size() << " library items..." << std::endl;
    for (LibraryItem* item : items) {
        delete item;
    }
    items.clear();
    
    std::cout << "Library System shut down successfully." << std::endl;
    std::cout << "========================================" << std::endl;
}

// Get Singleton Instance
Library* Library::getInstance() {
    if (instance == nullptr) {
        instance = new Library();
    }
    return instance;
}

// ==================== ITEM MANAGEMENT ====================

// Add item to library
void Library::addItem(LibraryItem* item) {
    if (item == nullptr) {
        std::cerr << "Error: Cannot add null item to library" << std::endl;
        return;
    }
    
    // Check for duplicate ID
    for (LibraryItem* existingItem : items) {
        if (existingItem->getItemId() == item->getItemId()) {
            std::cerr << "Error: Item with ID '" << item->getItemId() 
                 << "' already exists" << std::endl;
            return;
        }
    }
    
    items.push_back(item);
    std::cout << "✓ Added " << item->getItemType() << ": " 
         << item->getTitle() << " (ID: " << item->getItemId() << ")" << std::endl;
}

// Search item by ID
LibraryItem* Library::searchItemById(std::string id) {
    for (LibraryItem* item : items) {
        if (item->getItemId() == id) {
            return item;
        }
    }
    
    // Not found - throw exception
    throw ItemNotFoundException("Item with ID '" + id + "' not found");
}

// Search items by title (partial match, case-insensitive)
vector<LibraryItem*> Library::searchByTitle(std::string keyword) const {
    vector<LibraryItem*> results;
    
    // Convert keyword to lowercase for case-insensitive search
    std::string lowerKeyword = keyword;
    transform(lowerKeyword.begin(), lowerKeyword.end(), 
              lowerKeyword.begin(), ::tolower);
    
    for (LibraryItem* item : items) {
        std::string title = item->getTitle();
        // Convert title to lowercase
        transform(title.begin(), title.end(), title.begin(), ::tolower);
        
        // Check if keyword is found in title
        if (title.find(lowerKeyword) != std::string::npos) {
            results.push_back(item);
        }
    }
    
    return results;
}

// Search items by author (partial match, case-insensitive)
vector<LibraryItem*> Library::searchByAuthor(std::string author) const {
    vector<LibraryItem*> results;
    
    // Convert author to lowercase
    std::string lowerAuthor = author;
    transform(lowerAuthor.begin(), lowerAuthor.end(), 
              lowerAuthor.begin(), ::tolower);
    
    for (LibraryItem* item : items) {
        std::string itemAuthor = item->getAuthor();
        // Convert to lowercase
        transform(itemAuthor.begin(), itemAuthor.end(), 
                  itemAuthor.begin(), ::tolower);
        
        // Check if author is found
        if (itemAuthor.find(lowerAuthor) != std::string::npos) {
            results.push_back(item);
        }
    }
    
    return results;
}

// Display all items in library
void Library::displayAllItems() const {
    if (items.empty()) {
        std::cout << "📚 Library is currently empty." << std::endl;
        return;
    }
    
    std::cout << "\n╔════════════════════════════════════════════╗" << std::endl;
    std::cout << "║       LIBRARY CATALOG (" << items.size() << " items)        ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════╝" << std::endl;
    
    // Group items by type
    int bookCount = 0, magCount = 0, videoCount = 0;
    
    std::cout << "\n📖 BOOKS:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    for (LibraryItem* item : items) {
        if (item->getItemType() == "Book") {
            item->displayInfo();
            std::cout << std::endl;
            bookCount++;
        }
    }
    if (bookCount == 0) std::cout << "  No books available." << std::endl;
    
    std::cout << "\n📰 MAGAZINES:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    for (LibraryItem* item : items) {
        if (item->getItemType() == "Magazine") {
            item->displayInfo();
            std::cout << std::endl;
            magCount++;
        }
    }
    if (magCount == 0) std::cout << "  No magazines available." << std::endl;
    
    std::cout << "\n🎬 EDUCATIONAL VIDEOS:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    for (LibraryItem* item : items) {
        if (item->getItemType() == "EducationalVideo") {
            item->displayInfo();
            std::cout << std::endl;
            videoCount++;
        }
    }
    if (videoCount == 0) std::cout << "  No videos available." << std::endl;
    
    std::cout << "\n📊 Summary: " << bookCount << " Books, " 
         << magCount << " Magazines, " << videoCount << " Videos" << std::endl;
}

// ==================== USER MANAGEMENT ====================

// Add user to library
void Library::addUser(User* user) {
    if (user == nullptr) {
        std::cerr << "Error: Cannot add null user to library" << std::endl;
        return;
    }
    
    // Check for duplicate ID
    for (User* existingUser : users) {
        if (existingUser->getUserId() == user->getUserId()) {
            std::cerr << "Error: User with ID '" << user->getUserId() 
                 << "' already exists" << std::endl;
            return;
        }
    }
    
    users.push_back(user);
    std::cout << "✓ User registered: " << user->getName() 
         << " (ID: " << user->getUserId() << ")" << std::endl;
}

// Search user by ID
User* Library::searchUserById(std::string id) {
    for (User* user : users) {
        if (user->getUserId() == id) {
            return user;
        }
    }
    
    // Not found - throw exception
    throw UserNotFoundException("User with ID '" + id + "' not found");
}

// Display all users
void Library::displayAllUsers() const {
    if (users.empty()) {
        std::cout << "👥 No registered users." << std::endl;
        return;
    }
    
    std::cout << "\n╔════════════════════════════════════════════╗" << std::endl;
    std::cout << "║      REGISTERED USERS (" << users.size() << " total)         ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════╝" << std::endl;
    
    for (size_t i = 0; i < users.size(); i++) {
        std::cout << "\n[" << (i + 1) << "] ";
        users[i]->displayUserInfo();
    }
}

// ==================== TRANSACTION MANAGEMENT ====================

// Borrow an item
Transaction* Library::borrowItem(std::string userId, std::string itemId, int days) {
    try {
        // Find user
        User* user = searchUserById(userId);
        
        // Find item
        LibraryItem* item = searchItemById(itemId);
        
        // Check if user can borrow
        if (!user->canBorrow()) {
            throw BorrowLimitExceededException(
                "User '" + user->getName() + "' has reached borrow limit or has excessive fines"
            );
        }
        
        // Check if item is available
        if (!item->checkAvailability()) {
            throw ItemNotAvailableException(
                "Item '" + item->getTitle() + "' is currently not available"
            );
        }
        
        // Generate transaction ID
        std::string transId = "T" + to_string(transactions.size() + 1001);
        
        // Create transaction
        Transaction* transaction = new Transaction(transId, user, item, days);
        
        // Update item availability
        item->setAvailability(false);
        
        // Add transaction to user's history
        user->addTransaction(transaction);
        
        // Add to library's transaction list
        transactions.push_back(transaction);
        
        // Success message
        std::cout << "\n✓ BORROW SUCCESSFUL" << std::endl;
        std::cout << "Transaction ID: " << transId << std::endl;
        std::cout << "User: " << user->getName() << std::endl;
        std::cout << "Item: " << item->getTitle() << std::endl;
        std::cout << "Due in " << days << " days" << std::endl;
        
        return transaction;
        
    } catch (LibraryException& e) {
        std::cerr << "Borrow failed: " << e.what() << std::endl;
        throw;  // Re-throw to caller
    }
}

// Return an item
bool Library::returnItem(std::string transactionId) {
    try {
        // Find transaction
        Transaction* transaction = nullptr;
        for (Transaction* trans : transactions) {
            if (trans->getTransactionId() == transactionId) {
                transaction = trans;
                break;
            }
        }
        
        if (transaction == nullptr) {
            std::cerr << "Error: Transaction '" << transactionId << "' not found" << std::endl;
            return false;
        }
        
        // Check if already returned
        if (transaction->isReturned()) {
            std::cout << "Notice: Item already returned on this transaction" << std::endl;
            return false;
        }
        
        // Process return
        transaction->processReturn();
        
        // Update item availability
        LibraryItem* item = transaction->getItem();
        item->setAvailability(true);
        
        // Success message
        std::cout << "\n✓ RETURN SUCCESSFUL" << std::endl;
        std::cout << "Transaction ID: " << transactionId << std::endl;
        std::cout << "Item: " << item->getTitle() << std::endl;
        
        // Check for fines
        if (transaction->isOverdue()) {
            int daysLate = transaction->getDaysOverdue();
            std::cout << "⚠️  Item was " << daysLate << " day(s) overdue" << std::endl;
            transaction->calculateFine();
        } else {
            std::cout << "✓ Returned on time - No fines" << std::endl;
        }
        
        return true;
        
    } catch (exception& e) {
        std::cerr << "Return failed: " << e.what() << std::endl;
        return false;
    }
}

// Display all overdue transactions
void Library::displayOverdueTransactions() const {
    vector<Transaction*> overdueList;
    
    // Collect overdue transactions
    for (Transaction* trans : transactions) {
        if (trans->isOverdue() && !trans->isReturned()) {
            overdueList.push_back(trans);
        }
    }
    
    // Display results
    if (overdueList.empty()) {
        std::cout << "✓ No overdue transactions - All items returned on time!" << std::endl;
        return;
    }
    
    std::cout << "\n╔════════════════════════════════════════════╗" << std::endl;
    std::cout << "║   OVERDUE TRANSACTIONS (" << overdueList.size() << " items)      ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════╝" << std::endl;
    
    for (size_t i = 0; i < overdueList.size(); i++) {
        std::cout << "\n[" << (i + 1) << "] ";
        overdueList[i]->displayTransactionInfo();
        std::cout << "   ⚠️  " << overdueList[i]->getDaysOverdue() 
             << " day(s) overdue" << std::endl;
    }
}

// ==================== ADDITIONAL UTILITY METHODS ====================

// Get total number of items
int Library::getTotalItems() const {
    return items.size();
}

// Get total number of users
int Library::getTotalUsers() const {
    return users.size();
}

// Get total number of transactions
int Library::getTotalTransactions() const {
    return transactions.size();
}

// Get number of available items
int Library::getAvailableItemsCount() const {
    int count = 0;
    for (LibraryItem* item : items) {
        if (item->checkAvailability()) {
            count++;
        }
    }
    return count;
}

// Get number of borrowed items
int Library::getBorrowedItemsCount() const {
    return getTotalItems() - getAvailableItemsCount();
}

// Display library statistics
void Library::displayStatistics() const {
    std::cout << "\n╔════════════════════════════════════════════╗" << std::endl;
    std::cout << "║         LIBRARY STATISTICS                 ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════╝" << std::endl;
    
    std::cout << "\n📚 Collection:" << std::endl;
    std::cout << "   Total Items:      " << getTotalItems() << std::endl;
    std::cout << "   Available:        " << getAvailableItemsCount() << std::endl;
    std::cout << "   Borrowed:         " << getBorrowedItemsCount() << std::endl;
    
    std::cout << "\n👥 Users:" << std::endl;
    std::cout << "   Registered:       " << getTotalUsers() << std::endl;
    
    std::cout << "\n📋 Transactions:" << std::endl;
    std::cout << "   Total:            " << getTotalTransactions() << std::endl;
    
    // Count active transactions
    int activeCount = 0;
    for (Transaction* trans : transactions) {
        if (!trans->isReturned()) {
            activeCount++;
        }
    }
    std::cout << "   Active:           " << activeCount << std::endl;
    std::cout << "   Completed:        " << (getTotalTransactions() - activeCount) << std::endl;
    
    // Count overdue
    int overdueCount = 0;
    for (Transaction* trans : transactions) {
        if (trans->isOverdue() && !trans->isReturned()) {
            overdueCount++;
        }
    }
    std::cout << "   Overdue:          " << overdueCount << std::endl;
    
    std::cout << "╚════════════════════════════════════════════╝" << std::endl;
}

// Search items by type
vector<LibraryItem*> Library::searchByType(std::string type) const {
    vector<LibraryItem*> results;
    
    for (LibraryItem* item : items) {
        if (item->getItemType() == type) {
            results.push_back(item);
        }
    }
    
    return results;
}

// Get all available items
vector<LibraryItem*> Library::getAvailableItems() const {
    vector<LibraryItem*> availableItems;
    
    for (LibraryItem* item : items) {
        if (item->checkAvailability()) {
            availableItems.push_back(item);
        }
    }
    
    return availableItems;
}

// Get user's active transactions
vector<Transaction*> Library::getUserActiveTransactions(std::string userId) const {
    vector<Transaction*> userTransactions;
    
    for (Transaction* trans : transactions) {
        if (trans->getBorrower()->getUserId() == userId && !trans->isReturned()) {
            userTransactions.push_back(trans);
        }
    }
    
    return userTransactions;
}

// Remove item from library (admin function)
bool Library::removeItem(std::string itemId) {
    // Check if item is currently borrowed
    for (Transaction* trans : transactions) {
        if (trans->getItem()->getItemId() == itemId && !trans->isReturned()) {
            std::cerr << "Error: Cannot remove item that is currently borrowed" << std::endl;
            return false;
        }
    }
    
    // Find and remove item
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getItemId() == itemId) {
            std::cout << "Removing item: " << (*it)->getTitle() << std::endl;
            delete *it;  // Free memory
            items.erase(it);
            std::cout << "✓ Item removed successfully" << std::endl;
            return true;
        }
    }
    
    std::cerr << "Error: Item with ID '" << itemId << "' not found" << std::endl;
    return false;
}

// Remove user from library (admin function)
bool Library::removeUser(std::string userId) {
    // Check if user has active transactions
    for (Transaction* trans : transactions) {
        if (trans->getBorrower()->getUserId() == userId && !trans->isReturned()) {
            std::cerr << "Error: Cannot remove user with active transactions" << std::endl;
            return false;
        }
    }
    
    // Find and remove user
    for (auto it = users.begin(); it != users.end(); ++it) {
        if ((*it)->getUserId() == userId) {
            std::cout << "Removing user: " << (*it)->getName() << std::endl;
            delete *it;  // Free memory
            users.erase(it);
            std::cout << "✓ User removed successfully" << std::endl;
            return true;
        }
    }
    
    std::cerr << "Error: User with ID '" << userId << "' not found" << std::endl;
    return false;
}

// Generate library report
void Library::generateReport() const {
    std::cout << "\n";
    std::cout << "╔══════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              LIBRARY SYSTEM REPORT                   ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════════════════╝" << std::endl;
    
    // Statistics
    displayStatistics();
    
    // Collection breakdown
    std::cout << "\n📊 Collection Breakdown:" << std::endl;
    vector<LibraryItem*> books = searchByType("Book");
    vector<LibraryItem*> magazines = searchByType("Magazine");
    vector<LibraryItem*> videos = searchByType("EducationalVideo");
    
    std::cout << "   Books:            " << books.size() << std::endl;
    std::cout << "   Magazines:        " << magazines.size() << std::endl;
    std::cout << "   Videos:           " << videos.size() << std::endl;
    
    // Overdue summary
    std::cout << "\n⚠️  Overdue Items:" << std::endl;
    displayOverdueTransactions();
    
    std::cout << "\n" << std::string(56, '=') << std::endl;
}
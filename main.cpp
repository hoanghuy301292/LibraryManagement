#include <iostream>
#include "include/Library.h"
#include "include/Book.h"
#include "include/Magazine.h"
#include "include/EducationalVideo.h"
#include "include/StudentUser.h"
#include "include/FacultyUser.h"
#include "include/LibraryException.h"

using namespace std;

int main() {
    try {
        // Get Library instance (Singleton)
        Library* library = Library::getInstance();
        
        // Create some books
        Book* book1 = new Book("B001", "Clean Code", "Robert Martin", 
                               2008, "978-0132350884", 464, "Programming", true);
        Book* book2 = new Book("B002", "Design Patterns", "Gang of Four", 
                               1994, "978-0201633610", 395, "Software Engineering", true);
        
        // Create magazine
        Magazine* mag1 = new Magazine("M001", "Nature", "Various", 
                                      2024, 1234, "January", "Nature Publishing");
        
        // Create video
        EducationalVideo* video1 = new EducationalVideo("V001", "C++ Fundamentals", 
                                                        "John Doe", 2023, 180, 
                                                        "1080p", "Programming", "English");
        
        // Add items to library
        library->addItem(book1);
        library->addItem(book2);
        library->addItem(mag1);
        library->addItem(video1);
        
        // Create users
        StudentUser* student = new StudentUser("U001", "Alice Johnson", 
                                               "alice@university.edu", "123-456-7890",
                                               "S12345", "Computer Science", 2);
        
        FacultyUser* faculty = new FacultyUser("U002", "Dr. Bob Smith", 
                                               "bob@university.edu", "098-765-4321",
                                               "Computer Science", "Professor");
        
        library->addUser(student);
        library->addUser(faculty);
        
        // Display all items
        cout << "\n========== ALL LIBRARY ITEMS ==========" << endl;
        library->displayAllItems();
        
        // Borrow a book
        cout << "\n========== BORROWING BOOK ==========" << endl;
        Transaction* trans1 = library->borrowItem("U001", "B001", 14);
        cout << "Book borrowed successfully!" << endl;
        
        // Try to borrow the same book (should throw exception)
        cout << "\n========== TRYING TO BORROW SAME BOOK ==========" << endl;
        try {
            library->borrowItem("U002", "B001");
        } catch (ItemNotAvailableException& e) {
            cout << "Error: " << e.what() << endl;
        }
        
        // Search functionality
        cout << "\n========== SEARCHING FOR 'Code' ==========" << endl;
        vector<LibraryItem*> results = library->searchByTitle("Code");
        for (auto item : results) {
            item->displayInfo();
            cout << endl;
        }
        
        // Display overdue transactions
        cout << "\n========== OVERDUE TRANSACTIONS ==========" << endl;
        library->displayOverdueTransactions();
        
        cout << "\n========== PROGRAM COMPLETED ==========" << endl;
        
    } catch (LibraryException& e) {
        cerr << "Library Error: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

// Forward declaration
class Transaction;

class User
{
    protected:
        std::string userId;
        std::string name;
        std::string email;
        std::string phoneNumber;
        std::vector<Transaction*> borrowHistory;
        int maxBorrowLimit;
        double totalFines;

    public:
        User(std::string id, std::string name, std::string email, std::string phone, int limit = 5);
        User(const User& other); //Copy constructor
        virtual ~User();

        bool canBorrow() const;
        void addTransaction(Transaction* trans);
        void payFine(double amount);

        virtual void displayUserInfo() const;
        virtual int getCurrentBorrowCount() const;
        virtual double getDiscountRate() const;

        // Getters
        std::string getUserId() const;
        std::string getName() const;
        std::string getEmail() const;
        double getTotalFines() const;
};

#endif // USER_H
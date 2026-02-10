#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <exception>
using namespace std;

class LibraryException : public exception {
protected:
    string message;
    string errorCode;

public:
    LibraryException(string msg);
    LibraryException(string msg, string code);
    virtual ~LibraryException() noexcept = default;
    
    virtual const char* what() const noexcept override;
    virtual string getErrorCode() const noexcept;
    virtual string getFormattedMessage() const noexcept;
};

class ItemNotFoundException : public LibraryException {
public:
    ItemNotFoundException(string msg);
    ItemNotFoundException(string msg, string itemId);
    virtual ~ItemNotFoundException() noexcept;
};

class UserNotFoundException : public LibraryException {
public:
    UserNotFoundException(string msg);
    UserNotFoundException(string msg, string userId);
    virtual ~UserNotFoundException() noexcept;
};

class ItemNotAvailableException : public LibraryException {
private:
    string itemId;
    string currentBorrower;
    
public:
    ItemNotAvailableException(string msg);
    ItemNotAvailableException(string msg, string itemId, string borrower = "");
    virtual ~ItemNotAvailableException() noexcept;
    
    string getItemId() const noexcept;
    string getCurrentBorrower() const noexcept;
};

class BorrowLimitExceededException : public LibraryException {
private:
    int currentCount;
    int maxLimit;
    string userId;
    
public:
    BorrowLimitExceededException(string msg);
    BorrowLimitExceededException(string msg, string userId, int current, int limit);
    virtual ~BorrowLimitExceededException() noexcept;
    
    int getCurrentCount() const noexcept;
    int getMaxLimit() const noexcept;
    string getUserId() const noexcept;
};

class TransactionNotFoundException : public LibraryException {
public:
    TransactionNotFoundException(string msg);
    TransactionNotFoundException(string msg, string transactionId);
    virtual ~TransactionNotFoundException() noexcept;
};

class InvalidTransactionException : public LibraryException {
public:
    InvalidTransactionException(string msg);
    InvalidTransactionException(string msg, string reason);
    virtual ~InvalidTransactionException() noexcept;
};

class InvalidDataException : public LibraryException {
private:
    string fieldName;
    string invalidValue;
    
public:
    InvalidDataException(string msg);
    InvalidDataException(string msg, string field, string value);
    virtual ~InvalidDataException() noexcept;
    
    string getFieldName() const noexcept;
    string getInvalidValue() const noexcept;
};

class DatabaseException : public LibraryException {
public:
    DatabaseException(string msg);
    DatabaseException(string msg, string operation);
    virtual ~DatabaseException() noexcept;
};

class UnpaidFinesException : public LibraryException {
private:
    double fineAmount;
    string userId;
    
public:
    UnpaidFinesException(string msg);
    UnpaidFinesException(string msg, string userId, double amount);
    virtual ~UnpaidFinesException() noexcept;
    
    double getFineAmount() const noexcept;
    string getUserId() const noexcept;
};

class DuplicateEntryException : public LibraryException {
private:
    string duplicateId;
    string entityType;
    
public:
    DuplicateEntryException(string msg);
    DuplicateEntryException(string msg, string entityType, string duplicateId);
    virtual ~DuplicateEntryException() noexcept;
    
    string getDuplicateId() const noexcept;
    string getEntityType() const noexcept;
};

#endif
#include "../include/LibraryException.h"
#include <sstream>

// ==================== BASE EXCEPTION CLASS ====================

LibraryException::LibraryException(string msg) 
    : message(msg), errorCode("LIBRARY_ERROR") {
}

LibraryException::LibraryException(string msg, string code)
    : message(msg), errorCode(code) {
}

// Get error message
const char* LibraryException::what() const noexcept {
    return message.c_str();
}

// Get error code
std::string LibraryException::getErrorCode() const noexcept {
    return errorCode;
}

// Get formatted message with error code
std::string LibraryException::getFormattedMessage() const noexcept {
    std::stringstream ss;
    ss << "[" << errorCode << "] " << message;
    return ss.str();
}

// ==================== ITEM NOT FOUND EXCEPTION ====================

ItemNotFoundException::ItemNotFoundException(string msg)
    : LibraryException(msg, "ITEM_NOT_FOUND") {
}

ItemNotFoundException::ItemNotFoundException(string msg, string itemId)
    : LibraryException(msg + " (Item ID: " + itemId + ")", "ITEM_NOT_FOUND") {
}

// ==================== USER NOT FOUND EXCEPTION ====================

UserNotFoundException::UserNotFoundException(string msg)
    : LibraryException(msg, "USER_NOT_FOUND") {
}

UserNotFoundException::UserNotFoundException(string msg, string userId)
    : LibraryException(msg + " (User ID: " + userId + ")", "USER_NOT_FOUND") {
}

// ==================== ITEM NOT AVAILABLE EXCEPTION ====================

ItemNotAvailableException::ItemNotAvailableException(string msg)
    : LibraryException(msg, "ITEM_NOT_AVAILABLE"), itemId(""), currentBorrower("") {
}

ItemNotAvailableException::ItemNotAvailableException(string msg, 
                                                     string id,
                                                     string borrower)
    : LibraryException(msg, "ITEM_NOT_AVAILABLE"), 
      itemId(id), 
      currentBorrower(borrower) {
}

std::string ItemNotAvailableException::getItemId() const noexcept {
    return itemId;
}

std::string ItemNotAvailableException::getCurrentBorrower() const noexcept {
    return currentBorrower;
}

// ==================== BORROW LIMIT EXCEEDED EXCEPTION ====================

BorrowLimitExceededException::BorrowLimitExceededException(string msg)
    : LibraryException(msg, "BORROW_LIMIT_EXCEEDED"), 
      currentCount(0), maxLimit(0), userId("") {
}

BorrowLimitExceededException::BorrowLimitExceededException(string msg,
                                                           string uid,
                                                           int current,
                                                           int limit)
    : LibraryException(msg, "BORROW_LIMIT_EXCEEDED"),
      currentCount(current),
      maxLimit(limit),
      userId(uid) {
}

int BorrowLimitExceededException::getCurrentCount() const noexcept {
    return currentCount;
}

int BorrowLimitExceededException::getMaxLimit() const noexcept {
    return maxLimit;
}

std::string BorrowLimitExceededException::getUserId() const noexcept {
    return userId;
}

// ==================== TRANSACTION NOT FOUND EXCEPTION ====================

TransactionNotFoundException::TransactionNotFoundException(string msg)
    : LibraryException(msg, "TRANSACTION_NOT_FOUND") {
}

TransactionNotFoundException::TransactionNotFoundException(string msg,
                                                           string transactionId)
    : LibraryException(msg + " (Transaction ID: " + transactionId + ")", 
                      "TRANSACTION_NOT_FOUND") {
}

// ==================== INVALID TRANSACTION EXCEPTION ====================

InvalidTransactionException::InvalidTransactionException(string msg)
    : LibraryException(msg, "INVALID_TRANSACTION") {
}

InvalidTransactionException::InvalidTransactionException(string msg,
                                                         string reason)
    : LibraryException(msg + " (Reason: " + reason + ")", 
                      "INVALID_TRANSACTION") {
}

// ==================== INVALID DATA EXCEPTION ====================

InvalidDataException::InvalidDataException(string msg)
    : LibraryException(msg, "INVALID_DATA"), fieldName(""), invalidValue("") {
}

InvalidDataException::InvalidDataException(string msg,
                                           string field,
                                           string value)
    : LibraryException(msg, "INVALID_DATA"),
      fieldName(field),
      invalidValue(value) {
}

std::string InvalidDataException::getFieldName() const noexcept {
    return fieldName;
}

std::string InvalidDataException::getInvalidValue() const noexcept {
    return invalidValue;
}

// ==================== DATABASE EXCEPTION ====================

DatabaseException::DatabaseException(string msg)
    : LibraryException(msg, "DATABASE_ERROR") {
}

DatabaseException::DatabaseException(string msg, string operation)
    : LibraryException(msg + " (Operation: " + operation + ")", 
                      "DATABASE_ERROR") {
}

// ==================== UNPAID FINES EXCEPTION ====================

UnpaidFinesException::UnpaidFinesException(string msg)
    : LibraryException(msg, "UNPAID_FINES"), fineAmount(0.0), userId("") {
}

UnpaidFinesException::UnpaidFinesException(string msg,
                                           string uid,
                                           double amount)
    : LibraryException(msg, "UNPAID_FINES"),
      fineAmount(amount),
      userId(uid) {
}

double UnpaidFinesException::getFineAmount() const noexcept {
    return fineAmount;
}

std::string UnpaidFinesException::getUserId() const noexcept {
    return userId;
}

// ==================== DUPLICATE ENTRY EXCEPTION ====================

DuplicateEntryException::DuplicateEntryException(string msg)
    : LibraryException(msg, "DUPLICATE_ENTRY"), duplicateId(""), entityType("") {
}

DuplicateEntryException::DuplicateEntryException(string msg,
                                                 string type,
                                                 string id)
    : LibraryException(msg, "DUPLICATE_ENTRY"),
      duplicateId(id),
      entityType(type) {
}

std::string DuplicateEntryException::getDuplicateId() const noexcept {
    return duplicateId;
}

std::string DuplicateEntryException::getEntityType() const noexcept {
    return entityType;
}

// ==================== DESTRUCTORS ====================

ItemNotFoundException::~ItemNotFoundException() noexcept {}
UserNotFoundException::~UserNotFoundException() noexcept {}
ItemNotAvailableException::~ItemNotAvailableException() noexcept {}
BorrowLimitExceededException::~BorrowLimitExceededException() noexcept {}
TransactionNotFoundException::~TransactionNotFoundException() noexcept {}
InvalidTransactionException::~InvalidTransactionException() noexcept {}
InvalidDataException::~InvalidDataException() noexcept {}
DatabaseException::~DatabaseException() noexcept {}
UnpaidFinesException::~UnpaidFinesException() noexcept {}
DuplicateEntryException::~DuplicateEntryException() noexcept {}
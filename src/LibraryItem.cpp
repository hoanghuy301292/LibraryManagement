#include "../include/LibraryItem.h"

LibraryItem::LibraryItem(std::string id, std::string title, std::string author, int year)
    : itemId(id), title(title), author(author), publicationYear(year), isAvailable(true), lateFeePerDay(0.0) {}

LibraryItem::~LibraryItem() {}

bool LibraryItem::checkAvailability() const {
    return isAvailable;
}

void LibraryItem::setAvailability(bool availability) {
    isAvailable = availability;
}

std::string LibraryItem::getItemId() const {
    return itemId;
}

std::string LibraryItem::getTitle() const {
    return title;
}

std::string LibraryItem::getAuthor() const {
    return author;
}
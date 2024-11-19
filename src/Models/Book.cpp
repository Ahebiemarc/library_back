#include "../../includes/Book.hpp"
#include <stdexcept>
#include "crow.h"


Book::Book(){}
Book::Book(const std::string& title, const std::string& author, const std::string& status) : _title(title), _author(author), _status(status) {
}

Book::Book(int id, const std::string& title, const std::string& author, const std::string& status) : _id(id), _title(title), _author(author), _status(status) {
}

int Book::getId() const { return _id; }
std::string Book::getTitle() const { return _title; }
std::string Book::getAuthor() const { return _author; }
std::string Book::getStatus() const { return _status; }

void Book::setStatus(const std::string& status) {
    _status = status;

}






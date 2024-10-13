#include "../../includes/Book.hpp"
#include <stdexcept>


Book::Book(){}
Book::Book(const std::string& title, const std::string& author, const std::string& status) : _title(title), _author(author), _status(status) {
    _id++;
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

bool Book::saveToDatabase(Connections& cnn){
    sqlite3* db = cnn.getDB();
    const char* query = "INSERT INTO Books (title,author,status) VALUES (?,?,?)";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }

    sqlite3_bind_text(stmt, 1, _title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, _author.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, _status.c_str(), -1, SQLITE_STATIC);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
    
}

bool Book::updateStatus(Connections& cnn){
    sqlite3* db = cnn.getDB();
    const char* query = "UPDATE Books SET status = ? WHERE id = ?";
    sqlite3_stmt* stmt;

    if(sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK){
        return false;
    }

    sqlite3_bind_text(stmt, 1, _status.c_str(), -1, nullptr);
    sqlite3_bind_int(stmt, 2, _id);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

Book Book::findById(Connections& cnn, int id) {
    sqlite3* db = cnn.getDB();
    const char* query = "SELECT id, title, author, status FROM Books WHERE id = ?";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Erreur de préparation de la requête");
    }

    sqlite3_bind_int(stmt, 1, id);

    Book book;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        book._id = sqlite3_column_int(stmt, 0);
        book._title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        book._author = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        book._status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    }

    sqlite3_finalize(stmt);
    return book;
}

std::vector<Book> Book::getAllBooks(Connections& cnn) {
    sqlite3* db = cnn.getDB();
    const char* query = "SELECT id, title, author, status FROM Books";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error("Erreur de préparation de la requête");
    }

    std::vector<Book> books;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Book book;
        book._id = sqlite3_column_int(stmt, 0);
        book._title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        book._author = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        book._status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));

        books.push_back(book);
    }

    sqlite3_finalize(stmt);
    return books;
}
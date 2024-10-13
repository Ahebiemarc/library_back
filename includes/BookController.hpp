#ifndef BOOKCONTROLLER_HPP
#define BOOKCONTROLLER_HPP

#include "crow.h"
#include "Connections.hpp"
#include "Book.hpp"
#include <vector>

class BookController {
public:
    BookController(Connections& connection);
    
    void addBook(const crow::request& req, crow::response& res);
    void borrowBook(const crow::request& req, crow::response& res);
    void returnBook(const crow::request& req, crow::response& res);
    void listBooks(const crow::request& req, crow::response& res);

private:
    Connections& _connection;
};

#endif // BOOKCONTROLLER_HPP

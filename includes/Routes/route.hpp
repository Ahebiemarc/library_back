#ifndef ROUTE_HPP
#define ROUTE_HPP

#include "../Connections.hpp"
#include "../Handler/routeHandler.hpp"
#include "crow.h"

template <typename T>
void setupRoutes(crow::App<T>& app, Connections& cnn) {
    CROW_ROUTE(app, "/add_book").methods("POST"_method)([&cnn](const crow::request& req, crow::response& res) {
        std::cout << "Route /add_book atteinte avec POST" << std::endl;
        handleAddBook(req, res, cnn);
    });

    CROW_ROUTE(app, "/borrow_book").methods("POST"_method)([&cnn](const crow::request& req, crow::response& res) {
        handleBorrowBook(req, res, cnn);
    });

    CROW_ROUTE(app, "/return_book").methods("POST"_method)([&cnn](const crow::request& req, crow::response& res) {
        handleReturnBook(req, res, cnn);
    });

    CROW_ROUTE(app, "/list_books").methods("GET"_method)([&cnn](const crow::request& req, crow::response& res) {
        handleListBooks(req, res, cnn);
    });
}

#endif // ROUTE_HPP

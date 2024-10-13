#ifndef ROUTE_HPP
#define ROUTE_HPP


//#include "crow.h"
#include "../BookController.hpp"
#include "../Connections.hpp"

void setupRoutes(crow::SimpleApp& app, Connections& cnn){
    BookController controller(cnn);

    CROW_ROUTE(app, "/add_book").methods("POST"_method)([&controller](const crow::request& req, crow::response& res) {
        controller.addBook(req, res);
    });

    CROW_ROUTE(app, "/borrow_book").methods("POST"_method)([&controller](const crow::request& req, crow::response& res) {
        controller.borrowBook(req, res);
    });
    
    CROW_ROUTE(app, "/return_book").methods("POST"_method)([&controller](const crow::request& req, crow::response& res) {
        controller.returnBook(req, res);
    });
    
    CROW_ROUTE(app, "/list_books").methods("GET"_method)([&controller](const crow::request& req, crow::response& res) {
        controller.listBooks(req, res);
    });
}




#endif // ROUTE_HPP
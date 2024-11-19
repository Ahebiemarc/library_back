#ifndef ROUTE_HANDLERS_HPP
#define ROUTE_HANDLERS_HPP

#include "crow.h"
#include "../Connections.hpp"

// Handlers des différentes routes
void handleAddBook(const crow::request& req, crow::response& res, Connections& cnn);
void handleBorrowBook(const crow::request& req, crow::response& res, Connections& cnn);
void handleReturnBook(const crow::request& req, crow::response& res, Connections& cnn);
void handleListBooks(const crow::request& req, crow::response& res, Connections& cnn);

#endif

#include "../../includes/Handler/routeHandler.hpp"

void handleAddBook(const crow::request& req, crow::response& res, Connections& cnn){
    try {
            // Parse JSON body
        auto body = crow::json::load(req.body);
        if (!body) {
            std::cerr << "Invalid JSON received." << std::endl;
            res.code = 400;
            res.write(R"({"error": "Invalid JSON format."})");
            res.end();
            return;
        }
        
        std::string title = body["title"].s();
        std::string author = body["author"].s();

        // Prepare SQL query
        std::string query = "INSERT INTO Books (title, author, status) VALUES (?, ?, 'available');";
        cnn.execute(query, {title, author});

        res.code = 200;
        //res.write("Book added successfully.");
        res.write(R"({"message": "Book added successfully"})");

    } catch (const std::exception& e) {
        std::cerr << "Error Adding Book: " << e.what() << std::endl;
        res.code = 500;
        res.write(R"({"error": "Internal server error."})");

    }
    res.end();
}


void handleBorrowBook(const crow::request& req, crow::response& res, Connections& cnn){
    try{
        // Parse JSON body
        auto body = crow::json::load(req.body);
        if (!body || !body.has("id")) {
            res.code = 400;
            res.write(R"({"error": "Invalid request: 'id' field is required."})");
            res.end();
            return;
        }

        // extract the book ID
        int bookID = body["id"].i();

        // Check status book
        auto status = cnn.getBookStatus(bookID);
        if (!status) {
            res.code = 404;
            res.write(R"({"error": "Book not found."})");
            res.end();
            return;
        }

        if (status == "borrowed") {
            res.code = 400;
            res.write(R"({"error": "The book is already borrowed."})");
            res.end();
            return;
        }


        // Prepare SQL query
        std::string query = "UPDATE Books SET status = 'borrowed' WHERE id =?;";
        cnn.execute(query, {std::to_string(bookID)});

        res.code = 200;
        //res.write("Book borrowed successfully.");
        res.write(R"({"message": "Book borrowed successfully."})");

    } catch (const std::exception& e) {
        std::cerr << "Error borrowing book: " << e.what() << std::endl;
        res.code = 500;
        res.write(R"({"error": "Internal server error."})");
    }
    res.end();

}
void handleReturnBook(const crow::request& req, crow::response& res, Connections& cnn){
    try{
        auto body = crow::json::load(req.body);
        if (!body || !body.has("id")) {
            res.code = 400;
            res.write(R"({"error": "Invalid request: 'id' field is required."})");
            res.end();
            return;
        }

        // extract the book ID
        int bookID = body["id"].i();
        
        // Check status Book
        auto status = cnn.getBookStatus(bookID);
        if (!status) {
            res.code = 404;
            res.write(R"({"error": "Book not found."})");
            res.end();
            return;
        }

        if (*status != "borrowed") {
            res.code = 400;
            res.write(R"({"error": "The book is not currently borrowed."})");
            res.end();
            return;
        }

        // Prepare SQL query
        std::string query = "UPDATE Books SET status = 'available' WHERE id = ?;";
        cnn.execute(query, {std::to_string(bookID)}); // Utilisation de la méthode `execute`

        res.code = 200;
        res.write(R"({"message": "Book successfully returned."})");
    }  catch (const std::exception& e) {
        std::cerr << "Error returning book: " << e.what() << std::endl;
        res.code = 500;
        res.write(R"({"error": "Internal server error."})");

    }
    res.end();

}
void handleListBooks(const crow::request& req, crow::response& res, Connections& cnn){
    try {
        std::string query = "SELECT id, title, author, status FROM Books;";
        auto books = cnn.select(query);
        res.code = 200;
        res.write(books.dump()); //  Send result format JSON
        res.set_header("Access-Control-Allow-Origin", "*"); // Ajouter l'en-tête CORS ici aussi

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        res.code = 500;
        res.write(R"({"error": "An error occurred while fetching the books."})");

    }

    res.end();
}

#include "../../includes/BookController.hpp"
#include "json.hpp" // "nlohmann/json.hpp"

BookController::BookController(Connections& connection) : _connection(connection) {}

void BookController::addBook(const crow::request& req, crow::response& res) {
    try{
        // Extraire les données du corps de la requête
        auto body = nlohmann::json::parse(req.body);

        const std::string title = body["title"].get<std::string>();
        const std::string author = body["author"].get<std::string>();
        const std::string status = "available";
        Book newBook(title, author, status);

        // Valider les données
        if (newBook.getTitle().empty() || newBook.getTitle().empty()) {
            res.code = 400; // Erreur de validation
            res.write("Données incorrectes");
            res.end();
            return;
        }

        // Préparer et exécuter la requête d'insertion
        newBook.saveToDatabase(_connection);

        res.code =  201; // Succès d'insertion
        res.write("Livre ajouté avec succès");

    } catch(std::exception & e){
        res.code = 500; // Erreur serveur
        res.write("An error occurred" + std::string(e.what()));
    }
}

void BookController::borrowBook(const crow::request& req, crow::response& res) {
    try
    {
        auto body = nlohmann::json::parse(req.body);
        int bookId = body["id"].get<int>();
        
        // Trouver le livre par son ID
        Book book = Book::findById(_connection, bookId);
        if (book.getId() == 0) {  // Si le livre n'est pas trouvé
            res.code = 404;
            res.write("Livre non trouvé.");
            res.end();
            return;
        }

        // Vérifier si le livre est disponible
        if (book.getStatus() == "available") {
            std::string newStatus = "no_available";
            book.setStatus(newStatus);  // Changer le statut du livre
            book.updateStatus(_connection);  // Mettre à jour dans la base de données
            res.code = 201;
            res.write("Le livre a été emprunté avec succès.");
        } else {
            res.code = 400;
            res.write("Le livre n'est pas disponible.");
        }

    }
    catch(const std::exception& e)
    {
        res.code = 500; // Erreur serveur
        res.write("An error occurred" + std::string(e.what()));
    }
    
}

void BookController::returnBook(const crow::request& req, crow::response& res) {
    try
    {
        auto body = nlohmann::json::parse(req.body);
        int bookId = body["id"].get<int>();

        // Trouver le livre par son ID
        Book book = Book::findById(_connection, bookId);
        if (book.getId() == 0) {
            res.code = 404;
            res.write("Livre non trouvé.");
            return;
        }

        // Vérifier si le livre est actuellement emprunté
        if (book.getStatus() == "no_available") {
            std::string newStatus = "no_available";
            book.setStatus(newStatus);  // Changer le statut du livre
            book.updateStatus(_connection);  // Mettre à jour dans la base de données
            res.write("Le livre a été retourné avec succès.");
        } else {
            res.code = 400;
            res.write("Le livre n'était pas emprunté.");
        }
    }
    catch(const std::exception& e)
    {
        res.code = 500; // Erreur serveur
        res.write("An error occurred" + std::string(e.what()));
    }
    
}

void BookController::listBooks(const crow::request& req, crow::response& res) {
    try
    {
        // Récupérer tous les livres depuis la base de données
        auto books = Book::getAllBooks(_connection);

        // Convertir les livres en JSON
        nlohmann::json jsonBooks = nlohmann::json::array();
        for (const auto& book : books) {
            jsonBooks.push_back({
                {"id", book.getId()},
                {"title", book.getTitle()},
                {"author", book.getAuthor()},
                {"status", book.getStatus()}
            });
        }

        res.write(jsonBooks.dump());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

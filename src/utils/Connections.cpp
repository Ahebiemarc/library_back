#include "../../includes/Connections.hpp"
#include <iostream>

Connections::Connections(const std::string& dbName){
    if (sqlite3_open(dbName.c_str(), &_db) != SQLITE_OK){
        std::cerr << "Cannot open database" << sqlite3_errmsg(_db) << std::endl;
        _db = nullptr;
    }   
}

Connections::~Connections(){
    if (_db){
        sqlite3_close(_db);
    }   
}

sqlite3* Connections::getDB() const{
    return _db;
}
#include "../../includes/Connections.hpp"
#include <iostream>

// Méthode pour exécuter une requête SQL, comme la création de table
void Connections::execute(const std::string& query) {
    char* errorMessage = nullptr;
    int result = sqlite3_exec(_db, query.c_str(), nullptr, nullptr, &errorMessage);

    if (result != SQLITE_OK) {
        std::cerr << "Erreur lors de l'exécution de la requête SQL : " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    } else {
        std::cout << "Requête exécutée avec succès." << std::endl;
    }
}


void Connections::createBooksTable() {
    std::string createTableQuery = R"(
        CREATE TABLE IF NOT EXISTS books (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            author TEXT NOT NULL,
            status TEXT NOT NULL
        );
    )";

    // Exécute la requête pour créer la table
    execute(createTableQuery);
}



#include "../../includes/Connections.hpp"
#include <iostream>

Connections::Connections(const std::string& dbName){
    _db = nullptr;
    int status = sqlite3_open(dbName.c_str(), &_db);
    if (status != SQLITE_OK)
    {
        sqlite3_close(_db);
        return;
    }
    
}

/*Connections::~Connections(){
    if (_db){
        sqlite3_close(_db);
    }   
}*/

sqlite3* Connections::getDB() {
    if (_db != nullptr)
    {
        return _db;
    }
    return nullptr;
    
}

// Méthode pour exécuter une requête SQL, comme la création de table
void Connections::execute(const std::string& query, const std::vector<std::string>& params) {
    if (_db == nullptr)
    {
        return;
    }
    
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(_db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Erreur lors de la préparation de la requête : " << sqlite3_errmsg(_db) << std::endl;
        return;
    }

    for (size_t i = 0; i < params.size(); i++) {
        sqlite3_bind_text(stmt, static_cast<int>(i + 1), params[i].c_str(), -1, SQLITE_STATIC);
    }

    int result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        std::cerr << "Erreur lors de l'exécution de la requête : " << sqlite3_errmsg(_db) << std::endl;
    } else {
        std::cout << "Requête exécutée avec succès." << std::endl;
    }

    sqlite3_finalize(stmt);
}

// Méthode pour récupérer les données d'une requête SQL
std::optional<std::string> Connections::getBookStatus(int BookID) {
    if (_db == nullptr) {
        std::cerr << "Database not initialized." << std::endl;
        return std::nullopt;
    }

    std::string query = "SELECT status FROM Books WHERE id = ?;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(_db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Database error: " << sqlite3_errmsg(_db) << std::endl;
        return std::nullopt;
    }

    sqlite3_bind_int(stmt, 1, BookID);

    int step = sqlite3_step(stmt);
    if (step == SQLITE_ROW) {
        std::string status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        sqlite3_finalize(stmt);
        return status;
    }

    sqlite3_finalize(stmt);
    return std::nullopt;
}


crow::json::wvalue Connections::select(const std::string& query) {
    if (_db == nullptr) {
        throw std::runtime_error("Database not initialized.");
    }

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(_db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        throw std::runtime_error(sqlite3_errmsg(_db));
    }

    std::vector<crow::json::wvalue> results;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        crow::json::wvalue row;
        int columnCount = sqlite3_column_count(stmt);
        for (int i = 0; i < columnCount; ++i) {
            const char* columnName = sqlite3_column_name(stmt, i);
            const char* columnValue = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            row[columnName] = columnValue ? columnValue : "";
        }
        results.emplace_back(std::move(row));
    }

    sqlite3_finalize(stmt);
    return results;
}


void Connections::createBooksTable() {
    

    std::string createTableQuery = 
            "CREATE TABLE IF NOT EXISTS Books ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "title TEXT NOT NULL,"
            "author TEXT NOT NULL,"
            "status TEXT NOT NULL"
        ");";

    // Exécute la requête pour créer la table
    execute(createTableQuery, {});
}



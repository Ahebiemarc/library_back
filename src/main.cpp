#include "crow.h"
#include "../includes/Connections.hpp"
#include "../includes/Routes/route.hpp"

int main(){
    /*sqlite3 *db;
    crow::SimpleApp app;
    int res =  sqlite3_open("../db/Test.db",  &db);
    if (res)
    {
        std::cout << "SQLite database  can't opened" << std::endl;
        return -1;
    }
    else {
        std::cout << "SQLite database opened successfully " << std::endl;
    }

    sqlite3_close(db);*/

    // Créer la connexion à la base de données
    Connections connection("../db/TestDB.db");

    // Créer la table des livres
    connection.createBooksTable();

    // Configurer l'application Crow
    crow::SimpleApp app;

    // Configurer les routes
    setupRoutes(app, connection);

    // Démarrer le serveur
    app.port(18080).multithreaded().run();

    return 0;
    
}

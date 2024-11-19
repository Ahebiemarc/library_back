#include "crow.h"
#include "crow/middlewares/cors.h"
#include "../includes/Connections.hpp"
#include "../includes/Routes/route.hpp"

int main(){

    // Créer la connexion à la base de données
    Connections connection("../db/testDB.db");

    // Créer la table des livres
    connection.createBooksTable();

    // Configurer l'application Crow
    crow::App<crow::CORSHandler> app;

    // Configurer les routes
    setupRoutes(app, connection);

 

    // Démarrer le serveur
    app.port(18080).multithreaded().run();

    return 0;
    
}

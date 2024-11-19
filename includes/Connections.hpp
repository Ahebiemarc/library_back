#ifndef CONNECTIONS_HPP
#define CONNECTIONS_HPP


#include <sqlite3.h>
#include <string>
#include <vector>
#include <map>
#include <optional>
#include "crow.h"


class Connections {
    public:
        Connections(const std::string& dbName);
        //~Connections();

        sqlite3* getDB() ;
        void execute(const std::string& query, const std::vector<std::string>& params);
        std::optional<std::string> getBookStatus(int BookID);
        crow::json::wvalue select(const std::string& query);
        void createBooksTable();
    
    private:
        sqlite3* _db;
};



#endif // CONNECTIONS_HPP
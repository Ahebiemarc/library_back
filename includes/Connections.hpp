#ifndef CONNECTIONS_HPP
#define CONNECTIONS_HPP


#include <sqlite3.h>
#include <string>

class Connections {
    public:
        Connections(const std::string& dbName);
        ~Connections();

        sqlite3* getDB() const;
        void execute(const std::string& query);
        void createBooksTable();
    
    private:
        sqlite3* _db;
};



#endif // CONNECTIONS_HPP
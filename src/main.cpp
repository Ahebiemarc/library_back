#include <iostream>
#include <sqlite3.h>
#include "crow.h"

int main(){
    sqlite3 *db;
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

    sqlite3_close(db);
    return 0;
    
}

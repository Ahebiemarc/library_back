#ifndef BOOK_HPP
#define BOOK_HPP


#include <string>
#include <vector>
#include "Connections.hpp"

class Book{
    public:
        Book();
        Book(const std::string& title, const std::string& author, const std::string& status);
        Book(int id, const std::string& title, const std::string& author, const std::string& status);



        int getId() const;
        std::string getTitle() const;
        std::string getAuthor() const;
        std::string getStatus() const;

        void setStatus(const std::string& status);

        // Méthodes de gestion des livres
        bool saveToDatabase(Connections& cnn);
        bool updateStatus(Connections& cnn);
        static Book findById(Connections& cnn, int id);
        static std::vector<Book> getAllBooks(Connections& cnn);
    
    private:
        int _id;
        std::string _title;
        std::string _author;
        std::string _status;

};



#endif // BOOK_HPP
#ifndef BOOK_H
#define BOOK_H
#include <string>
namespace book {
    struct Book
    {
    private:
        int bookID, quantity;
        std::string name, category;
        Book* next;
    public:
        //book();
        //struct Book* head;
        void printCategory();
        std::string convertCategory(int);
        void addBook();
        void displayRecord();
        bool checkDuplicateID(int id);
        int randomID();
        int getBookID();
        void setBookID(int bookID);
        std::string getName();
        void setName(std::string name);
        int getQuantity();
        void setQuantity(int quantity);
        std::string getCategory();
        void setCategory(std::string category);
        std::string displayBook();
    };
}
#endif 

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
    };
}
#endif 

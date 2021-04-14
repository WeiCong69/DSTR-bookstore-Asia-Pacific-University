#ifndef BOOK_H
#define BOOK_H
#include <string>
namespace book {
    struct Book
    {
    private:
        int bookID, quantity;
        std::string name, category;
        float price;
        //Book* next;
    public:
        Book* next;
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
        float getPrice();
        void setPrice(float price);
        std::string displayBook(int style);
        void editBook();
        Book* searchBook(int id);
        void deleteBook();
        void push(Book** head_ref, std::string name, std::string category, int quantity,float price);
        void filterCategory();
        void MergeSort(Book** headRef, int choice);
        Book* SortedMerge(Book* a, Book* b, int choice);
        void FrontBackSplit(Book* source, Book** frontRef, Book** backRef);
        Book* RevSortedMerge(Book* a, Book* b, int choice);
        void sortBook();
        float roundoff(float value, unsigned char prec);

    };
}
#endif 

#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
#include "book.h"
using namespace book;

namespace transaction {
    struct Transaction
    {
    private:
        int transactionID;
        float totalPrice;
        Book* boughtBooks = NULL;
        Transaction* next;

    public:
        int getTransactionID();
        void setTransactionID(int transactionID);
        float getTotalPrice();
        void setTotalPrice(float totalPrice);
        Book* getBoughtBooks();
        void resetBoughtBooks();
        void setBoughtBooks(int id, std::string name, std::string category, int quantity, float price);
        void addTransaction();
        bool checkDuplicateID(int id);
        int randomID();
        void displayRecord();
        void addtoCart(Transaction** head);
        void removeFromCart(Transaction** head);
        void viewCart(Transaction** head);
        float calculateTotal(Transaction** head);
        Transaction* searchTransaction(int id, Transaction* head1);
        void sortTransaction();
        void MergeSort(Transaction** headRef, int choice);
        Transaction* SortedMerge(Transaction* a, Transaction* b, int choice);
        Transaction* RevSortedMerge(Transaction* a, Transaction* b, int choice);
        void FrontBackSplit(Transaction* source,
            Transaction** frontRef, Transaction** backRef);
    };
}
#endif
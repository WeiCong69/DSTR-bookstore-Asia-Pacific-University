#ifndef TRANSACTION_H
#define TRANSACTION_H
#include <string>
namespace transaction {
    struct Transaction
    {
    private:
        int transactionID;
        float totalPrice;
        Transaction* next;
        Book* bookCollection;
    public:
        int getTransactionID();
        void setTransactionID(int transactionID);
        float getTotalPrice();
        void setTotalPrice(float totalPrice);
        float roundoff(float value, unsigned char prec);
        void addTransaction();
        bool checkDuplicateID(int id);
        int randomID();
        int getQuantity();
        void setQuantity(int quantity);
    };
}
#endif
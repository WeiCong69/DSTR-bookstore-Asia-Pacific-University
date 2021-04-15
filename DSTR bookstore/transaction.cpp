#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "transaction.h"
#include "book.h"
#include "book.cpp"

using namespace std;
using namespace transaction;
using namespace book;


int Transaction::getTransactionID() {
    return this->transactionID;
}

void Transaction::setTransactionID(int transactionID) {
    this->transactionID = transactionID;
}

float Transaction::getTotalPrice() {
    return this->totalPrice;
}

void Transaction::setTotalPrice(float totalPrice) {
    this->totalPrice = totalPrice;
}

float Transaction::roundoff(float value, unsigned char prec)
{
    float pow_10 = pow(10.0f, (float)prec);
    return round(value * pow_10) / pow_10;
}

void Transaction::addTransaction() {
    int category, quantity;
    string name;
    bool duplicate = false;
    float price;
    struct Transaction* newTransaction = new Transaction;
    // Auto generate unique bookID. 1 is not allowed to be used as the bookID because 1 is special command to exit menu
    do {
        newTransaction->setTransactionID(randomID());
        if (newTransaction->getTransactionID() == 1) { continue; }
        duplicate = checkDuplicateID(newTransaction->getTransactionID());
    } while (duplicate);

    //Name
    cout << "Please enter the name of new book:\n";
    //cin >> name;
    getline(cin, name);
    getline(cin, name);
    //newTransaction->setTransaction(name);

    // Category
    //Transaction::printCategory();
    //cin >> category;
    //while (category < 0 || category>3 || cin.fail())
    //{
        //if (cin.fail())
        //{
            //cin.clear();
            //cin.ignore();
        //}
        //cout << "Invalid input\n";
        //cout << "Please choose the category from the range of 1-3 \n";
        //cin >> category;
    //}
    //name = convertCategory(category);
    //newBook->setCategory(name);

    //Quantity
    cout << "Please enter new quantity" << endl;
    cin >> quantity;
    while (quantity < 0 || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
        }
        cout << "Please enter a positive number\n";
        cin >> quantity;
    }
    newTransaction->setQuantity(quantity);

    //Price
    //cout << "Please enter a price" << endl;
    //cin >> price;
    //while (price < 0 || cin.fail())
    //{
        //if (cin.fail())
        //{
            //cin.clear();
            //cin.ignore();
        //}
        //cout << "Please enter a positive value\n";
        //cin >> price;
    //}
    //newBook->setPrice(price);

    //newBook->next = head;
    //head = newBook;

}


bool Transaction::checkDuplicateID(int id) {
    bool found = false;
    Transaction* node = head;
    if (node == NULL) {
        return false;
    }
    else {
        do {
            if (node->getTransactionID() == id) {
                cout << "DUPLICATE ID FOUND !" << endl;
                return true;
            }
            node = node->next;

        } while (node != NULL);

        return false;
    }
}
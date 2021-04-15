#include <iostream>
#include <ctype.h>
#include "menu.h"
#include "book.h"
#include "transaction.h"
using namespace std;
using namespace book;
using namespace transaction;


Book* book1 = new Book;
Transaction* transaction1 = new Transaction;
//Book* head2 = NULL;
int getMenuChoice(int value)
{
    int choice = -1;
    // if (!isdigit(value))
    //     return;
    do
    {
        cout << "Enter your choice" << endl;
        cin >> choice;
        if (choice < 0 || choice > value)
        {
            cout << "Choice outside range. Please choose again" << endl;
        }
    } while (choice < 0 || choice > value);
    return choice;
}

void printMenu()
{
    cout << "*** Welcome to Our Inventory System by C++ ***" << endl;
    cout << "To select an action, enter " << endl;
    cout << "Manage Inventory " << endl;
    cout << "----------------------" << endl;
    cout << "1. Add new book" << endl;
    cout << "2. View or edit book details" << endl;
    cout << "3. Remove book from inventory" << endl;
    cout << "4. Filter books by category" << endl;
    cout << "5. Sort books" << endl;
    cout << "Manage Transaction " << endl;
    cout << "----------------------" << endl;
    cout << "6. Add Transaction" << endl;
    cout << "7. View transaction details" << endl;
    cout << "8. Sort Transactions based on total Price" << endl;
    cout << "9. to Exit" << endl;
}

void performAction(int choice)
{

    switch (choice)
    {
    case 0:
        cout << "0";
        break;
    case 1: {        
        book1->addBook();
        book1->displayRecord(NULL);
    }break;
    case 2:{
        //cout << "2";
        book1->editBook();
    }break;
    case 3:{
        book1->deleteBook();
    }break;
    case 4:{
        book1->filterCategory();
    }break;
    case 5:{
        book1->sortBook();
    }break;
    case 6: {
        transaction1->addTransaction();
        //transaction1->addTransaction();
        //transaction1->displayRecord();
    }break;
    case 7: {
        cout << "8";
    }break;
    case 9: {
        cout << "9";
        break;
    }
        break;
    default:
        cout << "Unknown error has occuered" << endl;
    }
}
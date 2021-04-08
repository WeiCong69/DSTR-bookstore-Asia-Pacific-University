#include <iostream>
#include <string>
#include <cstdlib>
#include "book.h"
using namespace std;
using namespace book;
//node


Book* head = NULL;
//Book(int a, int  b, string c,string d) : bookID(a), quantity(b), name(c),category(d){}
int Book::getBookID() {
    return this->bookID;
}

void Book::setBookID(int bookID) {
    this->bookID = bookID;
}

string Book::getName() {
    return this->name;
}

void Book::setName(string name) {
    this->name = name;
}

int Book::getQuantity() {
    return this->quantity;
}

void Book::setQuantity(int quantity) {
    this->quantity = quantity;
}

string Book::getCategory() {
    return this->category;
}

void Book::setCategory(string category) {
    this->category = category;
}

string Book::displayBook() {
    return to_string(getBookID()) + "\t" + getName() + "\t" + getCategory() + "\t" + to_string(getQuantity())+ "\n";
}

void Book::printCategory() {
    cout << "1. Fiction" << endl;
    cout << "2. Non-Fiction" << endl;
    cout << "3. Graphics" << endl;
    cout << "Please select a category " << endl;
}

string Book:: convertCategory(int selection) {
    std::string category;
    switch (selection) {
    case 1:
        category = "Fiction";
        break;
    case 2:
        category = "Non-Fiction";
        break;
    case 3:
        category = "Graphics";
        break;
    default:
        category = "Magazine";
    }
    return category;
}

void Book::addBook() {
    int category, quantity;
    string name;
    bool duplicate = false;
    struct Book* newBook = new Book;
    //cout << "Enter Book ID" << endl;

    //temp pointer to check if theres duplicated ID
    do {
        
        //cin >> newBook->bookID;
        //cin.get();
        newBook->bookID = randomID();
        duplicate = checkDuplicateID(newBook->bookID);

    } while (duplicate);
    /*struct Book* checkID;
    checkID = head;
    while (checkID != NULL)
    {
        if (newBook->bookID == checkID->bookID)
        {
            cout << "Duplicate Book ID! Re-enter book ID:";
            cin >> newBook->bookID;
            checkID = NULL; //to break the loop
        }
        else
        {
            checkID = checkID->next;
        }
    }*/
    //Name
    cout << "Please enter the name of new book:\n";
    //cin >> name;
    getline(cin, name);
    getline(cin, name);
    newBook->name = name;

    // Category
    Book::printCategory();
    cin >> category;
    while (category < 0 || category>3 || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
        }
        cout << "Invalid input\n";
        cout << "Please choose the category from the range of 1-3 ";
        cin >> category;
    }
    newBook->category = convertCategory(category);

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
    newBook->quantity = quantity;

    newBook->next = head;
    head = newBook;

}

void Book:: displayRecord() {
    struct Book* current;
    current = head;
    if (current == NULL) {
        cout << "No records found";
    }else {
        cout << "Book ID \tName \tCategory \t Quantity\n";
        while (current != NULL) {
            //cout << "" << current->bookID << "\t" << current->name << "\t" << current->category << "\t" << current->quantity << endl;
            //cout << "" << current->getBookID() << "\t" << current->getName() << "\t" << current->getCategory() << "\t" << current->getQuantity() << endl;
            cout<<current->displayBook();
            current = current->next;
        }

    }
}

bool Book::checkDuplicateID(int id) {
    bool found = false;
    Book * node = head;
    if (node == NULL) {
        return false;
    }
    else {
        do {
            if (node->bookID == id) {
                cout << "DUPLICATE ID FOUND !" << endl;
                return true;
            }
            node = node->next;

        } while (node != NULL);

        return false;
    }
}

int Book::randomID() {
    int id = rand();
    return id;
}

//void Book::editBook() {
//    //display all books
//    Book::displayRecord();
//    //choose a book by ID
//    //ask user which part to update
//    //
//}
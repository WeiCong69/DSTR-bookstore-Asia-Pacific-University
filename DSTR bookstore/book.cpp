#include <iostream>
#include <string>
#include "book.h"
using namespace std;
using namespace book;
//node


Book* head = NULL;
//Book(int a, int  b, string c,string d) : bookID(a), quantity(b), name(c),category(d){}

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
    struct Book* newBook = new Book;
    cout << "Enter Book ID" << endl;
    cin >> newBook->bookID;
    cin.get();
    //temp pointer to check if theres duplicated ID
    struct Book* checkID;
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
    }
    //Name
    cout << "Please enter the name of new book:\n";
    //cin >> name;
    
    getline(cin, name);
    newBook->name = name;

    // Category
    Book::printCategory();
    cin >> category;
    while (category < 0 || category>4 || cin.fail())
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
    }
    if (current != NULL) {
        cout << "Book ID \tName \tCategory \t Quantity\n";
        while (current != NULL) {
            cout << "" << current->bookID << "\t\t" << current->name << "\t" << current->category << "\t\t" << current->quantity << endl;
            current = current->next;

        }

    }
}

/*int main() {
    addBook();
    displayRecord();
}*/
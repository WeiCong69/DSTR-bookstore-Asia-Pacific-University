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

string Book::displayBook(int style) {
    switch (style) {
        case 1: {
            return to_string(getBookID()) + "\t" + getName() + "\t" + getCategory() + "\t" + to_string(getQuantity()) + "\n";
        }break;

        case 2: {
            return "Book ID   : " + to_string(getBookID()) + "\n" + "Book Name : " + getName() + "\n" + "Category  : " + getCategory() + "\n" + "Quantity  : " + to_string(getQuantity()) + "\n";
        }break;
        default:
            return "Book ID   : " + to_string(getBookID()) + "\n" + "Book Name : " + getName() + "\n" + "Category  : " + getCategory() + "\n" + "Quantity  : " + to_string(getQuantity()) + "\n";
    }
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
    // Auto generate unique bookID. 1 is not allowed to be used as the bookID because 1 is special command to exit menu
    do {
        newBook->setBookID(randomID());
        if (newBook->getBookID() == 1) { continue; }
        duplicate = checkDuplicateID(newBook->getBookID());
    } while (duplicate);

    //Name
    cout << "Please enter the name of new book:\n";
    //cin >> name;
    getline(cin, name);
    getline(cin, name);
    newBook->setName(name);

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
        cout << "Please choose the category from the range of 1-3 \n";
        cin >> category;
    }
    name = convertCategory(category);
    newBook->setCategory(name);

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
    newBook->setQuantity(quantity);

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
            cout<<current->displayBook(1);
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
            if (node->getBookID() == id) {
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

Book* Book::searchBook(int id) {
    struct Book* current;
    current = head;
    if (current == NULL) {
        return current;
    }
    while (current != NULL) {
        if (current->getBookID() == id) {
            return current;
        }
        current = current->next;
    }
    current = NULL;
    return current;

    }

void Book::editBook() {
    //display all books
    Book* tempBook = new Book;
    int choice,update,intVal,counter=0;
    string stringValue;
    do {
        if (counter == 0) {
            Book::displayRecord();
            cout << "\n Please select a book by keying in the book ID\n***Enter 1 to exit menu***\n ";
            cin >> choice;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                continue;
            }
            // If user keys in 1 then user exits edit book menu
            if (choice == 1) { break; }
            // system finds the book based on the id given by user
            tempBook = searchBook(choice);
            if (tempBook== NULL) {
                cout << "Book not found! Please enter another Book ID\n";
                continue;
            }
            else {
                counter++;
                continue;
            }
        }
        if (counter == 1) {
            //System shows book selected by user.
            cout<<tempBook->displayBook(2);
            cout << "1. Update BookName\n2.Update Category\n3.Update Quantity\n4. Exit updating book\n";
            cin >> update;
            if (cin.fail() || update < 1 || update>4) {
                cout << "Please select a proper part to update\n";
            }
            switch (update) {
            case 1: {
                cout << "Plese enter new name of the book\n";
                getline(cin, stringValue);
                getline(cin, stringValue);
                tempBook->setName(stringValue);
            } break;
            case 2: {
                cout << "Plese enter new category of the book\n";
                Book::printCategory();
                cin >> intVal;
                while (intVal < 0 || intVal>3 || cin.fail())
                {
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore();
                    }
                    cout << "Invalid input\n";
                    cout << "Please choose the category from the range of 1-3\n ";
                    cin >> intVal;
                }
                stringValue = Book::convertCategory(intVal);
                tempBook->setCategory(stringValue);
            }break;
            case 3: {
                cout << "Plese enter new quantity of the book\n";
                cin >> intVal;
                while (intVal < 0 || cin.fail())
                {
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore();
                    }
                    cout << "Invalid input\n";
                    cout << "Please input a positive number\n ";
                    cin >> intVal;
                }
                tempBook->setQuantity(intVal);
            }break;
            case 4:
                counter=69;
                continue;
                break;
            default:
                continue;
            }
            cout << "Update successfully. Do you wish to continue updating current book?\n1.Yes\n2. No\n";
            cin >> intVal;
            if (intVal == 1) {
                continue;
            }
            else {
                counter++;
            }
        }
    } while (counter < 2);
}


void Book::deleteBook() {
    push(&head, "Hulu Langat", "Fiction", 4);
    push(&head, "Hang Tuah", "Fiction", 5);
    Book* tempBook = new Book;
    int choice, update, intVal, counter = 0;
    string stringValue;
    if (head == NULL) {
        cout << "**********\n No books found in the system. Please add new books \n**********\n";
        return;
    }
    do {
        if (counter == 0) {
            Book::displayRecord();
            cout << "\n Please select a book by keying in the book ID\n***Enter 1 to exit menu***\n ";
            cin >> choice;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                continue;
            }
            if (choice == 1) { break; }

            tempBook = searchBook(choice);
            if (tempBook == NULL) {
                cout << "Book not found! Please enter another Book ID\n";
                continue;
            }
            else {
                counter++;
                continue;
            }
        }
        if (counter == 1) {
            cout << tempBook->displayBook(2);
            cout << "1. Delete Book\n2. Exit deleting book\n";
            cin >> update;
            if (cin.fail() || update < 1 || update>2) {
                cout << "Please select a valid option\n";
            }
            switch (update) {
            case 1: {
            //if book==head then make head->next the new head;
                if (tempBook == head) {
                    if (tempBook->next != NULL) {
                        head = head->next;
                        free(tempBook);
                    }
                    else {
                        head = NULL;
                        free(tempBook);
                    }
                }else {
                //Assume the book u wanna delete is B, the book previous of it is A and the book after it is C
                //Now we find A and connect A->next to C. Then we delete B
                    Book* prevBook = head;
                    while (prevBook->next != NULL && prevBook->next != tempBook) {
                        prevBook = prevBook->next;
                    }
                    if (prevBook->next == NULL) {
                        cout << "\nGiven node is not present in Linked List";
                    }
                    prevBook->next = prevBook->next->next;
                    free(tempBook);
                }

            } break;
            case 2:
                counter = 69;
                continue;
                break;
            default:
                continue;
            }
            cout << "Update successfully. Do you wish to delete another book?\n1.Yes\n2. No\n";
            cin >> intVal;
            if (intVal == 1) {
                counter--;
                continue;
            }
            else {
                counter++;
            }
        }
    } while (counter < 2);
}

void Book::push(Book** head_ref, string name, string category, int quantity){
    bool duplicate = false;
    Book* new_node = new Book;
    do {

        new_node->setBookID(randomID());
        if (new_node->getBookID() == 1) { continue; }
        duplicate = checkDuplicateID(new_node->getBookID());

    } while (duplicate);

    new_node->setName(name);
    new_node->setCategory(category);
    new_node->setQuantity(quantity);
    new_node->next = *head_ref;
    *head_ref = new_node;
}

void Book::filterCategory() {
    push(&head, "Hulu Langat1", "Graphics", 4);
    push(&head, "Hang Tuah2", "Fiction", 5);
    push(&head, "Hulu Langat3", "Graphics", 4);
    push(&head, "Hang Tuah4", "Non-Fiction", 5);
    int counter = 0,choice;
    string category;
    do {
        if (counter == 0) {
            cout << "Filtering books by category\n**************\n";
            printCategory();
            cin >> choice;
            while (choice < 0 || choice>3 || cin.fail())
            {
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore();
                }
                cout << "Invalid input\n";
                cout << "Please choose the category from the range of 1-3\n ";
                cin >> choice;
            }
            counter++;
        }
        if (counter == 1) {
            category = Book::convertCategory(choice);
            cout << category << endl;
            struct Book* current;
            current = head;
            if (current == NULL) {
                cout << "No records found";
            }
            else {
                cout << "Book ID \tName \tCategory \t Quantity\n";
                while (current != NULL) {
                    if (current->getCategory() == category) {
                        cout << current->displayBook(1);
                    }
                    current = current->next;
                }

            }
            cout << "Do you wish to view another category?\n1.Yes\n2.No\n";
            cin >> choice;
            if (choice == 1) {
                counter--;
            }
            else {
                counter++;
                break;
            }
        }
    } while (counter < 2);

}
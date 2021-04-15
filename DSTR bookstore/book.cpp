#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
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

float Book::getPrice() {
    return this->price;
}

void Book::setPrice(float price) {
    this->price = price;
}
float Book::roundoff(float value, unsigned char prec)
{
    float pow_10 = pow(10.0f, (float)prec);
    return round(value * pow_10) / pow_10;
}

string Book::displayBook(int style) {
    switch (style) {
    case 1: {
        return to_string(getBookID()) + "\t" + getName() + "\t" + getCategory() + "\t" + to_string(getQuantity()) + "\t" + to_string(getPrice()) + "\n";
    }break;

    case 2: {
        //return "Book ID   : " + to_string(getBookID()) + "\n" + "Book Name : " + getName() + "\n" + "Category  : " + getCategory() + "\n" + "Quantity  : " + to_string(getQuantity()) + "\n" + "Price     :RM " + to_string(ceil(getPrice() * 100.0) / 100.0) + "\n";
        return "Book ID   : " + to_string(getBookID()) + "\n" + "Book Name : " + getName() + "\n" + "Category  : " + getCategory() + "\n" + "Quantity  : " + to_string(getQuantity()) + "\n" + "Price     :RM " + to_string(roundoff(getPrice(), 2)) + "\n";

    }break;
    default:
        return "Book ID   : " + to_string(getBookID()) + "\n" + "Book Name : " + getName() + "\n" + "Category  : " + getCategory() + "\n" + "Quantity  : " + to_string(getQuantity()) + "\n" + "Price     :RM " + to_string(roundoff(getPrice(), 2)) + "\n";
    }
}

void Book::printCategory() {
    cout << "1. Fiction" << endl;
    cout << "2. Non-Fiction" << endl;
    cout << "3. Graphics" << endl;
    cout << "Please select a category " << endl;
}

string Book::convertCategory(int selection) {
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
    float price;
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
    //Price
    cout << "Please enter a price" << endl;
    cin >> price;
    while (price < 0 || cin.fail())
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
        }
        cout << "Please enter a positive value\n";
        cin >> price;
    }
    newBook->setPrice(price);

    newBook->next = head;
    head = newBook;

}

void Book::displayRecord(Book* head1) {
    struct Book* current;
    if (head1 == NULL) {
        current = head;
    }
    else {
        current = head1;
    }
    if (current == NULL) {
        cout << "No records found";
    }
    else {
        cout << left << setw(15) << "Book ID"
            << left << setw(35) << "Name"
            << left << setw(15) << "Category"
            << left << setw(15) << "Quantity"
            << left << setw(15) << "Price(RM)" << endl;
        while (current != NULL) {
            cout << left << setw(15) << current->getBookID()
                << left << setw(35) << current->getName()
                << left << setw(15) << current->getCategory()
                << left << setw(15) << current->getQuantity()
                << left << setw(15) << ceil(current->getPrice() * 100.0) / 100.0 << endl;
            //cout<<current->displayBook(1);
            current = current->next;
        }

    }
}

bool Book::checkDuplicateID(int id) {
    bool found = false;
    Book* node = head;
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

Book* Book::searchBook(int id, Book* head1) {
    struct Book* current;
    if (head1 == NULL) {
        current = head;
    }
    else {
        current = head1;
    }
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
    int choice, update, intVal, counter = 0;
    string stringValue;
    float floatVal;
    do {
        if (counter == 0) {
            Book::displayRecord(head);
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
            tempBook = searchBook(choice, head);
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
            //System shows book selected by user.
            cout << tempBook->displayBook(2);
            cout << "1. Update BookName\n2.Update Category\n3.Update Quantity\n4. Update Price\n5. Exit updating book\n";
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
            case 4: {
                cout << "Plese enter new price of the book\n";
                cin >> floatVal;
                while (floatVal < 0 || cin.fail())
                {
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore();
                    }
                    cout << "Invalid input\n";
                    cout << "Please input a positive number\n ";
                    cin >> floatVal;
                }
                tempBook->setPrice(floatVal);
            }break;
            case 5:
                counter = 69;
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
    push(&head, 0, "Hulu Langat", "Fiction", 4, 4.00);
    push(&head, 0, "Hang Tuah", "Fiction", 5, 5.00);
    Book* tempBook = new Book;
    int choice, update, intVal, counter = 0;
    string stringValue;
    if (head == NULL) {
        cout << "**********\n No books found in the system. Please add new books \n**********\n";
        return;
    }
    do {
        if (counter == 0) {
            Book::displayRecord(head);
            cout << "\n Please select a book by keying in the book ID\n***Enter 1 to exit menu***\n ";
            cin >> choice;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                continue;
            }
            if (choice == 1) { break; }

            tempBook = searchBook(choice, head);
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
                }
                else {
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

void Book::push(Book** head_ref, int id, string name, string category, int quantity, float price) {
    bool duplicate = false;
    Book* new_node = new Book;
    // if id=0, then let system generates the book ID,else use the manual id provided by user
    if (id == 0) {
        do {

            new_node->setBookID(randomID());
            if (new_node->getBookID() == 1) { continue; }
            duplicate = checkDuplicateID(new_node->getBookID());

        } while (duplicate);
    }
    else {
        new_node->setBookID(id);
    }
    new_node->setName(name);
    new_node->setCategory(category);
    new_node->setQuantity(quantity);
    new_node->setPrice(price);
    new_node->next = *head_ref;
    *head_ref = new_node;
}

void Book::filterCategory() {

    int counter = 0, choice;
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

void Book::sortBook() {
    int counter = 0, choice;
    push(&head, 0, "Hulu Langat", "Fiction", 4, 5.00);
    push(&head, 0, "Hang Tuah", "Fiction", 5233, 7.50433434);
    push(&head, 0, "Aliff", "Fiction", 23, 23.60);
    push(&head, 0, "Ledong James", "sex", 5, 34.22);
    do {
        if (counter == 0) {
            cout << "Please select the sorting method\n1. Ascending Sort by book quantity\n2. Descending Sort by book Quantity\n3.Ascending sort by Book id\n4. Descending sort by Book id\n";
            cin >> choice;
            while (choice < 0 || choice>4 || cin.fail())
            {
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore();
                }
                cout << "Invalid input\n";
                cout << "Please choose the category from the range of 1-4\n ";
                cin >> choice;
            }
            counter++;
        }
        if (counter == 1) {
            switch (choice) {
            case 1:
                MergeSort(&head, 1);
                displayRecord(head);
                break;
            case 2:
                MergeSort(&head, 2);
                displayRecord(head);
                break;
            case 3:
                MergeSort(&head, 3);
                displayRecord(head);
                break;
            case 4:
                MergeSort(&head, 4);
                displayRecord(head);
                break;
            default:
                displayRecord(head);
            }
            cout << "Do you wish to sort by another method?\n1.Yes\n2.No\n";
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
// 1 for ascending sorting quantity, 2 for descending sorting quantity, 3 for ascending sorting book ID, 4 for descending sorting book ID
void Book::MergeSort(Book** headRef, int choice)
{

    Book* head1 = *headRef;
    Book* a;
    Book* b;

    /* Base case -- length 0 or 1 */
    if ((head1 == NULL) || (head1->next == NULL)) {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    FrontBackSplit(head1, &a, &b);

    if (choice == 1) {
        // ascending sort by quantity
        MergeSort(&a, 1);
        MergeSort(&b, 1);
        *headRef = SortedMerge(a, b, 1);
    }
    else if (choice == 2) {
        //descending sort by quantity
        MergeSort(&a, 2);
        MergeSort(&b, 2);
        *headRef = RevSortedMerge(a, b, 1);
    }
    else if (choice == 3) {
        //ascending sort by bookID
        MergeSort(&a, 1);
        MergeSort(&b, 1);
        *headRef = SortedMerge(a, b, 2);
    }
    else {
        //descending sort by bookID
        MergeSort(&a, 2);
        MergeSort(&b, 2);
        *headRef = RevSortedMerge(a, b, 2);
    }
}

// 1 for book quantity, 2 for book ID
Book* Book::SortedMerge(Book* a, Book* b, int choice)
{
    Book* result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (choice == 1) {
        if (a->getQuantity() <= b->getQuantity()) {
            result = a;
            result->next = SortedMerge(a->next, b, 1);
        }
        else {
            result = b;
            result->next = SortedMerge(a, b->next, 1);
        }
    }
    else {
        if (a->getBookID() <= b->getBookID()) {
            result = a;
            result->next = SortedMerge(a->next, b, 2);
        }
        else {
            result = b;
            result->next = SortedMerge(a, b->next, 2);
        }
    }

    return (result);
}

Book* Book::RevSortedMerge(Book* a, Book* b, int choice)
{
    Book* result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (choice == 1) {
        if (a->getQuantity() >= b->getQuantity()) {
            result = a;
            result->next = RevSortedMerge(a->next, b, 1);
        }
        else {
            result = b;
            result->next = RevSortedMerge(a, b->next, 1);
        }
    }
    else {
        if (a->getBookID() >= b->getBookID()) {
            result = a;
            result->next = RevSortedMerge(a->next, b, 2);
        }
        else {
            result = b;
            result->next = RevSortedMerge(a, b->next, 2);
        }
    }
    return (result);
}

/* UTILITY FUNCTIONS */
/* Split the Books of the given list into front and back halves,
    and return the two lists using the reference parameters.
    If the length is odd, the extra node should go in the front list.
    Uses the fast/slow pointer strategy. */
void Book::FrontBackSplit(Book* source,
    Book** frontRef, Book** backRef)
{
    Book* fast;
    Book* slow;
    slow = source;
    fast = source->next;

    /* Advance 'fast' two Books, and advance 'slow' one Book */
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* 'slow' is before the midpoint in the list, so split it in two
    at that point. */
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "transaction.h"
#include "book.h"


using namespace std;
using namespace transaction;
using namespace book;


Transaction* head = NULL;
Book* showBook = new Book;

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


Book* Transaction::getBoughtBooks() {
    return this->boughtBooks;
}

void Transaction::setBoughtBooks(int id, string name, string category, int quantity, float price) {
    Book* test = new Book;
    test->push(&this->boughtBooks, id, name, category, quantity, price);
}


void Transaction::addTransaction() {
    Transaction* newTrans = new Transaction;
    bool duplicate = false, exit = true;
    int choice;
    //newTrans->setBoughtBooks("Hulu Langat", "Fiction", 4, 4.00);
    //newTrans->setBoughtBooks("Hang Tuah", "Fiction", 5, 5.00);
    //Transaction ID
    do {
        newTrans->setTransactionID(randomID());
        if (newTrans->getTransactionID() == 1) { continue; }
        duplicate = checkDuplicateID(newTrans->getTransactionID());
    } while (duplicate);
    while (exit) {
        cout << "Please select an action\n1. Add books to cart\n2.Remove books from cart\n3.View cart\n4.Checkout Cart\n5.Cancel Transaction\n";
        cin >> choice;
        while (choice < 0 || choice>6 || cin.fail())
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
            }
            cout << "Invalid input\n";
            cout << "Please choose the choice from the range of 1-6 \n";
            cin >> choice;
        }

        switch (choice) {
        case 1:
            cout << "test\n";
            addtoCart(&newTrans);
            break;
        case 3:
            viewCart(&newTrans);
            break;
        case 5:
            exit = false;
            break;
        }

    }



    newTrans->next = head;
    head = newTrans;

    //newBook->next = head;
    //head = newBook;

}

void Transaction::addtoCart(Transaction** head) {
    // Selecting books
    int choice, quantity = 0, counter = 0;
    Book* tempBook = new Book;
    Book* bookInStock = new Book;
    Book* bookInCart = new Book;
    Book* cart = (*head)->getBoughtBooks();
    do {
        if (counter == 0) {
            cout << "Please select books to be added into the transaction\n";
            bookInStock->displayRecord(NULL);
            cout << "\n Please select a book by keying in the book ID\n***Enter 1 to exit menu***\n ";
            cin >> choice;
            while (cin.fail() && choice < 0)
            {
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore();
                }
                cout << "Invalid input\n";
                cout << "Please key in the book ID\n";
                cin >> choice;
            }
            // If user keys in 1 then user exits edit book menu
            if (choice == 1) { return; }
            // system finds the book based on the id given by user
            tempBook = bookInStock->searchBook(choice, NULL);
            if (tempBook == NULL) {
                cout << "Book not found! Please enter another Book ID\n";
                continue;
            }
            counter++;
        }
        if (counter == 1) {
            cout << tempBook->displayBook(2);
            cout << "Please enter a quantity of book u wish to buy.\n";
            cin >> quantity;
            cout << quantity << endl;
            if (quantity > tempBook->getQuantity()) {
                cout << "Quantity more than stock available.Please re-enter a smaller number 1\n";
                continue;
            }
            //search for the choosen book  in the transaction cart
            bookInCart = bookInStock->searchBook(choice, cart);
            // If the selected book is not within cart, then add it
            if (bookInCart == NULL) {
                (*head)->setBoughtBooks(tempBook->getBookID(), tempBook->getName(), tempBook->getCategory(), quantity, tempBook->getPrice());
                return;
            }
            else {
                cout << to_string(bookInCart->getQuantity()) << endl;
                //If theres same book within the cart, check the quantity
                //if the quantity in cart + quantity key in jn is greater than total books in stock
                //Then, tell user to rechoose smaller quantity.
                if (tempBook->getQuantity() < bookInCart->getQuantity() + quantity) {
                    cout << "Quantity more than stock available.Please re-enter a smaller number 2\n";
                    continue;
                }
                else {
                    //if its smaller then update the quantity of the book in the cart
                    while (cart != NULL) {
                        if (cart->getBookID() == tempBook->getBookID()) {
                            cart->setQuantity(cart->getQuantity() + quantity);
                            break;
                        }
                        cart = cart->next;
                    }

                }
                counter++;
            }


            return;


            return;

        }
    } while (counter < 2);


}

void Transaction::viewCart(Transaction** head) {
    Book* cart = (*head)->getBoughtBooks();
    cart->displayRecord(cart);
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

int Transaction::randomID() {
    int id = rand();
    return id;
}

void Transaction::displayRecord() {
    struct Transaction* current;
    current = head;

    if (current == NULL) {
        cout << "No records found";
    }
    else {
        while (current != NULL) {
            Book* bought = current->getBoughtBooks();
            while (bought != NULL) {
                cout << current->getTransactionID() << endl;
                cout << bought->displayBook(2);
                bought = bought->next;
            }
            current = current->next;
        }

        //cout << left << setw(15) << "Book ID"
        //    << left << setw(35) << "Name"
        //    << left << setw(15) << "Category"
        //    << left << setw(15) << "Quantity"
        //    << left << setw(15) << "Price(RM)" << endl;
        //while (current != NULL) {
        //    cout << left << setw(15) << current->getBookID()
        //        << left << setw(35) << current->getName()
        //        << left << setw(15) << current->getCategory()
        //        << left << setw(15) << current->getQuantity()
        //        << left << setw(15) << ceil(current->getPrice() * 100.0) / 100.0 << endl;
        //    //cout<<current->displayBook(1);
        //    current = current->next;
    }


}
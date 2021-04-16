#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "transaction.h"
#include "book.h"


using namespace std;
using namespace transaction;
using namespace book;


Transaction* transactionHead = NULL;
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



Book* Transaction::getBoughtBooks() {
    return this->boughtBooks;
}

void Transaction::setBoughtBooks(int id, string name, string category, int quantity, float price) {
    Book* test = new Book;
    test->push(&this->boughtBooks, id, name, category, quantity, price);
}

void Transaction::resetBoughtBooks() {
    this->boughtBooks = NULL;
    //this->boughtBooks->next = NULL;
    //this->boughtBooks->next = NULL;
}


void Transaction::addTransaction() {
    Transaction* newTrans = new Transaction;

    viewCart(&newTrans);
    bool duplicate = false,exit=true;
    int choice;
    //newTrans->setBoughtBooks(67,"Hulu Langat", "Fiction", 4, 4.00);
    //newTrans->setBoughtBooks(34,"Hang Tuah", "Fiction", 5, 5.00);
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
            cout << "Please choose the choice from the range of 1-5 \n";
            cin >> choice;
        }

        switch (choice) {
        case 1:
            //Add books to cart
            addtoCart(&newTrans);
            break;
        case 2:
            //Delete books from cart
            removeFromCart(&newTrans);
            break;
        case 3:
            //check books in the cart
            viewCart(&newTrans);
            break;
        case 4: {
            if (newTrans->getBoughtBooks() == NULL) {
                cout << "The order is empty, you cannot checkout.Please add on some books\n";
               
            }
            else {
                newTrans->setTotalPrice(calculateTotal(&newTrans));
                //this function updates the stock after minusing the books in the cart
                showBook->updateQuantity(newTrans->getBoughtBooks());
                newTrans->next = transactionHead;
                transactionHead = newTrans;
                exit = false;
            }
        }break;
        case 5:
            exit = false;
            break;
        }

    }


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
            cout << "Please enter a quantity of book u wish to buy.\nEnter 0 to exit menu\n";
            cin >> quantity;
            while (cin.fail() && quantity < 0)
            {
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore();
                }
                cout << "Invalid input\n";
                cout << "Please key in the postive number for quantity\n";
                cin >> quantity;
            }
            if (quantity == 0)break;
            if (quantity > tempBook->getQuantity()) {
                cout << "Quantity more than stock available.Please re-enter a smaller number 1\n";
                continue;
            }
            //If cart is empty, then add it without checking
            if (cart == NULL) {
                (*head)->setBoughtBooks(tempBook->getBookID(), tempBook->getName(), tempBook->getCategory(), quantity, tempBook->getPrice());
                return;
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
void Transaction::removeFromCart(Transaction** head) {
    int choice, quantity = 0, counter = 0;
    Book* tempBook = new Book;
    Book* bookInStock = new Book;
    Book* bookInCart = new Book;
    do {
        Book* cart = (*head)->getBoughtBooks();
        if (counter == 0) {           
            if (cart == NULL) {
                cout << "No records found\n";
                break;
            }
            cout << "Please select books to be removed\n";
            bookInStock->displayRecord(cart);
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
            tempBook = bookInStock->searchBook(choice, cart);
            if (tempBook == NULL) {
                cout << "Book not found! Please enter another Book ID\n";
                continue;
            }
            counter++;
        }
        if (counter == 1) {
            cout << tempBook->displayBook(2);
            cout << "Please select an action.\n1.Remove book from cart\n2.Cancel\n";
            cin >> quantity;
            while (cin.fail() || quantity < 1 || quantity>2 )
            {
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore();
                }
                cout << "Invalid input\n";
                cout << "Please choose from range of 1-2\n";
                cin >> quantity;
            }
            switch (quantity) {
            case 1: {
                //(*head)->resetBoughtBooks();
                ////if book==head then make head->next the new head;
                if (tempBook == cart) {
                    if (tempBook->next != NULL) {
                        (*head)->boughtBooks = (*head)->boughtBooks->next;
                        //cart = cart->next;
                        //cout << "1\n";
                        //free(tempBook);
                    }
                    else {
                        (*head)->resetBoughtBooks();
                        //cout << "2\n";
                        //free(tempBook);
                    }
                }
                else {
                    //cout << "3\n";
                    //Assume the book u wanna delete is B, the book previous of it is A and the book after it is C
                    //Now we find A and connect A->next to C. Then we delete B
                    Book* prevBook = cart;
                    while (prevBook->next != NULL && prevBook->next != tempBook) {
                        prevBook = prevBook->next;
                    }
                    if (prevBook->next == NULL) {
                        cout << "\nGiven node is not present in Linked List";
                    }
                    prevBook->next = prevBook->next->next;
                    //free(tempBook);
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
            cin >> quantity;
            if (quantity == 1) {
                counter--;
                continue;
            }
            else {
                counter++;
            }


            


           

        }
    } while (counter < 2);
}

void Transaction::viewCart(Transaction** transactionHead) {
    Book* cart = (*transactionHead)->getBoughtBooks();
    if (cart == NULL) {
        cout << "No records found"<<endl;
    }
    else {
        
        cart->displayRecord(cart);
    }
    
}

float Transaction::calculateTotal(Transaction** head) {
    Book* cart = (*head)->getBoughtBooks();
    float total=0;
    if (cart == NULL)return total;
    while (cart != NULL) {
        //get the price of the book by multiplying the price with quantity
        total += cart->getQuantity() * cart->getPrice();
        cart = cart->next;
    }
    return total;

}
bool Transaction::checkDuplicateID(int id) {
    bool found = false;
    Transaction* node = transactionHead;
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
    Transaction *choosenTrans =new Transaction;
    current = transactionHead;
    int choice,counter = 0;

    if (current == NULL) {
        cout << "No records found";
        return;
    }
    do {
        if (counter == 0) {
            cout << left << setw(15) << "Transaction ID"
                << left << setw(35) << "Total Price (RM)" << endl;
            while (current != NULL) {
                cout << left << setw(15) << current->getTransactionID()
                    << left << setw(35) << ceil(current->getTotalPrice() * 100.0) / 100.0 << endl;
                Book* bought = current->getBoughtBooks();
                //while (bought != NULL) {
                //    cout << current->getTransactionID() << endl;
                //    cout << bought->displayBook(2);
                //    bought = bought->next;
                //}
                current = current->next;
            }
            cout << "\n Please check transaction details by keying in the transaction ID\n***Enter 1 to exit menu***\n ";
            cin >> choice;
            while (cin.fail() && choice < 0)
            {
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore();
                }
                cout << "Invalid input\n";
                cout << "Please key in the transaction ID\n";
                cin >> choice;
            }
            if (choice == 1) { return; }
            // system finds the book based on the id given by user
            choosenTrans = choosenTrans->searchTransaction(choice, transactionHead);
            if (choosenTrans == NULL) {
                cout << "Book not found! Please enter another Book ID\n";
                continue;
            }
            counter++;
        }
        if (counter == 1) {
            showBook->displayRecord(choosenTrans->getBoughtBooks());
            cout << "Do you check another transaction?\n1.Yes\n2. No\n";
            cin >> choice;
            if (choice == 1) {
                counter--;
                continue;
            }
            else {
                counter++;
            }
        }
    } while (counter < 2);


    

}

Transaction* Transaction::searchTransaction(int id, Transaction* head1) {
    struct Transaction* current;
    current = head1;
    if (current == NULL) {
        return current;
    }
    while (current != NULL) {
        if (current->getTransactionID() == id) {
            return current;
        }
        current = current->next;
    }
    current = NULL;
    return current;

}

void Transaction::sortTransaction() {
    int counter = 0, choice;

    do {
        if (counter == 0) {
            cout << "Please select the sorting method\n1. Ascending Sort by Total Price\n2. Descending Sort by Total Price\n3.Ascending sort by Transaction id\n4. Descending sort by Transaction id\n";
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
                MergeSort(&transactionHead, 1);
                displayRecord();
                break;
            case 2:
                MergeSort(&transactionHead, 2);
                displayRecord();
                break;
            case 3:
                MergeSort(&transactionHead, 3);
                displayRecord();
                break;
            case 4:
                MergeSort(&transactionHead, 4);
                displayRecord();
                break;
            default:
                displayRecord();

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
void Transaction::MergeSort(Transaction** headRef, int choice)
{

    Transaction* head1 = *headRef;
    Transaction* a;
    Transaction* b;

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
Transaction* Transaction::SortedMerge(Transaction* a, Transaction* b, int choice)
{
    Transaction* result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (choice == 1) {
        if (a->getTotalPrice() <= b->getTotalPrice()) {
            result = a;
            result->next = SortedMerge(a->next, b, 1);
        }
        else {
            result = b;
            result->next = SortedMerge(a, b->next, 1);
        }
    }
    else {
        if (a->getTransactionID() <= b->getTransactionID()) {
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

Transaction* Transaction::RevSortedMerge(Transaction* a, Transaction* b, int choice)
{
    Transaction* result = NULL;

    /* Base cases */
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    /* Pick either a or b, and recur */
    if (choice == 1) {
        if (a->getTotalPrice() >= b->getTotalPrice()) {
            result = a;
            result->next = RevSortedMerge(a->next, b, 1);
        }
        else {
            result = b;
            result->next = RevSortedMerge(a, b->next, 1);
        }
    }
    else {
        if (a->getTransactionID() >= b->getTransactionID()) {
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
void Transaction::FrontBackSplit(Transaction* source,
    Transaction** frontRef, Transaction** backRef)
{
    Transaction* fast;
    Transaction* slow;
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
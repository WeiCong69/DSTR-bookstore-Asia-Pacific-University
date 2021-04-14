#include <iostream>
#include <string>
#include "menu.h"


using namespace std;
int main()
{
    bool exit = true;
    int selection;
    while (exit)
    {
        printMenu();
        cin >> selection;
        //If user doesn't key in number
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "Invalid Input detected. Please input numbers only" << endl;
            continue;
        }
        //If user chooses a number outside the range(1-9)
        if (selection > 9 || selection < 1)
        {
            //test fetch in visual studio
            cout << "Choice Outside the range.Please select 1-9" << endl;
            continue;
        }
        //If user selects 9, user gets to exit the system
        if (selection == 9) {
            exit = false;
            break;
        }
        performAction(selection);
        //diu lei
    }
}

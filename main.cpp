#include <iostream>
#include "Database.h"
using namespace std;

int main() {
    int choice;
    Database DB;

    cout << "1) Create new database\n"
            << "2) Open database\n"
            << "3) Close database\n"
            << "4) Display record\n"
            << "5) Update record\n"
            << "6) Create report\n"
            << "7) Add record\n"
            << "8) Delete record\n"
            << "9) Quit" << endl;
    cin >> choice;
    while(!cin.fail())
    {
        switch (choice) {
            case 1:
                cout << "Creating new database..." << endl;
                DB.createDB("small-colleges");
                break;
            case 2:
                cout << "Opening database..." << endl;
                DB.open("small-colleges.data");
                break;
            case 3:
                cout << "Closing database..." << endl;
                DB.close();
                break;
            case 4:
                cout << "Displaying record..." << endl;
                break;
            case 5:
                cout << "Updating record..." << endl;
                break;
            case 6:
                cout << "Creating report..." << endl;
                break;
            case 7:
                cout << "Adding record..." << endl;
                break;
            case 8:
                cout << "Deleting record..." << endl;
                break;
            case 9:
                cout << "Quitting..." << endl;
                    exit(0);
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 9." << endl;
                break;
        }
        cout << "1) Create new database\n"
            << "2) Open database\n"
            << "3) Close database\n"
            << "4) Display record\n"
            << "5) Update record\n"
            << "6) Create report\n"
            << "7) Add record\n"
            << "8) Delete record\n"
            << "9) Quit" << endl;
        cin >> choice;
    }
    return 0;
}
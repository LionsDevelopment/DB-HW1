/*
CSCE 45203: Database Management Systems HW#1
Luke Lyons: 010936877
Lizzie Howell: 011002727
*/
#include <iostream>
#include "Database.h"
using namespace std;

int main() {
    int choice;
    string userInput;
    Database DB;

    cout << "1) Create new database\n"
        << "2) Open database\n"
        << "3) Close database\n"
        << "4) Display record\n"
        << "5) Update record\n"
        << "6) Create report\n"
        << "7) Delete record\n"
        << "8) Quit"
        << endl;
    cin >> choice;
    while(!cin.fail())
    {
        switch (choice) {
            case 1:
                cout << "Please put filename:" << endl;
                cin >> userInput;
                cout << "Creating new database..." << endl;
                DB.createDB(userInput);
                break;
            case 2:
                cout << "Please put filename:" << endl;
                cin >> userInput;
                cout << "Opening database..." << endl;
                DB.open(userInput+".data");
            break;
            case 3:
                cout << "Closing database..." << endl;
                DB.close();
                break;
            case 4:
                cout << "Please put College ID to display:" << endl;
                cin >> userInput;
                cout << "Displaying record..." << endl;
                DB.displayRecord(userInput);
                break;
            case 5:
                cout << "Please put which College Id you want to update:" << endl;
                cin >> userInput;
                DB.updateRecord(userInput);
                cout << "Updating record..." << endl;
                break;
            case 6:
                cout << "Creating report..." << endl;
                DB.createReport();
                break;
            case 7:
                cout << "Please put in College ID to delete:" << endl;
                cin >> userInput;
                cout << "Deleting record..." << endl;
                DB.deleteRecord(userInput);
                break;
            case 8:
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
            << "7) Delete record\n"
            << "8) Quit"
            << endl;
        cin >> choice;
    }
    return 0;
}
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
    string filename;
    Database DB;

    cout << "1) Create new database\n"
            << "2) Open database\n"
            << "3) Close database\n"
            << "4) Display record\n"
            << "5) Update record\n"
            << "6) Create report\n"
            << "7) Add record\n"
            << "8) Delete record\n"
            << "9) Quit\n"
            << "10) Test database\n"
            << "11) Run linear search\n"
            << "12) Run binary search" << endl;

    cin >> choice;
    while(!cin.fail())
    {
        switch (choice) {
            case 1:
                cout << "Please put filename:" << endl;
                cin >> filename;
                cout << "Creating new database..." << endl;
                DB.createDB(filename);
                break;
            case 2:
                cout << "Please put filename:" << endl;
                cin >> filename;
                cout << "Opening database..." << endl;
                DB.open(filename+".data");
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
            case 10:
                cout << "Testing database..." << endl;
                DB.testDB();
                break;
            //For testing only, remove later :>
            case 11:
                cout << "Running Linear Search..." << endl;
                DB.runLinearSearch();
                break;
            case 12:
                cout << "Running Binary Search..." << endl;
                DB.runBinarySearch();
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
            << "9) Quit\n"
            << "10) Test database\n"
            << "11) Run linear search\n"
            << "12) Run binary search" << endl;
        cin >> choice;
    }
    return 0;
}
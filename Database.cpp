/*

*/
#include "Database.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

Database::Database()
{
    num_records = 0;
    record_size = 76;
    dataFilePtr = NULL;
    openFlag = false;
}

Database::~Database() {}

// Private methods

int Database::getRecord(string &collegeId, string &state, string &city, string &name)
{
    int result = -1;

    if (Datainout.peek() == '\n')
        Datainout.get();
    getline(Datainout, collegeId, ',');

    if (!collegeId.empty())
    {
        getline(Datainout, state, ',');
        getline(Datainout, city, ',');
        getline(Datainout, name, '\n');
        result = 1;
    }
    else
    {
        collegeId = "";
        state = "";
        city = "";
        name = "";
        result = 0;
    }

    return result;
}

bool Database::writeRecord(fstream &Data_out, string collegeId, string state, string city, string name)
{
    if (!Data_out.is_open())
        return false;
    else
    {
        string truncateCollegeId = collegeId.substr(0, 6);
        string truncateState = state.substr(0, 14);
        string truncateCity = city.substr(0, 16);
        string truncateName = name.substr(0, 36);

        Data_out << setw(6) << left << truncateCollegeId << ","
                 << setw(14) << left << truncateState << ","
                 << setw(16) << left << truncateCity << ","
                 << setw(36) << left << truncateName
                 << endl;

        return true;
    }
}

bool Database::readCSV(ifstream &Data_in, fstream &Data_out, string &collegeId, string &state, string &city, string &name)
{
    getline(Data_in, state, ',');
    getline(Data_in, city, ',');
    getline(Data_in, name, '\n');
    writeRecord(Data_out, collegeId, state, city, name);
    getline(Data_in, collegeId, ',');
    return true;
}

bool Database::overwriteRecord(string collegeId, string state, string city, string name)
{
    return false;
}

/*
parameter(s): collegeId, &recordNum, &state, &name
returns: Boolean, true if the collegeId was found, false if not
purpose: if db open, it uses seeks to perform binary search on the sorted data file to locate the id.
It fills in the parameters with the data (if found), otherwise it sets them to default values.
*/
bool Database::binarySearch(string collegeId, string &recordNum, string &state, string &city, string &name)
{
    if (Datainout.is_open())
    {
        cout << "Binary Search" << endl;
        int low = 0;
        int high = num_records - 1;
        int mid;
        string collegeIdMid;
        string stateMid;
        string cityMid;
        string nameMid;

        while (low <= high)
        {
            mid = (low + high) / 2;
            // cout << "Low: " << low << " High: " << high << " Mid: " << mid << endl;
            Datainout.seekg(mid * record_size);
            getRecord(collegeIdMid, stateMid, cityMid, nameMid);
            // cout << "CollegeIdMid: " << collegeIdMid << " CollegeId: " << collegeId << endl;
            if (collegeIdMid == collegeId)
            {
                recordNum = to_string(mid);
                state = stateMid;
                city = cityMid;
                name = nameMid;
                return true;
            }
            else if (collegeIdMid < collegeId)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
    }
    return false;
}

/*
** BONUS **
parameter(s): collegeId, &recordNum, &state, &name
returns: Boolean, true if the collegeId was found, false if not
purpose: if db open, it reads records from the overflowFile sequentially.
If the record is found, it fills in the parameters with the data (if found), otherwise it sets them to default values.
*/
bool Database::linearSearch(string collegeId, string &recordNum, string &state, string &city, string &name)
{
    string tempCollegeId;
    string tempState;
    string tempCity;
    string tempName;

    for (int i = 0; i < num_records; i++)
    {
        Datainout.seekg(i * record_size);
        getRecord(tempCollegeId, tempState, tempCity, tempName);
        if (tempCollegeId == collegeId)
        {
            recordNum = to_string(i);
            state = tempState;
            city = tempCity;
            name = tempName;
            return true;
        }
    }
    recordNum = "";
    state = "";
    city = "";
    name = "";
    return false;
}

// Public methods
void Database::open(string filename)
{
    // Open file in read/write mode
    ifstream configInfo;
    string numRecords, recordSize;
    configInfo.open((filename.substr(0, filename.length() - 5)) + ".config");
    getline(configInfo, numRecords, ',');
    getline(configInfo, recordSize, ' ');

    num_records = stoi(numRecords);
    record_size = stoi(recordSize);

    Datainout.open(filename.c_str(), fstream::in | fstream::out);
    if (Datainout.is_open())

        cout << "Database Opened" << endl;
    else
        cout << "Database Failed to Open" << endl;
}

void Database::close()
{
    num_records = 0;
    Datainout.close();
    if (!Datainout.is_open())
        cout << "Database Closed" << endl;
    else
        cout << "Database Failed to Close" << endl;
}

int Database::readRecord(const int recordNum)
{
    int result = -1;
    string collegeId, state, city, name;

    if ((recordNum >= 0) && (recordNum <= num_records))
    {
        Datainout.seekg(recordNum * record_size);
        streampos position = Datainout.tellg();
        result = getRecord(collegeId, state, city, name);
        Datainout.seekg(position, ios::beg);
        cout << "Record " << recordNum << " found: " << collegeId << ", " << state << ", " << city << ", " << name << endl;
    }
    else
        cout << "Record" << recordNum << " can't seem to be found" << endl;

    return result;
}

void Database::createDB(string filename)
{

    ifstream Data_in;
    fstream Data_out;
    fstream Config_out;
    string collegeId = "collegeId";
    string state = "state";
    string city = "city";
    string name = "name";
    int found_records = 0;

    Data_in.open(filename + ".csv");
    Data_out.open(filename + ".data", fstream::out);

    getline(Data_in, collegeId, ',');
    while (!Data_in.eof())
    {
        readCSV(Data_in, Data_out, collegeId, state, city, name);
        found_records++;
    }

    Data_in.close();
    Data_out.close();
    Config_out.open(filename + ".config", fstream::out);
    Config_out << found_records << "," << record_size;
}

bool Database::find(string collegeId, string &recordNum, string &state, string &city, string &name)
{
    return false;
}

bool Database::deleteRecord(string collegeId)
{
    return false;
}

bool Database::addRecord(string collegeID, string state, string city, string name)
{
    return false;
}

bool Database::testDB()
{
    // It should create the pair of files from the input file by calling "createDB" followed by "open".
    // Then, call readRecord on record 0, record 14, record 6, record -1, and record 1000
    // and print their contents (or an error message) to the screen;
    try
    {
        cout << "Creating database...." << endl;
        createDB("small-colleges");
        cout << "Opening database...." << endl;
        open("small-colleges.data");

        readRecord(0);
        readRecord(14);
        readRecord(6);
        readRecord(-1);
        readRecord(1000);

        cout << "Closing database...." << endl;
        close();
        return true;
    }
    catch (const exception &e)
    {
        cerr << "An error occurred: " << e.what() << endl;
        return false;
    }
}

bool Database::runLinearSearch()
{
    cout << "Creating database...." << endl;
    createDB("small-colleges");
    cout << "Opening database...." << endl;
    open("small-colleges.data");

    string collegeId, state, city, name;
    string recordNum;
    cout << "Enter collegeId to search for: ";
    cin >> collegeId;

    if (linearSearch(collegeId, recordNum, state, city, name))
    {
        cout << "Record found: " << collegeId << ", " << state << ", " << city << ", " << name << endl;
    }
    else
    {
        cout << "Record not found" << endl;
    }

    cout << "Closing database...." << endl;
    close();
    return true;
}

bool Database::runBinarySearch()
{
    cout << "Creating database...." << endl;
    createDB("small-colleges");
    cout << "Opening database...." << endl;
    open("small-colleges.data");

    string collegeId, state, city, name;
    string recordNum;
    cout << "Enter collegeId to search for: ";
    cin >> collegeId;

    if (binarySearch(collegeId, recordNum, state, city, name))
    {
        cout << "Record found: " << collegeId << ", " << state << ", " << city << ", " << name << endl;
    }
    else
    {
        cout << "Record not found" << endl;
    }

    cout << "Closing database...." << endl;
    close();
    return true;
}
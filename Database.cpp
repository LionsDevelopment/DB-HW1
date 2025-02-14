/*
CSCE 45203: Database Management Systems HW#1
Luke Lyons: 010936877
Lizzie Howell: 011002727
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
    record_size = 130;
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
        string truncateCity = city.substr(0, 26);
        string truncateName = name.substr(0, 80);

        Data_out << setw(6) << left << truncateCollegeId << ","
                 << setw(14) << left << truncateState << ","
                 << setw(26) << left << truncateCity << ","
                 << setw(80) << left << truncateName
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

bool Database::overwriteRecord(string recordNum, string collegeId, string state, string city, string name)
{

    if (!Datainout.is_open()) {
        cout << "Error opening data file" << endl;
        return false;
    }

    // Calculate the byte offset of the record based on the record number
    long offset = (stoi(recordNum)) * record_size;

    // Move to the beginning of the specified record
    Datainout.seekg(0, ios::beg);
    Datainout.seekg(offset, ios::beg);

    // Read the line for that record
    string line;
    getline(Datainout, line);

    // Move back to the beginning of record and using input pointer
    Datainout.clear();
    Datainout.seekp(offset, ios::beg);

    // Update the record with the new fields
    writeRecord(Datainout, collegeId, state, city, name);
    return true;
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
        cout << "Binary Searching..." << endl;
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

    if(getline(Data_in, collegeId, ','))
    {
        while (!Data_in.eof())
        {
            readCSV(Data_in, Data_out, collegeId, state, city, name);
            found_records++;
        }

        Data_in.close();
        Data_out.close();
        Config_out.open(filename + ".config", fstream::out);
        Config_out << found_records << "," << record_size;
        return;
    }
    else
    {
        cout << "Given file is empty or doens't exist" << endl;
        Data_in.close();
        Data_out.close();
        return;
    }
}

bool Database::find(string collegeId, string &recordNum, string &state, string &city, string &name)
{
    bool successfulFind = false;
    if(binarySearch(collegeId, recordNum, state, city, name))
    {
        if(!collegeId.empty() || collegeId != " ")
        {
            cout << "College Id: " << collegeId << " was found" << endl;
            successfulFind = true;
        }
        else
        {
            cout << "Couldn't find college id: " << collegeId << endl;
        }
    }
    else
    {   
        cout << " There was an issue. Couldn't find college id: " << collegeId << endl;
        successfulFind = false;
    }    
    return successfulFind;
}

bool Database::deleteRecord(string collegeId)
{
    if(!Datainout.is_open()){
        return false;
    }
    
    bool recordDeleted = false;
    string recordNum, state, city, name;

    if(find(collegeId, recordNum, state, city, name))
    {
        if(overwriteRecord(recordNum, collegeId, " ", " ", " "))
        {
            cout << "Record " << recordNum << " was deleted" << endl;
            recordDeleted = true;
        }
        else
        {
            cout << "Record " << recordNum << " couldn't be deleted" << endl;
            recordDeleted = false;
        }
    }
    else
    {
        cout << "Record could not be found" << endl;
        recordDeleted = false;
    }

    return recordDeleted;
}

void Database::displayRecord(string collegeID)
{
    string recordNum, state, city, name;
    if(Datainout.is_open())
        if(binarySearch(collegeID, recordNum, state, city, name))
            cout << "Record Number: " << recordNum << " College ID: " << collegeID << " State: " << state << " City: " << city << " Name: " << name << endl; 
        else
            cout << "Couldn't Find ID" << endl;
    else
    {
        cout << "Database could not be found :: \"not open\"" << endl;
        return;
    }
}

void Database::createReport()
{
    if(Datainout.is_open())
    {
        string line, collegeId, state, city, name;
        int count = 0;
        int reportLength = 10;
        while(count < reportLength)
        {
            getRecord(collegeId, state, city, name);
            cout << "Record Number: " << count << " College ID: " << collegeId << " State: " << state << " City: " << city << " Name: " << name << endl; 
            count++;
        }
        return;
    }
    else
    {
        cout << "Database could not be found :: \"not open\"" << endl;
        return;
    }
}

void Database::updateRecord(string collegeId)
{
    string recordNum, state, city, name;
    if(binarySearch(collegeId, recordNum, state, city, name))
    {
        cout << "Please choose what value to update:\n" 
            << "1) State\n" 
            << "2) City\n"
            << "3) Name\n";

        int choice;
        string newValue;
        cin >> choice;
        switch(choice) 
        {
            case 1:
                cout << "Please put new state:" << endl;
                cin >> newValue;
                overwriteRecord(recordNum, collegeId, newValue, city, name);
                break;
            case 2:
                cout << "Please put new city:" << endl;
                cin >> newValue;
                overwriteRecord(recordNum, collegeId, state, newValue, name);
                break;
            case 3:
                cout << "Please put new college name:" << endl;
                cin >> newValue;
                overwriteRecord(recordNum, collegeId, state, city, newValue);
                break;
            default:
                cout << "Incorrect Input" << endl;
                break;
        }
    }
    else
    {
        cout << "Couldn't find College Id: " << collegeId << endl;
        return;
    }
}
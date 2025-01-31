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

Database::~Database(){}


//Private methods

int Database::getRecord(string &collegeId, string &state, string &city, string &name)
{
    int result = -1;

    if(Datainout.peek() == '\n')
        Datainout.get();
    getline(Datainout, collegeId, ',');

    if(!collegeId.empty()){
        getline(Datainout, state, ',');
        getline(Datainout, city, ',');
        getline(Datainout, name, '\n');
        result = 1;
    }
    else {
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
    if(!Data_out.is_open()) 
            return false;
    else{
        string truncateCollegeId = collegeId.substr(0,6);
        string truncateState = state.substr(0,14);
        string truncateCity = city.substr(0,16);
        string truncateName = name.substr(0,36);

        Data_out << setw(6) << left << truncateCollegeId << ","
            << setw(14) << left << truncateState << ","
            << setw(16) << left << truncateCity << ","
            << setw(36) << left << truncateName
            << endl;

        return true;
    }
}

bool Database::overwriteRecord(string collegeId, string state, string city, string name)
{
    return false;
}

bool Database::binarySearch(string collegeId, string &recordNum, string &state, string &city, string &name)
{
    return false;
}

bool Database::linearSearch(string collegeId, string &recordNum, string &state, string &city, string &name)
{
    return false;
}


//Public methods
void Database::open(string filename)
{
    // Open file in read/write mode
    ifstream configInfo;
    string numRecords, recordSize;
    configInfo.open((filename.substr(0, filename.length() - 5))+".config");
    getline(configInfo, numRecords, ',');
    getline(configInfo, recordSize, ' ');

    num_records = stoi(numRecords);
    record_size = stoi(recordSize);

    Datainout.open(filename.c_str(), fstream::in | fstream::out);
    if(Datainout.is_open())

        cout << "Database Opened" << endl;
    else    
        cout << "Database Failed to Open" << endl;

}

void Database::close()
{
    num_records = 0;
    Datainout.close();
    if(!Datainout.is_open())
        cout << "Database Closed" << endl;
    else    
        cout << "Database Failed to Close" << endl;
}

int Database::readRecord(const int recordNum)
{
    int result = -1;
    string collegeId, state, city, name;

    if((recordNum >= 0 ) && (recordNum <= num_records)){
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


void Database::createDB(string filename){
    
    ifstream Data_in;
    fstream Data_out;
    fstream Config_out;
    string collegeId = "collegeId"; 
    string state = "state";
    string city = "city";
    string name = "name";
    int found_records = 0; 
    
    Data_in.open(filename+".csv");
    Data_out.open(filename+".data", fstream::out);
    

    getline(Data_in, collegeId, ',');
    while(!Data_in.eof()){
        getline(Data_in, state, ',');
        getline(Data_in, city, ',');
        getline(Data_in, name);
        
        writeRecord(Data_out, collegeId, state, city, name);
        found_records++;

        getline(Data_in, collegeId, ',');
    }
    
    Data_in.close();
    Data_out.close();
    Config_out.open(filename+".config", fstream::out);
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


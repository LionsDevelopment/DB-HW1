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
    record_size = 0;
    dataFilePtr = NULL;
    openFlag = false;

}

Database::~Database(){}


//Private methods

//Need to double check, does not work 100% properly
int Database::getRecord(string &collegeId, string &state, string &city, string &name)
{
    int result = -1;
    string temp_record;
    streampos position = Datainout.tellg();
    getline(Datainout, temp_record);

    stringstream stream(temp_record);
    vector<string> recordInfo;


    if(!temp_record.empty()){
        Datainout.seekg(position, ios::beg);
        Datainout >> collegeId >> state >> city >> name;
        result = 1;
    }
    else if(!temp_record.empty()){
        collegeId = "";
        state = "";
        city = "";
        name = "";
        result = 0;
    }

    return result;
}


bool Database::writeRecord(string collegeId, string state, string city, string name)
{
    
}

bool Database::overwriteRecord(string collegeId, string state, string city, string name)
{
    
}

bool Database::binarySearch(string collegeId, string &recordNum, string &state, string &city, string &name)
{
    
}

bool Database::linearSearch(string collegeId, string &recordNum, string &state, string &city, string &name)
{
    
}


//Public methods
void Database::open(string filename)
{
    
}

void Database::close()
{
    
}

//Erm proably also doesn't work, not to sure about the assigning of the string values and calling the get record.
int Database::readRecord(const int recordNum)
{
    int result = -1;
    string collegeId, state, city, name;

    if((recordNum >= 0 ) && (recordNum <= numRecords - 1)){
        Datainout.seekg(recordNum * recordSize);
        result = getRecord(collegeId, state, city, name);
    }
    else
        cout << "Record" << recordNum << " can't seem to be found" << endl;
    
    return result;
}

bool Database::find(string collegeId, string &recordNum, string &state, string &city, string &name)
{
    
}

bool Database::deleteRecord(string collegeId)
{
    
}

bool Database::addRecord(string collegeID, string state, string city, string name)
{
    
}


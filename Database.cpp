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

}

Database::~Database()
{

}



//Private methods
int Database::getRecord(string &collegeId, string &state, string &city, string &name)
{


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

int Database::readRecord(string recordNum)
{
    
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


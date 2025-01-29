/*

*/

#include <iostream>
#include <fstream>

using namespace std;

class Database
{
    private:
        //Private Variables
        fstream Datainout;
        string *dataFilePtr;
        int num_records;
        int record_size;
        bool openFlag;

        //Private methods
        int getRecord(string &collegeId, string &state, string &city, string &name);

        bool writeRecord(string collegeId, string state, string city, string name);

        bool overwriteRecord(string collegeId, string state, string city, string name);

        bool binarySearch(string collegeId, string &recordNum, string &state, string &city, string &name);

        bool linearSearch(string collegeId, string &recordNum, string &state, string &city, string &name);
    
    public:
        //Private Variables
        const static int recordSize = 100;
        const static int numRecords = 100;

        //Public methods
        Database();
        ~Database();

        void open(string filename);

        void close();

        int readRecord(const int recordNum);

        bool find(string collegeId, string &recordNum, string &state, string &city, string &name);

        bool deleteRecord(string collegeId);

        bool addRecord(string collegeID, string state, string city, string name);

};

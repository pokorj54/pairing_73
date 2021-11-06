#include <sqlite3.h>

#include <cassert>
#include <iostream>

using namespace std;

string DB_Name = "positions/DB";

static int callback(void* ignored, int argc, char** argv, char** columns) {
    assert(argc == 1);
    (void)ignored;
    (void)columns;
    cout << argv[0];

    return 0;
}

int selectData(string start_position) {
    sqlite3* DB;
    char* errorMsg;

    string sql = "SELECT PAIRING FROM POSITIONS WHERE START_POSITION = '" + start_position + "';";

    int exit = sqlite3_open(DB_Name.c_str(), &DB);
    exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &errorMsg);

    if (exit != SQLITE_OK) {
        cerr << "Error in finding data" << endl;
        cerr << errorMsg << endl;
        sqlite3_free(errorMsg);
    }
    return 0;
}

int main(int argc, char** args) {
    if (argc != 2) {
        cerr << "Expected 1 argument explaining position eg. 441_333_221_222_044_006" << endl;
        return 1;
    }
    selectData(args[1]);
    return 0;
}
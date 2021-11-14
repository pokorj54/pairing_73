#include <sqlite3.h>

#include <cassert>
#include <iostream>

using namespace std;

string DB_Name = "positions/DB";

int create_index() {
    sqlite3* DB;
    char* errorMsg;

    string sql = "CREATE UNIQUE INDEX idx_start_position ON POSITIONS(START_POSITION);";

    int exit = sqlite3_open(DB_Name.c_str(), &DB);
    exit = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &errorMsg);

    if (exit != SQLITE_OK) {
        cerr << "Error in creating the index" << endl;
        cerr << errorMsg << endl;
        sqlite3_free(errorMsg);
    }
    return 0;
}

int main(void) {
    create_index();
    return 0;
}
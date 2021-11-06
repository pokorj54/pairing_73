
#include "sql_outputer.hpp"

SQLOutputer::SQLOutputer(string DB_filename) : DB_filename(DB_filename) {}

SQLOutputer::~SQLOutputer() {
    insertAllToDatabase();
}

void SQLOutputer::outputSolution(const array<array<array<int, 7>, 7>, 7>& solutionGrid, const Board& board) {
    buffer.push_back({solutionGrid, board});
    if (buffer.size() >= 1000) {
        insertAllToDatabase();
    }
}
void SQLOutputer::insertAllToDatabase() {
    sqlite3* DB;
    char* messageError;
    int exit = sqlite3_open(DB_filename.c_str(), &DB);
    sqlite3_exec(DB, "BEGIN TRANSACTION;", NULL, NULL, NULL);
    for (const auto& p : buffer) {
        auto solutionGrid = p.first;
        Board board = p.second;
        string sql(
            "INSERT INTO POSITIONS (START_POSITION, PAIRING) VALUES('" + board.toString('_') + "', '" + solution_to_string(solutionGrid) + "');");

        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Error when inserting data." << endl;
            cerr << messageError << endl;
            cerr << board.toString() << endl;
            cerr << solution_to_string(solutionGrid) << endl;
            sqlite3_free(messageError);
        } else {
            cout << "Records inserted successfully!" << endl;
        }
    }
    sqlite3_exec(DB, "END TRANSACTION;", NULL, NULL, NULL);
    sqlite3_close(DB);
    buffer.clear();
}

void SQLOutputer::initialize_DB() {
    sqlite3* DB;
    char* messageError;

    string sql_command =
        "DROP TABLE IF EXISTS POSITIONS;"
        "CREATE TABLE POSITIONS("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "START_POSITION  CHAR(50),"
        "PAIRING         CHAR(1500));";

    try {
        int exit = 0;
        exit = sqlite3_open(DB_filename.c_str(), &DB);

        exit = sqlite3_exec(DB, sql_command.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Error in creating the table." << endl;
            cerr << messageError << endl;
            sqlite3_free(messageError);
        } else {
            cout << "Table created successfully" << endl;
        }
        sqlite3_close(DB);
    } catch (const exception& e) {
        cerr << e.what();
    }
}
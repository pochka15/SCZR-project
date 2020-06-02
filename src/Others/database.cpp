#include <fstream>
#include <sqlite3.h>
#include <cstring>
#include <sstream>
#include <iostream>
#include "database.h"
#include "utilities.h"

const char *kDbFileName = "testDb.db";


/**
 * @return Opened database with the name provided in kDbFileName
 */
// TODO(@pochka15): test
sqlite3 *openedDb() {
    sqlite3 *outDb;
    std::stringstream dbFileUri;
    dbFileUri << "file:" << kDbFileName;

    int rc = sqlite3_open(dbFileUri.str().c_str(), &outDb);
    if (rc != SQLITE_OK) {
        exitWithError("Unable to open the database");
    }
    return outDb;
}

/**
 * Fill the table COVID-statistic with some hard-coded values. The table will be either created or the existing one will be used
 * @param openedDb
 */
// TODO(@pochka15): test
void fillDbTable(sqlite3 *openedDb) {
    char *zErrMsg = nullptr;
    int rc;

    const char *statement1 = "create table if not exists \"COVID-statistic\"\n"
                             "(\n"
                             "    Country VARCHAR(30),\n"
                             "    InfectedNumer INTEGER,\n"
                             "    Date DATE\n"
                             ");";

    rc = sqlite3_exec(openedDb, statement1, nullptr, nullptr, &zErrMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(zErrMsg);
        exitWithError(sqlite3_errmsg(openedDb));
    }
    const char *statement = "INSERT INTO \"COVID-statistic\" (Country, InfectedNumer, Date)\n"
                            "VALUES ('China', 1439323776, '2020-06-02'),\n"
                            "       ('India', 1380004385, '2020-06-02'),\n"
                            "       ('United States', 331002651, '2020-06-02'),\n"
                            "       ('Indonesia', 273523615, '2020-06-02'),\n"
                            "       ('Pakistan', 220892340, '2020-06-02'),\n"
                            "       ('Brazil', 212559417, '2020-06-02'),\n"
                            "       ('Nigeria', 206139589, '2020-06-02'),\n"
                            "       ('Bangladesh', 164689383, '2020-06-02'),\n"
                            "       ('Russia', 145934462, '2020-06-02'),\n"
                            "       ('Mexico', 128932753, '2020-06-02'),\n"
                            "       ('Japan', 126476461, '2020-06-02'),\n"
                            "       ('Ethiopia', 114963588, '2020-06-02'),\n"
                            "       ('Philippines', 109581078, '2020-06-02'),\n"
                            "       ('Egypt', 102334404, '2020-06-02'),\n"
                            "       ('Vietnam', 97338579, '2020-06-02'),\n"
                            "       ('DR Congo', 89561403, '2020-06-02'),\n"
                            "       ('Turkey', 84339067, '2020-06-02'),\n"
                            "       ('Iran', 83992949, '2020-06-02'),\n"
                            "       ('Germany', 83783942, '2020-06-02'),\n"
                            "       ('Thailand', 69799978, '2020-06-02'),\n"
                            "       ('United Kingdom', 67886011, '2020-06-02'),\n"
                            "       ('France', 65273511, '2020-06-02'),\n"
                            "       ('Italy', 60461826, '2020-06-02'),\n"
                            "       ('Tanzania', 59734218, '2020-06-02'),\n"
                            "       ('South Africa', 59308690, '2020-06-02'),\n"
                            "       ('Myanmar', 54409800, '2020-06-02'),\n"
                            "       ('Kenya', 53771296, '2020-06-02'),\n"
                            "       ('South Korea', 51269185, '2020-06-02'),\n"
                            "       ('Colombia', 50882891, '2020-06-02'),\n"
                            "       ('Spain', 46754778, '2020-06-02');";
    rc = sqlite3_exec(openedDb, statement, nullptr, nullptr, &zErrMsg);
    if (rc != SQLITE_OK) {
        sqlite3_free(zErrMsg);
        exitWithError(sqlite3_errmsg(openedDb));
    }
}

//TODO(@pochka15): Wy doesn't it work? :(
void generateDatabaseFile() {
    std::cout << "Looks like it doesn't work :(\n";
    std::ofstream("testDb.db").close(); // Create database
    sqlite3 *openedDatabase = openedDb();
    fillDbTable(openedDatabase);
    sqlite3_close(openedDatabase);
}

#include <iostream>
#include <string>
#include "database.h"

int createDatabase(const char* path) {
	sqlite3* db;
	int status = sqlite3_open(path, &db);
	if (status) {
		std::cout << "Error creating database at location " << path << std::endl;
	}
	else {
		std::cout << "Successfully created database at location " << path << std::endl;
	}
	sqlite3_close(db);

	return 0;
}

int createTable(const char* path) {
	std::string table_schema = (
		"CREATE TABLE IF NOT EXISTS monsters("
		"id INTEGER PRIMARY KEY,"
		"name TEXT NOT NULL,"
		"primary_type TEXT NOT NULL,"
		"secondary_type TEXT);"
	);

	sqlite3* db;

	try {
		int exit = 0;
		exit = sqlite3_open(path, &db);

		char* errorMessage;
		exit = sqlite3_exec(db, table_schema.c_str(), NULL, 0, &errorMessage);

		if (exit != SQLITE_OK) {
			std::cout << "Error creating table schema in database at location " << path << std::endl;
			sqlite3_free(errorMessage);
		}
		else {
			std::cout << "Successfully created table schema in database at location " << path << std::endl;
		}
		sqlite3_close(db);
	}
	catch (const std::exception &e) {
		std::cerr << e.what();
	}

	return 0;
}

int insertDataFromJson(const char* dbPath, const char* jsonPath) {

}

int debugCallback(void* NotUsed, int argc, char** argv, char** azColName) {

}

#include <iostream>
#include <fstream>
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
		"secondary_type TEXT NOT NULL);"
	);

	sqlite3* db;

	try {
		int exit = 0;
		exit = sqlite3_open(path, &db);

		char* errorMessage;
		exit = sqlite3_exec(db, table_schema.c_str(), NULL, 0, &errorMessage);

		if (exit != SQLITE_OK) {
			std::cout << "Error creating table schema in database at location " << path << std::endl;
			std::cout << "Error Code: " << exit << std::endl;
			std::cout << "Error Message: " << errorMessage << std::endl;
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

int deleteTable(const char* path) {
	sqlite3* db;
	char* errorMessage;
	int exit = sqlite3_open(path, &db);


	std::string clear{ "DROP TABLE monsters" };
	exit = sqlite3_exec(db, clear.c_str(), NULL, 0, &errorMessage);
	if (exit != SQLITE_OK) {
		std::cerr << "Error clearing existing monster data" << std::endl;
		std::cout << "Error Code: " << exit << std::endl;
		std::cout << "Error Message: " << errorMessage << std::endl;
	}
	else {
		std::cout << "Successfully dropped data table from database at location " << path << std::endl;
	}

	return 0;
}

int clearTable(const char* path) {
	sqlite3* db;
	char* errorMessage;
	int exit = sqlite3_open(path, &db);


	std::string clear{ "DELETE FROM monsters" };
	exit = sqlite3_exec(db, clear.c_str(), NULL, 0, &errorMessage);
	if (exit != SQLITE_OK) {
		std::cerr << "Error clearing existing monster data" << std::endl;
		std::cout << "Error Code: " << exit << std::endl;
		std::cout << "Error Message: " << errorMessage << std::endl;
	}
	else {
		std::cout << "Successfully cleared data from database at location " << path << std::endl;
	}

	return 0;
}

int insertDataFromJson(const char* dbPath, const char* jsonPath) {
	std::ifstream monster_json_file(jsonPath, std::ifstream::binary);
	Json::Value monsters;
	monster_json_file >> monsters;

	sqlite3* db;
	char* errorMessage;
	int exit = sqlite3_open(dbPath, &db);

	int n = monsters.size();
	for (int i = 0; i < n; i++) {
		auto mon_info = monsters[i];

		std::string data_schema = generateQueryString(mon_info);
		exit = sqlite3_exec(db, data_schema.c_str(), NULL, 0, &errorMessage);
		if (exit != SQLITE_OK) {
			std::cerr << "Error inserting monster data" << std::endl;
			std::cout << "Error Code: " << exit << std::endl;
			std::cout << "Error Message: " << errorMessage << std::endl;
			sqlite3_free(errorMessage);
			break;
		}
	}

	std::cout << "Successfully converted json data from " << jsonPath << " to database at location " << dbPath << std::endl;
	sqlite3_close(db);
	return 0;
}

std::string generateQueryString(Json::Value mon_info) {
	std::string monName = mon_info["name"].asString();
	std::string primType = mon_info["types"]["primary"].asString();
	std::string secType = mon_info["types"]["secondary"].asString();

	std::string data_schema{
	"INSERT INTO monsters (name, primary_type, secondary_type)"
	"VALUES('" + monName + "', '" + primType + "', '" + secType + "');"
	};

	return data_schema;
}

int debugCallback(void* NotUsed, int argc, char** argv, char** azColName) {
	return 0;
}

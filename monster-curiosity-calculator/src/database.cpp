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
		"dex_number INTEGER NOT NULL,"
		"primary_type TEXT NOT NULL,"
		"secondary_type TEXT NOT NULL,"
		"height DOUBLE NOT NULL,"
		"weight DOUBLE NOT NULL,"
		"hp INTEGER NOT NULL,"
		"attack INTEGER NOT NULL,"
		"defense INTEGER NOT NULL,"
		"special_attack INTEGER NOT NULL,"
		"special_defense INTEGER NOT NULL,"
		"speed INTEGER NOT NULL,"
		"stat_total INTEGER NOT NULL"
		");"
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


	std::string clear{ "DROP TABLE IF EXISTS monsters" };
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
	std::string dexNum = mon_info["id"].asString();
	std::string primType = mon_info["types"]["primary"].asString();
	std::string secType = mon_info["types"]["secondary"].asString();
	std::string height = mon_info["height(m)"].asString();
	std::string weight = mon_info["weight(kg)"].asString();
	std::string health = mon_info["stats"]["hp"].asString();
	std::string attack = mon_info["stats"]["attack"].asString();
	std::string defense = mon_info["stats"]["defense"].asString();
	std::string spe_atk = mon_info["stats"]["special-attack"].asString();
	std::string spe_def = mon_info["stats"]["special-defense"].asString();
	std::string speed = mon_info["stats"]["speed"].asString();
	std::string stat_total = mon_info["stats"]["total"].asString();

	std::string data_schema{
	"INSERT INTO monsters (name, dex_number, primary_type, secondary_type, height, weight, hp, attack, defense, special_attack, special_defense, speed, stat_total)"
	"VALUES('"
	};
	data_schema += monName + "', '";
	data_schema += dexNum + "', '";
	data_schema += primType + "', '";
	data_schema += secType + "', '";
	data_schema += height + "', '";
	data_schema += weight + "', '";
	data_schema += health + "', '";
	data_schema += attack + "', '";
	data_schema += defense + "', '";
	data_schema += spe_atk + "', '";
	data_schema += spe_def + "', '";
	data_schema += speed + "', '";
	data_schema += stat_total;
	data_schema += "');";

	return data_schema;
}

int debugCallback(void* NotUsed, int argc, char** argv, char** azColName) {
	return 0;
}

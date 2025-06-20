#include "database.h"

#include <iostream>
#include <fstream>
#include <string>
#include <format>
#include <chrono>

#include <sqlite3.h>
#include <json/json.h>
#include <json/value.h>

#include "mcc_structs.h"

namespace monster_calculator {

static const bool kDebug = true;

static const std::string kDbPath = "c:\\DB_TEST\\test.db";
static const std::string kJsonPath = "c:\\DB_TEST\\mccdata.json";

static int query_result_count = 0;
static int events_logged = 0;

int CreateDatabase() {
	const char* database_path = kDbPath.c_str();

	sqlite3* db;
	int status = sqlite3_open(database_path, &db);
	if (status) {
		std::cout << "Error opening database at location " << database_path << std::endl;
	}
	else {
		std::cout << "Successfully opened database at location " << database_path << std::endl;
	}
	sqlite3_close(db);

	return 0;
}

int CreateMainTable(OutputEnvironment& output_environment) {
	std::string table_schema = (
		"CREATE TABLE IF NOT EXISTS monsters("
		"id INTEGER PRIMARY KEY,"
		"name TEXT NOT NULL,"
		"dex_number INTEGER NOT NULL,"
		"primary_type TEXT NOT NULL,"
		"secondary_type TEXT NOT NULL,"
		"height DOUBLE NOT NULL,"
		"weight DOUBLE NOT NULL,"
		"ability_1 TEXT NOT NULL,"
		"ability_2 TEXT NOT NULL,"
		"hidden_ability TEXT NOT NULL,"
		"hp INTEGER NOT NULL,"
		"attack INTEGER NOT NULL,"
		"defense INTEGER NOT NULL,"
		"special_attack INTEGER NOT NULL,"
		"special_defense INTEGER NOT NULL,"
		"speed INTEGER NOT NULL,"
		"stat_total INTEGER NOT NULL"
		");"
		);

	const char* database_path = kDbPath.c_str();
	sqlite3* db;
	try {
		int exit = 0;
		exit = sqlite3_open(database_path, &db);

		char* error_message;
		exit = sqlite3_exec(db, table_schema.c_str(), NULL, 0, &error_message);

		if (exit != SQLITE_OK) {
			LogError(output_environment, exit, error_message);
			sqlite3_free(error_message);
		}
		else {
			std::cout << "Successfully created table schema in database at location " << database_path << std::endl;
		}
		sqlite3_close(db);
	}
	catch (const std::exception& e) {
		std::cerr << e.what();
	}

	return 0;
}

int DeleteMainTable(OutputEnvironment& output_environment) {
	const char* database_path = kDbPath.c_str();
	sqlite3* db;
	int exit = sqlite3_open(database_path, &db);

	char* error_message;
	std::string clear {"DROP TABLE IF EXISTS monsters"};
	exit = sqlite3_exec(db, clear.c_str(), NULL, 0, &error_message);
	if (exit != SQLITE_OK) {
		LogError(output_environment, exit, error_message);
	}
	else {
		std::cout << "Successfully dropped data table from database at location " << database_path << std::endl;
	}

	return 0;
}

int ClearMainTable(OutputEnvironment& output_environment) {
	const char* database_path = kDbPath.c_str();
	sqlite3* db;
	int exit = sqlite3_open(database_path, &db);

	char* error_message;
	std::string clear {"DELETE FROM monsters"};
	exit = sqlite3_exec(db, clear.c_str(), NULL, 0, &error_message);
	if (exit != SQLITE_OK) {
		LogError(output_environment, exit, error_message);
	}
	else {
		std::cout << "Successfully cleared data from database at location " << database_path << std::endl;
	}

	return 0;
}

int InsertDataFromJson(OutputEnvironment& output_environment) {
	const char* json_path = kJsonPath.c_str();
	std::ifstream monster_json_file(json_path, std::ifstream::binary);
	Json::Value monsters;
	monster_json_file >> monsters;

	const char* database_path = kDbPath.c_str();
	sqlite3* db;
	int exit = sqlite3_open(database_path, &db);

	char* error_message;
	int n = monsters.size();
	for (int i = 0; i < n; i++) {
		auto mon_info = monsters[i];

		std::string data_schema = GenerateJsonDataString(mon_info);
		exit = sqlite3_exec(db, data_schema.c_str(), NULL, 0, &error_message);
		if (exit != SQLITE_OK) {
			LogError(output_environment, exit, error_message);
			sqlite3_free(error_message);
			break;
		}
	}

	std::cout << "Successfully converted JSON data from " << json_path << " to database at location " << database_path << std::endl;
	sqlite3_close(db);
	return 0;
}

std::string GenerateJsonDataString(Json::Value mon_info) {
	std::string mon_name = mon_info["name"].asString();
	std::string dex_num = mon_info["id"].asString();

	std::string prim_type = mon_info["types"]["primary"].asString();
	std::string sec_type = mon_info["types"]["secondary"].asString();

	std::string height = mon_info["height(m)"].asString();
	std::string weight = mon_info["weight(kg)"].asString();

	std::string abil1 = mon_info["abilities"]["first"].asString();
	std::string abil2 = mon_info["abilities"]["second"].asString();
	std::string abil_hidden = mon_info["abilities"]["hidden"].asString();

	std::string health = mon_info["stats"]["hp"].asString();
	std::string attack = mon_info["stats"]["attack"].asString();
	std::string defense = mon_info["stats"]["defense"].asString();
	std::string spe_atk = mon_info["stats"]["special-attack"].asString();
	std::string spe_def = mon_info["stats"]["special-defense"].asString();
	std::string speed = mon_info["stats"]["speed"].asString();
	std::string stat_total = mon_info["stats"]["total"].asString();

	std::string data_schema {
		"INSERT INTO monsters (name, dex_number, primary_type, secondary_type, height, weight, ability_1, ability_2, hidden_ability, hp, attack, defense, special_attack, special_defense, speed, stat_total)"
		"VALUES('"
	};
	data_schema += mon_name + "', '";
	data_schema += dex_num + "', '";

	data_schema += prim_type + "', '";
	data_schema += sec_type + "', '";

	data_schema += height + "', '";
	data_schema += weight + "', '";

	data_schema += abil1 + "', '";
	data_schema += abil2 + "', '";
	data_schema += abil_hidden + "', '";

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

int QueryDatabase(QueryParameter& query_parameter, OutputEnvironment& output_environment) {
	const char* database_path = kDbPath.c_str();
	sqlite3* db;
	int exit = sqlite3_open(database_path, &db);

	// make sure to clear existing sub-table if it exists
	char* error_message;
	std::string clear {"DROP TABLE IF EXISTS submonsters"};
	exit = sqlite3_exec(db, clear.c_str(), NULL, 0, &error_message);
	if (exit != SQLITE_OK) {
		LogError(output_environment, exit, error_message);
	}
	else {
		std::cout << "Successfully cleared subset data from database at location " << database_path << std::endl;
	}

	// create subtable with schema of main table
	std::string parameter_string = GenerateQueryParameterString(query_parameter);
	std::string query_string = "CREATE TABLE submonsters AS SELECT * FROM monsters "
		+ parameter_string + ";";
	exit = sqlite3_exec(db, query_string.c_str(), NULL, 0, &error_message);


	query_string = "SELECT * FROM submonsters;";
	query_result_count = 0;
	output_environment.subset_entries.clear();
	sqlite3_stmt* stmt;
	exit = sqlite3_prepare_v2(db, query_string.c_str(), -1, &stmt, NULL);
	if (exit != SQLITE_OK) {
		std::cout << "ERROR" << std::endl;
	}
	while ((exit = sqlite3_step(stmt)) == SQLITE_ROW) {
		++query_result_count;
		int id = sqlite3_column_int(stmt, 0);
		const char *name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		output_environment.subset_entries.push_back(name);
	}
	sqlite3_finalize(stmt);
	/*
	// the 4th parameter is passed as the first arg to the callback function
	exit = sqlite3_exec(db, query_string.c_str(), DebugCallback, 0, &error_message);
	if (exit != SQLITE_OK) {
		std::cerr << "Error querying monster data" << std::endl;
		std::cout << "Error Code: " << exit << std::endl;
		std::cout << "Error Message: " << error_message << std::endl;
		sqlite3_free(error_message);
	}

	query_result_count = 0;
	query_string = "SELECT * FROM submonsters";
	exit = sqlite3_exec(db, query_string.c_str(), LogCallback, output_environment*, &error_message);
	if (exit != SQLITE_OK) {
		std::cerr << "Error querying monster data" << std::endl;
		std::cout << "Error Code: " << exit << std::endl;
		std::cout << "Error Message: " << error_message << std::endl;
		sqlite3_free(error_message);
	}
	*/

	output_environment.result_count_text = "Results: " + std::to_string(query_result_count);

	int queries_performed = output_environment.log_entries.size() + 1;
	output_environment.log_entries.push_back(std::to_string(queries_performed) + ": Query performed");

	std::cout << "Successfully queried database." << std::endl;
	std::cout << "Query Parameter: " << parameter_string << std::endl;
	std::cout << "# of results : " << query_result_count << std::endl;
	sqlite3_close(db);
	return 0;
}

std::string GenerateQueryParameterString(QueryParameter& query_parameter) {
	// TODO: change this guard clause if query params switch the type for param name
	if (query_parameter.parameter_name == "") {
		return "";
	}

	std::string parameter_string = "WHERE ";

	if (query_parameter.parameter_name == "primary_type") {
		if (query_parameter.parameter_value == "any") {
			parameter_string += "primary_type != '-'";
		}
		else if (query_parameter.parameter_value == "none") {
			parameter_string += "primary_type = '-'";
		}
		else {
			parameter_string += "primary_type = '" + query_parameter.parameter_value + "'";
		}
	}
	else {
		return "";
	}

	return parameter_string;
}

int LogSuccess(OutputEnvironment& output_environment, const char* log_message) {
	++events_logged;
}

int LogError(OutputEnvironment& output_environment, const int error_code, const char* error_msg) {
	++events_logged;

	std::string border = "-----------------------------";
	auto now = std::chrono::system_clock::now();
	std::string meta_info = std::format("[{}][{}]", events_logged, now);
	std::string error_info = std::format("Error {}: {}", error_code, error_msg);

	output_environment.log_entries.push_back(border);
	output_environment.log_entries.push_back(meta_info);
	output_environment.log_entries.push_back(error_info);
	output_environment.log_entries.push_back(border);

	std::cout << border << std::endl << meta_info << std::endl << error_info << std::endl;

	return 0;
}

// used to test queries to DB by printing results to log
// this method is called once PER RETURNED ROW from the query
// argc is # of returned columns, azColName is array of column names
// argv is the actual values that go with the columns
int DebugCallback(void* not_used, int argc, char** argv, char** azColName) {
	++query_result_count;
	if (!kDebug) {
		return 0;
	}

	for (int i = 0; i < argc; i++) {
		std::cout << azColName[i] << ": " << argv[i] << std::endl;
	}

	std::cout << std::endl;

	return 0;
}

} // namespace monster_calculator

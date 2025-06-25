#pragma once
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
#include "mcc_constants.h"

namespace monster_calculator {

static const bool kDebug = false;

static const std::string kDbPath = "c:\\DB_TEST\\test.db";
static const std::string kJsonPath = "c:\\DB_TEST\\mccdata.json";

int CreateDatabase(OutputEnvironment& output_environment) {
	const char* database_path = kDbPath.c_str();

	sqlite3* db;
	int status = sqlite3_open(database_path, &db);
	if (status) {
		LogEvent(output_environment, status, "Error opening/creating SQL database");
	}
	sqlite3_close(db);

	return 0;
}

int CreateMainTable(OutputEnvironment& output_environment) {
	const char* database_path = kDbPath.c_str();
	const std::string kMainTableScheme = (
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
	const char* table_schema = kMainTableScheme.c_str();

	sqlite3* db;
	int exit = 0;
	exit = sqlite3_open(database_path, &db);

	char* error_message;
	exit = sqlite3_exec(db, table_schema, NULL, 0, &error_message);

	if (exit != SQLITE_OK) {
		LogEvent(output_environment, exit, error_message);
		sqlite3_free(error_message);
	}
	sqlite3_close(db);

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
		LogEvent(output_environment, exit, error_message);
		sqlite3_free(error_message);
	}
	sqlite3_close(db);

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
		LogEvent(output_environment, exit, error_message);
		sqlite3_free(error_message);
	}
	sqlite3_close(db);

	return 0;
}

int InsertDataFromJson(OutputEnvironment& output_environment) {
	// parse json file into value struct
	const char* json_path = kJsonPath.c_str();
	std::ifstream monster_json_file(json_path, std::ifstream::binary);
	Json::Value monsters;
	monster_json_file >> monsters;

	// open sqlite database
	const char* database_path = kDbPath.c_str();
	sqlite3* db;
	int exit = sqlite3_open(database_path, &db);

	char* error_message;
	int n = monsters.size();
	for (int i = 0; i < n; i++) {
		// converts a SINGLE monster json value struct into a sql row
		auto mon_info = monsters[i];

		std::string data_schema = GenerateJsonDataString(mon_info);
		exit = sqlite3_exec(db, data_schema.c_str(), NULL, 0, &error_message);
		if (exit != SQLITE_OK) {
			LogEvent(output_environment, exit, error_message);
			sqlite3_free(error_message);
			break;
		}
	}
	sqlite3_close(db);

	return 0;
}

std::string GenerateJsonDataString(Json::Value mon_info) {
	// this one is pretty ugly, just converts data in Json::Value
	// into the format to add a single row to to the sql database
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

int CreateSubtable(QueryParameter& query_parameter, OutputEnvironment& output_environment) {
	const char* database_path = kDbPath.c_str();
	sqlite3* db;
	int exit = sqlite3_open(database_path, &db);

	// make sure to clear existing sub-table if it exists
	char* error_message;
	std::string clear {"DROP TABLE IF EXISTS submonsters"};
	exit = sqlite3_exec(db, clear.c_str(), NULL, 0, &error_message);
	if (exit != SQLITE_OK) {
		LogEvent(output_environment, exit, error_message);
		sqlite3_free(error_message);
		return 0;
	}

	// create subtable with schema of main table
	std::string parameter_string = GenerateQueryParameterString(query_parameter);
	std::string query_string = "CREATE TABLE submonsters AS SELECT * FROM monsters "
		+ parameter_string + ";";
	exit = sqlite3_exec(db, query_string.c_str(), NULL, 0, &error_message);
	if (exit != SQLITE_OK) {
		LogEvent(output_environment, exit, error_message);
		sqlite3_free(error_message);
		return 0;
	}

	// go through subtable to tabulate results
	query_string = "SELECT * FROM submonsters;";
	output_environment.subset_entries.clear();
	sqlite3_stmt* stmt;
	exit = sqlite3_prepare_v2(db, query_string.c_str(), -1, &stmt, NULL);
	if (exit != SQLITE_OK) {
		LogEvent(output_environment, exit, "Error preparing for subset tabulation");
	}
	while ((exit = sqlite3_step(stmt)) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		const char *name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		output_environment.subset_entries.push_back(name);
	}

	LogEvent(output_environment, 0, "Successfully calculated valid data subset");

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}

std::string GenerateQueryParameterString(QueryParameter& query_parameter) {
	// TODO: change this guard clause if query params switch the type for param name
	if (query_parameter.parameter_name == "") {
		return "";
	}

	std::string parameter_string = "WHERE ";
	// edge cases for things like "any" and "none"
	if (query_parameter.parameter_value == "any") {
		parameter_string += query_parameter.parameter_name + " != '-'";
	} else if (query_parameter.parameter_value == "none") {
		parameter_string += query_parameter.parameter_name + " = '-'";
	} else {
		parameter_string += query_parameter.parameter_name + " = '" + query_parameter.parameter_value + "'";
	}

	return parameter_string;
}

int SortSubtableEntries(QueryParameter& query_parameter, OutputEnvironment& output_environment) {
	const char* database_path = kDbPath.c_str();
	sqlite3* db;
	int exit = sqlite3_open(database_path, &db);

	output_environment.subset_entries.clear();

	std::string query_string = "SELECT * FROM submonsters "
		+ GenerateSortingParameterString(query_parameter) + ";";
	sqlite3_stmt* stmt;
	exit = sqlite3_prepare_v2(db, query_string.c_str(), -1, &stmt, NULL);
	if (exit != SQLITE_OK) {
		LogEvent(output_environment, exit, "Error preparing to re-order subset");
	}
	while ((exit = sqlite3_step(stmt)) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		const char* name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
		output_environment.subset_entries.push_back(name);
	}

	LogEvent(output_environment, 0, "Successfully re-ordered data subset");

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}

int SortSubtableCallback(void* not_used, int argc, char** argv, char** azColName) {
	return 0;
}

std::string GenerateSortingParameterString(QueryParameter& query_parameter) {
	if (query_parameter.parameter_name == "") {
		return "";
	}
	
	std::string sorting_string = "ORDER BY " + query_parameter.parameter_name + " " + query_parameter.parameter_value;
	return sorting_string;
}

int LogEvent(OutputEnvironment& output_environment, const int event_code, const char* event_msg) {
	namespace ch = std::chrono;
	auto curr_time = ch::floor<ch::seconds>(ch::system_clock::now());

	std::string timestamp_text = std::format("{:%T}", curr_time);
	std::string error_code_text = std::to_string(event_code);
	std::string error_message_text = event_msg;

	LogEntry entry = { timestamp_text, error_code_text, error_message_text };
	output_environment.log_entries.push_back(entry);

	return 0;
}

// used to test queries to DB by printing results to program terminal window
// this method is called once PER RETURNED ROW from the query
// argc is # of returned columns, azColName is array of column names
// argv is the actual values that go with the columns
int DebugCallback(void* not_used, int argc, char** argv, char** azColName) {
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

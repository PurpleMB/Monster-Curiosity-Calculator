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
	std::string unique_id = mon_info["unique_id"].asString();
	std::string mon_name = mon_info["name"].asString();
	std::string dex_num = mon_info["dex_number"].asString();

	std::string generation = mon_info["generation"].asString();
	std::string switchable = mon_info["form_switchable"].asString();
	std::string color = mon_info["color"].asString();
	std::string shape = mon_info["shape"].asString();

	std::string prim_type = mon_info["types"]["primary"].asString();
	std::string sec_type = mon_info["types"]["secondary"].asString();

	std::string growth_rate = mon_info["growth_rate"].asString();
	std::string base_experience = mon_info["base_experience"].asString();
	std::string base_happiness = mon_info["base_happiness"].asString();
	std::string catch_rate = mon_info["catch_rate"].asString();

	std::string hatch_count = mon_info["hatch_counter"].asString();
	std::string gender_rate = mon_info["gender_rate"].asString();
	std::string dimporhic = mon_info["dimorphic"].asString();

	std::string prim_egg = mon_info["egg_groups"]["primary"].asString();
	std::string sec_egg = mon_info["egg_groups"]["secondary"].asString();

	std::string is_default = mon_info["is_default"].asString();
	std::string is_baby = mon_info["is_baby"].asString();
	std::string is_legendary = mon_info["is_legendary"].asString();
	std::string is_mythical = mon_info["is_mythical"].asString();

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
		"INSERT INTO monsters ("
		"id"
		", name"
		", dex_number"
		", generation"
		", form_switchable"
		", color"
		", shape"
		", primary_type"
		", secondary_type"
		", growth_rate"
		", base_experience"
		", base_happiness"
		", catch_rate"
		", hatch_counter"
		", gender_rate"
		", dimorphic"
		", primary_egg_group"
		", secondary_egg_group"
		", is_default"
		", is_baby"
		", is_legendary"
		", is_mythical"
		", height"
		", weight"
		", ability_1"
		", ability_2"
		", hidden_ability"
		", hp"
		", attack"
		", defense"
		", special_attack"
		", special_defense"
		", speed"
		", stat_total"
		")VALUES('"
	};
	data_schema += unique_id + "', '";
	data_schema += mon_name + "', '";
	data_schema += dex_num + "', '";

	data_schema += generation + "', '";
	data_schema += switchable + "', '";
	data_schema += color + "', '";
	data_schema += shape + "', '";

	data_schema += prim_type + "', '";
	data_schema += sec_type + "', '";

	data_schema += growth_rate + "', '";
	data_schema += base_experience + "', '";
	data_schema += base_happiness + "', '";
	data_schema += catch_rate + "', '";

	data_schema += hatch_count + "', '";
	data_schema += gender_rate + "', '";
	data_schema += dimporhic + "', '";

	data_schema += prim_egg + "', '";
	data_schema += sec_egg + "', '";

	data_schema += is_default + "', '";
	data_schema += is_baby + "', '";
	data_schema += is_legendary + "', '";
	data_schema += is_mythical + "', '";

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

int CreateSubtable(OutputEnvironment& output_environment) {
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
	std::string parameter_string = GenerateQueryParameterString(output_environment.subset_parameters);
	std::string query_string = "CREATE TABLE submonsters AS SELECT * FROM monsters "
		+ parameter_string + ";";
	exit = sqlite3_exec(db, query_string.c_str(), NULL, 0, &error_message);
	if (exit != SQLITE_OK) {
		LogEvent(output_environment, exit, error_message);
		sqlite3_free(error_message);
		return 0;
	}

	sqlite3_close(db);
	return 0;
}

std::string GenerateQueryParameterString(std::vector<BetterQueryParameter>& subset_parameters) {
	if (subset_parameters.size() == 0) {
		return "";
	}

	std::string parameter_string = "WHERE ";
	for (int i = 0; i < subset_parameters.size(); i++) {
		parameter_string += "(";
		BetterQueryParameter subset_param = subset_parameters[i];
		std::string formatted_query = std::vformat(subset_param.query_format, std::make_format_args(subset_param.query_value));
		parameter_string += formatted_query;
		parameter_string += ")";

		if (i < subset_parameters.size() - 1) {
			parameter_string += " AND ";
		}
	}

	std::cout << parameter_string << std::endl;

	return parameter_string;
}

int SortSubtableEntries(OutputEnvironment& output_environment) {
	const char* database_path = kDbPath.c_str();
	sqlite3* db;
	int exit = sqlite3_open(database_path, &db);

	output_environment.subset_entries.clear();

	std::string query_string = "SELECT * FROM submonsters "
		+ GenerateSortingParameterString(output_environment.sorting_parameters) + ";";
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

std::string GenerateSortingParameterString(std::vector<BetterQueryParameter>& sorting_parameters) {
	if (sorting_parameters.size() == 0) {
		return "";
	}
	
	return "";
	//std::string sorting_string = "ORDER BY " + query_parameter.parameter_name + " " + query_parameter.parameter_value;
	//return sorting_string;
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

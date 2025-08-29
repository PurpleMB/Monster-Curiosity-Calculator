#pragma once
#include <string>

#include <sqlite3.h>

// remove after debuggind is done
#include <iostream>

#include "mcc_communication_structs.h"

namespace monster_calculator {

static const std::string kDbPath = ".\\data\\mccdata.db";
static const std::string kJsonPath = ".\\data\\mccdata.json";
static const std::string kMainTableName = "Monsters";
static const std::string kSubTableName = "Submonsters";

void OpenDatabaseConnection(OutputEnvironment& output_environment) {
	std::string log_msg;
	if (output_environment.database_connection != nullptr) {
		log_msg = std::vformat(
			"Previous database connection still open. Aborting attempt to open new connection at {0}",
			std::make_format_args(kDbPath)
		);
		output_environment.LogError(SQLITE_MISUSE, log_msg.c_str());
		return;
	}

	const char* database_path = kDbPath.c_str();
	sqlite3* connection;
	int connection_status = sqlite3_open(database_path, &connection);
	if (connection_status != SQLITE_OK) {
		log_msg = std::vformat(
			"Error establishing connection with database at {0}", 
			std::make_format_args(kDbPath)
		);
		output_environment.LogError(connection_status, log_msg.c_str());
		return;
	}

	output_environment.database_connection = connection;
	log_msg = std::vformat(
		"Successfully established connection with database at {0}",
		std::make_format_args(kDbPath)
	);
	output_environment.LogSuccess(log_msg.c_str());
}
void CloseDatabaseConnection(OutputEnvironment& output_environment) {
	std::string log_msg;
	if (output_environment.database_connection == nullptr) {
		log_msg = std::vformat(
			"No active database connection is open. Aborting attempt to close database connection at {0}",
			std::make_format_args(kDbPath)
		);
		output_environment.LogError(SQLITE_MISUSE, log_msg.c_str());
		return;
	}

	sqlite3* connection = output_environment.database_connection;
	int close_status = sqlite3_close(connection);
	if (close_status != SQLITE_OK) {
		log_msg = std::vformat(
			"Error closing connection with database at {0}",
			std::make_format_args(kDbPath)
		);
		output_environment.LogError(close_status, log_msg.c_str());
		return;
	}

	output_environment.database_connection = nullptr;
	log_msg = std::vformat(
		"Successfully closed connection with database at {0}",
		std::make_format_args(kDbPath)
	);
	output_environment.LogSuccess(log_msg.c_str());
}

void CreateTableFromSchema(OutputEnvironment& output_environment, std::string table_name, std::string table_schema) {
	std::string table_str = "CREATE TABLE IF NOT EXISTS {0} ({1})";
	table_str = std::vformat(table_str, std::make_format_args(table_name, table_schema));

	sqlite3_stmt* prepared_stmt;
	int prepare_status = sqlite3_prepare_v2(
		output_environment.database_connection,
		table_str.c_str(),
		table_str.length(),
		&prepared_stmt,
		nullptr
	);
	if (prepare_status != SQLITE_OK) {
		std::string prepare_msg = std::vformat(
			"Failed to prepare statement for creating table '{0}'",
			std::make_format_args(table_name)
		);
		output_environment.LogError(prepare_status, prepare_msg.c_str());
		return;
	}

	int step_status = sqlite3_step(prepared_stmt);
	std::string step_msg;
	if (step_status != SQLITE_DONE) {
		step_msg = std::vformat(
			"Error processing step during creation of table {0}",
			std::make_format_args(table_name)
		);
		output_environment.LogError(step_status, step_msg.c_str());
		return;
	}
	step_msg = std::vformat(
		"Successfully created table {0} from schema",
		std::make_format_args(table_name)
	);
	output_environment.LogSuccess(step_msg.c_str());
	

}

void GenerateTableSubset(OutputEnvironment& output_environment) {
	std::string subset_stmt = "CREATE TABLE {0} AS SELECT * FROM {1} WHERE {2}";
	std::string conditions = "bbbbbbb";
	subset_stmt = std::vformat(subset_stmt, std::make_format_args(kSubTableName, kMainTableName, conditions));
	std::cout << subset_stmt << std::endl;
}

} // namespace monster_calculator
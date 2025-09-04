#pragma once
#include <string>

#include <sqlite3.h>

// remove after debuggind is done
#include <iostream>

#include "mcc_communication_structs.h"
#include "mcc_database_structs.h"
#include "mcc_database_constants.h"

#include "mcc_database_querying.h"

namespace monster_calculator {

void OpenDatabaseConnection(OutputEnvironment& output_environment) {
	std::string log_msg;
	if (output_environment.database_connection != nullptr) {
		log_msg = std::vformat(
			"Previous database connection still open. Aborting attempt to open new connection at {0}",
			std::make_format_args(kDatabaseFilePath)
		);
		output_environment.LogError(SQLITE_MISUSE, log_msg.c_str());
		return;
	}

	const char* database_path = kDatabaseFilePath.c_str();
	sqlite3* connection;
	int connection_status = sqlite3_open(database_path, &connection);
	if (connection_status != SQLITE_OK) {
		log_msg = std::vformat(
			"Error establishing connection with database at {0}", 
			std::make_format_args(kDatabaseFilePath)
		);
		output_environment.LogError(connection_status, log_msg.c_str());
		return;
	}

	output_environment.database_connection = connection;
	log_msg = std::vformat(
		"Successfully established connection with database at {0}",
		std::make_format_args(kDatabaseFilePath)
	);
	output_environment.LogSuccess(log_msg.c_str());
}
void CloseDatabaseConnection(OutputEnvironment& output_environment) {
	std::string log_msg;
	if (output_environment.database_connection == nullptr) {
		log_msg = std::vformat(
			"No active database connection is open. Aborting attempt to close database connection at {0}",
			std::make_format_args(kDatabaseFilePath)
		);
		output_environment.LogError(SQLITE_MISUSE, log_msg.c_str());
		return;
	}

	sqlite3* connection = output_environment.database_connection;
	int close_status = sqlite3_close(connection);
	if (close_status != SQLITE_OK) {
		log_msg = std::vformat(
			"Error closing connection with database at {0}",
			std::make_format_args(kDatabaseFilePath)
		);
		output_environment.LogError(close_status, log_msg.c_str());
		return;
	}

	output_environment.database_connection = nullptr;
	log_msg = std::vformat(
		"Successfully closed connection with database at {0}",
		std::make_format_args(kDatabaseFilePath)
	);
	output_environment.LogSuccess(log_msg.c_str());
}

void CreateTableFromSchema(OutputEnvironment& output_environment, std::string table_name, TableSchemaList schema_list) {
	std::string table_str = "CREATE TABLE IF NOT EXISTS {0} ({1})";
	std::string table_schema = schema_list.GetTableSchema();
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
	if (step_status != SQLITE_DONE) {
		std::string step_msg = std::vformat(
			"Error processing step during creation of table {0}",
			std::make_format_args(table_name)
		);
		output_environment.LogError(step_status, step_msg.c_str());
		sqlite3_finalize(prepared_stmt);
		return;
	}

	sqlite3_finalize(prepared_stmt);
	std::string success_msg = std::vformat(
		"Successfully created table {0} from schema",
		std::make_format_args(table_name)
	);
	output_environment.LogSuccess(success_msg.c_str());
}

void DropTableIfExists(OutputEnvironment& output_environment, std::string table_name) {
	std::string drop_str = "DROP TABLE IF EXISTS {0}";
	drop_str = std::vformat(drop_str, std::make_format_args(table_name));

	sqlite3_stmt* prepared_stmt;
	int prepare_status = sqlite3_prepare_v2(
		output_environment.database_connection,
		drop_str.c_str(),
		drop_str.length(),
		&prepared_stmt,
		nullptr
	);
	if (prepare_status != SQLITE_OK) {
		std::string prepare_msg = std::vformat(
			"Failed to prepare statement for dropping table '{0}'",
			std::make_format_args(table_name)
		);
		output_environment.LogError(prepare_status, prepare_msg.c_str());
		return;
	}

	int drop_status = sqlite3_step(prepared_stmt);
	if (drop_status != SQLITE_DONE) {
		std::string drop_msg = std::vformat(
			"Error dropping table {0}",
			std::make_format_args(table_name)
		);
		output_environment.LogError(drop_status, drop_msg.c_str());
		sqlite3_finalize(prepared_stmt);
		return;
	}

	sqlite3_finalize(prepared_stmt);
	std::string success_msg = std::vformat(
		"Successfully dropped table {0}",
		std::make_format_args(table_name)
	);
	output_environment.LogSuccess(success_msg.c_str());
}

void ClearTableContents(OutputEnvironment& output_environment, std::string table_name) {
	std::string clear_str = "DELETE FROM {0}";
	clear_str = std::vformat(clear_str, std::make_format_args(table_name));

	sqlite3_stmt* prepared_stmt;
	int prepare_status = sqlite3_prepare_v2(
		output_environment.database_connection,
		clear_str.c_str(),
		clear_str.length(),
		&prepared_stmt,
		nullptr
	);
	if (prepare_status != SQLITE_OK) {
		std::string prepare_msg = std::vformat(
			"Failed to prepare statement for clearing table '{0}'",
			std::make_format_args(table_name)
		);
		output_environment.LogError(prepare_status, prepare_msg.c_str());
		return;
	}

	int step_status = sqlite3_step(prepared_stmt);
	if (step_status != SQLITE_DONE) {
		std::string step_msg = std::vformat(
			"Error processing step during clearing of table {0}",
			std::make_format_args(table_name)
		);
		output_environment.LogError(step_status, step_msg.c_str());
		sqlite3_finalize(prepared_stmt);
		return;
	}

	sqlite3_finalize(prepared_stmt);
	std::string success_msg = std::vformat(
		"Successfully cleared {0}",
		std::make_format_args(table_name)
	);
	output_environment.LogSuccess(success_msg.c_str());
}

void PopulateTableFromList(OutputEnvironment& output_environment, std::string table_name, TableSchemaList schema_list,
	std::vector<std::unordered_map<std::string, std::string>>& table_entries) {

	std::string insert_str = "INSERT INTO {0} ({1}) VALUES ({2})"; 
	std::vector<std::string> col_names = schema_list.GetTableColNames();
	std::string column_name_list = GenerateColumnList(col_names);
	std::string wildcard_list = GenerateValueWildcardList(col_names.size());
	std::string statement_text = std::vformat(insert_str, std::make_format_args(table_name, column_name_list, wildcard_list));

	sqlite3_stmt* insert_stmt;
	int prepare_status = sqlite3_prepare_v2(
		output_environment.database_connection,
		statement_text.c_str(),
		statement_text.length(),
		&insert_stmt,
		nullptr
	);
	if (prepare_status != SQLITE_OK) {
		std::string prepare_msg = std::vformat(
			"Failed to prepare statement for inserting into table '{0}'",
			std::make_format_args(table_name)
		);
		output_environment.LogError(prepare_status, prepare_msg.c_str());
		return;
	}

	int entries_count = table_entries.size();
	for (int entry_index = 0; entry_index < entries_count; entry_index++) {
		// bind column values to wildcard list
		std::unordered_map<std::string, std::string>& entry_data = table_entries[entry_index];
		for (int column_index = 0; column_index < col_names.size(); column_index++) {
			TableColumnSchema col_schema = schema_list.GetColumnSchema(column_index);
			std::string column_name = col_schema.GetColumnName();
			std::string column_type = col_schema.GetDataType();
			std::string column_value = entry_data[column_name];
			if (column_type == "INTEGER" || column_type == "INT") {
				sqlite3_bind_int(
					insert_stmt,
					column_index + 1,
					std::stoi(column_value)
				);
			}
			else if (column_type == "DOUBLE") {
				sqlite3_bind_double(
					insert_stmt,
					column_index + 1,
					std::stod(column_value)
                                                                                                                                                                     				);
			}
			else {
				sqlite3_bind_text(
					insert_stmt,
					column_index + 1,
					column_value.c_str(),
					column_value.length(),
					SQLITE_TRANSIENT
				);
			}
		}

		int step_status = sqlite3_step(insert_stmt);
		std::string step_msg;
		if (step_status != SQLITE_DONE) {
			step_msg = std::vformat(
				"Error processing step during population of table {0}",
				std::make_format_args(table_name)
			);
			output_environment.LogError(step_status, step_msg.c_str());
			sqlite3_finalize(insert_stmt);
			return;
		}
		sqlite3_reset(insert_stmt);
	}

	sqlite3_finalize(insert_stmt);
	std::string success_msg = std::vformat(
		"Successfully populated table {0}",
		std::make_format_args(table_name)
	);
	output_environment.LogSuccess(success_msg.c_str());
}

std::string GenerateColumnList(std::vector<std::string>& column_names) {
	std::string names_list = "";

	int column_count = column_names.size();
	for (int i = 0; i < column_count; i++) {
		names_list += column_names[i];
		if (i < column_count - 1) {
			names_list += ", ";
		}
	}

	return names_list;
}

std::string GenerateValueWildcardList(int value_count) {
	std::string wildcard_list = "";

	for (int i = 0; i < value_count; i++) {
		wildcard_list += "?";
		if (i < value_count - 1) {
			wildcard_list += ", ";
		}
	}

	return wildcard_list;
}

void GenerateTableSubset(OutputEnvironment& output_environment, std::string source_table, std::string target_table) {
	DropTableIfExists(output_environment, target_table);

	std::string subtable_str = "CREATE TABLE {0} AS SELECT * FROM {1} WHERE {2}";
	std::string conditions = output_environment.subset_parameters.GetSetQueryString();
	subtable_str = std::vformat(subtable_str, std::make_format_args(target_table, source_table, conditions));

	std::cout << subtable_str << std::endl;

	sqlite3_stmt* prepared_stmt;
	int prepare_status = sqlite3_prepare_v2(
		output_environment.database_connection,
		subtable_str.c_str(),
		subtable_str.length(),
		&prepared_stmt,
		nullptr
	);
	if (prepare_status != SQLITE_OK) {
		std::string prepare_msg = std::vformat(
			"Failed to prepare statement for creating subtable '{0}' from '{1}'",
			std::make_format_args(target_table, source_table)
		);
		output_environment.LogError(prepare_status, prepare_msg.c_str());
		return;
	}

	int step_status = sqlite3_step(prepared_stmt);
	if (step_status != SQLITE_DONE) {
		std::string step_msg = std::vformat(
			"Error processing step during creation of subtable '{0}' from '{1}'",
			std::make_format_args(target_table, source_table)
		);
		output_environment.LogError(step_status, step_msg.c_str());
		sqlite3_finalize(prepared_stmt);
		return;
	}

	sqlite3_finalize(prepared_stmt);
	std::string success_msg = std::vformat(
		"Successfully created subtable '{0}' from '{1}'",
		std::make_format_args(target_table, source_table)
	);
	output_environment.LogSuccess(success_msg.c_str());
}

void RetrieveTableEntries(OutputEnvironment& output_environment, std::string table_name) {
	std::string retrieve_str = "SELECT * FROM {0}";
	std::string statement_text = std::vformat(retrieve_str, std::make_format_args(table_name));

	sqlite3_stmt* retrieve_stmt;
	int prepare_status = sqlite3_prepare_v2(
		output_environment.database_connection,
		statement_text.c_str(),
		statement_text.length(),
		&retrieve_stmt,
		nullptr
	);
	if (prepare_status != SQLITE_OK) {
		std::string prepare_msg = std::vformat(
			"Failed to prepare statement for retrieving data from table '{0}'",
			std::make_format_args(table_name)
		);
		output_environment.LogError(prepare_status, prepare_msg.c_str());
		return;
	}

	output_environment.ClearSubsetEntries();

	int step_status = 0;
	while ((step_status = sqlite3_step(retrieve_stmt)) == SQLITE_ROW) {
		SubsetEntry subset_entry;
		for (int i = 0; i < sqlite3_column_count(retrieve_stmt); i++) {
			std::string col_name = sqlite3_column_name(retrieve_stmt, i);
			std::string col_val = std::string(reinterpret_cast<const char*>(sqlite3_column_text(retrieve_stmt, i)));
			subset_entry.AddData(col_name, col_val);
		}
		output_environment.subset_entries.push_back(subset_entry);
	}
	if (step_status != SQLITE_DONE) {
		std::string step_msg = std::vformat(
			"Error retrieving data from table '{0}'",
			std::make_format_args(table_name)
		);
		output_environment.LogError(step_status, step_msg.c_str());
		sqlite3_finalize(retrieve_stmt);
		return;
	}

	sqlite3_finalize(retrieve_stmt);
	std::string success_msg = std::vformat(
		"Successfully retrieved data from table {0}",
		std::make_format_args(table_name)
	);
	output_environment.LogSuccess(success_msg.c_str());
}

} // namespace monster_calculator
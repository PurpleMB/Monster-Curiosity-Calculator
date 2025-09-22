#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include <sqlite3.h>

#include "mcc_communication_structs.h"

namespace monster_calculator {

void OpenDatabaseConnection(OutputEnvironment& output_environment);
void CloseDatabaseConnection(OutputEnvironment& output_environment);

void CreateTableFromSchema(OutputEnvironment& output_environment, std::string table_name, TableSchemaList schema_list);
void DropTableIfExists(OutputEnvironment& output_environment, std::string table_name);
void ClearTableContents(OutputEnvironment& output_environment, std::string table_name);

void PopulateTableFromList(OutputEnvironment& output_environment, std::string table_name, TableSchemaList schema_list, 
	std::vector<std::unordered_map<std::string, std::string>>& table_entries);
std::string GenerateColumnList(std::vector<std::string>& column_names);
std::string GenerateValueWildcardList(int value_count);

void GenerateTableSubset(OutputEnvironment& output_environment, std::string source_table, std::string target_table);
void RetrieveTableEntries(OutputEnvironment& output_environment, std::string table_name);
void QueryValuesFromTable(OutputEnvironment& output_environment, std::string table_name, std::vector<int> query_indices, std::string query_text);
} // namespace monster_calculator

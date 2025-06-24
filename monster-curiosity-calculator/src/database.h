#pragma once
#include <unordered_map>
#include <string>

#include <json/json.h>
#include <json/value.h>

#include "mcc_structs.h"

namespace monster_calculator {
// basic database creation
int CreateDatabase();
int CreateMainTable(OutputEnvironment& output_environment);
int DeleteMainTable(OutputEnvironment& output_environment);
int ClearMainTable(OutputEnvironment& output_environment);
int InsertDataFromJson(OutputEnvironment& output_environment);
std::string GenerateJsonDataString(Json::Value mon_info);

// querying primary table
int CreateSubtable(QueryParameter& query_parameter, OutputEnvironment& output_environment);
int SortSubtableEntries(QueryParameter& query_parameter, OutputEnvironment& output_environment);
int SortSubtableCallback(void* not_used, int argc, char** argv, char** azColName);
std::string GenerateQueryParameterString(QueryParameter& query_parameter);
std::string GenerateSortingParameterString(QueryParameter& query_parameter);

// logging/debugging
int LogEvent(OutputEnvironment& output_environment, const int error_code, const char* error_msg);
int DebugCallback(void* not_used, int argc, char** argv, char** azColName);

} // namespace monster_calculator

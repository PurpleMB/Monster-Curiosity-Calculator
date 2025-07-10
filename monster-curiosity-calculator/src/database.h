#pragma once
#include <string>

#include <json/json.h>
#include <json/value.h>

#include "mcc_structs.h"

namespace monster_calculator {
// basic database creation
int CreateDatabase(OutputEnvironment& output_environment);
int CreateMainTable(OutputEnvironment& output_environment);
int DeleteMainTable(OutputEnvironment& output_environment);
int ClearMainTable(OutputEnvironment& output_environment);
int InsertDataFromJson(OutputEnvironment& output_environment);
std::string GenerateJsonDataString(Json::Value mon_info);

// querying primary table
int CreateSubtable(OutputEnvironment& output_environment);
int SortSubtableEntries(OutputEnvironment& output_environment);
int SortSubtableCallback(void* not_used, int argc, char** argv, char** azColName);
std::string GenerateQueryParameterString(std::vector<std::vector<BetterQueryParameter>>& subset_parameters);
std::string GenerateSortingParameterString(std::vector<BetterQueryParameter>& sorting_parameter);

// logging/debugging
int LogEvent(OutputEnvironment& output_environment, const int error_code, const char* error_msg);
int DebugCallback(void* not_used, int argc, char** argv, char** azColName);

} // namespace monster_calculator

#pragma once
#include <unordered_map>
#include <string>

#include <json/json.h>
#include <json/value.h>

#include "mcc_structs.h"

namespace monster_calculator {
// basic database creation
int CreateDatabase();
int CreateMainTable();
int DeleteMainTable();
int ClearMainTable();
int InsertDataFromJson();
std::string GenerateJsonDataString(Json::Value mon_info);

// querying primary table
int QueryDatabase(QueryParameter& query_parameter, OutputEnvironment& output_environment);
std::string GenerateQueryParameterString(QueryParameter& query_parameter);

// debug functions
int DebugCallback(void* not_used, int argc, char** argv, char** azColName);

} // namespace monster_calculator

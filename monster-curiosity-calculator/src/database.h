#pragma once
#include <unordered_map>
#include <string>

#include <json/json.h>
#include <json/value.h>

#include "mcc_structs.h"

namespace monster_calculator {

int CreateDatabase();
int CreateTable();
int DeleteTable();
int ClearTable();
int InsertDataFromJson();
std::string GenerateJsonDataString(Json::Value mon_info);
int QueryDatabase(QueryParameter& query_parameter);
std::string GenerateQueryParameterString(QueryParameter& query_parameter);
int DebugCallback(void* not_used, int argc, char** argv, char** azColName);

} // namespace monster_calculator

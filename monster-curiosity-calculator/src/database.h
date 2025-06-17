#pragma once
#include <unordered_map>

#include <json/json.h>
#include <json/value.h>

namespace monster_calculator {

int CreateDatabase();
int CreateTable();
int DeleteTable();
int ClearTable();
int InsertDataFromJson();
std::string GenerateJsonDataString(Json::Value mon_info);
int QueryDatabase(std::unordered_map<std::string, std::vector<std::string>> query_arguments);
int DebugCallback(void* not_used, int argc, char** argv, char** azColName);

} // namespace monster_calculator

#pragma once
#include <json/json.h>
#include <json/value.h>

namespace monster_calculator {

int CreateDatabase();
int CreateTable();
int DeleteTable();
int ClearTable();
int InsertDataFromJson();
std::string GenerateJsonDataString(Json::Value mon_info);
int QueryDatabase();
int DebugCallback(void* not_used, int argc, char** argv, char** azColName);

} // namespace monster_calculator

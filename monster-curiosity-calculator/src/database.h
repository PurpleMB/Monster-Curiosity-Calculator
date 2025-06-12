#pragma once
#include <json/json.h>
#include <json/value.h>

namespace monster_calculator {

int CreateDatabase(const char* path);
int CreateTable(const char* path);
int DeleteTable(const char* path);
int ClearTable(const char* path);
int InsertDataFromJson(const char* db_path, const char* json_path);
std::string GenerateJsonDataString(Json::Value mon_info);
int QueryDatabase(const char* path);
int DebugCallback(void* not_used, int argc, char** argv, char** azColName);

} // namespace monster_calculator

#pragma once
#include <sqlite3.h>
#include <json/json.h>
#include <json/value.h>

namespace monster_calculator {

int createDatabase(const char* path);
int createTable(const char* path);
int deleteTable(const char* path);
int clearTable(const char* path);
int insertDataFromJson(const char* dbPath, const char* jsonPath);
std::string generateDataString(Json::Value mon_info);
int queryDatabase(const char* path, const int argc, const char** argv, std::vector<std::string>& results);
int debugCallback(void* NotUsed, int argc, char** argv, char** azColName);

} // namespace monster_calculator

#pragma once
#include <sqlite3.h>
#include <json/json.h>
#include <json/value.h>

int createDatabase(const char* path);
int createTable(const char* path);
int deleteTable(const char* path);
int clearTable(const char* path);
int insertDataFromJson(const char* dbPath, const char* jsonPath);
std::string generateQueryString(Json::Value mon_info);
int debugCallback(void* NotUsed, int argc, char** argv, char** azColName);

#pragma once
#include <sqlite3.h>

int createDatabase(const char* path);
int createTable(const char* path);
int insertDataFromJson(const char* dbPath, const char* jsonPath);
int debugCallback(void* NotUsed, int argc, char** argv, char** azColName);

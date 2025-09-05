#pragma once
#include <string>
#include <vector>

#include "mcc_database_structs.h"

namespace monster_calculator {

extern const std::string kMainTableSchema;
extern const std::string kMainTableSchemaPruned;
extern const std::vector<std::string> kMainTableColumnNameList;

extern const std::string kDatabaseFilePath;
extern const std::string kMainTableName;
extern const std::string kSubTableName;
extern const TableSchemaList kMainTableSchemaList;
} // namespace monster_calculator

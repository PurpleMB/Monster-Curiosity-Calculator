#pragma once
#include <string>

#include <json/json.h>
#include <json/value.h>

#include "mcc_parameter_structs.h"
#include "mcc_communication_structs.h"

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
int SortSubtableEntries(OutputEnvironment& output_environment, ParameterTypeConverter param_converter);
int SortSubtableCallback(void* not_used, int argc, char** argv, char** azColName);
std::string GenerateQueryParameterString(ParameterSet& subset_parameters);

int QuerySubtable(OutputEnvironment& output_environment);

// logging/debugging
int LogEvent(OutputEnvironment& output_environment, const int error_code, const char* error_msg);
int DebugCallback(void* not_used, int argc, char** argv, char** azColName);

} // namespace monster_calculator

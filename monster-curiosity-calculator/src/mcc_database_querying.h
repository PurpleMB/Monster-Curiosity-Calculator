#pragma once
#include "mcc_communication_structs.h"

namespace monster_calculator {

void OpenDatabaseConnection(OutputEnvironment& output_environment);
void CloseDatabaseConnection(OutputEnvironment& output_environment);

void CreateTableFromSchema(OutputEnvironment& output_environment, std::string table_name, std::string table_schema);

void GenerateTableSubset(OutputEnvironment& output_environment);

} // namespace monster_calculator

#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include <json/json.h>
#include <json/value.h>

namespace purple_mb::monster_calculator {

// This functions takes the provided path, opens its, and expects a json file with a list of json entries.
// Each entry is then parsed using the entry_name_map. The map keys are used to retrieve json data, which is saved to the output map with the value from the
// name map as the key in the output map. This is done to retrieve the data and associate it with the column names expected by the SQLite database.
std::vector<std::unordered_map<std::string, std::string>> CompileJsonData(const std::string file_path, const std::unordered_map<std::string, std::string>& entry_name_map);

// This is a helper function for the above function. It is responsible for doing the data retrieval and mapping for a
// single json entry from the opened file.
std::unordered_map<std::string, std::string> UnpackJsonEntry(Json::Value entry, const std::unordered_map<std::string, std::string>& entry_name_map);

} // namespace purple_mb::monster_calculator

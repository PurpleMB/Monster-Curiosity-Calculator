#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include <json/json.h>
#include <json/value.h>

namespace monster_calculator {

std::vector<std::unordered_map<std::string, std::string>> CompileMonsterJsonData(std::string file_path);
std::unordered_map<std::string, std::string> UnpackMonsterJsonEntry(Json::Value entry);

} // namespace monster_calculator

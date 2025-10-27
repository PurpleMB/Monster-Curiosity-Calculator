#pragma once

#include "mcc_json_processing.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>

#include <json/json.h>
#include <json/value.h>

namespace purple_mb::monster_calculator {

std::vector<std::unordered_map<std::string, std::string>> CompileJsonData(const std::string file_path, const std::unordered_map<std::string, std::string>& entry_name_map) {
	// open the file
	const char* json_path = file_path.c_str();
	std::ifstream monster_json_stream(json_path, std::ifstream::binary);

	// pipe the file into a json stream
	Json::Value monster_values;
	monster_json_stream >> monster_values;

	// begin filling the output map with unpacked entries
	std::vector<std::unordered_map<std::string, std::string>> json_entries_list = {};
	int monster_count = monster_values.size();
	for(int i = 0; i < monster_count; i++) {
		Json::Value monster_entry = monster_values[i];
		json_entries_list.push_back(UnpackJsonEntry(monster_entry, entry_name_map));
	}

	return json_entries_list;
}

std::unordered_map<std::string, std::string> UnpackJsonEntry(Json::Value entry, const std::unordered_map<std::string, std::string>& entry_name_map) {
	std::unordered_map<std::string, std::string> entry_data_map = {};

	// go through all name mapping, retrieving each piece of data and adding to output map
	for (std::pair<std::string, std::string> name_pair : entry_name_map) {
		// same pieces of data have different names in the json file and the database
		std::string json_name = name_pair.first;
		std::string database_name = name_pair.second;

		std::string entry_value = entry[json_name].asString();
		entry_data_map.insert({database_name, entry_value});
	}

	return entry_data_map;
}

} // namespace purple_mb::monster_calculator
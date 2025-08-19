#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "imgui.h"

#include "mcc_parameter_structs.h"

namespace monster_calculator {

struct WindowParameters {
	std::string name;
	ImVec2 window_size;
	ImVec2 window_position;
	int imgui_window_settings;
	float internal_margin;
};

struct LogEntry {
	std::string timestamp;
	std::string message_code;
	std::string log_message;
};

struct OutputEnvironment {
	std::vector<LogEntry> log_entries;
	std::vector<SubsetEntry> subset_entries;
	ParameterSet subset_parameters;
	QueryParameter value_parameter;
	//std::vector<BetterQueryParameter> sorting_parameters;

	OutputEnvironment() {
		log_entries = {};
		subset_entries = {};
		subset_parameters = ParameterSet();
		value_parameter = QueryParameter();
	}
};

} // namespace monster_calculator
 
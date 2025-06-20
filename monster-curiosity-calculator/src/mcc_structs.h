#pragma once
#include <string>
#include <vector>

#include "imgui.h"

namespace monster_calculator {

// TODO: use this to define display and possible values of different metrics we can refine query by
struct ParameterType {
	std::string parameter_name;
	std::vector<std::string> possible_parameter_values;
};

struct QueryParameter {
	std::string parameter_name = "";
	std::string parameter_value = "";
};

struct WindowParameters {
	std::string name = "";
	ImVec2 window_size;
	ImVec2 window_position;
	int imgui_window_settings = 0;
};

struct OutputEnvironment {
	std::string result_count_text = "Results: ";
	std::vector<std::string> log_entries = {};
	std::vector<std::string> subset_entries = {};
};

} // namespace monster_calculator
 
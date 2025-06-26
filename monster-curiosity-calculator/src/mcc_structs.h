#pragma once
#include <string>
#include <vector>

#include "imgui.h"

namespace monster_calculator {

enum ParameterCategory {
	Enumerated,
	Numerical,
	Undefined
};

// TODO: use this to define display and possible values of different metrics we can refine query by
struct ParameterType {
	std::string display_name;
	std::string query_name;
	ParameterCategory catergory;
	std::vector<std::string> values;

	ParameterType(std::string name, std::string q_name, ParameterCategory cat, std::vector<std::string> vals) {
		display_name = name;
		query_name = q_name;
		catergory = cat;
		values = vals;
	}

	virtual ~ParameterType() = default;

	virtual ParameterCategory GetParameterCategory() {
		return catergory;
	}
};

/*
struct EnumeratedParameter : ParameterType {
	std::vector<std::string> possible_parameter_values;

	EnumeratedParameter(std::string name, std::string q_name, std::vector<std::string> values)
	: ParameterType(name, q_name) {
		possible_parameter_values = values;
	}

	ParameterCategory GetParameterCategory() override {
		return Enumerated;
	}
};

struct NumericalParameter : ParameterType {
	int lower_bound;
	int upper_bound;

	NumericalParameter(std::string name, std::string q_name, int lower, int upper)
	: ParameterType(name, q_name) {
		lower_bound = lower;
		upper_bound = upper;
	}

	ParameterCategory GetParameterCategory() override {
		return Numerical;
	}
};
*/

struct QueryParameter {
	std::string parameter_name;
	std::string parameter_value;
};

struct BetterQueryParameter {
	std::string query_format;
	std::string query_values;
};

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
	std::vector<std::string> subset_entries;
	QueryParameter sorting_parameter;
};

} // namespace monster_calculator
 